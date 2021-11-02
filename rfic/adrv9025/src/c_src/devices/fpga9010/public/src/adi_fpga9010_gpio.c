
/**
 * \file: adi_fpga9010_jesd.c
 *
 * \brief Contains top level tx fpga9010 related functions
 *
 * FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_gpio.h"
#include "adi_fpga9010.h"
#include "../../private/include/fpga9010_bf_axi_tokelau.h"


int32_t adi_fpga9010_GpioModeSet(adi_fpga9010_Device_t *device, adi_fpga9010_GpioModes_e gpioMode)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t enable = 1;
    uint8_t disable = 0;
    uint8_t i = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    

    if (gpioMode == ADI_FPGA9010_GPIO_MODE_NONE)
    {
        recoveryAction = fpga9010_AxiTokelauGpioEnSpi2BfSet(device, FPGA9010_BF_AXI_TOKELAU, disable);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not disable spi2 mode");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        recoveryAction = fpga9010_AxiTokelauGpioEnTokJtagBfSet(device, FPGA9010_BF_AXI_TOKELAU, disable);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not disable jtag mode");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        for (i = 0; i < ADI_FPGA9010_GPIO_PINS; i++)
        {
            device->devStateInfo.gpioPinMode[i] = ADI_FPGA9010_GPIO_MODE_NONE;
        }
    }

    if (gpioMode == ADI_FPGA9010_GPIO_MODE_JTAG)
    {
        recoveryAction = fpga9010_AxiTokelauGpioEnTokJtagBfSet(device, FPGA9010_BF_AXI_TOKELAU, enable);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not enable jtag mode");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        for (i = 0; i < ADI_FPGA9010_GPIO_PINS; i++)
        {
            device->devStateInfo.gpioPinMode[i] = ADI_FPGA9010_GPIO_MODE_JTAG;
        }
    }

    if (gpioMode == ADI_FPGA9010_GPIO_MODE_SPI2)
    {
        recoveryAction = fpga9010_AxiTokelauGpioEnSpi2BfSet(device, FPGA9010_BF_AXI_TOKELAU, enable);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not enable spi2 mode");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        /* GPIO[3:0] are used for SPI2 mode */
        device->devStateInfo.gpioPinMode[0] = ADI_FPGA9010_GPIO_MODE_SPI2;
        device->devStateInfo.gpioPinMode[1] = ADI_FPGA9010_GPIO_MODE_SPI2;
        device->devStateInfo.gpioPinMode[2] = ADI_FPGA9010_GPIO_MODE_SPI2;
        device->devStateInfo.gpioPinMode[3] = ADI_FPGA9010_GPIO_MODE_SPI2;
    }

    return recoveryAction;
}

int32_t adi_fpga9010_GpioModeGet(adi_fpga9010_Device_t *device, adi_fpga9010_GpioModes_e *gpioMode)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t jtagStatus;
    uint8_t spi2Status;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    ADI_NULL_PTR_RETURN(&device->common, gpioMode);
    
    recoveryAction = fpga9010_AxiTokelauGpioEnSpi2BfGet(device, FPGA9010_BF_AXI_TOKELAU, &spi2Status);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read spi2 mode");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
    recoveryAction = fpga9010_AxiTokelauGpioEnTokJtagBfGet(device, FPGA9010_BF_AXI_TOKELAU, &jtagStatus);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read jtag mode");
        ADI_ERROR_RETURN(device->common.error.newAction);
    
    *gpioMode = ADI_FPGA9010_GPIO_MODE_NONE ;
    
    if (spi2Status > 0)
    {
        *gpioMode = ADI_FPGA9010_GPIO_MODE_SPI2;
    }
    
    if (jtagStatus > 0)
    {
        //Jtag mode overrides spi2 mode
        *gpioMode = ADI_FPGA9010_GPIO_MODE_JTAG;
    }

    return recoveryAction;
}

