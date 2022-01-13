/**
 * \file adi_adrv9025_daughter_board.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_adrv9025_daughter_board.h"

#include "adi_board_adrv9025ADS8.h"



#include "adi_ad9528.h"
#include "adi_ad9528_utilities.h"
#include "adi_fpga9025_utilities.h"
#include "adi_adrv9025_gpio.h"
#include "adi_adrv9025_utilities.h"
#include "adi_adrv9025_hal.h"
#include "adi_adrv9025_data_interface.h"
#include "adi_fpga9025.h"
#include "adi_fpga9010.h"
#include "platform_utils/adi_fmc_fru.h"
#include "platform_utils/adi_fmc_eeprom.h"
#include <stdlib.h>
#include <string.h>
#include "adi_platform_identify.h"
#include "adi_motherboard_trx.h"

#include "adi_fpga9025_axi_adv_spi.h"
#include "adi_fpga9025_clk.h"
#include "adi_fpga9025_jesd.h"
#include "adi_adrv9025_cals.h"

/****************************************************************************
* Local functions
****************************************************************************/
int32_t adi_board_adrv9025_Ad9528Init(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t              recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    adi_ad9528_Device_t* ad9528Device   = NULL;
    adi_ad9528_Init_t*   ad9528Init     = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    ad9528Device = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice;
    ad9528Init   = (adi_ad9528_Init_t *)trxDaughterboard->clockInit;

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

int32_t adi_board_adrv9025_Ad9528Configure(adi_daughterboard_trx_t* trxDaughterboard,
                                           uint32_t                 deviceClock_kHz,
                                           uint32_t                 vcxoFreq_kHz,
                                           uint32_t                 refAFreq_kHz,
                                           uint32_t                 fpgaClock_kHz)
{
    int32_t                             recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    adi_ad9528_ClockFrequencySettings_t clockFrequencies = {0};
    adi_ad9528_Device_t*                ad9528Device     = NULL;
    adi_ad9528_Init_t*                  ad9528Init       = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }
    ad9528Device = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice;
    ad9528Init   = (adi_ad9528_Init_t *)trxDaughterboard->clockInit;

    clockFrequencies.vcxoFrequency_Hz = vcxoFreq_kHz * 1000;
    if ((trxDaughterboard->boardAttribute & TRX_DAUGHTERBOARD_ATTRIBUTE_TYPE_EE) == 0)
    {
        clockFrequencies.refAFrequency_Hz  = refAFreq_kHz * 1000;
        clockFrequencies.outputClock_Hz[1] = deviceClock_kHz * 1000;
    }

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

    if ((recoveryAction = adi_ad9528_InitStructConfig(ad9528Device,
                                                      &clockFrequencies,
                                                      ad9528Init)) < 0)
    {
        return recoveryAction;
    }

    if ((trxDaughterboard->boardAttribute & TRX_DAUGHTERBOARD_ATTRIBUTE_TYPE_EE) == 0)
    {
        ad9528Init->pll1Settings.vcxoBufferCtrl = ADI_AD9528_SINGLE_ENDED;
    }

    return recoveryAction;
}

