/*
 * IC drv2605
 * input mode:RTP (Real-Time Playback)
 * output mode:LRA (Linear Resonance Actuator)
 * Rated Voltage: Rated Voltage[7:0]
 * overdrive clamp voltage: ODClamp[7:0]
 *
 * Vavg = Rated Voltage[7:0]*5.44/255 = 3v
 * Vavg = 0.91Vpeak
 * Vpeak = ODClamp[7:0]*5.44/255
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/hwmon.h>
#include <linux/hwmon-sysfs.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/earlysuspend.h>
#include <linux/pm.h>
#include <linux/delay.h>

#include <mach/eint.h>
#include <mach/mt_gpio.h>

#include "cust_eint.h"
#include "cust_gpio_usage.h"

#define MOTOR_NAME	"drv2605"
#define MOTOR_I2C_ADDRESS	0x5a
#define MOTOR_I2C_BUS_NUM	3

// auto calibration success
#define OK (0)
// drv2605 state
#define STANDBY (1<<6)
#define READY   (~(1<<6))
#define DEV_RESET (1<<7)
#define BIT0    (1<<0)
#define BIT3    (1<<3)
#define BIT6    (1<<6)
#define BIT7    (1<<7)
#define DATAFORMAT_BIT BIT3

// drv2605 register
// mode register
#define REG_STATUS (0x00)
#define REG_INPUT_MODE (0x01)
#define REG_RTP  (0x02)
#define REG_WAWEFORM_LIB (0x03)
#define REG_WAWEFORM0 (0x04)
#define REG_WAWEFORM1 (0x05)
#define REG_WAWEFORM2 (0x06)
#define REG_WAWEFORM3 (0x07)
#define REG_WAWEFORM4 (0x08)
#define REG_WAWEFORM5 (0x09)
#define REG_WAWEFORM6 (0x0a)
#define REG_WAWEFORM7 (0x0b)
#define REG_GO   (0x0c)
#define REG_RATED_VOLTAGE   (0x16) //
#define REG_OVERDRIVE_CLAMP (0x17)
#define REG_FEEDBACK_CONTROL (0x1a) // bit7 ERM or LRA mode 0:ERM mode 1:LRA mode
#define REG_CONTROL1  (0x1b) //
#define REG_CONTROL2  (0x1c) // bit7 output direction  0:uni-directional 1:bi-directional
#define REG_CONTROL3  (0x1d) // bit3 dataFormat_RTP    0:singned         1:unsigned
// the scale of the output voltage
#define RATIO_00 (0x00)
#define RATIO_50 (0x7f)
#define RATIO_75 (0xbf)
#define RATIO_100 (0xff)
// drv2605 input mode
#define AUTO_CALIBRATION (0x07)
#define RTP_MODE         (0x05)
// drv2605 output mode
#define ERM_MODE (~BIT7)
#define LRA_MODE BIT7

#define CHECK_IN  (1)
#define CHECK_OUT (0)
#define WAIT_TIMES (20)
#define CAL_FLAG BIT3
#define CAL_PASS (0)
#define CAL_FAIL (1)

/*
 * Enable pin:
 * 1: active
 * 0: the device enters a state that is equivalent to the low-power STANDBY state
 */
#ifdef GPIO_MOTOR_ON_PIN
#define GPIO_MOTOR_EN_PIN				GPIO_MOTOR_ON_PIN
#define GPIO_MOTOR_EN_PIN_M_GPIO	GPIO_MOTOR_ON_PIN_M_GPIO
#endif

typedef enum {
	THREE_VOLT = 0,
	FOUR_VOLT,
	FIVE_VOLT,
	MAX_VOLT
} VOLTAGE;

static unsigned char vol_output[MAX_VOLT] = {
	0x8c,  // output voltage 3v
	0x9a,  // output voltage 3.2v
};

static unsigned char check_status = CHECK_OUT;
static struct i2c_client *sClient = NULL;

static unsigned char motor_read_byte(unsigned char cmd)
{
	unsigned char cmd_buf = 0;
	unsigned char readData = 0;
	int ret = 0;

	cmd_buf = cmd;

	if(!sClient) {
		printk(KERN_ERR "[motor] %s: i2c_client is NULL!\n", __func__);
		return -1;
	}
	else {
		sClient->addr = (sClient->addr & I2C_MASK_FLAG) | I2C_WR_FLAG |I2C_RS_FLAG;
		ret = i2c_master_send(sClient, &cmd_buf, (1<<8 | 1));
		if (ret < 0) {
			printk(KERN_ERR "[motor] %s: read data error!\n", __func__);
			return ret;
		}
	}

	readData = cmd_buf;
	sClient->addr = sClient->addr & I2C_MASK_FLAG;

	return readData;
}

static int motor_write_byte(unsigned char cmd, unsigned char writeData)
{
	char write_data[2] = {0};
	int ret = 0;

	if(!sClient) {
		printk("[motor][%s] i2c_client is NULL\n",__func__);
		return -1;
	}
	else {
		write_data[0] = cmd;
		write_data[1] = writeData;
		ret = i2c_master_send(sClient, write_data, 2);
		if (ret < 0) {
			printk(KERN_ERR "[motor] %s send command error!!\n",__func__);
			return ret;
		}
	}

	return 0;
}

