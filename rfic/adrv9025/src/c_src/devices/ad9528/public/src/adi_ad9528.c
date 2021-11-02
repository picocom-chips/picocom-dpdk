/**
 * \file adi_ad9528.c
 * \brief Contains source code for configuring and initializing AD9528 clock device
 */
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#include "adi_ad9528_user.h"
#include <stdint.h>
#include "adi_ad9528_hal.h"
#include "adi_ad9528.h"
#include "../../private/include/adi_ad9528_registers.h"
#include "adi_common.h"
#include "adi_ad9528_error.h"
#include "math.h"

int32_t adi_ad9528_HwOpen(adi_ad9528_Device_t *device)
{   
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    adi_common_LogLevelSet(&device->common, ADI_AD9528_LOGGING);
    if (device->common.error.errCode != ADI_COMMON_HAL_OK)
    {
        switch (device->common.error.errCode)
        {
            case ADI_COMMON_HAL_LOGGING_FAIL:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 ADI_COMMON_ACT_WARN_RESET_LOG,
                                 NULL,
                                 "Logging error");
                ADI_ERROR_RETURN(device->common.error.newAction);
            case ADI_COMMON_HAL_LOGGGING_LEVEL_FAIL:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 ADI_COMMON_ACT_WARN_RESET_LOG,
                                 NULL,
                                 "Logging Level error");
                ADI_ERROR_RETURN(device->common.error.newAction);
            case ADI_COMMON_HAL_GEN_SW: /* fall through */
            default:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 ADI_COMMON_ACT_ERR_CHECK_PARAM,
                                 NULL,
                                 "Param error");
                ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    recoveryAction = adi_common_hal_HwOpen(&device->common);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        switch (device->common.error.errCode)
        {
            case ADI_COMMON_HAL_SPI_FAIL:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                                 NULL,
                                 "SPI error");
                ADI_ERROR_RETURN(device->common.error.newAction);
            default:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 ADI_COMMON_ACT_ERR_CHECK_PARAM,
                                 NULL,
                                 "Param error");
                ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_ad9528_HwClose(adi_ad9528_Device_t *device)
{    
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = adi_common_hal_HwClose(&device->common);
    if (device->common.error.errCode != ADI_COMMON_HAL_OK)
    {
        switch (device->common.error.errCode)
        {
            case ADI_COMMON_HAL_SPI_FAIL:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 recoveryAction,
                                 NULL,
                                 "SPI error");
                ADI_ERROR_RETURN(device->common.error.newAction);
            default:
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_ADI_HAL,
                                 device->common.error.errCode,
                                 ADI_COMMON_ACT_ERR_CHECK_PARAM,
                                 NULL,
                                 "Param error");
                ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_ad9528_ClockRatesRead(adi_ad9528_Device_t *device, uint32_t *outputClock_Hz)
{
    UNUSED_PARA(device);
    UNUSED_PARA(outputClock_Hz);
    return ADI_COMMON_ACT_NO_ACTION;
} //debug function to help verify data structure is setup correctly.


int32_t adi_ad9528_HwReset(adi_ad9528_Device_t *device)
{
    /* toggle RESETB on device */
    int32_t halError = (int32_t)ADI_COMMON_HAL_OK;
    static const uint8_t RESETB_LEVEL_LOW = 0;
    static const uint8_t RESETB_LEVEL_HIGH = 1;
    static const uint8_t RESETB_WAIT_MS = 1;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);

    /* toggle RESETB on device with matching spi chip select index */
    halError = adi_common_hal_HwReset(&device->common, RESETB_LEVEL_LOW);
    if (halError != ADI_COMMON_HAL_OK)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API,
            halError, /* TODO: fix to use a error code from ERRSRC_API */
            ADI_COMMON_ACT_ERR_RESET_MODULE,
            NULL,
            "HwReset GPIO error");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    halError = adi_common_hal_Wait_ms(&device->common, RESETB_WAIT_MS);
    if (halError != ADI_COMMON_HAL_OK)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API,
            halError, /* TODO: fix to use a error code from ERRSRC_API */
            ADI_COMMON_ACT_ERR_RESET_MODULE,
            NULL,
            "Timer error");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    halError = adi_common_hal_HwReset(&device->common, RESETB_LEVEL_HIGH);
    if (halError != ADI_COMMON_HAL_OK)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API,
            halError, /* TODO: fix to use a error code from ERRSRC_API */
            ADI_COMMON_ACT_ERR_RESET_MODULE,
            NULL,
            "HwReset GPIO error");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    device->devStateInfo.initialized = 0;

    return (device->common.error.newAction);
}

