/**
 * \file ads8_spi.h
 * Analog Devices ADS8 Platform + microzed hardware abstraction layer
 *
 * Copyright 2017 Analog Devices Inc.
 *
 * Support for linux layer SPI functions
 */

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef __ADS8_SPI_H__
#define __ADS8_SPI_H__

#include <stdint.h>
#include "adi_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t ads8_SpiOpen(void *devHalCfg);
int32_t ads8_SpiClose(void *devHalCfg);
int32_t ads8_SpiInit(void *devHalCfg);
int32_t ads8_SpiWrite(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes);
int32_t ads8_SpiWrite_v2(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes);
int32_t ads8_SpiWrite_v3(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes);
int32_t ads8_SpiRead(void *devHalCfg, const uint8_t txData[], uint8_t rxData[], uint32_t numTxRxBytes);
int32_t ads8_SpiRead_v2(void *devHalCfg, const uint8_t txData[], uint8_t rxData[], uint32_t numTxRxBytes);
int32_t ads8_SpiRead_v3(void *devHalCfg, const uint8_t txData[], uint8_t rxData[], uint32_t numTxRxBytes);
        
#ifdef __cplusplus
}
#endif
#endif /* __ADS8_SPI_H__ */