static void gpio_hw_init(void)
{
	mt_set_gpio_mode(GPIO_MOTOR_ON_PIN, GPIO_MOTOR_ON_PIN_M_GPIO);
	mt_set_gpio_dir(GPIO_MOTOR_ON_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_MOTOR_ON_PIN, GPIO_OUT_ONE);
}

static void get_motor_standby(void)
{
	// clear RTP strength
	motor_write_byte(REG_RTP, 0x00); //set RTP strength to 0
	mt_set_gpio_out(GPIO_MOTOR_ON_PIN,GPIO_OUT_ZERO);
}

static void get_motor_ready(void)
{
	mt_set_gpio_out(GPIO_MOTOR_ON_PIN,GPIO_OUT_ONE);

	// set back RTP strength to full scale, and set drv2605 to work in RTP mode
	motor_write_byte(REG_RTP, 0xff); //set RTP strength to full scale
	motor_write_byte(REG_INPUT_MODE, RTP_MODE);
	usleep_range(1000, 2000); //delay at least 1ms
}

static void set_go_bit(void)
{
	// write value 0x01 to 0x0c register
	motor_write_byte(REG_GO, 0x01);
}
static void set_rated_voltage(VOLTAGE rated_voltage)
{
	// 3v by default,rated voltage[7:0]==0x8c
	VOLTAGE vol = 0;
	if( rated_voltage>=MAX_VOLT ) {
		vol = THREE_VOLT;
	} else {
		vol = rated_voltage;
	}
	motor_write_byte(REG_RATED_VOLTAGE, vol_output[vol]);
}
static void set_overdrive_clamp(VOLTAGE vol)
{
	// if rated voltage == 3v,then overdrive clamp voltage == 3.2v
	motor_write_byte(REG_OVERDRIVE_CLAMP, vol_output[vol]);
}
static void set_auto_cali_mode(void)
{
	// EMR: feedback control register,default value 0x24
	// LRA:                                         0xa4
	motor_write_byte(REG_INPUT_MODE, AUTO_CALIBRATION);
	motor_write_byte(REG_FEEDBACK_CONTROL, 0xa4);
}

static void check_calibration_result(void)
{
	unsigned char data = 0,i = 0;

	do {
		data = motor_read_byte(REG_GO);
	}
	while(((data&BIT0)!=OK) && (i++<0xff));
	if(i == 0xff)
		printk("[motor] %s is not likely to complete the calibtation\n",__func__);

	data = motor_read_byte(REG_STATUS);
	if((data&BIT3) != OK)
		printk("[motor] %s auto calibration error\n",__func__);
}

static void auto_calibration_procedure(void)
{
	// fill it later
	// EMR
	set_rated_voltage(THREE_VOLT);
	set_overdrive_clamp(FOUR_VOLT);
	set_auto_cali_mode();
	set_go_bit();
	check_calibration_result();
}

static void set_closed_loop_mode(void)
{
	//this is the default mode, do nothing
}
static void set_bi_directional_mode(void)
{
	//this is the default mode, do nothing
}

static void set_realtime_playback(void)
{
	motor_write_byte(REG_INPUT_MODE, RTP_MODE);
}

static void set_rtp_dataformat(void)
{
	// set dataFormat_bit to value 1
	// unsigned data
	unsigned char data = 0;
	data = motor_read_byte(REG_CONTROL3);
	data |= DATAFORMAT_BIT;
	motor_write_byte(REG_CONTROL3, data);
}

static void set_vibration_intensity(unsigned char strength)
{
	// set default value to 75%
	// write RTP register to value 0xbf
	motor_write_byte(REG_RTP, strength);
}

static void set_rtp_mode(void)
{
	set_realtime_playback();
	set_rtp_dataformat(); // unsigned data

	set_vibration_intensity(RATIO_75); // 75% default
}

static void check_dev_id(void)
{
	unsigned char data = 0;
//	get_motor_ready();
	data = motor_read_byte(REG_STATUS);
	switch( data&0xe0 ) {
		case 0x80:
			check_status = CHECK_IN;
			printk("[motor] %s: this is DRV2604\n",__func__);
			break;
		case 0x60:
			check_status = CHECK_IN;
			printk("[motor] %s: this is DRV2605\n",__func__);
			break;
		case 0xc0:
			check_status = CHECK_IN;
			printk("[motor] %s: this is DRV2604L\n",__func__);
			break;
		default:
			check_status = CHECK_OUT;
			printk("[motor] %s: not identify id:0x%x\n",__func__,data&0xe0);
	}
//	get_motor_standby();
}

/* the function is not invoked */
static void get_motor_init(void)
{
	// EMR
	// closed loop,bi-directional mode

	get_motor_ready();
	auto_calibration_procedure();
	set_closed_loop_mode();
	set_bi_directional_mode();
	set_rtp_mode();

	get_motor_standby();
}