int32_t adi_ad9528_SpiCfgSet(adi_ad9528_Device_t *device, adi_ad9528_SpiSettings_t* spi)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    uint8_t spiReg = 0;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    /* Check spi settings is not null */
    ADI_NULL_PTR_RETURN(&device->common, spi);

#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    if (spi->msbFirst == 0)
    {
        spiReg |= 0x42; /* SPI bit is 1=LSB first */
    }

    if (spi->autoIncAddrUp > 0)
    {
        spiReg |= 0x24;
    }

    if (spi->fourWireMode > 0)
    {
        spiReg |= 0x18;
    }

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_ADI_SPI_CONFIG_A, spiReg);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_ADI_SPI_CONFIG_A");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_ad9528_SpiCfgGet(adi_ad9528_Device_t *device, adi_ad9528_SpiSettings_t* spi)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    uint8_t spiReg = 0;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    /* Check spi settings is not null */
    ADI_NULL_PTR_RETURN(&device->common, spi);

#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    recoveryAction = adi_ad9528_SpiByteRead(device, AD9528_ADDR_ADI_SPI_CONFIG_A, &spiReg);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not read register AD9528_ADDR_ADI_SPI_CONFIG_A");
    ADI_ERROR_RETURN(device->common.error.newAction);

    spi->fourWireMode = (spiReg & 0x10) >> 4;
    spi->autoIncAddrUp = (spiReg & 0x20) >> 5;
    spi->msbFirst = 0x0001 - ((spiReg & 0x40) >> 6);

    return ADI_COMMON_ACT_NO_ACTION;
}