int32_t adi_fpga9010_GpioInputDirSet(adi_fpga9010_Device_t *device, uint32_t pinSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t orgPinSelMask = 0;
    uint32_t newPinSelMask = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    if (pinSelMask > ADI_FPGA9010_GPIO_MAX_VALUE)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, pinSelMask, "pinSelMask cannot exceed max value");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfGet(device, FPGA9010_BF_AXI_TOKELAU, &orgPinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO tristate state");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    newPinSelMask = orgPinSelMask | pinSelMask;

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfSet(device, FPGA9010_BF_AXI_TOKELAU, newPinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write GPIO tristate value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_GpioInputDirGet(adi_fpga9010_Device_t *device, uint32_t *pinSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    ADI_NULL_PTR_RETURN(&device->common, pinSelMask);

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfGet(device, FPGA9010_BF_AXI_TOKELAU, pinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO tristate state");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_GpioOutputDirSet(adi_fpga9010_Device_t *device, uint32_t pinSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t orgPinSelMask = 0;
    uint32_t newPinSelMask = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    if (pinSelMask > ADI_FPGA9010_GPIO_MAX_VALUE)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, pinSelMask, "pinSelMask cannot exceed max value");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfGet(device, FPGA9010_BF_AXI_TOKELAU, &orgPinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO tristate state");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    newPinSelMask = ~(~orgPinSelMask | pinSelMask);

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfSet(device, FPGA9010_BF_AXI_TOKELAU, newPinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write GPIO tristate value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_GpioOutputDirGet(adi_fpga9010_Device_t *device, uint32_t *pinSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
    uint32_t mask = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    ADI_NULL_PTR_RETURN(&device->common, pinSelMask);

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfGet(device, FPGA9010_BF_AXI_TOKELAU, &mask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO tristate state");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    //an output pin is represented as a 0 in the diredction register.
    *pinSelMask = ~mask & ADI_FPGA9010_GPIO_MAX_VALUE;

    return recoveryAction;
}

int32_t adi_fpga9010_GpioOeSet(adi_fpga9010_Device_t *device, adi_fpga9010_GpioPinType_e gpioPinType, uint32_t pinSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t orgPinSelMask = 0;
    uint32_t newPinSelMask = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    if (pinSelMask > ADI_FPGA9010_GPIO_MAX_VALUE)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, pinSelMask, "pinSelMask cannot exceed max value");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfGet(device, FPGA9010_BF_AXI_TOKELAU, &orgPinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO tristate state");
    ADI_ERROR_RETURN(device->common.error.newAction);

    if (gpioPinType == ADI_FPGA9010_GPIO_PIN_OUTPUT)
    {
        //output pins are 0
        newPinSelMask = orgPinSelMask & ~pinSelMask;
    }
    else
    {
        //input pins are 1
        newPinSelMask = orgPinSelMask | pinSelMask;
    }

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfSet(device, FPGA9010_BF_AXI_TOKELAU, newPinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write GPIO tristate value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_GpioOeGet(adi_fpga9010_Device_t *device, uint32_t *pinSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    ADI_NULL_PTR_RETURN(&device->common, pinSelMask);

    recoveryAction = fpga9010_AxiTokelauGpioTristateBfGet(device, FPGA9010_BF_AXI_TOKELAU, pinSelMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO tristate value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_GpioWrite(adi_fpga9010_Device_t *device, uint32_t wrData)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);

    recoveryAction = fpga9010_AxiTokelauGpioOutputBfSet(device, FPGA9010_BF_AXI_TOKELAU, wrData);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write GPIO pin value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_GpioRead(adi_fpga9010_Device_t *device, uint32_t *rdData)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    ADI_NULL_PTR_RETURN(&device->common, rdData);

    recoveryAction = fpga9010_AxiTokelauGpioInputBfGet(device, FPGA9010_BF_AXI_TOKELAU, rdData);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read GPIO pin value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_TddGpioSet(adi_fpga9010_Device_t *device, adi_fpga9010_TddModule_e tddModuleSel, adi_fpga9010_GpioPinSel_e gpioSel) 
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t txToOrxEnMask = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    if (gpioSel < ADI_FPGA9010_GPIO_00 || gpioSel > ADI_FPGA9010_GPIO_18)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, gpioSel, "Invalid GPIO selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    if (device->devStateInfo.gpioPinMode[(uint32_t)gpioSel] != ADI_FPGA9010_GPIO_MODE_NONE)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, gpioSel, "GPIO selected is currently in use.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    device->devStateInfo.gpioPinMode[(uint32_t)gpioSel] = ADI_FPGA9010_GPIO_MODE_TDD;

    switch (tddModuleSel)
    {
        case ADI_FPGA9010_ENABLE1CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx1ToOrx1BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Enable1 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_ENABLE2CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx2ToOrx1BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Enable2 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_ENABLE3CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx1ToOrx2BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Enable3 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_ENABLE4CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx2ToOrx2BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Enable4 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT1CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx3ToOrx3BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Select1 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT2CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx4ToOrx3BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Select2 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT3CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx3ToOrx4BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Select3 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT4CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx4ToOrx4BfSet(device, FPGA9010_BF_AXI_TOKELAU, gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Select4 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, gpioSel, "Invalid TDD module selected.");
            ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    txToOrxEnMask |= (1 << (uint32_t)gpioSel);
    
    recoveryAction = fpga9010_AxiTokelauGpioEnTxToOrxBfSet(device, FPGA9010_BF_AXI_TOKELAU, txToOrxEnMask);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not set Tx to ORx enable bitfield.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_TddGpioGet(adi_fpga9010_Device_t *device, adi_fpga9010_TddModule_e tddModuleSel, adi_fpga9010_GpioPinSel_e *gpioSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_NULL_PTR_RETURN(&device->common, gpioSel);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
    
    switch (tddModuleSel)
    {
        case ADI_FPGA9010_ENABLE1CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx1ToOrx1BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Enable1 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_ENABLE2CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx2ToOrx1BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Enable2 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_ENABLE3CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx1ToOrx2BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Enable3 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_ENABLE4CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx2ToOrx2BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Enable4 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT1CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx3ToOrx3BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Select1 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT2CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx4ToOrx3BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Select2 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT3CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx3ToOrx4BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Select3 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_FPGA9010_SELECT4CONTROL:
            recoveryAction = fpga9010_AxiTokelauGpioSelTx4ToOrx4BfGet(device, FPGA9010_BF_AXI_TOKELAU, (uint8_t *)gpioSel);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not get Select4 GPIO sel.");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, gpioSel, "Invalid TDD module selected.");
            ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_TddGpioAllClear(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t i = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
        
    for (i = 0; i < ADI_FPGA9010_GPIO_PINS; i++)
    {
        if (device->devStateInfo.gpioPinMode[i] == ADI_FPGA9010_GPIO_MODE_TDD)
        {
            device->devStateInfo.gpioPinMode[i] = ADI_FPGA9010_GPIO_MODE_NONE;
        }
    }
    
    recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo, 0x43041080, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Error clearing gpio_sel_tx_to_orx_0 register.");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo, 0x43041084, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, recoveryAction, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Error clearing gpio_sel_tx_to_orx_1 register.");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_AxiTokelauGpioEnTxToOrxBfSet(device, FPGA9010_BF_AXI_TOKELAU, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, device->common.error.errCode, recoveryAction, NULL, "Could not clear Tx to ORx enable bitfield.");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}


