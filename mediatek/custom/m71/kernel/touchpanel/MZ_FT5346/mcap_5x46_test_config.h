char const *ft5x46_test_config_default = "\
[Valid_File]\r\nOnlyMultipleTest=1\r\n[Interface]\r\nIC_Type=FT5X46\r\nInterface_Type=0\r\nSlave_Addr=0x70\r\nFreq_Index=2\r\nPhase_Pola=-1\r\nMax_Points=5\r\niRotationDegree=0\r\nisReversed=0\r\nixMaxPixel=1080\r\niyMaxPixel=1920\r\n[Config]\r\nRun_Mode=0\r\nTest_Way=0\r\nHandle_SN=0\r\nSN_Length=18\r\nSN_AutoTest=1\r\nSKey_Index=0\r\nSKeyValue=13\r\nTP_AutoTest=0\r\nTP_AutoTest_Time=0\r\nTP_ReplaceTP=0\r\nTP_ReplaceTP_Time=0\r\nStore_Result=0\r\nAuto_Switch=0\r\nResult_Type=0\r\nResult_Format=0\r\nResult_Path_Enable=1\r\nResult_OP_Num=0\r\nResult_Use_IcId=0\r\nResult_ReplaceOldLog=1\r\nResult_SaveTestMsg=1\r\nOutput_LevelSignal=0\r\nOutput_NgSignal=0\r\nInput_LevelSignal=0\r\nReverse_Time=0\r\nSwitch_Protocol=0\r\nCLB_Other_Return=0\r\nResult_SimpleDirectory=0\r\n[TestItem]\r\nFW_VERSION_TEST=0\r\nFACTORY_ID_TEST=0\r\nIC_VERSION_TEST=0\r\nPROJECT_CODE_TEST=0\r\nRAWDATA_TEST=1\r\nADC_DETECT_TEST=0\r\nSCAP_CB_TEST=0\r\nSCAP_RAWDATA_TEST=1\r\nCHANNEL_NUM_TEST=0\r\nINT_PIN_TEST=0\r\nRESET_PIN_TEST=0\r\nNOISE_TEST=0\r\nWEAK_SHORT_CIRCUIT_TEST=0\r\nUNIFORMITY_TEST=0\r\nCM_TEST=0\r\nVIRTUAL_BUTTON_TEST=0\r\nDIAGONAL_TEST=0\r\nONELINE_TEST=0\r\nFREEPAINT_TEST=0\r\nLINEARITY_TEST=0\r\nLCM_ID_TEST=0\r\nPANEL_DIFFER_TEST=0\r\nPANEL_DIFFER_UNIFORMITY_TEST=0\r\nRAWDATA_MARGIN_TEST=0\r\nSPECIAL_BUTTON_TEST=0\r\n[Basic_Threshold]\r\nFW_VER_VALUE=24\r\nFactory_ID_Number=81\r\nIC_Version=0\r\nProject_Code=\r\nRawDataTest_Low_Min=7000\r\nRawDataTest_Low_Max=11000\r\nRawDataTest_High_Min=7000\r\nRawDataTest_High_Max=11000\r\nRawDataTest_LowFreq=1\r\nRawDataTest_HighFreq=1\r\nAdc_Detect_Max=50\r\nSCapCbTest_OFF_Min=0\r\nSCapCbTest_OFF_Max=240\r\nSCapCbTest_ON_Min=0\r\nSCapCbTest_ON_Max=240\r\nScapCBTest_SetWaterproof_OFF=1\r\nScapCBTest_SetWaterproof_ON=1\r\nSCapRawDataTest_OFF_Min=3000\r\nSCapRawDataTest_OFF_Max=15000\r\nSCapRawDataTest_ON_Min=3000\r\nSCapRawDataTest_ON_Max=15000\r\nSCapRawDataTest_SetWaterproof_OFF=1\r\nSCapRawDataTest_SetWaterproof_ON=1\r\nChannelNumTest_TxNum=14\r\nChannelNumTest_RxNum=25\r\nChannelNumTest_Tx_NP_Num=13\r\nChannelNumTest_Rx_NP_Num=24\r\nChannelNumTest_Mapping=1\r\nChannelNumTest_NoMapping=0\r\nIntPinTest_RegAddr=8\r\nResetPinTest_RegAddr=136\r\nWeakShortTest_CG=1200\r\nWeakShortTest_CC=1200\r\nUniformityTest_Tx_Hole=20\r\nUniformityTest_Rx_Hole=20\r\nUniformityTest_MinMax_Hole=70\r\nUniformityTest_Check_Tx=1\r\nUniformityTest_Check_Rx=1\r\nUniformityTest_Check_MinMax=1\r\nCMTest_Min_Hole=0.5\r\nCMTest_Max_Hole=5\r\nCMTest_Check_Min=1\r\nCMTest_Check_Max=1\r\nNoiseTest_Max=20\r\nNoiseTest_Frames=15\r\nNoiseTest_Time=1\r\nNoiseTest_SampeMode=0\r\nNoiseTest_NoiseMode=0\r\nNoiseTest_ShowTip=0\r\nDistance_Diagonal=50\r\nType_Diagonal=2\r\nMaxNG_Diagonal=0\r\nLimitTime_Diagonal=0\r\nLinearityCheck_Diagonal=1\r\nSET_TOUCH_THRESHOLD=0\r\nPreserved_key_threshold=800\r\n1_key_threshold=800\r\n2_key_threshold=800\r\n3_key_threshold=800\r\n4_key_threshold=800\r\nLCM_ID=18\r\nRawdataMarginTest_Min=10\r\nRawdataMarginTest_Max=1\r\nKey_Div_Number=1\r\n[INVALID_NODE]\r\nInvalidNode[1][25]=0\r\nInvalidNode[2][25]=0\r\nInvalidNode[3][25]=0\r\nInvalidNode[4][25]=0\r\nInvalidNode[5][25]=0\r\nInvalidNode[6][25]=0\r\nInvalidNode[7][25]=0\r\nInvalidNode[9][25]=0\r\nInvalidNode[10][25]=0\r\nInvalidNode[11][25]=0\r\nInvalidNode[12][25]=0\r\nInvalidNode[13][25]=0\r\nInvalidNode[14][25]=0\r\nInvalidNode[8][25]=2\r\n[SiuParam]\r\nCheck_Siu_Version=0\r\nSiu_MainVersion=0\r\nSiu_SubVersion=0\r\nCheck_Set_IICVol=0\r\nIIC_Vol_Type=0\r\nIIC_Vdd_Type=0\r\nCheck_Iovcc=0\r\nIovcc_Vol_Type=0\r\nIovcc_Current_Type=0\r\nIovcc_Min_Hole=0\r\nIovcc_Max_Hole=50\r\nCheck_Vdd=0\r\nVdd_Vol_Type=0\r\nCheck_Normal=0\r\nCheck_Sleep=0\r\nVdd_Normal_Min=0\r\nVdd_Normal_Max=500\r\nVdd_Sleep_Min=0\r\nVdd_Sleep_Max=150\r\n[SpecialSet]\r\nRawData_Max_Low_Tx1=12854,13105,13001,12905,12817,12738,12664,12586,12513,12469,12437,12401,12380,12996,12958,12929,12917,12909,12908,12930,12922,12933,12923,12649,876,\r\nRawData_Max_Low_Tx2=12894,13168,13057,12957,12874,12793,12720,12640,12560,12523,12482,12448,12408,12961,12919,12895,12878,12866,12849,12859,12842,12845,12829,12572,505,\r\nRawData_Max_Low_Tx3=12931,13213,13105,13001,12923,12840,12763,12682,12604,12565,12520,12486,12440,12896,12857,12836,12815,12798,12777,12780,12759,12758,12738,12492,428,\r\nRawData_Max_Low_Tx4=12969,13248,13136,13039,12957,12877,12796,12716,12635,12597,12548,12517,12475,12832,12794,12770,12749,12731,12714,12716,12698,12696,12678,12429,417,\r\nRawData_Max_Low_Tx5=13004,13280,13160,13062,12976,12896,12818,12737,12656,12621,12570,12541,12495,12749,12724,12700,12678,12664,12646,12650,12635,12633,12612,12363,422,\r\nRawData_Max_Low_Tx6=13028,13293,13168,13069,12979,12896,12821,12744,12665,12629,12576,12541,12500,12663,12642,12619,12602,12581,12551,12556,12542,12545,12518,12272,435,\r\nRawData_Max_Low_Tx7=13029,13281,13157,13050,12962,12877,12798,12724,12649,12607,12556,12517,12478,12558,12538,12516,12497,12461,12408,12412,12398,12399,12374,12167,705,\r\nRawData_Max_Low_Tx8=13034,13279,13151,13043,12957,12864,12786,12713,12632,12593,12544,12500,12461,12455,12436,12416,12394,12362,12324,12325,12313,12313,12296,12160,12175,\r\nRawData_Max_Low_Tx9=13111,13353,13225,13120,13035,12944,12873,12800,12721,12685,12636,12600,12560,12471,12462,12444,12420,12395,12374,12374,12364,12366,12349,12174,2823,\r\nRawData_Max_Low_Tx10=13174,13414,13287,13183,13094,13010,12941,12868,12797,12756,12716,12679,12642,12474,12469,12450,12420,12404,12383,12383,12374,12374,12355,12140,411,\r\nRawData_Max_Low_Tx11=13213,13461,13336,13230,13137,13053,12987,12923,12850,12812,12768,12726,12695,12450,12444,12422,12391,12378,12353,12360,12345,12345,12321,12104,354,\r\nRawData_Max_Low_Tx12=13277,13532,13402,13298,13204,13118,13055,12992,12920,12884,12836,12793,12765,12426,12425,12404,12373,12362,12338,12345,12327,12327,12297,12084,357,\r\nRawData_Max_Low_Tx13=13265,13533,13407,13312,13227,13148,13095,13036,12971,12936,12896,12857,12838,12370,12377,12356,12327,12314,12296,12297,12280,12279,12251,12042,369,\r\nRawData_Max_Low_Tx14=13036,13336,13238,13158,13095,13035,12999,12950,12895,12867,12845,12811,12800,12399,12399,12377,12353,12339,12322,12321,12304,12304,12276,12063,533,\r\nRawData_Min_Low_Tx1=5510,5617,5573,5531,5493,5460,5428,5394,5363,5345,5331,5315,5306,5570,5554,5541,5537,5533,5532,5542,5538,5543,5539,5421,376,\r\nRawData_Min_Low_Tx2=5526,5644,5597,5553,5518,5483,5452,5418,5384,5367,5350,5336,5318,5555,5537,5527,5520,5514,5507,5511,5504,5505,5499,5388,217,\r\nRawData_Min_Low_Tx3=5543,5663,5617,5573,5539,5504,5471,5436,5402,5385,5366,5352,5332,5528,5511,5502,5493,5486,5477,5478,5469,5468,5460,5354,184,\r\nRawData_Min_Low_Tx4=5559,5678,5630,5589,5553,5519,5484,5450,5415,5399,5378,5365,5347,5500,5484,5474,5465,5457,5450,5450,5442,5442,5434,5327,179,\r\nRawData_Min_Low_Tx5=5574,5692,5640,5598,5562,5528,5494,5459,5424,5409,5388,5375,5355,5465,5454,5444,5434,5428,5420,5422,5415,5415,5406,5299,182,\r\nRawData_Min_Low_Tx6=5584,5697,5644,5601,5563,5528,5495,5462,5429,5413,5390,5375,5358,5427,5418,5409,5402,5393,5379,5382,5376,5377,5366,5260,187,\r\nRawData_Min_Low_Tx7=5585,5693,5639,5594,5556,5519,5486,5454,5421,5403,5382,5365,5348,5382,5374,5364,5357,5341,5318,5320,5314,5315,5304,5215,303,\r\nRawData_Min_Low_Tx8=5586,5691,5637,5591,5553,5514,5480,5449,5414,5397,5376,5358,5341,5339,5330,5322,5312,5298,5282,5283,5277,5277,5270,5212,5219,\r\nRawData_Min_Low_Tx9=5619,5723,5669,5624,5587,5548,5517,5486,5453,5437,5416,5400,5384,5345,5342,5334,5324,5313,5304,5304,5300,5300,5293,5218,1211,\r\nRawData_Min_Low_Tx10=5646,5750,5695,5651,5612,5576,5547,5516,5485,5468,5450,5435,5418,5346,5345,5336,5324,5316,5307,5307,5304,5304,5295,5204,177,\r\nRawData_Min_Low_Tx11=5663,5769,5716,5670,5631,5595,5567,5539,5508,5492,5472,5454,5441,5336,5334,5324,5311,5306,5295,5298,5291,5291,5281,5188,152,\r\nRawData_Min_Low_Tx12=5691,5800,5744,5700,5660,5622,5595,5568,5538,5522,5502,5483,5471,5326,5325,5316,5303,5298,5288,5291,5283,5283,5271,5180,153,\r\nRawData_Min_Low_Tx13=5685,5801,5747,5706,5669,5636,5613,5588,5559,5544,5528,5511,5502,5302,5305,5296,5283,5278,5270,5271,5264,5263,5251,5162,159,\r\nRawData_Min_Low_Tx14=5588,5716,5674,5640,5613,5587,5571,5550,5527,5515,5505,5491,5486,5315,5315,5305,5295,5289,5282,5281,5274,5274,5262,5171,229,\r\nRawData_Max_High_Tx1=12885,13139,13035,12943,12850,12775,12696,12619,12555,12509,12475,12437,12418,13031,12989,12968,12955,12948,12950,12973,12971,12973,12957,12685,901,\r\nRawData_Max_High_Tx2=12920,13199,13088,12985,12901,12829,12751,12670,12593,12553,12511,12482,12444,12990,12948,12931,12908,12896,12882,12889,12885,12880,12853,12608,526,\r\nRawData_Max_High_Tx3=12947,13239,13130,13027,12943,12863,12783,12707,12625,12587,12545,12506,12461,12915,12877,12856,12833,12817,12801,12800,12786,12777,12758,12514,446,\r\nRawData_Max_High_Tx4=12989,13270,13155,13057,12973,12901,12818,12727,12651,12611,12566,12535,12489,12850,12811,12782,12763,12747,12726,12731,12714,12710,12693,12444,442,\r\nRawData_Max_High_Tx5=13025,13305,13186,13084,12999,12913,12845,12761,12681,12644,12594,12563,12524,12776,12748,12728,12707,12681,12671,12678,12661,12658,12640,12390,438,\r\nRawData_Max_High_Tx6=13052,13325,13192,13097,13001,12920,12847,12769,12689,12653,12604,12565,12523,12689,12667,12649,12629,12608,12579,12583,12573,12572,12541,12300,450,\r\nRawData_Max_High_Tx7=13062,13315,13182,13077,12990,12903,12832,12755,12675,12637,12584,12548,12506,12590,12563,12546,12527,12489,12436,12441,12426,12427,12405,12202,730,\r\nRawData_Max_High_Tx8=13067,13315,13186,13074,12986,12896,12826,12749,12670,12628,12577,12541,12499,12492,12476,12454,12433,12402,12364,12370,12360,12341,12335,12196,12206,\r\nRawData_Max_High_Tx9=13143,13386,13260,13160,13063,12976,12903,12836,12756,12721,12672,12633,12595,12511,12502,12476,12454,12429,12412,12415,12409,12404,12384,12205,2853,\r\nRawData_Max_High_Tx10=13199,13445,13315,13211,13123,13035,12968,12899,12831,12790,12747,12706,12670,12506,12497,12479,12453,12434,12415,12419,12408,12406,12380,12170,429,\r\nRawData_Max_High_Tx11=13235,13483,13356,13249,13161,13074,13007,12944,12871,12840,12790,12748,12720,12472,12467,12447,12412,12401,12380,12383,12362,12369,12350,12131,378,\r\nRawData_Max_High_Tx12=13305,13556,13420,13318,13230,13143,13077,13013,12947,12913,12863,12814,12794,12451,12455,12434,12402,12392,12369,12369,12350,12353,12339,12117,371,\r\nRawData_Max_High_Tx13=13301,13571,13440,13350,13262,13185,13126,13074,13011,12980,12936,12895,12874,12411,12416,12394,12371,12357,12341,12342,12327,12317,12297,12086,392,\r\nRawData_Max_High_Tx14=13078,13374,13274,13199,13137,13080,13041,12986,12937,12912,12885,12856,12838,12447,12444,12420,12399,12388,12371,12370,12359,12352,12320,12111,557,\r\nRawData_Min_High_Tx1=5523,5631,5587,5547,5508,5475,5442,5409,5381,5361,5347,5331,5322,5585,5567,5558,5553,5550,5550,5561,5559,5561,5553,5437,387,\r\nRawData_Min_High_Tx2=5538,5657,5610,5565,5529,5499,5465,5430,5397,5381,5363,5350,5334,5568,5550,5543,5532,5528,5522,5525,5523,5520,5509,5404,226,\r\nRawData_Min_High_Tx3=5549,5675,5628,5583,5547,5513,5479,5447,5411,5395,5377,5360,5341,5535,5519,5510,5501,5493,5487,5486,5480,5477,5468,5364,192,\r\nRawData_Min_High_Tx4=5567,5688,5639,5597,5561,5529,5494,5455,5423,5405,5386,5373,5353,5508,5491,5478,5471,5463,5454,5457,5450,5448,5441,5334,190,\r\nRawData_Min_High_Tx5=5583,5703,5652,5608,5571,5535,5505,5469,5435,5420,5398,5385,5368,5476,5464,5456,5447,5435,5431,5434,5427,5426,5418,5310,188,\r\nRawData_Min_High_Tx6=5594,5711,5654,5613,5573,5538,5507,5473,5439,5423,5402,5385,5367,5439,5429,5421,5413,5404,5391,5393,5389,5388,5375,5272,194,\r\nRawData_Min_High_Tx7=5598,5707,5650,5605,5568,5531,5500,5467,5433,5417,5394,5378,5360,5396,5385,5378,5369,5353,5330,5333,5326,5327,5317,5230,314,\r\nRawData_Min_High_Tx8=5601,5707,5652,5604,5566,5528,5498,5465,5430,5412,5391,5375,5357,5354,5348,5338,5329,5316,5300,5302,5298,5289,5287,5228,5232,\r\nRawData_Min_High_Tx9=5633,5738,5684,5640,5599,5562,5531,5502,5468,5453,5432,5415,5399,5363,5358,5348,5338,5327,5320,5321,5319,5316,5308,5231,1223,\r\nRawData_Min_High_Tx10=5657,5763,5707,5663,5625,5587,5558,5529,5499,5482,5463,5446,5430,5360,5357,5349,5337,5330,5321,5323,5318,5318,5306,5216,185,\r\nRawData_Min_High_Tx11=5673,5779,5724,5679,5641,5604,5575,5548,5517,5504,5482,5464,5452,5346,5343,5335,5320,5315,5306,5307,5298,5301,5294,5199,162,\r\nRawData_Min_High_Tx12=5703,5810,5752,5708,5670,5633,5605,5577,5549,5535,5513,5492,5484,5337,5339,5330,5316,5312,5301,5301,5294,5295,5289,5193,159,\r\nRawData_Min_High_Tx13=5701,5817,5760,5722,5684,5651,5626,5604,5577,5564,5544,5527,5518,5319,5322,5312,5303,5297,5289,5290,5283,5279,5271,5180,168,\r\nRawData_Min_High_Tx14=5606,5732,5690,5657,5631,5606,5589,5566,5545,5534,5523,5510,5502,5335,5334,5324,5315,5310,5303,5302,5297,5294,5280,5191,239,\r\n\
";