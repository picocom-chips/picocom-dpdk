/**
 * \file adi_board_trx_dev.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_daughterboard_trx_dev.h"
#include <stdlib.h>
#include <string.h>

extern int32_t adi_adrv9025Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                          adrvtrx_board_action_e   actionFlags);

extern int32_t adi_adrv9010Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                          adrvtrx_board_action_e   actionFlags);

extern int32_t adi_fpga9025Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                          adrvtrx_board_action_e   actionFlags);

extern int32_t adi_fpga9010Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                          adrvtrx_board_action_e   actionFlags);

extern int32_t adi_clock9528Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                           adrvtrx_board_action_e   actionFlags);

int32_t adi_daughterboard_Create(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_HAL_OK;
    if (trxDaughterboard == NULL)
    {
        return (ADI_COMMON_HAL_GEN_SW);
    }
#if 0
    // Memory allocation for clock device.
    trxDaughterboard->ClockDispatch = adi_clock9528Board_Dispatch;
    recoveryAction                  = trxDaughterboard->ClockDispatch(trxDaughterboard,
                                                                      TRX_BOARD_ACTION_DEVICE_ALLOC);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        if (trxDaughterboard->clockDevice)
        {
            free((void *)trxDaughterboard->clockDevice);
        }
        return (ADI_COMMON_HAL_GEN_SW);
    }
#endif
#if !defined(ADRV9025) && !defined(ADRV9010)
    if ((trxDaughterboard->daughterCardId >= ADI_BOARD_9025_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9025_MAX))
    {
        trxDaughterboard->BoardDispatch = adi_adrv9025Board_Dispatch;
    }
    else if ((trxDaughterboard->daughterCardId >= ADI_BOARD_9010_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9010_MAX))
    {
        trxDaughterboard->BoardDispatch = adi_adrv9010Board_Dispatch;
    }

    /* Set up FPGA Device Dispatch pointer */
    if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
    {
        trxDaughterboard->FpgaDispatch = adi_fpga9025Board_Dispatch;
    }
    else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
    {
        trxDaughterboard->FpgaDispatch = adi_fpga9010Board_Dispatch;
    }
        
    else
    {
        return (ADI_COMMON_HAL_GEN_SW);
    }
#elif defined(ADRV9025)
    printf("daughterCardId = %d \n",trxDaughterboard->daughterCardId);
    if ((trxDaughterboard->daughterCardId >= ADI_BOARD_9025_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9025_MAX))
    {
        trxDaughterboard->BoardDispatch = adi_adrv9025Board_Dispatch;
    }
#if 0
    /* Set up FPGA Device Dispatch pointer */
    if (trxDaughterboard->motherboardId == ADI_ADS9_PLATFORM)
    {
        trxDaughterboard->FpgaDispatch = adi_fpga9025Board_Dispatch;
    }
    else if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
    {
        trxDaughterboard->FpgaDispatch = adi_fpga9010Board_Dispatch;
    }        
    else
    {
        return (ADI_COMMON_HAL_GEN_SW);
    }
#endif
#elif defined(ADRV9010)
    if ((trxDaughterboard->daughterCardId >= ADI_BOARD_9010_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9010_MAX))
    {
        trxDaughterboard->BoardDispatch = adi_adrv9010Board_Dispatch;
    }
    /* Set up FPGA Device Dispatch pointer */
    if (trxDaughterboard->motherboardId == ADI_ADS8_PLATFORM)
    {
        trxDaughterboard->FpgaDispatch = adi_fpga9010Board_Dispatch;
    }
        
    else
    {
        return (ADI_COMMON_HAL_GEN_SW);
    }
#endif

    // Memory allocation for board device.
    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DEVICE_ALLOC);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        if (trxDaughterboard->clockDevice)
        {
            free((void *)trxDaughterboard->clockDevice);
        }

        if (trxDaughterboard->trxDevice)
        {
            free((void *)trxDaughterboard->trxDevice);
        }
        return (ADI_COMMON_HAL_GEN_SW);
    }
