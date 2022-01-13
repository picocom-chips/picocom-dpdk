/**
 * \file adi_device_share.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */
#include "adi_device_share.h"
#include "adi_adrv9025_types.h"
#include "adi_ad9528_types.h"
#include "adi_adrv9025_hal.h"
#include "adi_ad9528_hal.h"
#include "adi_ad9528_utilities.h"



static int32_t reset_setup_hold_block(adi_adrv9025_Device_t* device)
{
    int32_t  retVal  = ADI_COMMON_ACT_NO_ACTION;
    retVal = adi_adrv9025_SpiByteWrite(device,0x004a, 0x92);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI write failure");
    ADI_ERROR_RETURN(device->common.error.newAction);

    retVal = adi_adrv9025_SpiByteWrite(device,0x004a, 0x12); /*toggle resetb_tflash to start a new setup/hold measurement*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI write failure");
    ADI_ERROR_RETURN(device->common.error.newAction);

    retVal = adi_adrv9025_SpiByteWrite(device,0x004a, 0x92);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI write failure");
    ADI_ERROR_RETURN(device->common.error.newAction);
    return 0;
}
static int32_t read_setup_hold_data(adi_adrv9025_Device_t *device,
                                    uint16_t              *setupWord,
                                    uint16_t              *holdWord)
{
    int32_t retVal  = ADI_COMMON_ACT_NO_ACTION;
    uint8_t setup_l = 0;
    uint8_t setup_h = 0;
    uint8_t hold_l  = 0;
    uint8_t hold_h  = 0;

    retVal = adi_adrv9025_SpiByteRead(device,0x004c, &setup_l);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI read failure");
    ADI_ERROR_RETURN(device->common.error.newAction);
    retVal = adi_adrv9025_SpiByteRead(device,0x004d, &setup_h);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI read failure");
    ADI_ERROR_RETURN(device->common.error.newAction);
    retVal = adi_adrv9025_SpiByteRead(device,0x004e, &hold_l);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI read failure");
    ADI_ERROR_RETURN(device->common.error.newAction);
    retVal = adi_adrv9025_SpiByteRead(device,0x004f, &hold_h);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI read failure");
    ADI_ERROR_RETURN(device->common.error.newAction);

    *setupWord =  (uint16_t)(((uint16_t)setup_h << 8) | (uint16_t)setup_l);
    *holdWord =   (uint16_t)(((uint16_t)hold_h << 8) | (uint16_t)hold_l);

    return retVal;
}

int32_t adi_device_share_setupHoldMonitorTimingBlock(adi_adrv9025_Device_t *device,
                                                     adi_ad9528_Device_t   *clock,
                                                     uint8_t               fine,
                                                     uint16_t              *setupWordArr,
                                                     uint16_t              *holdWordArr)
{

    int32_t              retVal         = ADI_COMMON_ACT_NO_ACTION;
    static const uint8_t FINE_MAX       = 16;
    static const uint8_t COARSE_MAX     = 32;
    uint8_t              fineCount      = 0;
    uint8_t              coarseCount    = 0;
    uint16_t             counter        = 0;
    uint16_t             setupWord      = 0;
    uint16_t             holdWord       = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);
    ADI_NULL_DEVICE_PTR_RETURN(clock);
    
    ADI_NULL_DEVICE_PTR_RETURN(setupWordArr);
    ADI_NULL_DEVICE_PTR_RETURN(holdWordArr);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);

    /* Enable Timing Flash */
    retVal = adi_adrv9025_SpiByteWrite(device,0x0048, 0x58);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"SPI write failure");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* Reset/setup timing hold block */
    retVal = reset_setup_hold_block(device);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error Resetting/setting up timing hold block");
    ADI_ERROR_RETURN(device->common.error.newAction);

    retVal = adi_ad9528_SysrefRequest(clock, 0x01);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error while requesting sysref");
    ADI_ERROR_RETURN(device->common.error.newAction);
    for (coarseCount = 0; coarseCount < COARSE_MAX; coarseCount++)
    {
        adi_ad9528_SpiByteWrite(clock, 0x304, coarseCount);
        adi_ad9528_SpiByteWrite(clock, 0x00f, 0x01);
        retVal = adi_ad9528_SysrefRequest(clock, 0x01);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error while requesting sysref");
        ADI_ERROR_RETURN(device->common.error.newAction);
        if (fine == 1)
        {
            for (fineCount = 0; fineCount < FINE_MAX-1; fineCount++)
            {
                adi_ad9528_SpiByteWrite(clock, 0x303, fineCount + 16);
                adi_ad9528_SpiByteWrite(clock, 0x00f, 0x01);
                retVal = reset_setup_hold_block(device);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error Resetting/setting up timing hold block");
                ADI_ERROR_RETURN(device->common.error.newAction);
                retVal = adi_ad9528_SysrefRequest(clock, 0x01);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error while requesting sysref");
                ADI_ERROR_RETURN(device->common.error.newAction);
                adi_common_hal_Wait_ms(&device->common, 100);
                /* read data */
                read_setup_hold_data(device, &setupWord, &holdWord);
                setupWordArr[counter] = setupWord;
                holdWordArr[counter++] = holdWord;
            }
        }
        retVal = reset_setup_hold_block(device);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error Resetting/setting up timing hold block");
        ADI_ERROR_RETURN(device->common.error.newAction);
        retVal = adi_ad9528_SysrefRequest(clock, 0x01);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEBF, ADI_COMMON_ERR_API_FAIL, retVal, NULL,"Error while requesting sysref");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_common_hal_Wait_ms(&device->common, 100);
        /* read data */
        read_setup_hold_data(device, &setupWord, &holdWord);
        setupWordArr[counter] = setupWord;
        holdWordArr[counter++] = holdWord;
    }
    return retVal;
}

