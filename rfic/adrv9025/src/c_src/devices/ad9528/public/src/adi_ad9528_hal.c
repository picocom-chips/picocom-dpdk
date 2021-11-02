/**
* \file adi_ad9528_hal.c
* \brief Contains ADI AD9528 Clock Generator Hardware Abstraction functions
*        Analog Devices maintains and provides updates to this code layer.
*        The end user should not modify this file or any code in this directory.
*/
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#include "adi_ad9528_user.h"
#include "adi_ad9528_hal.h"
#include "adi_common_error.h"
#include "adi_common_hal.h"


int32_t adi_ad9528_SpiByteWrite(adi_ad9528_Device_t *device, uint16_t addr, uint8_t data)
{
    int32_t halError = 0;
    int32_t i = 0;
    uint8_t txData[3] = { 0 };

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_VARIABLE_LOG(&device->common, ADI_COMMON_LOG_SPI, "%s(0x%04X, 0x%02X)", addr, data);
#endif

    txData[0] = (uint8_t)(0x7F & (addr >> 8));
    txData[1] = (uint8_t)(addr & 0x00FF);
    txData[2] = data;

    for (i = 0; i < ADI_AD9528_NUMBER_SPI_RETRY; i++)
    {
        halError = adi_hal_SpiWrite(device->common.devHalInfo, txData, 3);
        if (halError == ADI_COMMON_HAL_OK)
        {
            break;
        }
    }

    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_ADI_HAL, halError, ADI_COMMON_ACT_ERR_RESET_INTERFACE, NULL, "SpiWriteByte failed");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return ADI_COMMON_ACT_NO_ACTION;
}

int32_t adi_ad9528_SpiByteRead(adi_ad9528_Device_t *device, uint16_t addr, uint8_t *data)
{
    int32_t trxHalAction = 0;
    int32_t halError = 0;
    int32_t i = 0;
    uint8_t txData[3] = { 0 };
    uint8_t rxData[3] = { 0 };

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, data);

    txData[0] = (uint8_t)(0x80 | (addr >> 8));
    txData[1] = (uint8_t)(addr & 0x00FF);
    txData[2] = 0;

    for (i = 0; i < ADI_AD9528_NUMBER_SPI_RETRY; i++)
    {
        halError = adi_hal_SpiRead(device->common.devHalInfo, txData, rxData, 3);
        if (halError == ADI_COMMON_HAL_OK)
        {
            break;
        }
    }

    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_ADI_HAL, halError, ADI_COMMON_ACT_ERR_RESET_INTERFACE, NULL, "SpiWriteByte failed");
    ADI_ERROR_RETURN(device->common.error.newAction);

    *data = rxData[2];
    
#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_VARIABLE_LOG(&device->common, ADI_COMMON_LOG_SPI, "%s(0x%04X, 0x%02X)", addr, data);
    if (trxHalAction != 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_ADI_HAL, trxHalAction, ADI_COMMON_ACT_WARN_RESET_LOG, NULL, "Logging failed");
    }
#endif

    return ADI_COMMON_ACT_NO_ACTION;
}