#if 0
    /* Memory allocation for FPGA device. FPGA is platform dependent */
    recoveryAction = trxDaughterboard->FpgaDispatch(trxDaughterboard,
                                                    TRX_BOARD_ACTION_DEVICE_ALLOC);
    if ((recoveryAction != ADI_COMMON_HAL_OK) || (trxDaughterboard->fpgaDevice == 0))
    {
        if (trxDaughterboard->clockDevice)
        {
            free((void *)trxDaughterboard->clockDevice);
        }
        if (trxDaughterboard->trxDevice)
        {
            free((void *)trxDaughterboard->trxDevice);
        }
        if (trxDaughterboard->fpgaDevice)
        {
            free((void *)trxDaughterboard->fpgaDevice);
        }
        return (ADI_COMMON_HAL_GEN_SW);
    }
#endif
    return (ADI_COMMON_HAL_OK);
}

int32_t adi_daughterboard_Init(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t              recoveryAction = ADI_HAL_OK;
    adi_common_Device_t* commonDev;

    /* Check if function pointer is populated */
    if (adi_hal_DevHalCfgCreate == NULL)
    {
        /* TODO: add an error structure to the board level*/
        printf("NULL Hal layer function pointer");
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }
#if 0
    /* Initializing Clock common structure */
    commonDev             = trxDaughterboard->clockAbstractDev.commonAbstractDevice;
    commonDev->devHalInfo = adi_hal_DevHalCfgCreate((ADI_HAL_INTERFACE_SPI | ADI_HAL_INTERFACE_LOG | ADI_HAL_INTERFACE_HWRESET | ADI_HAL_INTERFACE_TIMER),
                                                    1,
                                                    "ad9528.txt");
    if (commonDev->devHalInfo == NULL)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }
#endif
    /* Initializing Board common structure */
    if (((trxDaughterboard->daughterCardId >= ADI_BOARD_9025_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9025_MAX)) ||
        ((trxDaughterboard->daughterCardId >= ADI_BOARD_9010_MIN) && (trxDaughterboard->daughterCardId <= ADI_BOARD_9010_MAX)))
    {
        commonDev             = trxDaughterboard->trxAbstractDev.commonAbstractDevice;
        commonDev->devHalInfo = adi_hal_DevHalCfgCreate((ADI_HAL_INTERFACE_SPI | ADI_HAL_INTERFACE_LOG | ADI_HAL_INTERFACE_TIMER),
                                                        0,
                                                        "adrvTrxLog.txt");
        if (commonDev->devHalInfo == NULL)
        {
            return ADI_COMMON_ACT_ERR_CHECK_PARAM;
        }
    }
#if 0
    /* Initializing FPGA common structure */
    commonDev             = trxDaughterboard->fpgaAbstractDev.commonAbstractDevice;
    commonDev->devHalInfo = adi_hal_DevHalCfgCreate((ADI_HAL_INTERFACE_BBICCTRL | ADI_HAL_INTERFACE_LOG | ADI_HAL_INTERFACE_I2C | ADI_HAL_INTERFACE_TIMER),
                                                    0,
                                                    "fpgaLog.txt");
    if (commonDev->devHalInfo == NULL)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }


    /***** Open hardware for the different devices *****/
    commonDev = trxDaughterboard->fpgaAbstractDev.commonAbstractDevice;
    if ((recoveryAction = adi_hal_HwOpen(commonDev->devHalInfo)) != (int32_t)ADI_HAL_OK)
    {
        printf("Board FPGA HwOpen failed. %s \n",
               commonDev->error.errormessage);
        return recoveryAction;
    }
    commonDev->error.logEnable = ADI_ENABLE;

    /* Open Clock device */
    recoveryAction = trxDaughterboard->ClockDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DEVICE_HWOPEN);
    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("Clock Device HwOpen failed.\n");
        return recoveryAction;
    }
