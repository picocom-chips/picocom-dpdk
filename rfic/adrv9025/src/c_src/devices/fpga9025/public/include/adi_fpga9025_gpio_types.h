/*!
* \file adi_adrv9025_gpio_types.h
* \brief Contains FPGA9025 GPIO enum and struct definitions
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_GPIO_TYPES_H_
#define _ADI_FPGA9025_GPIO_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ADI_FPGA9025_GPIO_PINS 19
#define ADI_FPGA9025_GPIO_MAX_VALUE 0x7FFFF

typedef enum adi_fpga9025_GpioModes
{
    ADI_FPGA9025_GPIO_MODE_NONE = 0x0,
    ADI_FPGA9025_GPIO_MODE_JTAG,
    ADI_FPGA9025_GPIO_MODE_SPI2,
    ADI_FPGA9025_GPIO_MODE_TDD
} adi_fpga9025_GpioModes_e;

typedef enum adi_fpga9025_GpioPinType
{
    ADI_FPGA9025_GPIO_PIN_OUTPUT = 0x0,
    ADI_FPGA9025_GPIO_PIN_INPUT = 0x1
} adi_fpga9025_GpioPinType_e;

typedef enum adi_fpga9025_GpioPinSel
{
    ADI_FPGA9025_GPIO_00 = 0,   /*!< Select GPIO_00*/
    ADI_FPGA9025_GPIO_01,       /*!< Select GPIO_01*/
    ADI_FPGA9025_GPIO_02,       /*!< Select GPIO_02*/
    ADI_FPGA9025_GPIO_03,       /*!< Select GPIO_03*/
    ADI_FPGA9025_GPIO_04,       /*!< Select GPIO_04*/
    ADI_FPGA9025_GPIO_05,       /*!< Select GPIO_05*/
    ADI_FPGA9025_GPIO_06,       /*!< Select GPIO_06*/
    ADI_FPGA9025_GPIO_07,       /*!< Select GPIO_07*/
    ADI_FPGA9025_GPIO_08,       /*!< Select GPIO_08*/
    ADI_FPGA9025_GPIO_09,       /*!< Select GPIO_09*/
    ADI_FPGA9025_GPIO_10,       /*!< Select GPIO_10*/
    ADI_FPGA9025_GPIO_11,       /*!< Select GPIO_11*/
    ADI_FPGA9025_GPIO_12,       /*!< Select GPIO_12*/
    ADI_FPGA9025_GPIO_13,       /*!< Select GPIO_13*/
    ADI_FPGA9025_GPIO_14,       /*!< Select GPIO_14*/
    ADI_FPGA9025_GPIO_15,       /*!< Select GPIO_15*/
    ADI_FPGA9025_GPIO_16,       /*!< Select GPIO_16*/
    ADI_FPGA9025_GPIO_17,       /*!< Select GPIO_17*/
    ADI_FPGA9025_GPIO_18,       /*!< Select GPIO_18*/
    ADI_FPGA9025_GPIO_INVALID   /*!< Invalid GPIO*/
} adi_fpga9025_GpioPinSel_e;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_GPIO_TYPES_H_ */
