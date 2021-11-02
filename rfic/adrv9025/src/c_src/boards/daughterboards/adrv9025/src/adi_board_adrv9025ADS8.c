/**
 * \file adi_board_adrv9025ADS8.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_board_adrv9025ADS8.h"
#include "adi_adrv9025_daughter_board.h"
#include "adi_ad9528.h"
#include "adi_ad9528_utilities.h"
#include "adi_fpga9010_utilities.h"
#include "adi_fpga9010_jesd.h"
#include "adi_fpga9010_clk.h"
#include "adi_adrv9025_gpio.h"
#include "adi_adrv9025_utilities.h"
#include "adi_adrv9025_hal.h"
#include "adi_adrv9025_data_interface.h"
#include "adi_adrv9025_cals.h"
#include "adi_fpga9010.h"
#include "adi_fpga9010_axi_adv_spi.h"
#include "adi_fmc_eeprom.h"
#include <stdlib.h>
#include <string.h>

static int32_t adi_board_RxLinkSamplingRateFind(adi_fpga9010_Device_t*   device,
                                                adi_adrv9025_Init_t*     adrv9025Init,
                                                adi_adrv9025_FramerSel_e framerSel,
                                                uint32_t*                iqRate_kHz)
{
    int32_t                         recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    adi_adrv9025_AdcSampleXbarSel_e conv           = ADI_ADRV9025_ADC_RX1_Q;
    uint32_t                        framerIndex    = 0;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);
    ADI_NULL_PTR_RETURN(&device->common,
                        iqRate_kHz);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);

    switch (framerSel)
    {
    case ADI_ADRV9025_FRAMER_0:
        framerIndex = 0;
        break;
    case ADI_ADRV9025_FRAMER_1:
        framerIndex = 1;
        break;
    case ADI_ADRV9025_FRAMER_2:
        framerIndex = 2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSel,
                         "Only one framer can be selected at a time.");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    if (adrv9025Init->dataInterface.framer[framerIndex].jesd204M < 1)
    {
        *iqRate_kHz = 0;
        return recoveryAction;
    }

    conv = adrv9025Init->dataInterface.framer[framerIndex].adcCrossbar.conv0;

    switch (conv)
    {
    case ADI_ADRV9025_ADC_RX1_I:                 /* fall through */
    case ADI_ADRV9025_ADC_RX1_Q:                 /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX1_BAND_B_I: /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX1_BAND_B_Q: /* fall through */
        *iqRate_kHz = adrv9025Init->rx.rxChannelCfg[0].profile.rxOutputRate_kHz;
        break;

    case ADI_ADRV9025_ADC_RX2_I:                 /* fall through */
    case ADI_ADRV9025_ADC_RX2_Q:                 /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX2_BAND_B_I: /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX2_BAND_B_Q: /* fall through */
        *iqRate_kHz = adrv9025Init->rx.rxChannelCfg[1].profile.rxOutputRate_kHz;
        break;

    case ADI_ADRV9025_ADC_RX3_I:                 /* fall through */
    case ADI_ADRV9025_ADC_RX3_Q:                 /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX3_BAND_B_I: /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX3_BAND_B_Q: /* fall through */
        *iqRate_kHz = adrv9025Init->rx.rxChannelCfg[2].profile.rxOutputRate_kHz;
        break;

    case ADI_ADRV9025_ADC_RX4_I:                 /* fall through */
    case ADI_ADRV9025_ADC_RX4_Q:                 /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX4_BAND_B_I: /* fall through */
    case ADI_ADRV9025_ADC_DUALBAND_RX4_BAND_B_Q: /* fall through */
        *iqRate_kHz = adrv9025Init->rx.rxChannelCfg[3].profile.rxOutputRate_kHz;
        break;

        // NOTE: ORx2/4 profiles never referenced, ORx2IQ enum below refers to digital channel not RF input
        // RF ORx1/2 share digital ORX1, and RF ORX3/4 share digital ORX2
    case ADI_ADRV9025_ADC_ORX1_I: /* fall through */
    case ADI_ADRV9025_ADC_ORX1_Q: /* fall through */
        *iqRate_kHz = adrv9025Init->rx.rxChannelCfg[4].profile.rxOutputRate_kHz;
        break;

        // NOTE: ORx2/4 profiles never referenced, ORx2IQ enum below refers to digital channel not RF input
        // RF ORx1/2 share digital ORX1, and RF ORX3/4 share digital ORX2
    case ADI_ADRV9025_ADC_ORX2_I: /* fall through */
    case ADI_ADRV9025_ADC_ORX2_Q: /* fall through */
        *iqRate_kHz = adrv9025Init->rx.rxChannelCfg[6].profile.rxOutputRate_kHz;
        break;

    default:
        *iqRate_kHz = 0;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         adcCrossbar.conv0,
                         "Invalid ADC crossbar used to read iqRate_kHz");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