#endif
    /* Open Board device */
    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DEVICE_HWOPEN);
    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX HwOpen failed.\n");
        return recoveryAction;
    }


    return (recoveryAction);
}

static int32_t trx_board_Clear(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t              recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    adi_common_Device_t* commonDev;

    ADI_NULL_DEVICE_PTR_RETURN(trxDaughterboard);

    /* Check if function pointer is populated */
    if (adi_hal_DevHalCfgFree == NULL)
    {
        /* TODO: add an error structure to the board level*/
        printf("NULL Hal layer function pointer");
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    /* If HW devices have been allocated, clear & free.
     * Otherwise, skip. */
    if ((void *)trxDaughterboard->fpgaDevice != NULL)
    {
        /* Close FPGA device */
        commonDev = trxDaughterboard->fpgaAbstractDev.commonAbstractDevice;
        if ((recoveryAction = adi_hal_HwClose(commonDev->devHalInfo)) != (int32_t)ADI_HAL_OK)
        {
            return recoveryAction;
        }
        adi_hal_DevHalCfgFree(commonDev->devHalInfo);
    }

    if ((void *)trxDaughterboard->clockDevice != NULL)
    {
        /* Close Clock device */
        recoveryAction = trxDaughterboard->ClockDispatch(trxDaughterboard,
                                                         TRX_BOARD_ACTION_DEVICE_HWCLOSE);
        if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
        {
            printf("Clock Device HwClose failed\n");
            return recoveryAction;
        }
    }

    if ((void *)trxDaughterboard->BoardDispatch != NULL)
    {
        recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                         TRX_BOARD_ACTION_DEVICE_HWCLOSE);
        if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
        {
            printf("TRX HwClose failed\n");
            return recoveryAction;
        }
    }

    return recoveryAction;
}

int32_t adi_daughterboard_Destroy(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if (trxDaughterboard == NULL)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    /* Need to bring down devices and free the common devices contain insides device structures. */
    if ((recoveryAction = trx_board_Clear(trxDaughterboard)) != ADI_COMMON_ACT_NO_ACTION)
    {
        return recoveryAction;
    }

    /* Now free the device structures */
    if ((void *)trxDaughterboard->trxDevice != NULL)
    {
        if ((trxDaughterboard->boardAttribute & TRX_DAUGHTERBOARD_ATTRIBUTE_PREALLOCATE_TRX_DEVICE) == 0)
        {
            free((void *)trxDaughterboard->trxDevice);
        }

        trxDaughterboard->trxDevice = (uintptr_t)NULL;
    }

    if ((void *)trxDaughterboard->fpgaDevice != NULL)
    {
        free((void *)trxDaughterboard->fpgaDevice);
        trxDaughterboard->fpgaDevice = (uintptr_t)NULL;
    }

    if ((void *)trxDaughterboard->clockDevice != NULL)
    {
        free((void *)trxDaughterboard->clockDevice);
        trxDaughterboard->clockDevice = (uintptr_t)NULL;
    }

    /* Now free the daughterboard common device */
    if (adi_hal_DevHalCfgFree)
    {
        adi_hal_DevHalCfgFree((void *)trxDaughterboard->common.devHalInfo);
    }

    /* Clean up specific data */
    trxDaughterboard->boardAttribute       = 0;
    trxDaughterboard->initializedStatus    = 0;
    trxDaughterboard->daughterCardName[0]  = '\0';
    trxDaughterboard->daughterCardStrId[0] = '\0';

    return recoveryAction;
}

int32_t adi_daughterboard_Program(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if (trxDaughterboard == NULL)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    /* Execute Program Phase 1 */
    recoveryAction = trxDaughterboard->BoardProgramPhase1(trxDaughterboard);

    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("BoardProgramPhase1 failed! recoveryAction[%d]\n",recoveryAction);
        return recoveryAction;
    }

    /* Execute Program Phase 2 */
    recoveryAction = trxDaughterboard->BoardProgramPhase2(trxDaughterboard);

    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("BoardProgramPhase2 failed!recoveryAction[%d]\n",recoveryAction);
        return recoveryAction;
    }

    return recoveryAction;
}

