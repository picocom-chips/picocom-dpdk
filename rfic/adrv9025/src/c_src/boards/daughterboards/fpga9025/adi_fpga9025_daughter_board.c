/**
 * \file adi_fpga9025_daughter_board.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025.h"
#include <stdlib.h>
#include <string.h>
#include "adi_platform_identify.h"
#include "adi_motherboard_trx.h"

/****************************************************************************
* Local functions
****************************************************************************/

int32_t adi_fpga9025Board_Dispatch(adi_daughterboard_trx_t* trxDaughterboard,
                                   adrvtrx_board_action_e   actionFlags)
{
    int32_t                recoveryAction = ADI_COMMON_HAL_OK;
    uint32_t               fpgaVersion    = 0;
    adi_fpga9025_Device_t* fpga9025Device = NULL;
    uint8_t                enableJesd204C = ADI_FALSE;

    /* FPGA allocation */
    if (actionFlags == TRX_BOARD_ACTION_DEVICE_ALLOC)
    {
        trxDaughterboard->fpgaDevice = (uintptr_t)calloc(1,
                                                         sizeof(adi_fpga9025_Device_t));
        if (trxDaughterboard->fpgaDevice == 0)
        {
            return (ADI_COMMON_HAL_GEN_SW);
        }

        /* Assigning Abstract pointers */
        trxDaughterboard->fpgaAbstractDev.commonAbstractDevice                  = (adi_common_Device_t *)trxDaughterboard->fpgaDevice;
        trxDaughterboard->fpgaAbstractDev.fpgaAbstractDevice                    = trxDaughterboard->fpgaDevice;
        ((adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice)->memoryPageSize = MEM_SIZE_1GB;

        return (ADI_COMMON_HAL_OK);
    }

    /* FPGA Initialization */
    if (actionFlags == TRX_BOARD_ACTION_FPGA_INIT)
    {
        fpga9025Device = (adi_fpga9025_Device_t *)trxDaughterboard->fpgaDevice;
        enableJesd204C = trxDaughterboard->savedInfo.enable204cState;

        /* Verify FPGA design Version number is for ADRV9025 & is recent enough for the current API */
        recoveryAction = adi_fpga9025_VersionRead(fpga9025Device);
        if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
        {
            return (recoveryAction);
        }

        /* Init FPGA */
        fpgaVersion = (fpga9025Device->devStateInfo.versionMajor << 16) + fpga9025Device->devStateInfo.versionMinor;

        if (fpgaVersion < ADI_FPGA9025_MIN_VERSION)
        {
            ADI_ERROR_REPORT(&fpga9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_INVALID_FPGA_IMAGE,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Incompatible FPGA.");
            ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);
        }

        if (fpga9025Device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
        {
            fpga9025Device->devStateInfo.encodingHighValue  = 10;
            fpga9025Device->devStateInfo.encodingLowValue   = 8;
            fpga9025Device->devStateInfo.linkLayerDataWidth = 40;
            fpga9025Device->devStateInfo.dmaDataWidth       = 32;

            if (enableJesd204C != ADI_FALSE)
            {
                ADI_ERROR_REPORT(&fpga9025Device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_INV_PARAM,
                                 ADI_COMMON_ACT_ERR_CHECK_PARAM,
                                 NULL,
                                 "Cannot use a 204C profile with a 204B FPGA.");
                ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);
            }
        }
        else if (fpga9025Device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
        {
            fpga9025Device->devStateInfo.encodingHighValue  = 66;
            fpga9025Device->devStateInfo.encodingLowValue   = 64;
            fpga9025Device->devStateInfo.linkLayerDataWidth = 66;
            fpga9025Device->devStateInfo.dmaDataWidth       = 64;

            if (enableJesd204C == ADI_FALSE)
            {
                ADI_ERROR_REPORT(&fpga9025Device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_INV_PARAM,
                                 ADI_COMMON_ACT_ERR_CHECK_PARAM,
                                 NULL,
                                 "Cannot use a 204B profile with a 204C FPGA.");
                ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);
            }
        }
        else
        {
            ADI_ERROR_REPORT(&fpga9025Device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_INVALID_FPGA_IMAGE,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Invalid FPGA image.");
            ADI_ERROR_RETURN(fpga9025Device->common.error.newAction);
        }

        return (ADI_COMMON_HAL_OK);
    }

    return (ADI_COMMON_HAL_OK);
}