static int I2C_SetBit(U8 Reg, U8 Mask, U8 Val)
{
	U8 RegValue = motor_read_byte(Reg);
	if((RegValue&Mask)==Val)
		return 0;
	else{
		RegValue = (RegValue&~Mask)|Val;
		return motor_write_byte(Reg, RegValue);
	}
}

void drv2605_motor_hw_init(void)
{
	int i=0;

	printk("[motor] %s: enter\n", __func__);

	/* set drv2605 to work in RTP mode */
	motor_write_byte(REG_INPUT_MODE, RTP_MODE);

	I2C_SetBit(REG_INPUT_MODE, 0x40, 0x00);	//wakeup device
	usleep_range(1000, 2000); //wait at least 1ms for device ready
	check_dev_id();	//check device ID

	motor_write_byte(REG_RATED_VOLTAGE, 0x4f);
	motor_write_byte(REG_OVERDRIVE_CLAMP, 0x81);
	I2C_SetBit(REG_FEEDBACK_CONTROL, 0x80, 0x80);	//set LRA actuator
	I2C_SetBit(REG_CONTROL2, 0x80, 0x00);		//set Uni-Directional
	I2C_SetBit(REG_CONTROL3, 0x09, 0x08);		//set LRA close loop, and DataFormat_RTP to unsigned

	motor_write_byte(REG_INPUT_MODE, 0x07);	//start Calibration
	while(((motor_read_byte(REG_GO)&0x01)==0x01)&&(++i<WAIT_TIMES));	//polling GO bit, until GO bit self-cleared

	if(i == WAIT_TIMES) {
		printk("[%s] Calibration time out,may be failed\n", __func__);
	} else {
		printk("[%s] Calibration wait times:%d\n", __func__, i);
	}

	//calibration done
	if( (motor_read_byte(REG_STATUS)&CAL_FLAG)==CAL_PASS ) {		//check Diag_Result BIT for calibration success or failure
		printk("[%s] auto calibration success\n",__func__);
	} else {
		printk("[%s] auto calibration failed\n",__func__);
	}

	//motor_write_byte(REG_RTP, 0xff);	  //set RTP strength to full scale
	//motor_write_byte(REG_INPUT_MODE, 0x05); //wakeup device, and set DRV2605 to work in RTP mode

	I2C_SetBit(REG_INPUT_MODE, 0x40, 0x40);	//suspend device
	get_motor_standby();

	printk("[%s]  exit \n", __func__);
}

void motor_enable(void)
{
	if( check_status==CHECK_IN ) {
		get_motor_ready();
	}
}
void motor_disable(void)
{
	if( check_status==CHECK_IN ) {
		get_motor_standby();
	}
}

int motor_set_vibration(unsigned char value)
{
	motor_write_byte(REG_RTP, value);
	return 0;
}


#ifdef CONFIG_PM
static int motor_suspend(struct device *dev){
	// option 1:
	// set the 0x01 register's STANDBY bit to 1
	// to take the device into the standby mode
	// option 2:
	// de-assert the IC'S EN pin
	// the options above will achieve the same effect
	get_motor_standby();
	return 0;
}

static int motor_resume(struct device *dev)
{
	// step1:
	// assert the IC'S EN pin
	// step 2:
	// set the 0x01 register's STANDBY bit to value 0
	// to take the device out of the standby mode
	//get_motor_ready();
	return 0;
}

static const struct dev_pm_ops motor_pm_ops= {
	.suspend = motor_suspend,
	.resume  = motor_resume,
};
#endif

static int motor_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		printk(KERN_ERR "[motor] %s: I2c function error\n", __func__);
		return -ENOSYS;
	}
	sClient = client;
	gpio_hw_init();
	usleep_range(1000, 2000); //delay at least 1ms
	drv2605_motor_hw_init();

	printk("[motor] %s: success!", __func__);
	return 0;
}

static int motor_i2c_remove(struct i2c_client *client)
{
	return 0;
}

static struct i2c_device_id motor_i2c_dev_id[] = {
	{MOTOR_NAME, 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, motor_i2c_dev_id);

static struct i2c_board_info motor_board_info[] = {
	{
		I2C_BOARD_INFO("drv2605", MOTOR_I2C_ADDRESS),
	},
};

static struct i2c_driver motor_i2c_driver = {
	.driver = {
		.name = MOTOR_NAME,
		.owner = THIS_MODULE,
#ifdef CONFIG_PM
		.pm = &motor_pm_ops,
#endif
	},
	.probe = motor_i2c_probe,
	.remove = motor_i2c_remove,
	.id_table = motor_i2c_dev_id,
};

static int __init motor_init(void)
{
	/* register motor i2c device */
	i2c_register_board_info(MOTOR_I2C_BUS_NUM, motor_board_info, 1);

	/* register motor i2c driver */
	return i2c_add_driver(&motor_i2c_driver);
}

static void __exit motor_exit(void)
{
	i2c_del_driver(&motor_i2c_driver);
}

module_init(motor_init);
module_exit(motor_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TI DRV2605 motor I2C driver");
MODULE_AUTHOR("bsp@meizu.com");
