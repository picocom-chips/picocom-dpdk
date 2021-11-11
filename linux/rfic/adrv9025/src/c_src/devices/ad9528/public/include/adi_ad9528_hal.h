/**
* \file adi_ad9528_hal.h
* \brief Contains prototypes and macro definitions for Private ADI HAL wrapper
*        functions implemented in adi_ad9528_hal.c
*/
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef _ADI_AD9528_HAL_H_
#define _ADI_AD9528_HAL_H_

#include <stdint.h>
#include <stddef.h>

#include "adi_ad9528_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t adi_ad9528_SpiByteWrite(adi_ad9528_Device_t *device, uint16_t addr, uint8_t data);
int32_t adi_ad9528_SpiByteRead(adi_ad9528_Device_t *device, uint16_t addr, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* ADI_AD9528_HAL_H_ */
