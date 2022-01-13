/**
 * \file adi_board_adrv9025CE01_types.h
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_BOARD_ADRV9025ADS8_TYPES_H_
#define _ADI_BOARD_ADRV9025ADS8_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "adi_adrv9025_types.h"
#include "adi_ad9528_types.h"
#include "adi_fpga9010_types.h"

/**
* \brief Data structure to hold devices in an adi_board_adrv9025Ads8 daughter card
*/
typedef struct adi_board_adrv9025Ads8
{
    adi_adrv9025_Device_t* adrv9025Device; /*!< Pointer to ADRV9025 device on CE01 board */
    adi_fpga9010_Device_t* fpgaDevice;     /*!< Pointer to FPGA device on CE01 board */
    adi_ad9528_Device_t*   ad9528Device;   /*!< Pointer to AD9528 clock device on CE01 board */

    /* TODO: Update this with final interface */
    char pcbName[32];
} adi_board_adrv9025Ads8_t;

#ifdef __cplusplus
}
#endif

#endif
