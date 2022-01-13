/*!
* \file adi_adrv9025_utilities_types.h
* \brief Contains FPGA9025 utilities enum and struct definitions
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_UTILITIES_TYPES_H_
#define _ADI_FPGA9025_UTILITIES_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct adi_fpga9025_DesLaneXbar
{
    uint8_t lane0FramerOutSel; /*!< Framer output to route to Physical Lane 0 (valid 0-7) */
    uint8_t lane1FramerOutSel; /*!< Framer output to route to Physical Lane 1 (valid 0-7) */
    uint8_t lane2FramerOutSel; /*!< Framer output to route to Physical Lane 2 (valid 0-7) */
    uint8_t lane3FramerOutSel; /*!< Framer output to route to Physical Lane 3 (valid 0-7) */
} adi_fpga9025_DesLaneXbar_t;

typedef struct adi_fpga9025_DataLinkCfg
{
    uint32_t iqRate_kHz;
    uint8_t  jesd204M;
    uint8_t  lanesEnabled;
    uint16_t jesd204K;
    uint8_t  scramble;
    uint8_t  jesd204S;
    uint8_t  jesd204Np;
    uint8_t  jesd204E;
    uint16_t datamoversUsed;
    uint8_t  deviceId;
    adi_fpga9025_DesLaneXbar_t serializerLaneCrossbar; /*!< Lane crossbar to map framer lane outputs to physical lanes */
} adi_fpga9025_DataLinkCfg_t;

typedef struct adi_fpga9025_SetupFpgaCfg
{
    uint32_t                   deviceClk_kHz;
    adi_fpga9025_DataLinkCfg_t deframerlink0; // Rx
    adi_fpga9025_DataLinkCfg_t deframerlink1; // ORx
    adi_fpga9025_DataLinkCfg_t deframerlink2; // Not in FPGA at the moment

    adi_fpga9025_DataLinkCfg_t framerlink0; // Tx
    adi_fpga9025_DataLinkCfg_t framerlink1; // Not in FPGA at the moment
    uint8_t                    realIf;
} adi_fpga9025_SetupFpgaCfg_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_UTILITIES_TYPES_H_ */
