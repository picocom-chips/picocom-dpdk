/**
 * \file ads9_spi.h
 * Analog Devices ADS9 Platform + microzed hardware abstraction layer
 *
 * Copyright 2019 Analog Devices Inc.
 *
 * Support for linux layer SPI functions
 */

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef __ADS9_SPI_H__
#define __ADS9_SPI_H__

#include <stdint.h>
#include "adi_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t ads9_SpiOpen(void* devHalCfg);

int32_t ads9_SpiClose(void* devHalCfg);

int32_t ads9_SpiInit(void* devHalCfg);

int32_t ads9_SpiWrite(void*         devHalCfg,
                      const uint8_t txData[],
                      uint32_t      numTxBytes);

int32_t ads9_SpiWrite_v2(void*         devHalCfg,
                         const uint8_t txData[],
                         uint32_t      numTxBytes);

int32_t ads9_SpiWrite_v3(void*         devHalCfg,
                         const uint8_t txData[],
                         uint32_t      numTxBytes);

int32_t ads9_SpiRead(void*         devHalCfg,
                     const uint8_t txData[],
                     uint8_t       rxData[],
                     uint32_t      numTxRxBytes);

int32_t ads9_SpiRead_v2(void*         devHalCfg,
                        const uint8_t txData[],
                        uint8_t       rxData[],
                        uint32_t      numTxRxBytes);

int32_t ads9_SpiRead_v3(void*         devHalCfg,
                        const uint8_t txData[],
                        uint8_t       rxData[],
                        uint32_t      numTxRxBytes);

#ifdef __cplusplus
}
#endif
#endif /* __ADS9_SPI_H__ */