int32_t adi_daughterboard_ClockConfig(adi_daughterboard_trx_t* trxDaughterboard,
                                      uintptr_t                clockInit,
                                      uint32_t                 deviceClock_kHz,
                                      uint32_t                 vcxoFreq_kHz,
                                      uint32_t                 refAFreq_kHz,
                                      uint32_t                 fpgaClock_kHz)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    if (clockInit == 0)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    if ((trxDaughterboard->daughterCardId <= ADI_BOARD_BLANK_EEPROM))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    trxDaughterboard->parameterBucket[0] = deviceClock_kHz;
    trxDaughterboard->parameterBucket[1] = vcxoFreq_kHz;
    trxDaughterboard->parameterBucket[2] = refAFreq_kHz;
    trxDaughterboard->parameterBucket[3] = fpgaClock_kHz;

    /* Replace Clock Init if differeent */
    if (trxDaughterboard->clockInit != clockInit)
    {
        trxDaughterboard->clockInit = clockInit;
    }

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_CLOCK_CONFIG);
    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Clock Config failed.\n");
        return recoveryAction;
    }

    return recoveryAction;
}

int32_t adi_daughterboard_JesdBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                      uint32_t                 txLinkSel,
                                      uint32_t                 rxLinkSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    trxDaughterboard->parameterBucket[0] = txLinkSel;
    trxDaughterboard->parameterBucket[1] = rxLinkSel;

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DEVICE_JESD_BRINGUP);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Jesd Bringup failed.\n");
        return recoveryAction;
    }

    return recoveryAction;
}

int32_t adi_daughterboard_JesdTxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                        uint32_t                 txLinkSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    trxDaughterboard->parameterBucket[0] = txLinkSel;

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DEVICE_JESD_TX_BRINGUP);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Jesd Tx Bringup failed.\n");
        return recoveryAction;
    }

    return recoveryAction;
}

int32_t adi_daughterboard_JesdRxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                        uint32_t                 rxLinkSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    trxDaughterboard->parameterBucket[0] = rxLinkSel;

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DEVICE_JESD_RX_BRINGUP);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Jesd Rx Bringup failed.\n");
        return recoveryAction;
    }

    return recoveryAction;
}

int32_t adi_daughterboard_Ad9528Init(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard, TRX_BOARD_ACTION_DEVICE_AD9528_INIT);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("Ad9528 Init has failed.\n");
    }

    return recoveryAction;
}

int32_t adi_daughterboard_FpgaInit(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard, TRX_BOARD_ACTION__FPGA__INIT);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("Ad9528Init has failed.\n");
    }

    return recoveryAction;
}

int32_t adi_daughterboard_ProgramPhase1(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    //if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL) || (trxDaughterboard->FpgaDispatch == NULL))
    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }



    /* Execute Daughterboard Phase 1*/
    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_PHASE_1);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Phase 1 failed.\n");
        return recoveryAction;
    }



    return recoveryAction;
}

int32_t adi_daughterboard_ProgramPhase2(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_PHASE_2);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Phase 2 failed.\n");
        return recoveryAction;
    }

    return recoveryAction;
}

int32_t adi_daughterboard_DataInterfaceReset(adi_daughterboard_trx_t* trxDaughterboard)
{
    int32_t recoveryAction = ADI_COMMON_HAL_OK;

    if ((trxDaughterboard == NULL) || (trxDaughterboard->BoardDispatch == NULL))
    {
        return (ADI_COMMON_HAL_GEN_SW);
    }

    recoveryAction = trxDaughterboard->BoardDispatch(trxDaughterboard,
                                                     TRX_BOARD_ACTION_DATA_INTF_RESET);

    if (recoveryAction != (int32_t)ADI_COMMON_HAL_OK)
    {
        printf("TRX Phase 1 failed.\n");
        return recoveryAction;
    }

    return recoveryAction;
}
