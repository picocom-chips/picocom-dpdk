/**
 * \file ads8_i2c.h
 * Analog Devices ADS8 Platform + microzed hardware abstraction layer
 *
 * Copyright 2017 Analog Devices Inc.
 *
 * Support for linux layer I2C functions
 */

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef __ADS8_I2C_H__
#define __ADS8_I2C_H__

#include <stdint.h>
#include "adi_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t ads8_I2cOpen(void *devHalCfg);
int32_t ads8_I2cClose(void *devHalCfg);
int32_t ads8_I2cInit(void *devHalCfg);
int32_t ads8_I2cWrite(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes);
int32_t ads8_I2cRead(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes, uint8_t rxData[], uint32_t numRxBytes);

#ifdef __cplusplus
}
#endif
#endif /* __ADS8_I2C_H__ */