static int32_t adi_board_TxLinkSamplingRateFind(adi_fpga9010_Device_t*     device,
                                                adi_adrv9025_Init_t*       adrv9025Init,
                                                adi_adrv9025_DeframerSel_e deframerSel,
                                                uint32_t*                  iqRate_kHz)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t deframerIndex  = 0;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);
    ADI_NULL_PTR_RETURN(&device->common,
                        iqRate_kHz);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);

    switch (deframerSel)
    {
    case ADI_ADRV9025_DEFRAMER_0:
        deframerIndex = 0;
        break;
    case ADI_ADRV9025_DEFRAMER_1:
        deframerIndex = 1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSel,
                         "Only one deframer can be selected at a time.");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    if (adrv9025Init->dataInterface.deframer[deframerIndex].jesd204M < 1)
    {
        *iqRate_kHz = 0;
        return recoveryAction;
    }

    //Use samplerate of DAC set to use deframer output 0.
    if ((adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx1DacChanI == ADI_ADRV9025_DEFRAMER_OUT0) ||
        (adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx1DacChanQ == ADI_ADRV9025_DEFRAMER_OUT0))
    {
        *iqRate_kHz = adrv9025Init->tx.txChannelCfg[0].profile.txInputRate_kHz;
    }
    else if ((adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx2DacChanI == ADI_ADRV9025_DEFRAMER_OUT0) ||
        (adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx2DacChanQ == ADI_ADRV9025_DEFRAMER_OUT0))
    {
        *iqRate_kHz = adrv9025Init->tx.txChannelCfg[1].profile.txInputRate_kHz;
    }
    else if ((adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx3DacChanI == ADI_ADRV9025_DEFRAMER_OUT0) ||
        (adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx3DacChanQ == ADI_ADRV9025_DEFRAMER_OUT0))
    {
        *iqRate_kHz = adrv9025Init->tx.txChannelCfg[2].profile.txInputRate_kHz;
    }
    else if ((adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx4DacChanI == ADI_ADRV9025_DEFRAMER_OUT0) ||
        (adrv9025Init->dataInterface.deframer[deframerIndex].dacCrossbar.tx4DacChanQ == ADI_ADRV9025_DEFRAMER_OUT0))
    {
        *iqRate_kHz = adrv9025Init->tx.txChannelCfg[3].profile.txInputRate_kHz;
    }

    return recoveryAction;
}

