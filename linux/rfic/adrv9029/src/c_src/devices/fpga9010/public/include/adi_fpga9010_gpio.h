/**
* \file adi_fpga9010_gpio.h
* \brief Contains top level fpga9010 related function prototypes for
*        adi_fpga9010_gpio.c
*
* FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
*/
/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_GPIO_H_
#define _ADI_FPGA9010_GPIO_H_

#include "adi_fpga9010_gpio_types.h"
#include "adi_fpga9010_tdd_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
* \brief Writes the values to the GPIO output register.
*
* This function will write contents of wrData to the the GPIO output register 
*
* \param device Pointer to the FPGA9010 data structure
* \param wrData The user provided variable containing the output register values.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioWrite(adi_fpga9010_Device_t *device, uint32_t wrData);

/**
* \brief reads the values on the GPIO input register.
*
* This function will read the GPIO input register and put the value into the
* the user provided rdData variable.
*
* \param device Pointer to the FPGA9010 data structure
* \param rdData The user provided variable containing the input register values. 
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioRead(adi_fpga9010_Device_t *device, uint32_t *rdData);

/**
* \brief Sets the gpioMode.
*
* This function will set the Gpio Mode.
* Valid Modes are
* gpioMode[2:0]  |  GPIO direction
* ----------------|-------------------
*        000      |        normal
*        001      |        Jtag
*        010      |        spi2
*
* \param device Pointer to the FPGA9010 data structure
* \param gpioMode The user provided variable containing the mode to set.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioModeSet(adi_fpga9010_Device_t *device, adi_fpga9010_GpioModes_e gpioMode);
    
/**
* \brief Gets the gpioMode.
*
* This function will read the Gpio Mode.
* Valid Modes are
* gpioMode[2:0]  |  GPIO direction
* ----------------|-------------------
*        000      |        normal
*        001      |        Jtag
*        010      |        spi2
*
* \param device Pointer to the FPGA9010 data structure
* \param gpioMode The user provided variable into which the mode value will be written.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioModeGet(adi_fpga9010_Device_t *device, adi_fpga9010_GpioModes_e *gpioMode);

/**
* \brief Sets the gpio input direction pins.
*
* This function will mask all other gpio bits and only set the bits that are high
* in the pinSelMask variable.
*
* \param device Pointer to the FPGA9010 data structure
* \param pinSelMask The user provided variable containing the mapping of bits
* to be set as input pins.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioInputDirSet(adi_fpga9010_Device_t *device, uint32_t pinSelMask);
    
/**
* \brief Gets the gpio input direction pins.
*
* \param device Pointer to the FPGA9010 data structure
* \param pinSelMask The user provided variable which will contain the mapping of bits
* set as Input pins, a high means the pin is an input.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioInputDirGet(adi_fpga9010_Device_t *device, uint32_t *pinDirMask);
    
/**
* \brief Sets the gpio output directction pins.
*
* This function will mask all other gpio bits and and only set the bits that are high
* in the pinSelMask variable.
*
* \param device Pointer to the FPGA9010 data structure
* \param pinSelMask The user provided variable containing the mapping of bits
* to be set as Output pins .
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
    int32_t adi_fpga9010_GpioOutputDirSet(adi_fpga9010_Device_t *device, uint32_t pinDirMask);
    
/**
* \brief Gets the gpio output directction pins.
*
* \param device Pointer to the FPGA9010 data structure
* \param pinSelMask The user provided variable which will contain the mapping of bits
* set as Output pins, a high means the pin is an Output.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioOutputDirGet(adi_fpga9010_Device_t *device, uint32_t *pinDirMask);

/**
* \brief Gets the output Enable register.
*  similar functionality to adi_fpga9010_GpioInputDirGet but with a different signiture
*
* This function will get gpio output enable register value
*
* \param pinSelMask The user provided variable containing the input/output mapping of bits.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioOeGet(adi_fpga9010_Device_t *device, uint32_t *pinSelMask);
    
/**
* \brief Sets the output Enable register.
* similar functionality to adi_fpga9010_GpioInputDirSet but with a different signiture
*
* This function will set gpio pins to either input or output  depending on the gpioPinType variable.
* the pinSelMask is used to mask all other gpio bits and 
* only set the bits that are high in the pinSelMask.
*
* \param device Pointer to the FPGA9010 data structure
* \param gpioPinType The variable containing the direction in which to set the pins.
* \param pinSelMask The user provided variable containing the mapping of bits to set.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_GpioOeSet(adi_fpga9010_Device_t *device, adi_fpga9010_GpioPinType_e gpioPinType, uint32_t pinSelMask);

/**
* \brief    Maps the selected TDD module enable signal to the selected GPIO pin.
*
* \param device Pointer to the FPGA9010 data structure
* \param tddModuleSel The selected TDD module.
* \param gpioSel Which GPIO the tddModuleSel enable signal will be routed to.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_TddGpioSet(adi_fpga9010_Device_t *device, adi_fpga9010_TddModule_e tddModuleSel, adi_fpga9010_GpioPinSel_e gpioSel);

/**
* \brief    Returns which GPIO is mapped to the selected TDD module.
*
* \param device Pointer to the FPGA9010 data structure
* \param tddModuleSel The selected TDD module.
* \param gpioSel A pointer to adi_fpga9010_GpioPinSel_e that will hold the GPIO for the selected TDD module.
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_TddGpioGet(adi_fpga9010_Device_t *device, adi_fpga9010_TddModule_e tddModuleSel, adi_fpga9010_GpioPinSel_e *gpioSel);

/**
* \brief    Clears all TDD GPIO settings.
*
* \param device Pointer to the FPGA9010 data structure
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
*/
int32_t adi_fpga9010_TddGpioAllClear(adi_fpga9010_Device_t *device);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_GPIO_H_ */