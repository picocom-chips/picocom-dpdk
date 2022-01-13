/**
* \file ads9_init.h
* \brief Contains ADI Transceiver Hardware Abstraction functions for the ADS9 Platform.
*        Analog Devices maintains and provides updates to this code layer for the ADS9 platform.
*        The end user should not modify this file or any code in this directory. The end user
*        may provide a similar platform layer that can be used in place of this platform layer, 
*        that uses the same function prototypes.
*/

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#ifndef __ADS9_INIT_H__
#define __ADS9_INIT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t ads9_HwOpen(void* devHalCfg);

int32_t ads9_HwReset(void*   devHalCfg,
                     uint8_t pinLevel);

int32_t ads9_HwClose(void* devHalCfg);

int32_t ads9_HwVerify(void *devHalCfg);

void* ads9_DevHalCfgCreate(uint32_t    interfaceMask,
                           uint8_t     spiChipSelect,
                           const char* logFilename);

int32_t ads9_DevHalCfgFree(void* devHalCfg);

#ifdef __cplusplus
}
#endif
#endif /*__ADS9_INIT_H__*/