static int32_t adi_board_adrv9025ADS8_Fpga9010Init(adi_fpga9010_Device_t* fpgaDevice,
                                                   adi_adrv9025_Init_t*   adrv9025Init)
{
    adi_fpga9010_Init_t initSet = {{{0}}};
    /* TODO: If above 614.4MHz, divide clock to FPGA in 9528 */
    uint32_t refClk_kHz    = adrv9025Init->clocks.deviceClock_kHz;
    int32_t  testReturnVal = ADI_COMMON_ACT_NO_ACTION;

    fpgaDevice->memoryPageSize = 0x10000000;

    adi_fpga9010_SetupFpgaCfg_t fpgaCfg = {0};
    fpgaCfg.deviceClk_kHz               = refClk_kHz;
    fpgaCfg.framerlink0.datamoversUsed  = 0; /*not used - remove from structure*/

    /*TODO, find first valid Rx based on rx channel mask*/
    adi_board_RxLinkSamplingRateFind(fpgaDevice,
                                     adrv9025Init,
                                     ADI_ADRV9025_FRAMER_0,
                                     &fpgaCfg.deframerlink0.iqRate_kHz);
    fpgaCfg.deframerlink0.jesd204K     = adrv9025Init->dataInterface.framer[0].jesd204K;
    fpgaCfg.deframerlink0.jesd204M     = adrv9025Init->dataInterface.framer[0].jesd204M;
    fpgaCfg.deframerlink0.jesd204Np    = adrv9025Init->dataInterface.framer[0].jesd204Np;
    fpgaCfg.deframerlink0.jesd204E     = adrv9025Init->dataInterface.framer[0].jesd204E;
    fpgaCfg.deframerlink0.jesd204S     = 1;
    fpgaCfg.deframerlink0.lanesEnabled = adrv9025Init->dataInterface.framer[0].serializerLanesEnabled;
    fpgaCfg.deframerlink0.scramble     = adrv9025Init->dataInterface.framer[0].scramble;

    adi_board_RxLinkSamplingRateFind(fpgaDevice,
                                     adrv9025Init,
                                     ADI_ADRV9025_FRAMER_1,
                                     &fpgaCfg.deframerlink1.iqRate_kHz);
    fpgaCfg.deframerlink1.jesd204K     = adrv9025Init->dataInterface.framer[1].jesd204K;
    fpgaCfg.deframerlink1.jesd204M     = adrv9025Init->dataInterface.framer[1].jesd204M;
    fpgaCfg.deframerlink1.jesd204Np    = adrv9025Init->dataInterface.framer[1].jesd204Np;
    fpgaCfg.deframerlink1.jesd204E     = adrv9025Init->dataInterface.framer[1].jesd204E;
    fpgaCfg.deframerlink1.jesd204S     = 1;
    fpgaCfg.deframerlink1.lanesEnabled = adrv9025Init->dataInterface.framer[1].serializerLanesEnabled;
    fpgaCfg.deframerlink1.scramble     = adrv9025Init->dataInterface.framer[1].scramble;

    adi_board_RxLinkSamplingRateFind(fpgaDevice,
                                     adrv9025Init,
                                     ADI_ADRV9025_FRAMER_2,
                                     &fpgaCfg.deframerlink2.iqRate_kHz);
    fpgaCfg.deframerlink2.jesd204K     = adrv9025Init->dataInterface.framer[2].jesd204K;
    fpgaCfg.deframerlink2.jesd204M     = adrv9025Init->dataInterface.framer[2].jesd204M;
    fpgaCfg.deframerlink2.jesd204Np    = adrv9025Init->dataInterface.framer[2].jesd204Np;
    fpgaCfg.deframerlink2.jesd204E     = adrv9025Init->dataInterface.framer[2].jesd204E;
    fpgaCfg.deframerlink2.jesd204S     = 1;
    fpgaCfg.deframerlink2.lanesEnabled = adrv9025Init->dataInterface.framer[2].serializerLanesEnabled;
    fpgaCfg.deframerlink2.scramble     = adrv9025Init->dataInterface.framer[2].scramble;

    adi_board_TxLinkSamplingRateFind(fpgaDevice,
                                     adrv9025Init,
                                     ADI_ADRV9025_DEFRAMER_0,
                                     &fpgaCfg.framerlink0.iqRate_kHz);
    fpgaCfg.framerlink0.jesd204K     = adrv9025Init->dataInterface.deframer[0].jesd204K;
    fpgaCfg.framerlink0.jesd204M     = adrv9025Init->dataInterface.deframer[0].jesd204M;
    fpgaCfg.framerlink0.jesd204Np    = adrv9025Init->dataInterface.deframer[0].jesd204Np;
    fpgaCfg.framerlink0.jesd204E     = adrv9025Init->dataInterface.deframer[0].jesd204E;
    fpgaCfg.framerlink0.jesd204S     = 1;
    fpgaCfg.framerlink0.lanesEnabled = adrv9025Init->dataInterface.deframer[0].deserializerLanesEnabled;
    fpgaCfg.framerlink0.scramble     = adrv9025Init->dataInterface.deframer[0].scramble;
    fpgaCfg.framerlink0.deviceId     = adrv9025Init->dataInterface.deframer[0].deviceId;

    adi_board_TxLinkSamplingRateFind(fpgaDevice,
                                     adrv9025Init,
                                     ADI_ADRV9025_DEFRAMER_1,
                                     &fpgaCfg.framerlink1.iqRate_kHz);
    fpgaCfg.framerlink1.jesd204K     = adrv9025Init->dataInterface.deframer[1].jesd204K;
    fpgaCfg.framerlink1.jesd204M     = adrv9025Init->dataInterface.deframer[1].jesd204M;
    fpgaCfg.framerlink1.jesd204Np    = adrv9025Init->dataInterface.deframer[1].jesd204Np;
    fpgaCfg.framerlink1.jesd204E     = adrv9025Init->dataInterface.deframer[1].jesd204E;
    fpgaCfg.framerlink1.jesd204S     = 1;
    fpgaCfg.framerlink1.lanesEnabled = adrv9025Init->dataInterface.deframer[1].deserializerLanesEnabled;
    fpgaCfg.framerlink1.scramble     = adrv9025Init->dataInterface.deframer[1].scramble;
    fpgaCfg.framerlink1.deviceId     = adrv9025Init->dataInterface.deframer[1].deviceId;

    /* Based on schematic showing inverted signals going into these links */
    initSet.datapath.syncBPolarity = 0x7;

    /* Setup the serializer lane swaps for this board */
    initSet.datapath.pcbSerLaneSwap[0] = 3;
    initSet.datapath.pcbSerLaneSwap[1] = 2;
    initSet.datapath.pcbSerLaneSwap[2] = 1;
    initSet.datapath.pcbSerLaneSwap[3] = 0;
    initSet.datapath.pcbSerLaneSwap[4] = 7;
    initSet.datapath.pcbSerLaneSwap[5] = 7;
    initSet.datapath.pcbSerLaneSwap[6] = 7;
    initSet.datapath.pcbSerLaneSwap[7] = 7;

    /* Setup the deserializer lane swaps for this board */
    initSet.datapath.pcbDesLaneSwap[0] = 1;
    initSet.datapath.pcbDesLaneSwap[1] = 0;
    initSet.datapath.pcbDesLaneSwap[2] = 2;
    initSet.datapath.pcbDesLaneSwap[3] = 3;
    initSet.datapath.pcbDesLaneSwap[4] = 7;
    initSet.datapath.pcbDesLaneSwap[5] = 7;
    initSet.datapath.pcbDesLaneSwap[6] = 7;
    initSet.datapath.pcbDesLaneSwap[7] = 7;

    testReturnVal = adi_fpga9010_InitConfig(fpgaDevice,
                                            &fpgaCfg,
                                            &initSet);
    if (testReturnVal != 0)
    {
        return testReturnVal;
    }

    /* Setup ADRV9025 + ADS8 specific settings */
    initSet.clocks.qpll.refClkSelect[0] = ADI_FPGA9010_QPLL_GTREFCLK0;
    initSet.clocks.qpll.quadSelect      = ADI_FPGA9010_QPLL_QUAD0;
    initSet.datapath.serializerCfg[0].polarity = 0;
    initSet.datapath.serializerCfg[1].polarity = 0;
    initSet.datapath.serializerCfg[2].polarity = 0;
    initSet.datapath.serializerCfg[3].polarity = 0;
    initSet.datapath.deserializerCfg[0].polarity = 1;
    initSet.datapath.deserializerCfg[1].polarity = 1;
    initSet.datapath.deserializerCfg[2].polarity = 1;
    initSet.datapath.deserializerCfg[3].polarity = 1;

    testReturnVal = adi_fpga9010_InitSet(fpgaDevice,
                                         &initSet);
    if (testReturnVal != 0)
    {
        return testReturnVal;
    }

    return ADI_COMMON_ACT_NO_ACTION;
}

static int32_t adi_board_adrv9025ADS8_Ad9528Init(adi_ad9528_Device_t*   ad9528Device,
                                                 adi_fpga9010_Device_t* fpga9010Device,
                                                 adi_ad9528_Init_t*     ad9528Init,
                                                 adi_adrv9025_Init_t*   adrv9025Init)
{
    UNUSED_PARA(fpga9010Device);
    UNUSED_PARA(adrv9025Init);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((recoveryAction = adi_ad9528_HwReset(ad9528Device)) < 0)
    {
        return recoveryAction;
    }

    
    if ((recoveryAction = adi_ad9528_Initialize(ad9528Device,
                                                ad9528Init)) < 0)
    {
        return recoveryAction;
    }
    

    return recoveryAction;
}

