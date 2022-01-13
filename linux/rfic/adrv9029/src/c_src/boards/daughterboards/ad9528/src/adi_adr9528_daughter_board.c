/**
 * \file adi_ad9528_daughter_board.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include <stdlib.h>
#include <string.h>
#include "adi_ad9528.h"
#include "adi_ad9528_utilities.h"
#include "adi_motherboard_trx.h"


/****************************************************************************
* Local functions
****************************************************************************/

int32_t adi_clock9528Board_Dispatch(adi_daughterboard_trx_t *trxDaughterboard, adrvtrx_board_action_e actionFlags)
{
    int32_t recoveryAction = ADI_COMMON_HAL_OK;
    adi_common_Device_t *commonDev = NULL;
    
    /* Clock 9528 device allocation */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_ALLOC) 
    {
        trxDaughterboard->clockDevice = (uintptr_t) calloc(1, sizeof(adi_ad9528_Device_t));
        if (trxDaughterboard->clockDevice == 0)
        {
            return (ADI_COMMON_HAL_GEN_SW);
        }
    
        /* Assigning Abstract pointers */
        trxDaughterboard->clockAbstractDev.commonAbstractDevice = (adi_common_Device_t *) trxDaughterboard->clockDevice;
        trxDaughterboard->clockAbstractDev.clockAbstractDevice = trxDaughterboard->clockDevice;
                
        return (ADI_COMMON_HAL_OK);
    }
    
    /* HW Open */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_HWOPEN) 
    {
        commonDev = trxDaughterboard->clockAbstractDev.commonAbstractDevice;
        if ((recoveryAction = adi_ad9528_HwOpen((adi_ad9528_Device_t *) trxDaughterboard->clockDevice)) != (int32_t)ADI_HAL_OK)
        {
            printf("Clock HwOpen failed. %s \n", commonDev->error.errormessage);
            return recoveryAction;
        }
        commonDev->error.logEnable = ADI_ENABLE;
        
        return (ADI_COMMON_HAL_OK);
    }
    
    /* HW Close */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_HWCLOSE) 
    {
        commonDev = trxDaughterboard->clockAbstractDev.commonAbstractDevice;
        if ((recoveryAction = adi_ad9528_HwClose((adi_ad9528_Device_t *) trxDaughterboard->clockDevice)) != (int32_t)ADI_HAL_OK)
        {
            return recoveryAction;
        }
        adi_hal_DevHalCfgFree(commonDev->devHalInfo);
        
        return (ADI_COMMON_HAL_OK);
    }
    
    return (recoveryAction);
}