int32_t adi_ad9528_Initialize(adi_ad9528_Device_t *device, adi_ad9528_Init_t *init) 
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t pll2_Adiv = init->pll2Settings.totalNdiv % 4;
    uint8_t pll2_Bdiv = init->pll2Settings.totalNdiv / 4;
    uint8_t reg108 = 0;
    uint8_t reg109 = 0;
    uint8_t i = 0;
    uint8_t j = 0;
        
    /* Range checks */

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    /* Check spi settings is not null */
    ADI_NULL_PTR_RETURN(&device->common, init);
    
    /* refA_Divider is a 10-bit bitfield */
    if (init->pll1Settings.refA_Divider > 1023)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll1Settings.refA_Divider, "AD9528 refA_Divider out of range");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    /* refB_Divider is a 10-bit bitfield */
    if (init->pll1Settings.refB_Divider > 1023)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll1Settings.refB_Divider, "AD9528 refB_Divider out of range");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    /* nDividerPll1 is a 10-bit bitfield */
    if (init->pll1Settings.nDividerPll1 > 1023)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll1Settings.nDividerPll1, "AD9528 nDividerPll1 out of range");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* cal value must equal (RF * N2) */
    if (init->pll2Settings.totalNdiv != (init->pll2Settings.n2Divider * init->pll2Settings.rfDivider))
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "totalNDiv (VCO Cal Divider) value must match RF div * N2 div");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if(init->pll2Settings.totalNdiv == 18 || init->pll2Settings.totalNdiv == 27)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Illegal VCO Cal divider value (if B < 7 only specific A values are allowed)");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    /*  n2Divider valid range is 1-256  */
    if (init->pll2Settings.n2Divider > 256 || init->pll2Settings.n2Divider < 1)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll2Settings.n2Divider, "AD9528 n2Divider out of range");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /*  r1Divider valid range is 1-31  */
    if (init->pll2Settings.r1Divider > 31 || init->pll2Settings.r1Divider < 1)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll2Settings.r1Divider, "AD9528 r1Divider out of range");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (pll2_Adiv > 3) {  //A div valid range (0 to 3)
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll2Settings.totalNdiv, "AD9528 PLL2 A Divider out of range (0 to 3)");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (pll2_Bdiv < 4 || pll2_Bdiv > 63) {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll2Settings.totalNdiv, "AD9528 PLL2 B Divider out of range (3 to 63)");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (init->pll2Settings.rfDivider < 3 || init->pll2Settings.rfDivider > 5) {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->pll2Settings.rfDivider, "AD9528 PLL2 RF Divider out of range (3,4, or 5)");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    for (i = 0; i < 14; i = i + 1)
    {
        /*  outChannelDiv valid range is 1-256  */
        if (init->outputSettings.outChannelDiv[i] > 256 || init->outputSettings.outChannelDiv[i] < 1)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->outputSettings.outChannelDiv, "An AD9528 outChannelDiv is out of range");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        
        /*  sanity check on Analog Delay. If a delay is requested the enable needs to be set */
        if (((init->outputSettings.outAnalogDelay[i] & 0x0F) > 0) && ((init->outputSettings.outAnalogDelay[i] & 0x10) != 0x10))
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, init->outputSettings.outAnalogDelay, "An Analog Delay is requested but enable is not set");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif    

    adi_ad9528_SpiCfgSet(device, &init->spiSettings);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /**********************************************************************
    * Configure PLL1
    **********************************************************************/
    /*REF A div[7:0]*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_REF_A_DIVIDER_LSB, (init->pll1Settings.refA_Divider & 0xFF));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_REF_A_DIVIDER_LSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /*REF A div[9:8]*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_REF_A_DIVIDER_MSB, ((init->pll1Settings.refA_Divider >> 8) & 0x03));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_REF_A_DIVIDER_MSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /*REF B div[7:0]*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_REF_B_DIVIDER_LSB, (init->pll1Settings.refB_Divider & 0xFF));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_REF_B_DIVIDER_LSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /*REF B div[9:8]*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_REF_B_DIVIDER_MSB, ((init->pll1Settings.refB_Divider >> 8) & 0x03));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_REF_B_DIVIDER_MSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /*PLL1 N div[7:0]*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL1_N_DIV_LSB, (init->pll1Settings.nDividerPll1 & 0xFF));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL1_N_DIV_LSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* PLL1 N div[9:8] */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL1_N_DIV_MSB, ((init->pll1Settings.nDividerPll1 >> 8) & 0x03));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL1_N_DIV_MSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* PLL1 Charge Pump control 1*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL1_CHARGEPUMP, 0x0A);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL1_CHARGEPUMP");
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* PLL1 Charge Pump control 2*/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL1_CP_CTRL2, 0x03);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL1_CP_CTRL2");
    ADI_ERROR_RETURN(device->common.error.newAction);

    switch (init->pll1Settings.refA_bufferCtrl)
    {
        case ADI_AD9528_DISABLED:            reg108 &= ~0x28; reg109 &= ~0x01; break; /*clear all REFA enable bits*/
        case ADI_AD9528_SINGLE_ENDED:        reg108 |= 0x08; reg109 &= ~0x01; break; /*Set REFA receiver enable, clear REFA SE negative input enable*/
        case ADI_AD9528_NEG_SINGLE_ENDED:    reg108 |= 0x08; reg108 &= ~0x10; reg109 |= 0x01; break; /*Disable REFA diff receiver, enable REFA receiver and use negative REFA input*/
        case ADI_AD9528_DIFFERENTIAL:        reg108 |= 0x28; reg109 &= ~0x01; break;
        default:                            reg108 |= 0x08; reg109 &= ~0x01; break; /*default to single ended case*/
    }
    switch (init->pll1Settings.refB_bufferCtrl) {
        case ADI_AD9528_DISABLED:            reg108 &= ~0x50; reg109 &= ~0x02; break; /*clear all REFB enable bits*/
        case ADI_AD9528_SINGLE_ENDED:        reg108 |= 0x10; reg109 &= ~0x02; break; /*Set REFB receiver enable, clear REFB SE negative input enable*/
        case ADI_AD9528_NEG_SINGLE_ENDED:    reg108 |= 0x10; reg108 &= ~0x40; reg109 |= 0x02; break; /*Disable REFB diff receiver, enable REFB receiver and use negative REFB input*/
        case ADI_AD9528_DIFFERENTIAL:        reg108 |= 0x50; reg109 &= ~0x02; break;
        default:                            reg108 |= 0x10; reg109 &= ~0x02; break; /*default to single ended case*/
    }
    switch (init->pll1Settings.vcxoBufferCtrl) {
        case ADI_AD9528_DISABLED:            reg108 &= ~0x03; reg108 |= 0x04; break; /*power down VCXO input*/
        case ADI_AD9528_SINGLE_ENDED:        reg108 &= ~0x07; break; /*Clear VCXO receiver power down, defaults to Single ended mode*/
        case ADI_AD9528_NEG_SINGLE_ENDED:    reg108 &= ~0x07; reg108 |= 0x02; break; /*Clear VCXO power down, enable Negative single ended mode[1]*/
        case ADI_AD9528_DIFFERENTIAL:        reg108 &= ~0x07; reg108 |= 0x01; break; /*Clear VCXO power down, enable differential input buffer[0]*/
        default:                            reg108 &= ~0x07; break; /*default to positive single ended case*/
    }

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_INPUT_RECEIVERS1, reg108);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_INPUT_RECEIVERS1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_INPUT_RECEIVERS2, reg109);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_INPUT_RECEIVERS2");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_INPUT_RECEIVERS3, 0x02);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_INPUT_RECEIVERS3");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL1_FASTLOCK, 0x00);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL1_FASTLOCK");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /**********************************************************************
    * Configure PLL2
    **********************************************************************/

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_CHARGEPUMP, 0xE6); /*PLL2 Charge Pump[7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_CHARGEPUMP");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_N_DIV, ((pll2_Adiv & 0x3) << 6) | (pll2_Bdiv & 0x3F)); /*PLL2 A and B divider*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_N_DIV");

    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_CTRL, 0x03); /*PLL2 control*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_CTRL");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_VCO_DIV, init->pll2Settings.rfDivider); /*VCO divider*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_VCO_DIV");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_LF_CTRL1, 0x2A); /*PLL2 Loop filter [7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_LF_CTRL1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_LF_CTRL2, 0x00); /*PLL2 Loop filter [8]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_LF_CTRL2");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_REPLICA_CHDIV, init->pll2Settings.n2Divider - 1); /*N2 Divider*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_REPLICA_CHDIV");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_REPLICA_DIV_PHASE, 0x00); /*Replica Channel Divider phase*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_REPLICA_DIV_PHASE");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_RDIV, init->pll2Settings.r1Divider); /*R1 Divider*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_RDIV");
    ADI_ERROR_RETURN(device->common.error.newAction);

    if (init->pll2Settings.r1Divider > 1)
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_VCO_CTRL, 0x11); /*Enable R1*/
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_VCO_CTRL");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_PLL2_VCO_CTRL, 0x01); /*Manual VCO CAL*/
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_PLL2_VCO_CTRL");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /**********************************************************************
    * Configure Output Distribution
    **********************************************************************/
    for (i = 0; i<14; i = i + 1) {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_OUT0_CTRL1 + j, ((init->outputSettings.outSource[i] & 0x7) << 5) | (init->outputSettings.outAnalogDelay[i] & 0x1F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write an AD9528_ADDR_CH_OUT0_CTRL1 register");
        ADI_ERROR_RETURN(device->common.error.newAction);
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_OUT0_CTRL2 + j, ((init->outputSettings.outBufferCtrl[i] & 0x3) << 6) | (init->outputSettings.outDigitalDelay[i] & 0x3F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write an AD9528_ADDR_CH_OUT0_CTRL2 register");
        ADI_ERROR_RETURN(device->common.error.newAction);
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_OUT0_CHDIV + j, init->outputSettings.outChannelDiv[i] - 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write an AD9528_ADDR_CH_OUT0_CHDIV register");
        ADI_ERROR_RETURN(device->common.error.newAction);
        j = j + 3;
    }

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_OUTPUT_SYNC, 0x00); /*Sync outputs*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_OUTPUT_SYNC");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_MASK_SYNC1, 0x00); /*Mask SYNC[7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_MASK_SYNC1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_MASK_SYNC2, 0x00); /*Mask SYNC[13:8]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_MASK_SYNC2");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_EN_OUTPUT_PATH_SEL1, 0x00); /*Bypass SYSREF resample [6:0], bit0:Enable VCXO to feed output distribution*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_EN_OUTPUT_PATH_SEL1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_EN_OUTPUT_PATH_SEL2, 0x00); /*Bypass SYSREF resample [13:7]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_EN_OUTPUT_PATH_SEL2");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /**********************************************************************
    * Configure SYSREF operation
    **********************************************************************/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSERF_DIV_LSB, init->sysrefSettings.sysrefDivide & 0xFF); /*SYSREF divider [7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSERF_DIV_LSB");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSERF_DIV_MSB, (init->sysrefSettings.sysrefDivide >> 8) & 0xFF); /*SYSREF divider [7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSERF_DIV_MSB");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL3, ((init->sysrefSettings.sysrefRequestMethod & 0x1) << 7) |
        ((init->sysrefSettings.sysrefPinEdgeMode & 0x3) << 5));
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSREF_CTRL3");
    ADI_ERROR_RETURN(device->common.error.newAction);

    device->devStateInfo.sysrefCtrlReg403Init = ((init->sysrefSettings.sysrefSource & 0x03) << 6) |
                                                ((init->sysrefSettings.sysrefPatternMode & 0x3) << 4) |
                                                ((init->sysrefSettings.sysrefNshotMode & 0x7) << 1);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL4, device->devStateInfo.sysrefCtrlReg403Init);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSREF_CTRL4");
    ADI_ERROR_RETURN(device->common.error.newAction);

    if (init->sysrefSettings.sysrefPinBufferMode == ADI_AD9528_DISABLED)
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL5, 0x04); /*power down input buffer for external SYSREF*/
    }
    else if (init->sysrefSettings.sysrefPinBufferMode == ADI_AD9528_SINGLE_ENDED)
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL5, 0x00); /*enable positive singled ended input*/
    }
    else if (init->sysrefSettings.sysrefPinBufferMode == ADI_AD9528_NEG_SINGLE_ENDED)
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL5, 0x02); /*enable negative singled ended input*/
    }
    else if (init->sysrefSettings.sysrefPinBufferMode == ADI_AD9528_DIFFERENTIAL)
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL5, 0x01); /*enable differential input buffer*/
    }
    else
    {
        recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL5, 0x04); /*power down input buffer for external SYSREF*/
    }
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSREF_CTRL5");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Set the info variable */
    device->devStateInfo.sysrefPatternMode = init->sysrefSettings.sysrefPatternMode;

    /**********************************************************************
    * Power down control
    **********************************************************************/
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_POWERDOWN_CTRL, 0x10);/* power up PLL1, PLL2 and output distribution*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_POWERDOWN_CTRL");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_POWERDOWN1, init->outputSettings.outPowerDown & 0xFF); /*power down out[7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_CH_POWERDOWN1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_POWERDOWN2, ((init->outputSettings.outPowerDown >> 8) & 0x3F)); /*power down out[13:8]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_CH_POWERDOWN2");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_LDO_ENABLES1, 0xFF); /*LDO enable per output channel [7:0]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_LDO_ENABLES1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_LDO_ENABLES2, 0xFF); /*LDO enable per output channel [15:8]*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_LDO_ENABLES2");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_STATUS0_CTRL, 0x07); /*STATUS 0 outputs REFA present*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_STATUS0_CTRL");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_STATUS1_CTRL, 0x01); /*STATUS 1 outputs PLL1 and PLL2 locked*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_STATUS1_CTRL");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_STATUS_OE, 0x0C);/* Make Status0 and Status1 outputs after reset.*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_STATUS_OE");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_IO_UPDATE, 0x01); /*IO update to make all these settings valid in the 9528*/
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_IO_UPDATE");
    ADI_ERROR_RETURN(device->common.error.newAction);

    device->lockStatusExpectedValue = 0;
    
    if (init->pll1Settings.refA_bufferCtrl != ADI_AD9528_DISABLED)
    {
        device->lockStatusExpectedValue |= 0x04; /* bit 2 is REFA detected status */
    }
    
    if (init->pll1Settings.refB_bufferCtrl != ADI_AD9528_DISABLED)
    {
        device->lockStatusExpectedValue |= 0x08; /* bit 3 is REFB detected status */
    }
    
    /* If PLL 1 is enabled */
    if (init->pll1Settings.nDividerPll1 != 0)
    {
        device->lockStatusExpectedValue |= 0x41; /* bit 6 is PLL1 feedback detected status, bit 0 is pll1 locked status */
    }
    
    /* PLL2 is always enabled */
    device->lockStatusExpectedValue |= 0x82; /* bit 7 is PLL2 feedback detected status, bit 1 is pll2 locked status */
    
    /* VCXO should always be present */
    device->lockStatusExpectedValue |= 0x20; /* bit 5 is VCXO detected status*/
    
    if (init->pllLockTimeout_ms != 0)
    {
        recoveryAction = adi_ad9528_PllLockDebounce(device, init->pllLockTimeout_ms);
    }

    return recoveryAction;
}

