#include "initdata.h"

adi_adrv9025_ApiVersion_t initStructApiVersion = {6, 0, 0, 41};

adi_adrv9025_ArmVersion_t initStructArmVersion = {6, 0, 0, 18};

adi_adrv9025_StreamVersion_t initStructStreamVersion = {9, 0, 0, 5};

adi_adrv9025_Init_t deviceInitStruct = 
{
    { // clocks
        245760,  // deviceClock_kHz
        9830400,  // clkPllVcoFreq_kHz
        0,  // serdesPllVcoFreq_kHz
        0,  // ldoSelect
        0,  // extLoFreq1_kHz
        0,  // extLoFreq2_kHz
        ADI_ADRV9025_INTLO_NOOUTPUT,  // rfPll1LoMode
        ADI_ADRV9025_INTLO_NOOUTPUT,  // rfPll2LoMode
        0,  // rfPll1LoOutDivider
        0,  // rfPll2LoOutDivider
        ADI_ADRV9025_RFPLLMCS_NOSYNC,  // rfPllPhaseSyncMode
        ADI_ADRV9025_LOSEL_LO1,  // rx12LoSelect
        ADI_ADRV9025_LOSEL_LO1,  // rx34LoSelect
        ADI_ADRV9025_LOSEL_LO2,  // tx12LoSelect
        ADI_ADRV9025_LOSEL_LO2,  // tx34LoSelect
        ADI_ADRV9025_ORXLOSEL_TXLO,  // orx12LoSelect
        ADI_ADRV9025_ORXLOSEL_TXLO   // orx34LoSelect
    },
    { // gpInterrupts
        0xFFFFFFFFFFFFFFFF,  // gpIntMaskPin0
        0xFFFFFFFFFFFFFFFF   // gpIntMaskPin1
    },
    { // rx
        0x3FF,  // rxInitChannelMask
        {  // rxChannelCfg (array)
        {  // rxChannelCfg[0]
            { // profile
                ADI_ADRV9025_RX1,  // channelType
                1,  // rxFirDecimation
                1,  // rxDec5Decimation
                2,  // rhb1Decimation
                1,  // rhb1WideBandMode
                2,  // rhb2Decimation
                2,  // rhb3Decimation
                2,  // rxFir1Decimation
                1,  // rxFir2Decimation
                122880,  // rxOutputRate_kHz
                100000,  // rfBandwidth_kHz
                100000,  // rxBbf3dBCorner_kHz
                50000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {-12, 4, -2, -2, 10, -18, 25, -25, 8, 73, -587, 17346, -587, 73, 8, -25, 25, -18, 10, -2, -2, 4, -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_BYPASS,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x01,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[1]
            { // profile
                ADI_ADRV9025_RX2,  // channelType
                1,  // rxFirDecimation
                1,  // rxDec5Decimation
                2,  // rhb1Decimation
                1,  // rhb1WideBandMode
                2,  // rhb2Decimation
                2,  // rhb3Decimation
                2,  // rxFir1Decimation
                1,  // rxFir2Decimation
                122880,  // rxOutputRate_kHz
                100000,  // rfBandwidth_kHz
                100000,  // rxBbf3dBCorner_kHz
                50000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {-12, 4, -2, -2, 10, -18, 25, -25, 8, 73, -587, 17346, -587, 73, 8, -25, 25, -18, 10, -2, -2, 4, -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_BYPASS,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x02,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[2]
            { // profile
                ADI_ADRV9025_RX3,  // channelType
                1,  // rxFirDecimation
                1,  // rxDec5Decimation
                2,  // rhb1Decimation
                1,  // rhb1WideBandMode
                2,  // rhb2Decimation
                2,  // rhb3Decimation
                2,  // rxFir1Decimation
                1,  // rxFir2Decimation
                122880,  // rxOutputRate_kHz
                100000,  // rfBandwidth_kHz
                100000,  // rxBbf3dBCorner_kHz
                50000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {-12, 4, -2, -2, 10, -18, 25, -25, 8, 73, -587, 17346, -587, 73, 8, -25, 25, -18, 10, -2, -2, 4, -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_BYPASS,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x04,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[3]
            { // profile
                ADI_ADRV9025_RX4,  // channelType
                1,  // rxFirDecimation
                1,  // rxDec5Decimation
                2,  // rhb1Decimation
                1,  // rhb1WideBandMode
                2,  // rhb2Decimation
                2,  // rhb3Decimation
                2,  // rxFir1Decimation
                1,  // rxFir2Decimation
                122880,  // rxOutputRate_kHz
                100000,  // rfBandwidth_kHz
                100000,  // rxBbf3dBCorner_kHz
                50000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {-12, 4, -2, -2, 10, -18, 25, -25, 8, 73, -587, 17346, -587, 73, 8, -25, 25, -18, 10, -2, -2, 4, -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_BYPASS,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x08,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[4]
            { // profile
                ADI_ADRV9025_ORX1,  // channelType
                1,  // rxFirDecimation
                5,  // rxDec5Decimation
                2,  // rhb1Decimation
                0,  // rhb1WideBandMode
                1,  // rhb2Decimation
                1,  // rhb3Decimation
                1,  // rxFir1Decimation
                1,  // rxFir2Decimation
                245760,  // rxOutputRate_kHz
                450000,  // rfBandwidth_kHz
                225000,  // rxBbf3dBCorner_kHz
                225000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {33, -7, 9, -7, 3, 9, -27, 62, -138, 349, -1663, 19282, -1663, 349, -138, 62, -27, 9, 3, -7, 9, -7, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_DEC2,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x10,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[5]
            { // profile
                ADI_ADRV9025_ORX2,  // channelType
                1,  // rxFirDecimation
                5,  // rxDec5Decimation
                2,  // rhb1Decimation
                0,  // rhb1WideBandMode
                1,  // rhb2Decimation
                1,  // rhb3Decimation
                1,  // rxFir1Decimation
                1,  // rxFir2Decimation
                245760,  // rxOutputRate_kHz
                450000,  // rfBandwidth_kHz
                225000,  // rxBbf3dBCorner_kHz
                225000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {33, -7, 9, -7, 3, 9, -27, 62, -138, 349, -1663, 19282, -1663, 349, -138, 62, -27, 9, 3, -7, 9, -7, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_DEC2,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x20,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[6]
            { // profile
                ADI_ADRV9025_ORX3,  // channelType
                1,  // rxFirDecimation
                5,  // rxDec5Decimation
                2,  // rhb1Decimation
                0,  // rhb1WideBandMode
                1,  // rhb2Decimation
                1,  // rhb3Decimation
                1,  // rxFir1Decimation
                1,  // rxFir2Decimation
                245760,  // rxOutputRate_kHz
                450000,  // rfBandwidth_kHz
                225000,  // rxBbf3dBCorner_kHz
                225000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {33, -7, 9, -7, 3, 9, -27, 62, -138, 349, -1663, 19282, -1663, 349, -138, 62, -27, 9, 3, -7, 9, -7, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_DEC2,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x40,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[7]
            { // profile
                ADI_ADRV9025_ORX4,  // channelType
                1,  // rxFirDecimation
                5,  // rxDec5Decimation
                2,  // rhb1Decimation
                0,  // rhb1WideBandMode
                1,  // rhb2Decimation
                1,  // rhb3Decimation
                1,  // rxFir1Decimation
                1,  // rxFir2Decimation
                245760,  // rxOutputRate_kHz
                450000,  // rfBandwidth_kHz
                225000,  // rxBbf3dBCorner_kHz
                225000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {33, -7, 9, -7, 3, 9, -27, 62, -138, 349, -1663, 19282, -1663, 349, -138, 62, -27, 9, 3, -7, 9, -7, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_DEC2,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x80,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[8]
            { // profile
                ADI_ADRV9025_LB12,  // channelType
                1,  // rxFirDecimation
                5,  // rxDec5Decimation
                2,  // rhb1Decimation
                0,  // rhb1WideBandMode
                1,  // rhb2Decimation
                1,  // rhb3Decimation
                1,  // rxFir1Decimation
                1,  // rxFir2Decimation
                245760,  // rxOutputRate_kHz
                450000,  // rfBandwidth_kHz
                225000,  // rxBbf3dBCorner_kHz
                225000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {33, -7, 9, -7, 3, 9, -27, 62, -138, 349, -1663, 19282, -1663, 349, -138, 62, -27, 9, 3, -7, 9, -7, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_DEC2,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x100,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        },
        {  // rxChannelCfg[9]
            { // profile
                ADI_ADRV9025_LB34,  // channelType
                1,  // rxFirDecimation
                5,  // rxDec5Decimation
                2,  // rhb1Decimation
                0,  // rhb1WideBandMode
                1,  // rhb2Decimation
                1,  // rhb3Decimation
                1,  // rxFir1Decimation
                1,  // rxFir2Decimation
                245760,  // rxOutputRate_kHz
                450000,  // rfBandwidth_kHz
                225000,  // rxBbf3dBCorner_kHz
                225000,  // rxAdcBandWidth_kHz
                { // rxFir
                    6,  // gain_dB
                    24,  // numFirCoefs
                    {33, -7, 9, -7, 3, 9, -27, 62, -138, 349, -1663, 19282, -1663, 349, -138, 62, -27, 9, 3, -7, 9, -7, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                ADI_ADRV9025_RXDDC_DEC2,  // rxDdcMode
                { // rxNcoShifterCfg
                    0,  // bandAInputBandWidth_kHz
                    0,  // bandAInputCenterFreq_kHz
                    0,  // bandANco1Freq_kHz
                    0,  // bandANco2Freq_kHz
                    0,  // bandBInputBandWidth_kHz
                    0,  // bandBInputCenterFreq_kHz
                    0,  // bandBNco1Freq_kHz
                    0,  // bandBNco2Freq_kHz
                    0   // bandAbCombinedEnable
                },
                4,  // tiaPowerMode
                { // rxDataFormat
                    0x200,  // rxChannelMask
                    ADI_ADRV9025_GAIN_COMPENSATION_DISABLED,  // formatSelect
                    { // floatingPointConfig
                        ADI_ADRV9025_FP_FORMAT_SIGN_EXP_SIGNIFICAND,  // fpDataFormat
                        ADI_ADRV9025_ROUND_TO_EVEN,  // fpRoundMode
                        ADI_ADRV9025_2_EXPONENTBITS,  // fpNumExpBits
                        ADI_ADRV9025_FPATTEN_0DB,  // fpAttenSteps
                        ADI_ADRV9025_FP_FORMAT_HIDE_LEADING_ONE_DISABLE,  // fpHideLeadingOne
                        ADI_ADRV9025_FP_FORMAT_NAN_ENCODE_DISABLE   // fpEncodeNan
                    },
                    { // integerConfigSettings
                        ADI_ADRV9025_NO_EMBEDDED_SLICER_BITS,  // intEmbeddedBits
                        ADI_ADRV9025_INTEGER_16BIT_2SCOMP,  // intSampleResolution
                        ADI_ADRV9025_NO_PARITY,  // intParity
                        ADI_ADRV9025_LOWER_NIBBLE_ON_Q   // intEmbeddedPos
                    },
                    { // slicerConfigSettings
                        ADI_ADRV9025_EXTSLICER_STEPSIZE_1DB,  // extSlicerStepSize
                        ADI_ADRV9025_INTSLICER_STEPSIZE_1DB,  // intSlicerStepSize
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx1ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx2ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE,  // rx3ExtSlicerGpioSelect
                        ADI_ADRV9025_EXTSLICER_RX_GPIO_DISABLE   // rx4ExtSlicerGpioSelect
                    },
                    { // embOvldMonitorSettings
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbQ
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneI
                        ADI_ADRV9025_RX_EMB_MON_SRC_NO_MON_DATA_EMBEDDED,  // embeddedMonitorSrcLsbPlusOneQ
                        ADI_ADRV9025_HB2_LOW_SRC_OVRG_LOW_INT1_THRESH_CNTR_EXCEEDED,  // embeddedMonitorHb2LowSrcSel
                        ADI_ADRV9025_HB2_HIGH_SRC_INVALID,  // embeddedMonitorHb2HighSrcSel
                        ADI_ADRV9025_APD_LOW_SRC_INVALID,  // embeddedMonitorApdLowSrcSel
                        ADI_ADRV9025_APD_HIGH_SRC_INVALID,  // embeddedMonitorApdHighSrcSel
                        0,  // invertHb2Flag
                        0   // invertApdFlag
                    },
                    0,  // externalLnaGain
                    0   // tempCompensationEnable
                },
            },
        }
        }, // rxChannelCfg (end of array)
    },
    { // tx
        0x0F,  // txInitChannelMask
        {  // txChannelCfg (array)
        {  // txChannelCfg[0]
            { // profile
                122880,  // txInputRate_kHz
                100000,  // primarySigBandwidth_kHz
                450000,  // rfBandwidth_kHz
                450000,  // txDac3dBCorner_kHz
                225000,  // txBbf3dBCorner_kHz
                2,  // dpdHb1Interpolation
                2,  // dpdHb2Interpolation
                1,  // txFirInterpolation
                2,  // thb1Interpolation
                1,  // thb2Interpolation
                2,  // thb3Interpolation
                1,  // txInt5Interpolation
                { // txFir
                    6,  // gain_dB
                    20,  // numFirCoefs
                    {-28, 45, -82, 152, -262, 462, -893, 1945, -4588, 22882, -4588, 1945, -893, 462, -262, 152, -82, 45, -28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                8   // txBbfPowerMode
            },
            { // txAttenCtrl
                ADI_ADRV9025_TXATTEN_0P05_DB,  // txAttenStepSize
                63,  // txRampDownEvents
                0,  // reserved
                ADI_ADRV9025_TXATTEN_SPI_MODE,  // attenMode
                ADI_ADRV9025_TX_DACFS_0DB,  // dacFullScale
                10000   // txAttenInit_mdB
            },
            ADI_ADRV9025_TX_DACFS_0DB   // dacFullScale
        },
        {  // txChannelCfg[1]
            { // profile
                122880,  // txInputRate_kHz
                100000,  // primarySigBandwidth_kHz
                450000,  // rfBandwidth_kHz
                450000,  // txDac3dBCorner_kHz
                225000,  // txBbf3dBCorner_kHz
                2,  // dpdHb1Interpolation
                2,  // dpdHb2Interpolation
                1,  // txFirInterpolation
                2,  // thb1Interpolation
                1,  // thb2Interpolation
                2,  // thb3Interpolation
                1,  // txInt5Interpolation
                { // txFir
                    6,  // gain_dB
                    20,  // numFirCoefs
                    {-28, 45, -82, 152, -262, 462, -893, 1945, -4588, 22882, -4588, 1945, -893, 462, -262, 152, -82, 45, -28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                8   // txBbfPowerMode
            },
            { // txAttenCtrl
                ADI_ADRV9025_TXATTEN_0P05_DB,  // txAttenStepSize
                63,  // txRampDownEvents
                0,  // reserved
                ADI_ADRV9025_TXATTEN_SPI_MODE,  // attenMode
                ADI_ADRV9025_TX_DACFS_0DB,  // dacFullScale
                10000   // txAttenInit_mdB
            },
            ADI_ADRV9025_TX_DACFS_0DB   // dacFullScale
        },
        {  // txChannelCfg[2]
            { // profile
                122880,  // txInputRate_kHz
                100000,  // primarySigBandwidth_kHz
                450000,  // rfBandwidth_kHz
                450000,  // txDac3dBCorner_kHz
                225000,  // txBbf3dBCorner_kHz
                2,  // dpdHb1Interpolation
                2,  // dpdHb2Interpolation
                1,  // txFirInterpolation
                2,  // thb1Interpolation
                1,  // thb2Interpolation
                2,  // thb3Interpolation
                1,  // txInt5Interpolation
                { // txFir
                    6,  // gain_dB
                    20,  // numFirCoefs
                    {-28, 45, -82, 152, -262, 462, -893, 1945, -4588, 22882, -4588, 1945, -893, 462, -262, 152, -82, 45, -28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                8   // txBbfPowerMode
            },
            { // txAttenCtrl
                ADI_ADRV9025_TXATTEN_0P05_DB,  // txAttenStepSize
                63,  // txRampDownEvents
                0,  // reserved
                ADI_ADRV9025_TXATTEN_SPI_MODE,  // attenMode
                ADI_ADRV9025_TX_DACFS_0DB,  // dacFullScale
                10000   // txAttenInit_mdB
            },
            ADI_ADRV9025_TX_DACFS_0DB   // dacFullScale
        },
        {  // txChannelCfg[3]
            { // profile
                122880,  // txInputRate_kHz
                100000,  // primarySigBandwidth_kHz
                450000,  // rfBandwidth_kHz
                450000,  // txDac3dBCorner_kHz
                225000,  // txBbf3dBCorner_kHz
                2,  // dpdHb1Interpolation
                2,  // dpdHb2Interpolation
                1,  // txFirInterpolation
                2,  // thb1Interpolation
                1,  // thb2Interpolation
                2,  // thb3Interpolation
                1,  // txInt5Interpolation
                { // txFir
                    6,  // gain_dB
                    20,  // numFirCoefs
                    {-28, 45, -82, 152, -262, 462, -893, 1945, -4588, 22882, -4588, 1945, -893, 462, -262, 152, -82, 45, -28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                },
                8   // txBbfPowerMode
            },
            { // txAttenCtrl
                ADI_ADRV9025_TXATTEN_0P05_DB,  // txAttenStepSize
                63,  // txRampDownEvents
                0,  // reserved
                ADI_ADRV9025_TXATTEN_SPI_MODE,  // attenMode
                ADI_ADRV9025_TX_DACFS_0DB,  // dacFullScale
                10000   // txAttenInit_mdB
            },
            ADI_ADRV9025_TX_DACFS_0DB   // dacFullScale
        }
        }, // txChannelCfg (end of array)
    },
    { // dataInterface
        {  // framer (array)
        {  // framer[0]
            0,  // enableJesd204C
            0,  // bankId
            1,  // deviceId
            0,  // lane0Id
            8,  // jesd204M
            32,  // jesd204K
            4,  // jesd204F
            16,  // jesd204Np
            0,  // jesd204E
            1,  // scramble
            15,  // serializerLanesEnabled
            0,  // lmfcOffset
            0,  // syncbInSelect
            0,  // overSample
            1,  // syncbInLvdsMode
            0,  // syncbInLvdsPnInvert
            { // serializerLaneCrossbar
                0,  // lane0FramerOutSel
                1,  // lane1FramerOutSel
                2,  // lane2FramerOutSel
                3   // lane3FramerOutSel
            },
            { // adcCrossbar
                ADI_ADRV9025_ADC_RX1_I,  // conv0
                ADI_ADRV9025_ADC_RX1_Q,  // conv1
                ADI_ADRV9025_ADC_RX2_I,  // conv2
                ADI_ADRV9025_ADC_RX2_Q,  // conv3
                ADI_ADRV9025_ADC_DUALBAND_RX3_BAND_A_I,  // conv4
                ADI_ADRV9025_ADC_RX3_Q,  // conv5
                ADI_ADRV9025_ADC_DUALBAND_RX4_BAND_A_I,  // conv6
                ADI_ADRV9025_ADC_RX4_Q,  // conv7
                ADI_ADRV9025_ADC_DISABLE,  // conv8
                ADI_ADRV9025_ADC_DISABLE,  // conv9
                ADI_ADRV9025_ADC_DISABLE,  // conv10
                ADI_ADRV9025_ADC_DISABLE,  // conv11
                ADI_ADRV9025_ADC_DISABLE,  // conv12
                ADI_ADRV9025_ADC_DISABLE,  // conv13
                ADI_ADRV9025_ADC_DISABLE,  // conv14
                ADI_ADRV9025_ADC_DISABLE,  // conv15
                ADI_ADRV9025_ADC_DISABLE,  // conv16
                ADI_ADRV9025_ADC_DISABLE,  // conv17
                ADI_ADRV9025_ADC_DISABLE,  // conv18
                ADI_ADRV9025_ADC_DISABLE,  // conv19
                ADI_ADRV9025_ADC_DISABLE,  // conv20
                ADI_ADRV9025_ADC_DISABLE,  // conv21
                ADI_ADRV9025_ADC_DISABLE,  // conv22
                ADI_ADRV9025_ADC_DISABLE   // conv23
            },
            0,  // newSysrefOnRelink
            0,  // sysrefForStartup
            0,  // sysrefNShotEnable
            0,  // sysrefNShotCount
            0   // sysrefIgnoreWhenLinked
        },
        {  // framer[1]
            0,  // enableJesd204C
            0,  // bankId
            1,  // deviceId
            0,  // lane0Id
            2,  // jesd204M
            32,  // jesd204K
            0,  // jesd204F
            16,  // jesd204Np
            0,  // jesd204E
            1,  // scramble
            0,  // serializerLanesEnabled
            0,  // lmfcOffset
            1,  // syncbInSelect
            0,  // overSample
            1,  // syncbInLvdsMode
            0,  // syncbInLvdsPnInvert
            { // serializerLaneCrossbar
                8,  // lane0FramerOutSel
                8,  // lane1FramerOutSel
                8,  // lane2FramerOutSel
                8   // lane3FramerOutSel
            },
            { // adcCrossbar
                ADI_ADRV9025_ADC_ORX1_I,  // conv0
                ADI_ADRV9025_ADC_ORX1_Q,  // conv1
                ADI_ADRV9025_ADC_DISABLE,  // conv2
                ADI_ADRV9025_ADC_DISABLE,  // conv3
                ADI_ADRV9025_ADC_DISABLE,  // conv4
                ADI_ADRV9025_ADC_DISABLE,  // conv5
                ADI_ADRV9025_ADC_DISABLE,  // conv6
                ADI_ADRV9025_ADC_DISABLE,  // conv7
                ADI_ADRV9025_ADC_DISABLE,  // conv8
                ADI_ADRV9025_ADC_DISABLE,  // conv9
                ADI_ADRV9025_ADC_DISABLE,  // conv10
                ADI_ADRV9025_ADC_DISABLE,  // conv11
                ADI_ADRV9025_ADC_DISABLE,  // conv12
                ADI_ADRV9025_ADC_DISABLE,  // conv13
                ADI_ADRV9025_ADC_DISABLE,  // conv14
                ADI_ADRV9025_ADC_DISABLE,  // conv15
                ADI_ADRV9025_ADC_DISABLE,  // conv16
                ADI_ADRV9025_ADC_DISABLE,  // conv17
                ADI_ADRV9025_ADC_DISABLE,  // conv18
                ADI_ADRV9025_ADC_DISABLE,  // conv19
                ADI_ADRV9025_ADC_DISABLE,  // conv20
                ADI_ADRV9025_ADC_DISABLE,  // conv21
                ADI_ADRV9025_ADC_DISABLE,  // conv22
                ADI_ADRV9025_ADC_DISABLE   // conv23
            },
            0,  // newSysrefOnRelink
            0,  // sysrefForStartup
            0,  // sysrefNShotEnable
            0,  // sysrefNShotCount
            0   // sysrefIgnoreWhenLinked
        },
        {  // framer[2]
            0,  // enableJesd204C
            0,  // bankId
            1,  // deviceId
            0,  // lane0Id
            0,  // jesd204M
            1,  // jesd204K
            0,  // jesd204F
            16,  // jesd204Np
            0,  // jesd204E
            1,  // scramble
            0,  // serializerLanesEnabled
            0,  // lmfcOffset
            2,  // syncbInSelect
            0,  // overSample
            1,  // syncbInLvdsMode
            0,  // syncbInLvdsPnInvert
            { // serializerLaneCrossbar
                0,  // lane0FramerOutSel
                0,  // lane1FramerOutSel
                0,  // lane2FramerOutSel
                0   // lane3FramerOutSel
            },
            { // adcCrossbar
                ADI_ADRV9025_ADC_DISABLE,  // conv0
                ADI_ADRV9025_ADC_DISABLE,  // conv1
                ADI_ADRV9025_ADC_DISABLE,  // conv2
                ADI_ADRV9025_ADC_DISABLE,  // conv3
                ADI_ADRV9025_ADC_DISABLE,  // conv4
                ADI_ADRV9025_ADC_DISABLE,  // conv5
                ADI_ADRV9025_ADC_DISABLE,  // conv6
                ADI_ADRV9025_ADC_DISABLE,  // conv7
                ADI_ADRV9025_ADC_DISABLE,  // conv8
                ADI_ADRV9025_ADC_DISABLE,  // conv9
                ADI_ADRV9025_ADC_DISABLE,  // conv10
                ADI_ADRV9025_ADC_DISABLE,  // conv11
                ADI_ADRV9025_ADC_DISABLE,  // conv12
                ADI_ADRV9025_ADC_DISABLE,  // conv13
                ADI_ADRV9025_ADC_DISABLE,  // conv14
                ADI_ADRV9025_ADC_DISABLE,  // conv15
                ADI_ADRV9025_ADC_DISABLE,  // conv16
                ADI_ADRV9025_ADC_DISABLE,  // conv17
                ADI_ADRV9025_ADC_DISABLE,  // conv18
                ADI_ADRV9025_ADC_DISABLE,  // conv19
                ADI_ADRV9025_ADC_DISABLE,  // conv20
                ADI_ADRV9025_ADC_DISABLE,  // conv21
                ADI_ADRV9025_ADC_DISABLE,  // conv22
                ADI_ADRV9025_ADC_DISABLE   // conv23
            },
            0,  // newSysrefOnRelink
            0,  // sysrefForStartup
            0,  // sysrefNShotEnable
            0,  // sysrefNShotCount
            0   // sysrefIgnoreWhenLinked
        }
        }, // framer (end of array)
        {  // deframer (array)
        {  // deframer[0]
            0,  // enableJesd204C
            0,  // bankId
            1,  // deviceId
            0,  // lane0Id
            8,  // jesd204M
            32,  // jesd204K
            4,  // jesd204F
            16,  // jesd204Np
            0,  // jesd204E
            1,  // scramble
            15,  // deserializerLanesEnabled
            0,  // lmfcOffset
            0,  // syncbOutSelect
            1,  // syncbOutLvdsMode
            0,  // syncbOutLvdsPnInvert
            0,  // syncbOutCmosSlewRate
            0,  // syncbOutCmosDriveLevel
            { // deserializerLaneCrossbar
                0,  // deframerInput0LaneSel
                1,  // deframerInput1LaneSel
                2,  // deframerInput2LaneSel
                3   // deframerInput3LaneSel
            },
            { // dacCrossbar
                ADI_ADRV9025_DEFRAMER_OUT0,  // tx1DacChanI
                ADI_ADRV9025_DEFRAMER_OUT1,  // tx1DacChanQ
                ADI_ADRV9025_DEFRAMER_OUT2,  // tx2DacChanI
                ADI_ADRV9025_DEFRAMER_OUT3,  // tx2DacChanQ
                ADI_ADRV9025_DEFRAMER_OUT4,  // tx3DacChanI
                ADI_ADRV9025_DEFRAMER_OUT5,  // tx3DacChanQ
                ADI_ADRV9025_DEFRAMER_OUT6,  // tx4DacChanI
                ADI_ADRV9025_DEFRAMER_OUT7   // tx4DacChanQ
            },
            0,  // newSysrefOnRelink
            1,  // sysrefForStartup
            0,  // sysrefNShotEnable
            0,  // sysrefNShotCount
            0   // sysrefIgnoreWhenLinked
        },
        {  // deframer[1]
            0,  // enableJesd204C
            0,  // bankId
            0,  // deviceId
            0,  // lane0Id
            0,  // jesd204M
            0,  // jesd204K
            0,  // jesd204F
            0,  // jesd204Np
            0,  // jesd204E
            0,  // scramble
            0,  // deserializerLanesEnabled
            0,  // lmfcOffset
            0,  // syncbOutSelect
            0,  // syncbOutLvdsMode
            0,  // syncbOutLvdsPnInvert
            0,  // syncbOutCmosSlewRate
            0,  // syncbOutCmosDriveLevel
            { // deserializerLaneCrossbar
                8,  // deframerInput0LaneSel
                8,  // deframerInput1LaneSel
                8,  // deframerInput2LaneSel
                8   // deframerInput3LaneSel
            },
            { // dacCrossbar
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx1DacChanI
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx1DacChanQ
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx2DacChanI
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx2DacChanQ
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx3DacChanI
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx3DacChanQ
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE,  // tx4DacChanI
                ADI_ADRV9025_DEFRAMER_OUT_DISABLE   // tx4DacChanQ
            },
            0,  // newSysrefOnRelink
            1,  // sysrefForStartup
            0,  // sysrefNShotEnable
            0,  // sysrefNShotCount
            0   // sysrefIgnoreWhenLinked
        }
        }, // deframer (end of array)
        {  // serCfg (array)
        {  // serCfg[0]
            0,  // serAmplitude
            1,  // serPreEmphasis
            3,  // serPostEmphasis
            0   // serInvertLanePolarity
        },
        {  // serCfg[1]
            0,  // serAmplitude
            1,  // serPreEmphasis
            3,  // serPostEmphasis
            0   // serInvertLanePolarity
        },
        {  // serCfg[2]
            0,  // serAmplitude
            1,  // serPreEmphasis
            3,  // serPostEmphasis
            0   // serInvertLanePolarity
        },
        {  // serCfg[3]
            0,  // serAmplitude
            1,  // serPreEmphasis
            3,  // serPostEmphasis
            0   // serInvertLanePolarity
        }
        }, // serCfg (end of array)
        {  // desCfg (array)
        {  // desCfg[0]
            0,  // desInvertLanePolarity
            0,  // highBoost
            0,  // configOption1
            0,  // configOption2
            0,  // configOption3
            0,  // configOption4
            0,  // configOption5
            0,  // configOption6
            0,  // configOption7
            0,  // configOption8
            0,  // configOption9
            0   // configOption10
        },
        {  // desCfg[1]
            0,  // desInvertLanePolarity
            0,  // highBoost
            0,  // configOption1
            0,  // configOption2
            0,  // configOption3
            0,  // configOption4
            0,  // configOption5
            0,  // configOption6
            0,  // configOption7
            0,  // configOption8
            0,  // configOption9
            0   // configOption10
        },
        {  // desCfg[2]
            0,  // desInvertLanePolarity
            0,  // highBoost
            0,  // configOption1
            0,  // configOption2
            0,  // configOption3
            0,  // configOption4
            0,  // configOption5
            0,  // configOption6
            0,  // configOption7
            0,  // configOption8
            0,  // configOption9
            0   // configOption10
        },
        {  // desCfg[3]
            0,  // desInvertLanePolarity
            0,  // highBoost
            0,  // configOption1
            0,  // configOption2
            0,  // configOption3
            0,  // configOption4
            0,  // configOption5
            0,  // configOption6
            0,  // configOption7
            0,  // configOption8
            0,  // configOption9
            0   // configOption10
        }
        }, // desCfg (end of array)
        { // linkSharingCfg
            0,  // linkSharingEnabled
            0,  // linkSharingM
            0,  // linkSharingS
            0,  // linkSharingNp
            { // linkSharingAdcCrossbar
                ADI_ADRV9025_ADC_DISABLE,  // conv0
                ADI_ADRV9025_ADC_DISABLE,  // conv1
                ADI_ADRV9025_ADC_DISABLE,  // conv2
                ADI_ADRV9025_ADC_DISABLE,  // conv3
                ADI_ADRV9025_ADC_DISABLE,  // conv4
                ADI_ADRV9025_ADC_DISABLE,  // conv5
                ADI_ADRV9025_ADC_DISABLE,  // conv6
                ADI_ADRV9025_ADC_DISABLE,  // conv7
                ADI_ADRV9025_ADC_DISABLE,  // conv8
                ADI_ADRV9025_ADC_DISABLE,  // conv9
                ADI_ADRV9025_ADC_DISABLE,  // conv10
                ADI_ADRV9025_ADC_DISABLE,  // conv11
                ADI_ADRV9025_ADC_DISABLE,  // conv12
                ADI_ADRV9025_ADC_DISABLE,  // conv13
                ADI_ADRV9025_ADC_DISABLE,  // conv14
                ADI_ADRV9025_ADC_DISABLE   // conv15
            },
        },
        { // dataCfg
            0,  // enable
            0,  // configOption1
            0   // configOption2
        },
        0,  // channelSelect
        0   // channelMode
    },
    { // adcProfiles
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        0,  // OrxChannel1Index
        0   // OrxChannel2Index
    },
};


adi_adrv9025_PostMcsInit_t adrv9025PostMcsInitInst = 
{
    { // radioCtrlInit
        { // radioCtrlModeCfg
            { // txRadioCtrlModeCfg
                ADI_ADRV9025_TX_EN_SPI_MODE,  // txEnableMode
                0x0F   // txChannelMask
            },
            { // rxRadioCtrlModeCfg
                ADI_ADRV9025_RX_EN_SPI_MODE,  // rxEnableMode
                0xFF   // rxChannelMask
            },
            { // orxRadioCtrlModeCfg
                ADI_ADRV9025_ORX_EN_SPI_MODE,  // orxEnableMode
                0,  // orxPinSelectSettlingDelay_armClkCycles
                ADI_ADRV9025_SINGLE_CH_PIN_MODE_ORX1_FE,  // singleChannel1PinModeOrxSel
                ADI_ADRV9025_SINGLE_CH_PIN_MODE_ORX1_FE,  // singleChannel2PinModeLowOrxSel
                ADI_ADRV9025_SINGLE_CH_PIN_MODE_ORX1_FE,  // singleChannel2PinModeHighOrxSel
                ADI_ADRV9025_DUAL_CH_PIN_MODE_ORX1_ORX3_SEL   // dualChannel2PinModeOrxSel
            },
        },
        { // txToOrxMapping
            ADI_ADRV9025_MAP_TX1_ORX1,  // orx1Map
            ADI_ADRV9025_MAP_TX2_ORX2,  // orx2Map
            ADI_ADRV9025_MAP_TX3_ORX3,  // orx3Map
            ADI_ADRV9025_MAP_TX4_ORX4   // orx4Map
        },
        { // streamGpioCfg
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput0
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput1
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput2
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput3
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput4
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput5
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput6
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput7
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput8
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput9
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput10
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput11
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput12
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput13
            ADI_ADRV9025_GPIO_INVALID,  // streamGpInput14
            ADI_ADRV9025_GPIO_INVALID   // streamGpInput15
        },
        3500000000U,  // lo1PllFreq_Hz
        3550000000U,  // lo2PllFreq_Hz
        0U   // auxPllFreq_Hz
    },
    { // initCals
        0xD27FF,  // calMask
        0x0F,  // channelMask
        0   // warmBoot
    },
    { // calRsltsFile
    },
    0   // checkFwVer
};