int32_t adi_board_adrv9025ADS8_JesdTxBringup(adi_adrv9025_Device_t* adrv9025Device,
                                             adi_fpga9010_Device_t* fpga9010Device,
                                             adi_ad9528_Device_t*   ad9528Device,
                                             uint32_t               link)
{
    int32_t                 recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    adi_adrv9025_InitCals_t serdesCal        = {0};
    uint8_t                 errFlags         = 0;
    static const uint8_t    CAL_ALL_CHANNELS = 0x0F;

    /* Unmask incoming sysref in FPGA framers (leave rx links untouched) */
    recoveryAction = adi_fpga9010_SysRefEnableSet(fpga9010Device,
                                                  (uint8_t)link,
                                                  0,
                                                  ADI_ENABLE);
    ADI_ERROR_REPORT(&fpga9010Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9010Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9010Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9010Device->common.error.newAction);

    /* Enable/reset FPGA Framer(s) */
    recoveryAction = adi_fpga9010_FramerReset(fpga9010Device,
                                              (uint8_t)link);
    ADI_ERROR_REPORT(&fpga9010Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9010Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9010Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9010Device->common.error.newAction);

    /* Request sysref to start fpga framers sending data */
    recoveryAction = adi_ad9528_SysrefRequest(ad9528Device,
                                              1);
    ADI_ERROR_REPORT(&ad9528Device->common,
                     ADI_COMMON_ERRSRC_API,
                     ad9528Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     ad9528Device->common.error.errormessage);
    ADI_ERROR_RETURN(ad9528Device->common.error.newAction);

    /* Mask the sysref for the fpga framers as a precaution for the next sysref (leave rx links untouched) */
    recoveryAction = adi_fpga9010_SysRefEnableSet(fpga9010Device,
                                                  (uint8_t)link,
                                                  0,
                                                  ADI_DISABLE);
    ADI_ERROR_REPORT(&fpga9010Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9010Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9010Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9010Device->common.error.newAction);

    /* Reset/Enable Adrv9025 Deframer(s) */
    recoveryAction = adi_adrv9025_DfrmLinkStateSet(adrv9025Device,
                                                   (uint8_t)link,
                                                   ADI_DISABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    adi_common_hal_Wait_ms(&adrv9025Device->common,
                           50);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    recoveryAction = adi_adrv9025_DfrmLinkStateSet(adrv9025Device,
                                                   (uint8_t)link,
                                                   ADI_ENABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Notify ARM to run SERDES Calbriation if necessary */
    serdesCal.calMask     = ADI_ADRV9025_SERDES_INIT;
    serdesCal.channelMask = CAL_ALL_CHANNELS;
    serdesCal.warmBoot    = 0;
    recoveryAction        = adi_adrv9025_InitCalsRun(adrv9025Device,
                                                     &serdesCal);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Wait up to 6000 milliseconds for ARM */
    recoveryAction = adi_adrv9025_InitCalsWait(adrv9025Device,
                                               6000,
                                               &errFlags);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Adrv9025 Unmask Sysref in Deframer(s) */
    recoveryAction = adi_adrv9025_DeframerSysrefCtrlSet(adrv9025Device,
                                                        (adi_adrv9025_DeframerSel_e)link,
                                                        ADI_ENABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Request sysref for adrv9025 deframers only */
    recoveryAction = adi_ad9528_SysrefRequest(ad9528Device,
                                              1);
    ADI_ERROR_REPORT(&ad9528Device->common,
                     ADI_COMMON_ERRSRC_API,
                     ad9528Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     ad9528Device->common.error.errormessage);
    ADI_ERROR_RETURN(ad9528Device->common.error.newAction);

    /* Adrv9025 mask Sysref in Deframer(s) as a precaution */
    recoveryAction = adi_adrv9025_DeframerSysrefCtrlSet(adrv9025Device,
                                                        (adi_adrv9025_DeframerSel_e)link,
                                                        ADI_DISABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_board_adrv9025ADS8_JesdRxBringup(adi_adrv9025_Device_t* adrv9025Device,
                                             adi_fpga9010_Device_t* fpga9010Device,
                                             adi_ad9528_Device_t*   ad9528Device,
                                             uint32_t               link)
{
    int32_t recoveryAction          = ADI_COMMON_ACT_NO_ACTION;
    uint8_t sysrefEnabledForFramer2 = ADI_FALSE;

    if (adrv9025Device->devStateInfo.linkSharingEnabled == 1)
    {
        /* Start the AUX Sys Ref in JTX Link 1*/
        recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                         ADI_ADRV9025_FRAMER_1,
                                                         ADI_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        /* Adrv9010 Unmask incoming Sysref in Framer(s) */
        recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                          ADI_ADRV9025_FRAMER_1,
                                                          ADI_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        recoveryAction = adi_ad9528_SysrefRequest(ad9528Device,
                                                  1);
        ADI_ERROR_REPORT(&ad9528Device->common,
                         ADI_COMMON_ERRSRC_API,
                         ad9528Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         ad9528Device->common.error.errormessage);
        ADI_ERROR_RETURN(ad9528Device->common.error.newAction);

        recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                         ADI_ADRV9025_FRAMER_1,
                                                         ADI_DISABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                          ADI_ADRV9025_FRAMER_1,
                                                          ADI_DISABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                         ADI_ADRV9025_FRAMER_0,
                                                         ADI_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                          ADI_ADRV9025_FRAMER_0,
                                                          ADI_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        /* Check that if the profile uses Framer 2 */
        if ((link & (uint32_t)ADI_ADRV9025_FRAMER_2) == (uint32_t)ADI_ADRV9025_FRAMER_2)
        {
            recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                             ADI_ADRV9025_FRAMER_2,
                                                             ADI_ENABLE);
            ADI_ERROR_REPORT(&adrv9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             adrv9025Device->common.error.errCode,
                             recoveryAction,
                             NULL,
                             adrv9025Device->common.error.errormessage);
            ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

            recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                              ADI_ADRV9025_FRAMER_2,
                                                              ADI_ENABLE);
            ADI_ERROR_REPORT(&adrv9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             adrv9025Device->common.error.errCode,
                             recoveryAction,
                             NULL,
                             adrv9025Device->common.error.errormessage);
            ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

            sysrefEnabledForFramer2 = ADI_TRUE;
        }
    }
    else
    {
        /* Enable/reset Adrv9010 Framer(s) */
        recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                         link,
                                                         ADI_DISABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        adi_common_hal_Wait_ms(&adrv9025Device->common,
                               50);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                         link,
                                                         ADI_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        /* Adrv9010 Unmask incoming Sysref in Framer(s) */
        recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                          (uint8_t)link,
                                                          ADI_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);
    }

    /* Wait 100ms for clock recovery on FPGA to lock */
    adi_common_hal_Wait_ms(&adrv9025Device->common,
                           100);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Enable/reset FPGA Deframer(s) */
    recoveryAction = adi_fpga9010_DeframerReset(fpga9010Device,
                                                (uint8_t)link);
    ADI_ERROR_REPORT(&fpga9010Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9010Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9010Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9010Device->common.error.newAction);

    /* Unmask incoming sysref in FPGA deframers (leave tx links untouched) */
    recoveryAction = adi_fpga9010_SysRefEnableSet(fpga9010Device,
                                                  0,
                                                  (uint8_t)link,
                                                  ADI_ENABLE);
    ADI_ERROR_REPORT(&fpga9010Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9010Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9010Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9010Device->common.error.newAction);

    /* Request sysref to bring up Rx links */
    recoveryAction = adi_ad9528_SysrefRequest(ad9528Device,
                                              1);
    ADI_ERROR_REPORT(&ad9528Device->common,
                     ADI_COMMON_ERRSRC_API,
                     ad9528Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     ad9528Device->common.error.errormessage);
    ADI_ERROR_RETURN(ad9528Device->common.error.newAction);

    if (adrv9025Device->devStateInfo.linkSharingEnabled == 0)
    {
        /* Adrv9010 mask sysref in Framers. Precaution against future sysref signals */
        recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                          (uint8_t)link,
                                                          ADI_DISABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);
    }

    if (sysrefEnabledForFramer2 == ADI_TRUE)
    {
        recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                          ADI_ADRV9025_FRAMER_2,
                                                          ADI_DISABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);
    }

    /* Mask sysref in fpga deframers. Precaution against future sysref signals */
    recoveryAction = adi_fpga9010_SysRefEnableSet(fpga9010Device,
                                                  0,
                                                  (uint8_t)link,
                                                  ADI_DISABLE);
    ADI_ERROR_REPORT(&fpga9010Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9010Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9010Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9010Device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_board_adrv9025ADS8_JesdBringup(adi_adrv9025_Device_t* adrv9025Device,
                                           adi_fpga9010_Device_t* fpgaDevice,
                                           adi_ad9528_Device_t*   ad9528Device,
                                           uint32_t               txLinkSel,
                                           uint32_t               rxLinkSel)
{
    int32_t recoveryAction        = ADI_COMMON_ACT_NO_ACTION;
    uint8_t i                     = 0;
    uint8_t adrv9025LinkStatus    = 0;
    uint8_t fpga9010LinkStatus    = 0;
    uint8_t deframerLinkCondition = 0;

    /* Mask all sysrefs in Adrv9025 */
    recoveryAction = adi_adrv9025_DeframerSysrefCtrlSet(adrv9025Device,
                                                        ADI_ADRV9025_DEFRAMER_0,
                                                        ADI_DISABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    recoveryAction = adi_adrv9025_FramerSysrefCtrlSet(adrv9025Device,
                                                      ADI_ADRV9025_ALL_FRAMERS,
                                                      ADI_DISABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Mask all sysrefs in fpga */
    recoveryAction = adi_fpga9010_SysRefEnableSet(fpgaDevice,
                                                  ADI_FPGA9010_FRAMER_ALL,
                                                  ADI_FPGA9010_DEFRAMER_ALL,
                                                  ADI_DISABLE);
    ADI_ERROR_REPORT(&fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     fpgaDevice->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpgaDevice->common.error.errormessage);
    ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);

    /* Disable all the FPGA framer & deframers */
    recoveryAction = adi_fpga9010_FramerDisable(fpgaDevice,
                                                ADI_FPGA9010_FRAMER_ALL);
    ADI_ERROR_REPORT(&fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     fpgaDevice->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpgaDevice->common.error.errormessage);
    ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);

    recoveryAction = adi_fpga9010_DeframerDisable(fpgaDevice,
                                                  ADI_FPGA9010_DEFRAMER_ALL);
    ADI_ERROR_REPORT(&fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     fpgaDevice->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpgaDevice->common.error.errormessage);
    ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);

    /* Disable all the ADRV9025 framer & deframers */
    recoveryAction = adi_adrv9025_DfrmLinkStateSet(adrv9025Device,
                                                   (uint8_t)ADI_ADRV9025_DEFRAMER_0,
                                                   ADI_DISABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    recoveryAction = adi_adrv9025_FramerLinkStateSet(adrv9025Device,
                                                     (uint8_t)ADI_ADRV9025_ALL_FRAMERS,
                                                     ADI_DISABLE);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Override DFE LPM in PHY before sending sys ref */
    adi_fpga9010_ChannelDfeLpmOverrideSet(fpgaDevice,
                                          0xFF,
                                          1);
    ADI_ERROR_REPORT(&fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     fpgaDevice->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpgaDevice->common.error.errormessage);
    ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);

    if (rxLinkSel != 0)
    {
        /* Bring up the Rx links */
        adi_board_adrv9025ADS8_JesdRxBringup(adrv9025Device,
                                             fpgaDevice,
                                             ad9528Device,
                                             rxLinkSel);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        if (fpgaDevice->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
        {
            adi_fpga9010_Jesd204CDeframerCmdDataSet(fpgaDevice,
                                                    rxLinkSel,
                                                    ADI_ENABLE,
                                                    ADI_ENABLE);
            ADI_ERROR_REPORT(&fpgaDevice->common,
                             ADI_COMMON_ERRSRC_API,
                             fpgaDevice->common.error.errCode,
                             recoveryAction,
                             NULL,
                             fpgaDevice->common.error.errormessage);
            ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);
        }
    }

    if (txLinkSel != 0)
    {
        /* Bring up the Tx links */
        adi_board_adrv9025ADS8_JesdTxBringup(adrv9025Device,
                                             fpgaDevice,
                                             ad9528Device,
                                             txLinkSel);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        if (fpgaDevice->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
        {
            adi_fpga9010_Jesd204CFramerCmdDataSet(fpgaDevice,
                                                  txLinkSel,
                                                  ADI_ENABLE,
                                                  ADI_ENABLE);
            ADI_ERROR_REPORT(&fpgaDevice->common,
                             ADI_COMMON_ERRSRC_API,
                             fpgaDevice->common.error.errCode,
                             recoveryAction,
                             NULL,
                             fpgaDevice->common.error.errormessage);
            ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);
        }
    }

    /* Disable DFE LPM in PHY before after sys ref */
    adi_fpga9010_ChannelDfeLpmOverrideSet(fpgaDevice,
                                          0xFF,
                                          0);
    ADI_ERROR_REPORT(&fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     fpgaDevice->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpgaDevice->common.error.errormessage);
    ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);

    /* Adrv9025 Deframer Status get*/
    for (i = 0; i < ADI_ADRV9025_NUM_DEFRAMERS; i++)
    {
        if ((txLinkSel & (1 << i)) > 0)
        {
            deframerLinkCondition = 0;
            recoveryAction        = adi_adrv9025_DfrmLinkConditionGet(adrv9025Device,
                                                                      (adi_adrv9025_DeframerSel_e)((uint8_t)(1 << i)),
                                                                      &deframerLinkCondition);
            ADI_ERROR_REPORT(&adrv9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             adrv9025Device->common.error.errCode,
                             recoveryAction,
                             NULL,
                             adrv9025Device->common.error.errormessage);
            ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

            if (deframerLinkCondition & 0x01)
            {
                adrv9025LinkStatus |= (1 << i);
            }
        }
    }

    /* Fpga Reading User Data Ready bit*/
    recoveryAction = adi_fpga9010_DeframerStatusGet(fpgaDevice,
                                                    rxLinkSel,
                                                    &fpga9010LinkStatus);
    ADI_ERROR_REPORT(&fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     fpgaDevice->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpgaDevice->common.error.errormessage);
    ADI_ERROR_RETURN(fpgaDevice->common.error.newAction);

    if (adrv9025LinkStatus != txLinkSel)
    {
        recoveryAction = ADI_COMMON_ACT_ERR_RESET_INTERFACE;
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Not all Tx links have been established.");

        /* Disable all the FPGA deframers. Don't update the error though, this is just cleanup */
        adi_fpga9010_FramerDisable(fpgaDevice,
                                   ADI_FPGA9010_FRAMER_ALL);
    }
    if (fpga9010LinkStatus != rxLinkSel)
    {
        recoveryAction = ADI_COMMON_ACT_ERR_RESET_INTERFACE;
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Not all Rx links have been established.");

        /* Disable all the FPGA deframers. Don't update the error though, this is just cleanup */
        adi_fpga9010_DeframerDisable(fpgaDevice,
                                     ADI_FPGA9010_DEFRAMER_ALL);
    }

    /* Kick off SERDES tracking cal if lanes are up */
    if (recoveryAction == ADI_COMMON_ACT_NO_ACTION)
    {
        recoveryAction = adi_adrv9025_TrackingCalsEnableSet(adrv9025Device,
                                                            ADI_ADRV9025_TRACK_DESERIALIZER,
                                                            ADI_ADRV9025_TRACKING_CAL_ENABLE);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_board_adrv9025ADS8_Program_Phase1(adi_board_adrv9025Ads8_t*     adrv9025Ads801,
                                              adi_adrv9025_Init_t*          adrv9025Init,
                                              adi_ad9528_Init_t*            ad9528Init,
                                              adi_adrv9025_PlatformFiles_t* adrv9025PlatformFiles)
{
    int32_t                            recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    adi_fpga9010_AxiAdvSpiFeatConfig_t fpgaAdvSpiCfg  = {0};

    fpgaAdvSpiCfg.enable            = 1;
    fpgaAdvSpiCfg.cpha              = 0;
    fpgaAdvSpiCfg.cpol              = 0;
    fpgaAdvSpiCfg.lsbFirst          = 0;
    fpgaAdvSpiCfg.fourWire          = 1;
    fpgaAdvSpiCfg.misoSampleSlip    = 1;
    fpgaAdvSpiCfg.threeWireTriPoint = 16;
    fpgaAdvSpiCfg.clockDiv          = 1;

    /* AD9528: 25Mhz SPICLK, but with SPIDO clocked half clock cycle later for improved setup.hold */
    recoveryAction = adi_fpga9010_AxiAdvSpiCfgSet(adrv9025Ads801->fpgaDevice,
                                                  &fpgaAdvSpiCfg,
                                                  0);
    if (recoveryAction != 0)
    {
        return recoveryAction;
    }
    /* ADRV9025: 25Mhz SPICLK, but with SPIDO clocked half clock cycle later for improved setup.hold */
    recoveryAction = adi_fpga9010_AxiAdvSpiCfgSet(adrv9025Ads801->fpgaDevice,
                                                  &fpgaAdvSpiCfg,
                                                  1);
    if (recoveryAction != 0)
    {
        return recoveryAction;
    }

    /* Reset FPGA MMCM to prevent lock up issues when switching FPGA refClk values */
    recoveryAction = adi_fpga9010_MmcmResetSet(adrv9025Ads801->fpgaDevice,
                                               ADI_FPGA9010_CORE_MMCM);
    ADI_ERROR_REPORT(&adrv9025Ads801->fpgaDevice->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error resetting clock wizard");
    ADI_ERROR_RETURN(adrv9025Ads801->fpgaDevice->common.error.newAction);

    /* Init Ad9528 */
    if ((recoveryAction = adi_board_adrv9025ADS8_Ad9528Init(adrv9025Ads801->ad9528Device,
                                                            adrv9025Ads801->fpgaDevice,
                                                            ad9528Init,
                                                            adrv9025Init)) != ADI_COMMON_ACT_NO_ACTION)
    {
        return recoveryAction;
    }
    

    if ((recoveryAction = adi_board_adrv9025ADS8_Fpga9010Init(adrv9025Ads801->fpgaDevice,
                                                              adrv9025Init)) != 0)
    {
        return recoveryAction;
    }
    

    /* Reset Hardware */
    recoveryAction = adi_adrv9025_HwReset(adrv9025Ads801->adrv9025Device);
    ADI_ERROR_REPORT(&adrv9025Ads801->adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_API_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to Reset Adrv9025 device");
    ADI_ERROR_RETURN(adrv9025Ads801->adrv9025Device->common.error.newAction);

    /* Custom Step for ADI eval card to read ADRV9025 internal LDO bypass setting from the eval boards EEPROM to make sure the
     * silicon is not accidentally damaged.  ADI stores this in a custom FMC EEPROM field used for the BOM revision of the PCB */
    if ((recoveryAction = adi_adrv9025Board_LdoSelectOverRide(adrv9025Init)) != ADI_COMMON_ACT_NO_ACTION)
    {
        ADI_ERROR_REPORT(&adrv9025Ads801->adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to perform Ldo Select override");
        ADI_ERROR_RETURN(recoveryAction);
    }

    /* Pre MCS - Broadcastable */
    if ((recoveryAction = adi_adrv9025_PreMcsInit_v2(adrv9025Ads801->adrv9025Device,
                                                     adrv9025Init,
                                                     adrv9025PlatformFiles->armImageFile,
                                                     adrv9025PlatformFiles->streamImageFile,
                                                     adrv9025PlatformFiles->rxGainTableFileArr,
                                                     adrv9025PlatformFiles->rxGainTableFileArrSize,
                                                     adrv9025PlatformFiles->txAttenTableFileArr,
                                                     adrv9025PlatformFiles->txAttenTableFileArrSize)) != ADI_COMMON_ACT_NO_ACTION)
    {
        return recoveryAction;
    }

    /* Pre MCS - Non-Broadcastable */
    if ((recoveryAction = adi_adrv9025_PreMcsInit_NonBroadCast(adrv9025Ads801->adrv9025Device,
                                                               adrv9025Init)) != ADI_COMMON_ACT_NO_ACTION)
    {
        return recoveryAction;
    }

    return 0;
}

int32_t adi_board_adrv9025ADS8_Program_Phase2(adi_board_adrv9025Ads8_t*   adrv9025Ads801,
                                              adi_adrv9025_Init_t*        adrv9025Init,
                                              adi_adrv9025_PostMcsInit_t* adrv9025PostMcsInit,
                                              adi_ad9528_Init_t*          ad9528Init)
{
    (void)(ad9528Init);
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t mcsStatus      = 0;
    uint8_t  i              = 0;
    uint32_t txLinkSel      = 0;
    uint32_t rxLinkSel      = 0;

    /* MCS start sequence*/
    if ((recoveryAction = adi_adrv9025_MultichipSyncSet(adrv9025Ads801->adrv9025Device,
                                                        ADI_ENABLE)) < 0)
    {
        return recoveryAction;
    }

    /* This loop will send SysRef pulses up to 255 times unless MCS status achieved before. */
    for (i = 0; i < 255; i++)
    {
        if ((recoveryAction = adi_ad9528_SysrefRequest(adrv9025Ads801->ad9528Device,
                                                       1)) != 0)
        {
            return recoveryAction;
        }
        else
        {
            if ((recoveryAction = adi_adrv9025_MultichipSyncStatusGet(adrv9025Ads801->adrv9025Device,
                                                                      &mcsStatus)) != 0)
            {
                return recoveryAction;
            }
            else
            {
                if ((mcsStatus & 0x17) == 0x17)
                {
                    break;
                }
            }
        }
    }

    if ((mcsStatus & 0x17) != 0x17)
    {
        /*perror("ADRV9025 CLKPLL MCS status not correct\n");*/
        /*TODO : Add error message once there is error reporting added at the board level*/
        return ADI_COMMON_ACT_ERR_RESET_FULL;
    }

    /* MCS end sequence*/
    if ((recoveryAction = adi_adrv9025_MultichipSyncSet(adrv9025Ads801->adrv9025Device,
                                                        ADI_DISABLE)) < 0)
    {
        return recoveryAction;
    }

    /* Post MCS */
    if ((recoveryAction = adi_adrv9025_PostMcsInit(adrv9025Ads801->adrv9025Device,
                                                   adrv9025PostMcsInit)) < 0)
    {
        return recoveryAction;
    }

    if ((recoveryAction = adi_adrv9025_SerializerReset(adrv9025Ads801->adrv9025Device,
                                                       adrv9025Init->clocks.serdesPllVcoFreq_kHz)) < 0)
    {
        return recoveryAction;
    }

    for (i = 0; i < ADI_ADRV9025_NUM_FRAMERS; i++)
    {
        if (adrv9025Init->dataInterface.framer[i].serializerLanesEnabled > 0)
        {
            rxLinkSel |= 1 << i;
        }
    }

    for (i = 0; i < ADI_ADRV9025_NUM_DEFRAMERS; i++)
    {
        if (adrv9025Init->dataInterface.deframer[i].deserializerLanesEnabled > 0)
        {
            txLinkSel |= 1 << i;
        }
    }

    /* JESD204 link bring up */
    if ((recoveryAction = adi_board_adrv9025ADS8_JesdBringup(adrv9025Ads801->adrv9025Device,
                                                             adrv9025Ads801->fpgaDevice,
                                                             adrv9025Ads801->ad9528Device,
                                                             txLinkSel,
                                                             rxLinkSel)) < 0)
    {
        return recoveryAction;
    }

    /* Initialize Tx Ramp down functionality */
    if ((recoveryAction = adi_adrv9025_TxRampDownInit(adrv9025Ads801->adrv9025Device,
                                                      adrv9025Init) < 0))
    {
        return recoveryAction;
    }

    /* Setup GP Interrupts from init structure */
    if ((recoveryAction = adi_adrv9025_GpIntInit(adrv9025Ads801->adrv9025Device,
                                                 &adrv9025Init->gpInterrupts) < 0))
    {
        return recoveryAction;
    }

    return 0;
}

int32_t adi_board_adrv9025ADS8_Ad9528Configure(adi_board_adrv9025Ads8_t* adrv9025ADS8,
                                               adi_ad9528_Init_t*        ad9528Init,
                                               uint32_t                  deviceClock_kHz,
                                               uint32_t                  vcxoFreq_kHz,
                                               uint32_t                  refAFreq_kHz,
                                               uint32_t                  fpgaClock_kHz)
{
    int32_t                             recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    adi_ad9528_ClockFrequencySettings_t clockFrequencies = {0};

    /* TODO: if 9025EE EVB, set different settings for 9528 setup */

    if (strstr(&adrv9025ADS8->pcbName[0],
               "9025EE") != NULL)
    {
        clockFrequencies.vcxoFrequency_Hz   = vcxoFreq_kHz * 1000;
        clockFrequencies.refAFrequency_Hz   = 0;
        clockFrequencies.outputClock_Hz[0]  = 120000; /* TODO: SYSREF should not be fixed, this will break future profiles */
        clockFrequencies.outputClock_Hz[3]  = fpgaClock_kHz * 1000;
        clockFrequencies.outputClock_Hz[12] = 120000;
        clockFrequencies.outputClock_Hz[13] = fpgaClock_kHz * 1000;
        clockFrequencies.outSource[0]       = ADI_AD9528_SYSREF;
        clockFrequencies.outSource[12]      = ADI_AD9528_SYSREF;

        /* Clear out the init structure because InitStructConfig sets all appropriate members */
        memset(ad9528Init,
               0,
               sizeof(adi_ad9528_Init_t));

        if ((recoveryAction = adi_ad9528_InitStructConfig(adrv9025ADS8->ad9528Device,
                                                          &clockFrequencies,
                                                          ad9528Init)) < 0)
        {
            return recoveryAction;
        }
    }
    else
    {
        clockFrequencies.vcxoFrequency_Hz   = vcxoFreq_kHz * 1000;
        clockFrequencies.refAFrequency_Hz   = refAFreq_kHz * 1000;
        clockFrequencies.outputClock_Hz[0]  = 120000; /* TODO: SYSREF should not be fixed, this will break future profiles */
        clockFrequencies.outputClock_Hz[1]  = deviceClock_kHz * 1000;
        clockFrequencies.outputClock_Hz[3]  = fpgaClock_kHz * 1000;
        clockFrequencies.outputClock_Hz[12] = 120000;
        clockFrequencies.outputClock_Hz[13] = fpgaClock_kHz * 1000;
        clockFrequencies.outSource[0]       = ADI_AD9528_SYSREF;
        clockFrequencies.outSource[12]      = ADI_AD9528_SYSREF;

        /* Clear out the init structure because InitStructConfig sets all appropriate members */
        memset(ad9528Init,
               0,
               sizeof(adi_ad9528_Init_t));

        if ((recoveryAction = adi_ad9528_InitStructConfig(adrv9025ADS8->ad9528Device,
                                                          &clockFrequencies,
                                                          ad9528Init)) < 0)
        {
            return recoveryAction;
        }

        ad9528Init->pll1Settings.vcxoBufferCtrl = ADI_AD9528_SINGLE_ENDED;
    }

    return recoveryAction;
}

int32_t adi_board_adrv9025ADS8_Jesd204LinkReset(adi_board_adrv9025Ads8_t* adrv9025ADS8,
                                                adi_adrv9025_Init_t*      adrv9025Init)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t  i              = 0;
    uint32_t txLinkSel      = 0;
    uint32_t rxLinkSel      = 0;

    for (i = 0; i < ADI_ADRV9025_NUM_FRAMERS; i++)
    {
        if (adrv9025Init->dataInterface.framer[i].serializerLanesEnabled > 0)
        {
            rxLinkSel |= 1 << i;
        }
    }

    for (i = 0; i < ADI_ADRV9025_NUM_DEFRAMERS; i++)
    {
        if (adrv9025Init->dataInterface.deframer[i].deserializerLanesEnabled > 0)
        {
            txLinkSel |= 1 << i;
        }
    }

    /* JESD204 link bring up */
    if ((recoveryAction = adi_board_adrv9025ADS8_JesdBringup(adrv9025ADS8->adrv9025Device,
                                                             adrv9025ADS8->fpgaDevice,
                                                             adrv9025ADS8->ad9528Device,
                                                             txLinkSel,
                                                             rxLinkSel)) < 0)
    {
        return recoveryAction;
    }

    return 0;
}