int32_t adi_ad9528_SysrefRequest(adi_ad9528_Device_t *device, uint8_t enableSYSREF)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t enableSysrefBit = 0;
    uint8_t reg403 = 0;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    if (device->devStateInfo.sysrefPatternMode == ADI_AD9528_NSHOT || enableSYSREF > 0)
    {
        enableSysrefBit = 0x01;
    }
    else
    {
        enableSysrefBit = 0x00;
    }
    
    reg403 = (device->devStateInfo.sysrefCtrlReg403Init | enableSysrefBit);
    
    /* Set SPI SYSREF request bit */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL4, reg403);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSREF_CTRL4");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    
    /* IO update to make all these settings valid in the 9528 */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_IO_UPDATE, 0x01);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_IO_UPDATE");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_ad9528_SysrefSetup(adi_ad9528_Device_t *device, adi_ad9528_SysrefSettings_t *sysrefSettings)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t reg403 = 0;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    /* Check spi settings is not null */
    ADI_NULL_PTR_RETURN(&device->common, sysrefSettings);

#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    device->devStateInfo.sysrefPatternMode = sysrefSettings->sysrefPatternMode;

    recoveryAction = adi_ad9528_SpiByteRead(device, AD9528_ADDR_SYSREF_CTRL4, &reg403);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not read to register AD9528_ADDR_SYSREF_CTRL4");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* clear bit 0 to stop a continuous sysref if it is on. */
    reg403 = reg403 & ~0x01; 
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL4, reg403);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSREF_CTRL4");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* clear bits for pattern mode and Nshot mode bitfields */
    reg403 = reg403 & ~0x3E; 
    reg403 = reg403 | ((sysrefSettings->sysrefPatternMode & 0x3) << 4) | ((sysrefSettings->sysrefNshotMode & 0x7) << 1);
    /* update internal sysref pattern mode and Nshot mode (number of pulses) */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_SYSREF_CTRL4, reg403);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_SYSREF_CTRL4");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* SYSREF request bit x403[0] is left 0.  The next call to AD9528_requestSysref will start the SYSREF */
    /* IO update to make all these settings valid in the 9528 */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_IO_UPDATE, 0x01); 
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_IO_UPDATE");
    ADI_ERROR_RETURN(device->common.error.newAction);


    return recoveryAction;
}