int32_t adi_adrv9025Board_RxLinkSamplingRateFind(adi_fpga9025_Device_t*   device,
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

int32_t adi_adrv9025Board_TxLinkSamplingRateFind(adi_fpga9025_Device_t*     device,
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

int32_t adi_adrv9025Board_LdoSelectOverRide(adi_adrv9025_Init_t* adrv9025Init)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t halRetVal      = 0;

    static const int32_t SIZE_BYTES    = 1024;
    static const int32_t FMCINDEX      = 0;
    static const uint8_t LDO_BYPASS    = 1;
    static const uint8_t LDO_NONBYPASS = 0;

    int   index         = 0;
    int   indx          = 0;
    char  infoStr[1024] = {0};
    char  bomStr[7]     = {0};
    char* tmpStrPtr;
    /* const char *ceBom = "047405"; */
    /* const char *eeBom = "045639"; */
    const char* bypassStr = "bypass";

    /* Adrv9010 programming sequence */

    /* Select all Tokelau devices available for broadcast write */
    /* TODO: Uncomment this call when fpga image support manual CS manipulation */
    //if ((recoveryAction = adi_fpga9010_AxiAdvSpiChipSelectAll(adrv9010Ce01->fpga9010Device, ADI_TRUE)) != 0)
    //{
    //return recoveryAction;
    //}

    /* Begin ADS8 LDO Select Feature */
    /* This code only supports the ADI Evaluation card */
    /* protecting against LDO Bypass Damage */

    /* this function writes return string */
    halRetVal = adi_FmcEepromInfoGet(FMCINDEX,
                                     &infoStr[0],
                                     SIZE_BYTES);
    if (halRetVal != ADI_HAL_OK)
    {
        /* Return error to caller */
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    if (strstr(infoStr,
               "ERROR") != NULL)
    {
        adrv9025Init->clocks.ldoSelect = LDO_NONBYPASS;
        printf("ERROR: Could not read EEPROM, defaulted to LDO Non Bypass case to stay safe.");
    }
    else
    {
        /* extract EEPROM fields */
        tmpStrPtr = strtok(infoStr, ";"); /* Manufacturer    */
        tmpStrPtr = strtok(NULL, ";");    /* Product Name    */
        tmpStrPtr = strtok(NULL, ";");    /* Serial Number   */
        tmpStrPtr = strtok(NULL, ";");    /* Part Number     */
        tmpStrPtr = strtok(NULL, ";");    /* PCB ID          */
        tmpStrPtr = strtok(NULL, ";");    /* BOM Part Number */

        if (tmpStrPtr == NULL)
        {
            /* Stay safe on boards that don't explicitly have bypass in EEPROM */
            adrv9025Init->clocks.ldoSelect = LDO_NONBYPASS;
        }
        else
        {
            /* get the CE BOM number */
            indx = 0;
            for (index = 8; index < 14; index++)
            {
                bomStr[indx] = tmpStrPtr[index];
                indx++;
            }

            /* Must match bypass string to fall into this case*/
            if (strncmp(bomStr,
                        bypassStr,
                        strlen(bypassStr)) == 0)
            {
                adrv9025Init->clocks.ldoSelect = LDO_BYPASS;
            }
            else
            {
                adrv9025Init->clocks.ldoSelect = LDO_NONBYPASS;
            }
        }
    }

    return recoveryAction;
}

int32_t adi_board_adrv9025_JesdTxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                         uint32_t                 link)
{
    int32_t                 recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    adi_adrv9025_InitCals_t serdesCal        = {0};
    uint8_t                 errFlags         = 0;
    static const uint8_t    CAL_ALL_CHANNELS = 0x0F;
    adi_fpga9025_Device_t*  fpga9025Device   = NULL;
    adi_adrv9025_Device_t*  adrv9025Device   = NULL;
    adi_ad9528_Device_t*    ad9528Device     = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    fpga9025Device = (adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice;
    adrv9025Device = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice;
    ad9528Device   = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice;

    /* Unmask incoming sysref in FPGA framers (leave rx links untouched) */
    recoveryAction = adi_fpga9025_SysRefEnableSet(fpga9025Device,
                                                  (uint8_t)link,
                                                  0,
                                                  ADI_ENABLE);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    /* Enable/reset FPGA Framer(s) */
    recoveryAction = adi_fpga9025_FramerReset(fpga9025Device,
                                              (uint8_t)link);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

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
    recoveryAction = adi_fpga9025_SysRefEnableSet(fpga9025Device,
                                                  (uint8_t)link,
                                                  0,
                                                  ADI_DISABLE);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

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

    recoveryAction = adi_common_hal_Wait_ms(&adrv9025Device->common,
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

    /* Wait up to 60 seconds for ARM */
    recoveryAction = adi_adrv9025_InitCalsWait(adrv9025Device,
                                               60000,
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

int32_t adi_board_adrv9025_JesdRxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                         uint32_t                 link)
{
    int32_t                recoveryAction          = ADI_COMMON_ACT_NO_ACTION;
    uint8_t                sysrefEnabledForFramer2 = ADI_FALSE;
    adi_fpga9025_Device_t* fpga9025Device          = NULL;
    adi_adrv9025_Device_t* adrv9025Device          = NULL;
    adi_ad9528_Device_t*   ad9528Device            = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    fpga9025Device = (adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice;
    adrv9025Device = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice;
    ad9528Device   = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice;

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

        /* Adrv9025 Unmask incoming Sysref in Framer(s) */
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
        /* Enable/reset Adrv9025 Framer(s) */
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

        recoveryAction = adi_common_hal_Wait_ms(&adrv9025Device->common,
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

        /* Adrv9025 Unmask incoming Sysref in Framer(s) */
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

    /* Disable DFE LPM in PHY before after sys ref */
    adi_fpga9025_ChannelDfeLpmOverrideSet(fpga9025Device,
                                          0xFF,
                                          0);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    /* Wait 100ms for clock recovery on FPGA to lock */
    recoveryAction = adi_common_hal_Wait_ms(&adrv9025Device->common,
                                            100);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     adrv9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     adrv9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

    /* Enable/reset FPGA Deframer(s) */
    recoveryAction = adi_fpga9025_DeframerReset(fpga9025Device,
                                                (uint8_t)link);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    /* Disable DFE LPM in PHY before after sys ref */
    recoveryAction = adi_fpga9025_ChannelDfeLpmOverrideSet(fpga9025Device,
                                                           0xFF,
                                                           0);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    /* Unmask incoming sysref in FPGA deframers (leave tx links untouched) */
    recoveryAction = adi_fpga9025_SysRefEnableSet(fpga9025Device,
                                                  0,
                                                  (uint8_t)link,
                                                  ADI_ENABLE);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

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
        /* Adrv9025 mask sysref in Framers. Precaution against future sysref signals */
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
    recoveryAction = adi_fpga9025_SysRefEnableSet(fpga9025Device,
                                                  0,
                                                  (uint8_t)link,
                                                  ADI_DISABLE);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_board_adrv9025_JesdBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                       uint32_t                 txLinkSel,
                                       uint32_t                 rxLinkSel)
{
    int32_t                recoveryAction        = ADI_COMMON_ACT_NO_ACTION;
    uint8_t                i                     = 0;
    uint8_t                adrv9025LinkStatus    = 0;
    uint8_t                fpga9025LinkStatus    = 0;
    uint8_t                deframerLinkCondition = 0;
    adi_fpga9025_Device_t* fpga9025Device        = NULL;
    adi_adrv9025_Device_t* adrv9025Device        = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    fpga9025Device = (adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice;
    adrv9025Device = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice;

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
    recoveryAction = adi_fpga9025_SysRefEnableSet(fpga9025Device,
                                                  ADI_FPGA9025_FRAMER_ALL,
                                                  ADI_FPGA9025_DEFRAMER_ALL,
                                                  ADI_DISABLE);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    /* Disable all the FPGA framer & deframers */
    recoveryAction = adi_fpga9025_FramerDisable(fpga9025Device,
                                                ADI_FPGA9025_FRAMER_ALL);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    recoveryAction = adi_fpga9025_DeframerDisable(fpga9025Device,
                                                  ADI_FPGA9025_DEFRAMER_ALL);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

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
    recoveryAction = adi_fpga9025_ChannelDfeLpmOverrideSet(fpga9025Device,
                                                           0xFF,
                                                           1);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    if (rxLinkSel != 0)
    {
        /* Bring up the Rx links */
        recoveryAction = adi_board_adrv9025_JesdRxBringup(trxDaughterboard,
                                                          rxLinkSel);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        if (fpga9025Device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
        {
            recoveryAction = adi_fpga9025_Jesd204CDeframerCmdDataSet(fpga9025Device,
                                                                     rxLinkSel,
                                                                     ADI_ENABLE,
                                                                     ADI_ENABLE);
            ADI_ERROR_REPORT(&fpga9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             fpga9025Device->common.error.errCode,
                             recoveryAction,
                             NULL,
                             fpga9025Device->common.error.errormessage);
            ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);
        }
    }

    if (txLinkSel != 0)
    {
        /* Bring up the Tx links */
        recoveryAction = adi_board_adrv9025_JesdTxBringup(trxDaughterboard,
                                                          txLinkSel);
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         adrv9025Device->common.error.errCode,
                         recoveryAction,
                         NULL,
                         adrv9025Device->common.error.errormessage);
        ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);

        if (fpga9025Device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
        {
            recoveryAction = adi_fpga9025_Jesd204CFramerCmdDataSet(fpga9025Device,
                                                                   txLinkSel,
                                                                   ADI_ENABLE,
                                                                   ADI_ENABLE);
            ADI_ERROR_REPORT(&fpga9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             fpga9025Device->common.error.errCode,
                             recoveryAction,
                             NULL,
                             fpga9025Device->common.error.errormessage);
            ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);
        }
    }

    /* Adrv9025 Deframer Status get*/
    for (i = 0; i < 2; i++)
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
    recoveryAction = adi_fpga9025_DeframerStatusGet(fpga9025Device,
                                                    rxLinkSel,
                                                    &fpga9025LinkStatus);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     fpga9025Device->common.error.errCode,
                     recoveryAction,
                     NULL,
                     fpga9025Device->common.error.errormessage);
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

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
        adi_fpga9025_FramerDisable(fpga9025Device,
                                   ADI_FPGA9025_FRAMER_ALL);
    }
    if (fpga9025LinkStatus != rxLinkSel)
    {
        recoveryAction = ADI_COMMON_ACT_ERR_RESET_INTERFACE;
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Not all Rx links have been established.");

        /* Disable all the FPGA deframers. Don't update the error though, this is just cleanup */
        adi_fpga9025_DeframerDisable(fpga9025Device,
                                     ADI_FPGA9025_DEFRAMER_ALL);
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

int32_t adi_board_adrv9025_Jesd204LinkReset(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t              recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t              i              = 0;
    uint32_t             txLinkSel      = 0;
    uint32_t             rxLinkSel      = 0;
    adi_adrv9025_Init_t* adrv9025Init   = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    adrv9025Init = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;

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
    if ((recoveryAction = adi_board_adrv9025_JesdBringup(trxDaughterboard,
                                                         txLinkSel,
                                                         rxLinkSel)) < 0)
    {
        return recoveryAction;
    }

    return 0;
}
#if 0
static int32_t adi_board_adrv9025_Fpga9025Init(adi_daughterboard_trx_t* trxDaughterboard)
{
    adi_fpga9025_Device_t* fpga9025Device = NULL;
    adi_adrv9025_Init_t*   adrv9025Init   = NULL;
    adi_fpga9025_Init_t    initSet        = {{{0}}};
    /* TODO: If above 614.4MHz, divide clock to FPGA in 9528 */
    uint32_t refClk_kHz    = 0;
    int32_t  testReturnVal = ADI_COMMON_ACT_NO_ACTION;
    int      i             = 0;
    int      j             = 0;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    fpga9025Device = (adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice;
    adrv9025Init   = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;
    refClk_kHz     = adrv9025Init->clocks.deviceClock_kHz;

    fpga9025Device->memoryPageSize = 0x40000000;

    adi_fpga9025_SetupFpgaCfg_t fpgaCfg = {0};
    fpgaCfg.deviceClk_kHz               = refClk_kHz;
    fpgaCfg.framerlink0.datamoversUsed  = 0; /*not used - remove from structure*/

    /*TODO, find first valid Rx based on rx channel mask*/
    adi_adrv9025Board_RxLinkSamplingRateFind(fpga9025Device,
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
    fpgaCfg.deframerlink0.serializerLaneCrossbar.lane0FramerOutSel = adrv9025Init->dataInterface.framer[0].serializerLaneCrossbar.lane0FramerOutSel;
    fpgaCfg.deframerlink0.serializerLaneCrossbar.lane1FramerOutSel = adrv9025Init->dataInterface.framer[0].serializerLaneCrossbar.lane1FramerOutSel;
    fpgaCfg.deframerlink0.serializerLaneCrossbar.lane2FramerOutSel = adrv9025Init->dataInterface.framer[0].serializerLaneCrossbar.lane2FramerOutSel;
    fpgaCfg.deframerlink0.serializerLaneCrossbar.lane3FramerOutSel = adrv9025Init->dataInterface.framer[0].serializerLaneCrossbar.lane3FramerOutSel;
    adi_adrv9025Board_RxLinkSamplingRateFind(fpga9025Device,
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
    fpgaCfg.deframerlink1.serializerLaneCrossbar.lane0FramerOutSel = adrv9025Init->dataInterface.framer[1].serializerLaneCrossbar.lane0FramerOutSel;
    fpgaCfg.deframerlink1.serializerLaneCrossbar.lane1FramerOutSel = adrv9025Init->dataInterface.framer[1].serializerLaneCrossbar.lane1FramerOutSel;
    fpgaCfg.deframerlink1.serializerLaneCrossbar.lane2FramerOutSel = adrv9025Init->dataInterface.framer[1].serializerLaneCrossbar.lane2FramerOutSel;
    fpgaCfg.deframerlink1.serializerLaneCrossbar.lane3FramerOutSel = adrv9025Init->dataInterface.framer[1].serializerLaneCrossbar.lane3FramerOutSel;

    adi_adrv9025Board_RxLinkSamplingRateFind(fpga9025Device,
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
    fpgaCfg.deframerlink2.serializerLaneCrossbar.lane0FramerOutSel = adrv9025Init->dataInterface.framer[2].serializerLaneCrossbar.lane0FramerOutSel;
    fpgaCfg.deframerlink2.serializerLaneCrossbar.lane1FramerOutSel = adrv9025Init->dataInterface.framer[2].serializerLaneCrossbar.lane1FramerOutSel;
    fpgaCfg.deframerlink2.serializerLaneCrossbar.lane2FramerOutSel = adrv9025Init->dataInterface.framer[2].serializerLaneCrossbar.lane2FramerOutSel;
    fpgaCfg.deframerlink2.serializerLaneCrossbar.lane3FramerOutSel = adrv9025Init->dataInterface.framer[2].serializerLaneCrossbar.lane3FramerOutSel;

    adi_adrv9025Board_TxLinkSamplingRateFind(fpga9025Device,
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

    adi_adrv9025Board_TxLinkSamplingRateFind(fpga9025Device,
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

    /* Setup the serializer lane swaps for this board (index maps to DUT lane; value is corresponding FPGA lane) */
    initSet.datapath.pcbSerLaneSwap[0] = 3;
    initSet.datapath.pcbSerLaneSwap[1] = 2;
    initSet.datapath.pcbSerLaneSwap[2] = 1;
    initSet.datapath.pcbSerLaneSwap[3] = 0;
    initSet.datapath.pcbSerLaneSwap[4] = 7;
    initSet.datapath.pcbSerLaneSwap[5] = 7;
    initSet.datapath.pcbSerLaneSwap[6] = 7;
    initSet.datapath.pcbSerLaneSwap[7] = 7;

    initSet.datapath.serLanePnInvert[0] = 0;
    initSet.datapath.serLanePnInvert[1] = 1;
    initSet.datapath.serLanePnInvert[2] = 0;
    initSet.datapath.serLanePnInvert[3] = 1;
    initSet.datapath.serLanePnInvert[4] = 0;
    initSet.datapath.serLanePnInvert[5] = 0;
    initSet.datapath.serLanePnInvert[6] = 0;
    initSet.datapath.serLanePnInvert[7] = 0;

    /* Setup the deserializer lane swaps for this board */
    initSet.datapath.pcbDesLaneSwap[0] = 1;
    initSet.datapath.pcbDesLaneSwap[1] = 0;
    initSet.datapath.pcbDesLaneSwap[2] = 2;
    initSet.datapath.pcbDesLaneSwap[3] = 3;
    initSet.datapath.pcbDesLaneSwap[4] = 7;
    initSet.datapath.pcbDesLaneSwap[5] = 7;
    initSet.datapath.pcbDesLaneSwap[6] = 7;
    initSet.datapath.pcbDesLaneSwap[7] = 7;

    initSet.datapath.desLanePnInvert[0] = 1;
    initSet.datapath.desLanePnInvert[1] = 1;
    initSet.datapath.desLanePnInvert[2] = 1;
    initSet.datapath.desLanePnInvert[3] = 1;
    initSet.datapath.desLanePnInvert[4] = 1;
    initSet.datapath.desLanePnInvert[5] = 1;
    initSet.datapath.desLanePnInvert[6] = 1;
    initSet.datapath.desLanePnInvert[7] = 1;

    testReturnVal = adi_fpga9025_InitConfig(fpga9025Device,
                                            &fpgaCfg,
                                            &initSet);
    if (testReturnVal != 0)
    {
        return testReturnVal;
    }

    // setup the bank id's for framers based on config
    for (i = 0; i < ADI_FPGA9025_NUM_OF_FRAMERS; i++)
    {
        initSet.datapath.framerCfg[i].bankId = adrv9025Init->dataInterface.deframer[i].bankId;
    }
    // setup the bank id's for deframers based on config
    for (i = 0; i < ADI_FPGA9025_NUM_OF_DEFRAMERS; i++)
    {
        for (j = 0; j < ADI_FPGA9025_NUM_LANES; j++)
        {
            initSet.datapath.deframerCfg[i].bankId[j] = adrv9025Init->dataInterface.framer[i].bankId;
        }
    }
    initSet.clocks.qpll.quadSelect = ADI_FPGA9025_QPLL_QUAD0;

    testReturnVal = adi_fpga9025_InitSet(fpga9025Device,
                                         &initSet);
    if (testReturnVal != 0)
    {
        return testReturnVal;
    }

    return ADI_COMMON_ACT_NO_ACTION;
}
#endif
int32_t adi_board_adrv9025_Program_Phase1(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t                            recoveryAction        = ADI_COMMON_ACT_NO_ACTION;
    //adi_fpga9025_AxiAdvSpiFeatConfig_t fpgaAdvSpiCfg         = {0};
    //adi_fpga9025_Device_t*             fpga9025Device        = NULL;
    adi_adrv9025_Init_t*               adrv9025Init          = NULL;
    adi_adrv9025_Device_t*             adrv9025Device        = NULL;
    adi_adrv9025_PlatformFiles_t*      adrv9025PlatformFiles = NULL;

    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }
#if 0
    fpgaAdvSpiCfg.enable            = 1;
    fpgaAdvSpiCfg.cpha              = 0;
    fpgaAdvSpiCfg.cpol              = 0;
    fpgaAdvSpiCfg.lsbFirst          = 0;
    fpgaAdvSpiCfg.fourWire          = 1;
    fpgaAdvSpiCfg.misoSampleSlip    = 1;
    fpgaAdvSpiCfg.threeWireTriPoint = 16;
    fpgaAdvSpiCfg.clockDiv          = 1;

    fpga9025Device        = (adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice;
#endif
    adrv9025Init          = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;
    adrv9025Device        = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice;
    adrv9025PlatformFiles = (adi_adrv9025_PlatformFiles_t *)trxDaughterboard->platformFilesInit;
#if 0
    /* AD9528: 25Mhz SPICLK, but with SPIDO clocked half clock cycle later for improved setup.hold */
    recoveryAction = adi_fpga9025_AxiAdvSpiCfgSet(fpga9025Device,
                                                  &fpgaAdvSpiCfg,
                                                  0);
    if (recoveryAction != 0)
    {
        return recoveryAction;
    }

    /* ADRV9025: 25Mhz SPICLK, but with SPIDO clocked half clock cycle later for improved setup.hold */
    recoveryAction = adi_fpga9025_AxiAdvSpiCfgSet(fpga9025Device,
                                                  &fpgaAdvSpiCfg,
                                                  1);
    if (recoveryAction != 0)
    {
        return recoveryAction;
    }

    /* Reset FPGA MMCM to prevent lock up issues when switching FPGA refClk values */
    recoveryAction = adi_fpga9025_MmcmResetSet(fpga9025Device,
                                               ADI_FPGA9025_CORE_MMCM);
    ADI_ERROR_REPORT(&fpga9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error resetting clock wizard");
    ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);

    /* Init Ad9528 */
    if ((recoveryAction = adi_board_adrv9025_Ad9528Init(trxDaughterboard)) != ADI_COMMON_ACT_NO_ACTION)
    {
        ADI_ERROR_REPORT(&trxDaughterboard->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_API_FAIL, recoveryAction, NULL, "Init Ad9528");
        ADI_ERROR_RETURN(recoveryAction);
    }

    

    // CE and EE board use the same adi_board_adrv9025_Fpga9025Init()
    if ((recoveryAction = adi_board_adrv9025_Fpga9025Init(trxDaughterboard)) != 0)
    {
        ADI_ERROR_REPORT(&trxDaughterboard->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_API_FAIL, recoveryAction, NULL, "Init FPGA");
        ADI_ERROR_RETURN(recoveryAction);
    }

#endif    

    /* Reset Hardware */
    recoveryAction = adi_adrv9025_HwReset(adrv9025Device);
    printf("%s %d, recoveryAction = %d\n",__func__,__LINE__,recoveryAction);
    ADI_ERROR_REPORT(&adrv9025Device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_API_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to Reset Adrv9025 device");
    ADI_ERROR_RETURN(adrv9025Device->common.error.newAction);
#if 0
    /* Custom Step for ADI eval card to read ADRV9025 internal LDO bypass setting from the eval boards EEPROM to make sure the
     * silicon is not accidentally damaged.  ADI stores this in a custom FMC EEPROM field used for the BOM revision of the PCB */
    if ((recoveryAction = adi_adrv9025Board_LdoSelectOverRide(adrv9025Init)) != ADI_COMMON_ACT_NO_ACTION)
    {
        ADI_ERROR_REPORT(&adrv9025Device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to perform Ldo Select override");
        ADI_ERROR_RETURN(recoveryAction);
    }
#endif
    /* Pre MCS - Broadcastable */
    if ((recoveryAction = adi_adrv9025_PreMcsInit_v2(adrv9025Device,
                                                     adrv9025Init,
                                                     adrv9025PlatformFiles->armImageFile,
                                                     adrv9025PlatformFiles->streamImageFile,
                                                     adrv9025PlatformFiles->rxGainTableFileArr,
                                                     adrv9025PlatformFiles->rxGainTableFileArrSize,
                                                     adrv9025PlatformFiles->txAttenTableFileArr,
                                                     adrv9025PlatformFiles->txAttenTableFileArrSize)) != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("%s %d, recoveryAction = %d\n",__func__,__LINE__,recoveryAction);
        return recoveryAction;
    }

    /* Pre MCS - Non-Broadcastable */
    if ((recoveryAction = adi_adrv9025_PreMcsInit_NonBroadCast(adrv9025Device,
                                                               adrv9025Init)) != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("%s %d, recoveryAction = %d\n",__func__,__LINE__,recoveryAction);
        return recoveryAction;
    }

    return 0;
}

int32_t adi_board_adrv9025_Program_Phase2(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t                     recoveryAction      = ADI_COMMON_ACT_NO_ACTION;
    //uint32_t                    mcsStatus           = 0;
    //uint8_t                     i                   = 0;
    //uint32_t                    txLinkSel           = 0;
    //uint32_t                    rxLinkSel           = 0;
    adi_adrv9025_Device_t*      adrv9025Device      = NULL;
    //adi_ad9528_Device_t*        ad9528Device        = NULL;
    adi_adrv9025_PostMcsInit_t* adrv9025PostMcsInit = NULL;
    adi_adrv9025_Init_t*        adrv9025Init        = NULL;
    
    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    adrv9025Device      = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice;
    //ad9528Device        = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice;
    adrv9025PostMcsInit = (adi_adrv9025_PostMcsInit_t *)trxDaughterboard->postMcsInit;
    adrv9025Init        = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;
#if 0
    /* MCS start sequence*/
    if ((recoveryAction = adi_adrv9025_MultichipSyncSet(adrv9025Device,
                                                        ADI_ENABLE)) < 0)
    {
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to perform MCS");
        ADI_ERROR_RETURN(recoveryAction);
    }

    /* This loop will send SysRef pulses up to 255 times unless MCS status achieved before. */
    for (i = 0; i < 255; i++)
    {
        if ((recoveryAction = adi_ad9528_SysrefRequest(ad9528Device,
                                                       1)) != 0)
        {
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_API_FAIL,
                             recoveryAction,
                             NULL,
                             "SysRef Request Failed");
            ADI_ERROR_RETURN(recoveryAction);
        }
        else
        {
            if ((recoveryAction = adi_adrv9025_MultichipSyncStatusGet(adrv9025Device,
                                                                      &mcsStatus)) != 0)
            {
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_API_FAIL,
                                 recoveryAction,
                                 NULL,
                                 "Unable to Get MCS status");
                ADI_ERROR_RETURN(recoveryAction);
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

    if (mcsStatus != 0x17)
    {
        /*perror("ADRV9025 CLKPLL MCS status not correct\n");*/
        /*TODO : Add error message once there is error reporting added at the board level*/
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         ADI_COMMON_ACT_ERR_RESET_FULL,
                         NULL,
                         "Unable to perform MCS");
        ADI_ERROR_RETURN(ADI_COMMON_ACT_ERR_RESET_FULL);
    }

    /* MCS end sequence*/
    if ((recoveryAction = adi_adrv9025_MultichipSyncSet(adrv9025Device,
                                                        ADI_DISABLE)) < 0)
    {
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to set MCS state");
        ADI_ERROR_RETURN(recoveryAction);
    }
#endif
    /* Post MCS */
    if ((recoveryAction = adi_adrv9025_PostMcsInit(adrv9025Device,
                                                   adrv9025PostMcsInit)) < 0)
    {
        printf("%s %d, recoveryAction = %d\n",__func__,__LINE__,recoveryAction);
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Unsable to Get MCS status");
		adrv9025Device->common.error.newAction = ADI_COMMON_ACT_NO_ACTION;
        //ADI_ERROR_RETURN(recoveryAction);
    }
#if 0
    if ((recoveryAction = adi_adrv9025_SerializerReset(adrv9025Device,
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
    if ((recoveryAction = adi_board_adrv9025_JesdBringup(trxDaughterboard,
                                                         txLinkSel,
                                                         rxLinkSel)) < 0)
    {
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "JESD204 link bring up fail");
        ADI_ERROR_RETURN(recoveryAction);
    }
#endif
    /* Initialize Tx Ramp down functionality */
    if ((recoveryAction = adi_adrv9025_TxRampDownInit(adrv9025Device,
                                                      adrv9025Init) < 0))
    {
        printf("%s %d, recoveryAction = %d\n",__func__,__LINE__,recoveryAction);
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL, 
                         "Initialize Tx Ramp down functionality fail");
        ADI_ERROR_RETURN(recoveryAction);
    }

    /* Setup GP Interrupts from init structure */
    if ((recoveryAction = adi_adrv9025_GpIntInit(adrv9025Device,
                                                 &adrv9025Init->gpInterrupts) < 0))
    {
        printf("%s %d, recoveryAction = %d\n",__func__,__LINE__,recoveryAction);
        ADI_ERROR_REPORT(&trxDaughterboard->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_API_FAIL,
                         recoveryAction,
                         NULL,
                         "Setup GP Interrupts from init structure fail");
        ADI_ERROR_RETURN(recoveryAction);
    }

    return 0;
}

int32_t adi_adrv9025Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                   adrvtrx_board_action_e   actionFlags)
{
    #define BOARD_LAYER_ERROR_SIZE_BYTES 1000u /* Match ARGB_SIZE_BYTES size*/
    int32_t                recoveryAction = ADI_COMMON_HAL_OK;
    adi_common_Device_t*   commonDev      = NULL;
    //adi_adrv9025_Device_t* adrv9025Device = NULL;
    //adi_fpga9010_Device_t* fpga9010Device = NULL;
    //adi_ad9528_Device_t*   ad9528Device   = NULL;
    //uint32_t               txLinkSel      = 0;
    //uint32_t               rxLinkSel      = 0;
    char errorStr[BOARD_LAYER_ERROR_SIZE_BYTES] = { 0 };

    if ((trxDaughterboard == NULL) || (actionFlags == 0))
    {
        return ADI_COMMON_HAL_GEN_SW;
    }

    //ad9528Device   = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice;
    //adrv9025Device = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice;
    //fpga9010Device = (adi_fpga9010_Device_t *)trxDaughterboard->fpgaDevice;

    /* Device allocation */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_ALLOC)
    {
        /* Only allocate if it is not already there */
        if ((trxDaughterboard->boardAttribute & TRX_DAUGHTERBOARD_ATTRIBUTE_PREALLOCATE_TRX_DEVICE) > 0)
        {
            if (trxDaughterboard->trxDevice == 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                       __func__,
                       __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                ADI_COMMON_ERRSRC_ADI_HAL,
                                ADI_COMMON_HAL_GEN_SW,
                                recoveryAction,
                                NULL,
                                "Device allocation fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else
        {
            if (trxDaughterboard->trxDevice == 0)
            {
                trxDaughterboard->trxDevice = (uintptr_t)calloc(1,
                                                                sizeof(adi_adrv9025_Device_t));
            }
        }

        /* Ensure daughterboard is allocated */
        if (trxDaughterboard->trxDevice == 0)
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                       __func__,
                       __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                            ADI_COMMON_ERRSRC_ADI_HAL,
                            ADI_COMMON_HAL_GEN_SW,
                            recoveryAction,
                            NULL,
                            "Device allocation fail");
            ADI_ERROR_RETURN(recoveryAction);
        }

        /* Assigning Abstract pointers */
        trxDaughterboard->trxAbstractDev.commonAbstractDevice = (adi_common_Device_t *)trxDaughterboard->trxDevice;
        trxDaughterboard->trxAbstractDev.trxAbstractDevice    = trxDaughterboard->trxDevice;

        return (ADI_COMMON_HAL_OK);
    }

    /* HW Open */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_HWOPEN)
    {
        adi_adrv9025_SpiSettings_t spiSettings = {
            .msbFirst = 1,
            .enSpiStreaming = 0,
            .autoIncAddrUp = 1,
            .fourWireMode = 1,
            .cmosPadDrvStrength = ADI_ADRV9025_CMOSPAD_DRV_STRONG,
        };

        commonDev = trxDaughterboard->trxAbstractDev.commonAbstractDevice;
        if ((recoveryAction = adi_adrv9025_HwOpen((adi_adrv9025_Device_t *)trxDaughterboard->trxDevice,
                                                  &spiSettings)) != (int32_t)ADI_COMMON_HAL_OK)
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n",
                   __func__,
                   __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_ADI_HAL,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "Device open fail");
            ADI_ERROR_RETURN(recoveryAction);
        }
        commonDev->error.logEnable = ADI_ENABLE;

        /* Clear any previous board Errors */
        if (commonDev != NULL)
        {
            if ((recoveryAction = adi_common_ErrorClear(commonDev)) != ADI_COMMON_ACT_NO_ACTION)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "Error Clear fail");
                ADI_ERROR_RETURN(recoveryAction);
            }  
        }

        return (ADI_COMMON_HAL_OK);
    }

    /* HW Close */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_HWCLOSE)
    {
        commonDev = trxDaughterboard->trxAbstractDev.commonAbstractDevice;
        if ((recoveryAction = adi_adrv9025_HwClose((adi_adrv9025_Device_t *)trxDaughterboard->trxDevice)) != (int32_t)ADI_COMMON_HAL_OK)
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n",
                __func__,
                __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_ADI_HAL,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "HW close fail");
            ADI_ERROR_RETURN(recoveryAction);
        }
        adi_hal_DevHalCfgFree(commonDev->devHalInfo);

        return (ADI_COMMON_HAL_OK);
    }
#if 0
    /*Clock Config */
    if (actionFlags == TRX_BOARD_ACTION_CLOCK_CONFIG)
    {
        uint32_t deviceClock_kHz = trxDaughterboard->parameterBucket[0];
        uint32_t vcxoFreq_kHz    = trxDaughterboard->parameterBucket[1];
        uint32_t refAFreq_kHz    = trxDaughterboard->parameterBucket[2];
        uint32_t fpgaClock_kHz   = trxDaughterboard->parameterBucket[3];

        if ((recoveryAction = adi_board_adrv9025_Ad9528Configure(trxDaughterboard,
                                                                 deviceClock_kHz,
                                                                 vcxoFreq_kHz,
                                                                 refAFreq_kHz,
                                                                 fpgaClock_kHz)) != ADI_COMMON_ACT_NO_ACTION)
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n",
                __func__,
                __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "Clock config fail");
            ADI_ERROR_RETURN(recoveryAction);
        }

        return (ADI_COMMON_HAL_OK);
    }

    /* JESD Bringup */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_JESD_BRINGUP)
    {
        txLinkSel = trxDaughterboard->parameterBucket[0];
        rxLinkSel = trxDaughterboard->parameterBucket[1];

        if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
        {
            /* JESD204 link bring up */
            if ((recoveryAction = adi_board_adrv9025_JesdBringup(trxDaughterboard,
                                                                 txLinkSel,
                                                                 rxLinkSel)) < 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD bring up fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
        {
            /* JESD204 link bring up */
            if ((recoveryAction = adi_board_adrv9025ADS8_JesdBringup(adrv9025Device,
                                                                     fpga9010Device,
                                                                     ad9528Device,
                                                                     txLinkSel,
                                                                     rxLinkSel)) < 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD bring up fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }

        return (ADI_COMMON_HAL_OK);
    }

    /* JESD204 tx link bring up */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_JESD_TX_BRINGUP)
    {
        txLinkSel = trxDaughterboard->parameterBucket[0];

        if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
        {
            /* JESD204 rx link bring up */
            if ((recoveryAction = adi_board_adrv9025_JesdTxBringup(trxDaughterboard,
                                                                   txLinkSel)) < 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD Tx bring up fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
        {
            /* JESD204 rx link bring up */
            if ((recoveryAction = adi_board_adrv9025ADS8_JesdTxBringup(adrv9025Device,
                                                                       fpga9010Device,
                                                                       ad9528Device,
                                                                       txLinkSel)) < 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD Tx bring up fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }

        return (ADI_COMMON_HAL_OK);
    }

    /* JESD204 rx link bring up */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_JESD_RX_BRINGUP)
    {
        rxLinkSel = trxDaughterboard->parameterBucket[0];

        if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
        {
            /* JESD204 rx link bring up */
            if ((recoveryAction = adi_board_adrv9025_JesdRxBringup(trxDaughterboard,
                                                                   rxLinkSel)) < 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD Rx bring up fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
        {
            /* JESD204 rx link bring up */
            if ((recoveryAction = adi_board_adrv9025ADS8_JesdRxBringup(adrv9025Device,
                                                                       fpga9010Device,
                                                                       ad9528Device,
                                                                       rxLinkSel)) < 0)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD Rx bring up fail");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }

        return (ADI_COMMON_HAL_OK);
    }

    if (actionFlags == TRX_BOARD_ACTION_DEVICE_AD9528_INIT)
    {
        if ((recoveryAction = adi_board_adrv9025_Ad9528Init(trxDaughterboard)) < 0)
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n", __func__, __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_ADI_HAL,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "Ad9528Init has failed");
            ADI_ERROR_RETURN(recoveryAction);
        }

        return (ADI_COMMON_HAL_OK);
    }

    if (actionFlags == TRX_BOARD_ACTION__FPGA__INIT)
    {
        if ((recoveryAction = adi_board_adrv9025_Fpga9025Init(trxDaughterboard)) < 0)
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n", __func__, __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_ADI_HAL,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "Fpga9025Init has failed");
            ADI_ERROR_RETURN(recoveryAction);
        }

        return (ADI_COMMON_HAL_OK);
    }
#endif    
    /* Phase 1 */
    if (actionFlags == TRX_BOARD_ACTION_PHASE_1)
    {
        adi_adrv9025_Init_t*          adrv9025Init          = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;
        //adi_adrv9025_PlatformFiles_t* adrv9025PlatformFiles = (adi_adrv9025_PlatformFiles_t *)trxDaughterboard->platformFilesInit;
        //adi_ad9528_Init_t*            ad9528Init            = (adi_ad9528_Init_t *)trxDaughterboard->clockInit;
        trxDaughterboard->savedInfo.enable204cState         = adrv9025Init->dataInterface.deframer[0].enableJesd204C;
#if 0
        /* Initialize FGPGA */
        recoveryAction = trxDaughterboard->FpgaDispatch(trxDaughterboard,
                                                        TRX_BOARD_ACTION_FPGA_INIT);
        if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
        {
            printf("FPGA 9025 initialization failed.\n");
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n",
                __func__,
                __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_ADI_HAL,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "FPGA Init fail");
            ADI_ERROR_RETURN(recoveryAction);
        }
#endif
        if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
        {
            if ((recoveryAction = adi_board_adrv9025_Program_Phase1(trxDaughterboard)) != ADI_COMMON_ACT_NO_ACTION)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.recoveryAction = %d\n",
                    __func__,
                    __LINE__,
                    recoveryAction);

                if (trxDaughterboard->common.error.errCode != ADI_COMMON_ACT_NO_ACTION)
                {
                    sprintf(errorStr, "ERROR-Phase1 fail: DaughterBoard Error - %d, %s\n", trxDaughterboard->common.error.errCode, trxDaughterboard->common.error.errormessage);
                }
                else
                {
                    sprintf(errorStr, "ERROR-Phase1 fail: No DaughterBoard Error\n");
                }

                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 errorStr);
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
        {
        #if 0
            if ((trxDaughterboard->daughterCardId >= ADI_BOARD_9025_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9025_MAX))
            {
                adi_board_adrv9025Ads8_t boardADS8 =
                {
                    .adrv9025Device = adrv9025Device,
                    .fpgaDevice = fpga9010Device,
                    .ad9528Device = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice
                };
                if ((recoveryAction = adi_board_adrv9025ADS8_Program_Phase1(&boardADS8,
                                                                            adrv9025Init,
                                                                            ad9528Init,
                                                                            adrv9025PlatformFiles)) != ADI_COMMON_ACT_NO_ACTION)
                {
                    recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                    printf("ERROR: %s:%u has failed.\n",
                        __func__,
                        __LINE__);

                    if (trxDaughterboard->common.error.errCode != ADI_COMMON_ACT_NO_ACTION)
                    {
                        sprintf(errorStr, "ERROR-Phase1 fail: DaughterBoard Error - %d, %s\n", trxDaughterboard->common.error.errCode, trxDaughterboard->common.error.errormessage);
                    }
                    else
                    {
                        sprintf(errorStr, "ERROR-Phase1 fail: No DaughterBoard Error\n");
                    }

                    ADI_ERROR_REPORT(&trxDaughterboard->common,
                                     ADI_COMMON_ERRSRC_ADI_HAL,
                                     ADI_COMMON_HAL_GEN_SW,
                                     recoveryAction,
                                     NULL,
                                     errorStr);
                    ADI_ERROR_RETURN(recoveryAction);
                }
            }
		#endif
        }
        else
        {
            recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
            printf("ERROR: %s:%u has failed.\n",
                __func__,
                __LINE__);
            ADI_ERROR_REPORT(&trxDaughterboard->common,
                             ADI_COMMON_ERRSRC_ADI_HAL,
                             ADI_COMMON_HAL_GEN_SW,
                             recoveryAction,
                             NULL,
                             "Phase 1 fail");
            ADI_ERROR_RETURN(recoveryAction);
        }

        return (ADI_COMMON_HAL_OK);
    }

    /* Phase 2 */
    if (actionFlags == TRX_BOARD_ACTION_PHASE_2)
    {
       // adi_adrv9025_Init_t*        adrv9025Init        = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;
        //adi_adrv9025_PostMcsInit_t* adrv9025PostMcsInit = (adi_adrv9025_PostMcsInit_t *)trxDaughterboard->postMcsInit;
        //adi_ad9528_Init_t*          ad9528Init          = (adi_ad9528_Init_t *)trxDaughterboard->clockInit;

        /* Proceed to the next board specific phase */
        if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
        {
            if ((recoveryAction = adi_board_adrv9025_Program_Phase2(trxDaughterboard)) != ADI_COMMON_ACT_NO_ACTION)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);

                if (trxDaughterboard->common.error.errCode != ADI_COMMON_ACT_NO_ACTION)
                {
                    sprintf(errorStr, "ERROR-Phase2 fail: DaughterBoard Error - %d, %s\n", trxDaughterboard->common.error.errCode, trxDaughterboard->common.error.errormessage);
                }
                else
                {
                    sprintf(errorStr, "ERROR-Phase2 fail: No DaughterBoard Error\n");
                }

                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                ADI_COMMON_ERRSRC_ADI_HAL,
                                ADI_COMMON_HAL_GEN_SW,
                                recoveryAction,
                                NULL,
                                errorStr);
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
        {
        #if 0
            fpga9010Device = (adi_fpga9010_Device_t *)trxDaughterboard->fpgaDevice;
            if ((trxDaughterboard->daughterCardId == ADI_BOARD_9025CE01) || (trxDaughterboard->daughterCardId == ADI_BOARD_9025EE01))
            {
                adi_board_adrv9025Ads8_t boardADS8 =
                {
                    .adrv9025Device = adrv9025Device,
                    .fpgaDevice = fpga9010Device,
                    .ad9528Device = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice
                };
                if ((recoveryAction = adi_board_adrv9025ADS8_Program_Phase2(&boardADS8,
                                                                            adrv9025Init,
                                                                            adrv9025PostMcsInit,
                                                                            ad9528Init)) != ADI_COMMON_ACT_NO_ACTION)
                {
                    recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                    printf("ERROR: %s:%u has failed.\n",
                        __func__,
                        __LINE__);

                    if (trxDaughterboard->common.error.errCode != ADI_COMMON_ACT_NO_ACTION)
                    {
                        sprintf(errorStr, "ERROR-Phase2 fail: DaughterBoard Error - %d, %s\n", trxDaughterboard->common.error.errCode, trxDaughterboard->common.error.errormessage);
                    }
                    else
                    {
                        sprintf(errorStr, "ERROR-Phase2 fail: No DaughterBoard Error\n");
                    }

                    ADI_ERROR_REPORT(&trxDaughterboard->common,
                                     ADI_COMMON_ERRSRC_ADI_HAL,
                                     ADI_COMMON_HAL_GEN_SW,
                                     recoveryAction,
                                     NULL,
                                     errorStr);
                    ADI_ERROR_RETURN(recoveryAction);
                }
            }
		#endif
        }
        else
        {
            return ADI_COMMON_HAL_GEN_SW;
        }
    }

    /* JESD Data Interface Reset */
    if (actionFlags == TRX_BOARD_ACTION_DATA_INTF_RESET)
    {
        adi_adrv9025_Init_t* adrv9025Init = (adi_adrv9025_Init_t *)trxDaughterboard->daughterCardInit;

        if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
        {
            if ((trxDaughterboard->daughterCardId == ADI_BOARD_9025CE01) || (trxDaughterboard->daughterCardId == ADI_BOARD_9025EE01))
            {
                if ((recoveryAction = adi_board_adrv9025_Jesd204LinkReset(trxDaughterboard)) != ADI_COMMON_ACT_NO_ACTION)
                {
                    recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                    printf("ERROR: %s:%u has failed.\n",
                        __func__,
                        __LINE__);
                    ADI_ERROR_REPORT(&trxDaughterboard->common,
                                     ADI_COMMON_ERRSRC_ADI_HAL,
                                     ADI_COMMON_HAL_GEN_SW,
                                     recoveryAction,
                                     NULL,
                                     "JESD Data Interface Reset");
                    ADI_ERROR_RETURN(recoveryAction);
                }
            }
        }
        else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
        {
            adi_board_adrv9025Ads8_t board9025 =
            {
                .adrv9025Device = (adi_adrv9025_Device_t *)trxDaughterboard->trxDevice,
                .fpgaDevice = (adi_fpga9010_Device_t *)trxDaughterboard->fpgaDevice,
                .ad9528Device = (adi_ad9528_Device_t *)trxDaughterboard->clockDevice
            };

            if ((recoveryAction = adi_board_adrv9025ADS8_Jesd204LinkReset(&board9025,
                                                                          adrv9025Init)) != ADI_COMMON_ACT_NO_ACTION)
            {
                recoveryAction = ADI_COMMON_ACT_ERR_RESET_FULL;
                printf("ERROR: %s:%u has failed.\n",
                    __func__,
                    __LINE__);
                ADI_ERROR_REPORT(&trxDaughterboard->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 ADI_COMMON_HAL_GEN_SW,
                                 recoveryAction,
                                 NULL,
                                 "JESD Data Interface Reset");
                ADI_ERROR_RETURN(recoveryAction);
            }
        }
        else
        {
            return ADI_COMMON_ACT_ERR_CHECK_PARAM;
        }

        return (ADI_COMMON_HAL_OK);
    }

    return (ADI_COMMON_HAL_OK);
}