int32_t adi_ad9528_ClockOutputsEnable(adi_ad9528_Device_t *device, uint16_t clkEnable)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    /* Check device pointer is not null */
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_AD9528_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    /* clkEnable: bit per clock output */
    /* power down out[7:0] */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_POWERDOWN1, ~clkEnable & 0xFF); 
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_CH_POWERDOWN1");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* power down out[13:8] */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_CH_POWERDOWN2, ((~clkEnable >> 8) & 0x3F)); 
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_CH_POWERDOWN2");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* IO update to make all these settings valid in the 9528 */
    recoveryAction = adi_ad9528_SpiByteWrite(device, AD9528_ADDR_IO_UPDATE, 0x01); 
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "AD9528 could not write to register AD9528_ADDR_IO_UPDATE");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

int32_t adi_ad9528_PllLockDebounce(adi_ad9528_Device_t *device, uint32_t timeout_ms)
{
    uint8_t reg508 = 0;
    uint8_t i = 0;
    uint32_t numLoops = 0;
    uint32_t lockCount = ADI_AD9528_PLL_DEBOUNCE_TIME_MS / ADI_AD9528_PLL_DEBOUNCE_INT_MS;
    uint8_t lockFlag = 0;
    int32_t recoveryAction = 0;

    if (timeout_ms < ADI_AD9528_PLL_DEBOUNCE_TIME_MS)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Timeout must be greater than ADI_AD9528_PLL_DEBOUNCE_TIME_MS");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Check lock status in 10ms intervals*/
        numLoops = (uint32_t)ceil(((double)timeout_ms) / ADI_AD9528_PLL_DEBOUNCE_INT_MS);
    }

    /* read twice to refresh status bits */
    recoveryAction = adi_ad9528_SpiByteRead(device, AD9528_ADDR_STATUS_READBACK0, &reg508);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_SPI_FAIL, recoveryAction, NULL, "Error reading SPI");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    for (i = 0; i < numLoops; i++)
    {
        adi_ad9528_SpiByteRead(device, AD9528_ADDR_STATUS_READBACK0, &reg508);
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        if ((reg508 & device->lockStatusExpectedValue) != device->lockStatusExpectedValue)
        {
            lockCount = ADI_AD9528_PLL_DEBOUNCE_TIME_MS / ADI_AD9528_PLL_DEBOUNCE_INT_MS;
        }
        else
        {
            lockCount--;
            if (lockCount == 0)
            {
                lockFlag = 1;
                break;
            }
        }
        
        adi_common_hal_Wait_ms(&device->common, ADI_AD9528_PLL_DEBOUNCE_INT_MS);
    }

    if (lockFlag == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_AD9528_ERR_PLL_LOCK_FAILED, ADI_COMMON_ACT_ERR_RESET_MODULE, NULL, "Ad9528 PLL Not locked");
        return ADI_COMMON_ACT_ERR_RESET_MODULE;
    }
    
    return ADI_COMMON_ACT_NO_ACTION;
}

int32_t adi_ad9528_PllLockStatusGet(adi_ad9528_Device_t *device, uint8_t *status)
{
    uint8_t reg508 = 0;
    int32_t recoveryAction = 0;

    /* read twice to refresh status bits */
    recoveryAction = adi_ad9528_SpiByteRead(device, AD9528_ADDR_STATUS_READBACK0, &reg508);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_SPI_FAIL, recoveryAction, NULL, "Error reading SPI");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_ad9528_SpiByteRead(device, AD9528_ADDR_STATUS_READBACK0, &reg508);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* if status is a valid pointer, return the PLL status */
    if (status != NULL)
    {
        *status = reg508;
    }

    /* PLLs 1 and 2 are locked and VCXO and REFA detected if reg508 has bits 5,2,1 and 0 set */
    if ((reg508 & device->lockStatusExpectedValue) == device->lockStatusExpectedValue)
    {
        return ADI_COMMON_ACT_NO_ACTION;
    }
    else
    {
        return ADI_COMMON_ACT_ERR_RESET_MODULE;
    }
}
