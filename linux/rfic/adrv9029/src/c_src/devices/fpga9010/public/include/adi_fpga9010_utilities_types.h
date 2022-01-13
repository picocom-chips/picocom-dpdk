/*!
* \file adi_adrv9010_utilities_types.h
* \brief Contains FPGA9010 utilities enum and struct definitions
*
* ADRV9010 API Version: $ADI_FPGA9010_API_VERSION$
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_UTILITIES_TYPES_H_
#define _ADI_FPGA9010_UTILITIES_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct adi_fpga9010_DesLaneXbar
{
    uint8_t lane0FramerOutSel; /*!< Framer output to route to Physical Lane 0 (valid 0-7) */
    uint8_t lane1FramerOutSel; /*!< Framer output to route to Physical Lane 1 (valid 0-7) */
    uint8_t lane2FramerOutSel; /*!< Framer output to route to Physical Lane 2 (valid 0-7) */
    uint8_t lane3FramerOutSel; /*!< Framer output to route to Physical Lane 3 (valid 0-7) */
    uint8_t lane4FramerOutSel; /*!< Framer output to route to Physical Lane 4 (valid 0-7) */
    uint8_t lane5FramerOutSel; /*!< Framer output to route to Physical Lane 5 (valid 0-7) */
    uint8_t lane6FramerOutSel; /*!< Framer output to route to Physical Lane 6 (valid 0-7) */
    uint8_t lane7FramerOutSel; /*!< Framer output to route to Physical Lane 7 (valid 0-7) */
} adi_fpga9010_DesLaneXbar_t;

typedef struct adi_fpga9010_DataLinkCfg
{
    uint32_t iqRate_kHz; 
    uint8_t jesd204M;
    uint8_t lanesEnabled;
    uint16_t jesd204K;
    uint8_t scramble;
    uint8_t jesd204S;
    uint8_t jesd204Np;
    uint8_t jesd204E;
    uint16_t datamoversUsed;
    uint8_t deviceId;
    adi_fpga9010_DesLaneXbar_t serializerLaneCrossbar; /*!< Lane crossbar to map framer lane outputs to physical lanes */
} adi_fpga9010_DataLinkCfg_t;

typedef struct adi_fpga9010_SetupFpgaCfg
{
    uint32_t deviceClk_kHz;
    adi_fpga9010_DataLinkCfg_t deframerlink0; // Rx
    adi_fpga9010_DataLinkCfg_t deframerlink1; // ORx
    adi_fpga9010_DataLinkCfg_t deframerlink2; // Not in FPGA at the moment

    adi_fpga9010_DataLinkCfg_t framerlink0; // Tx
    adi_fpga9010_DataLinkCfg_t framerlink1; // Not in FPGA at the moment
    uint8_t realIf;
} adi_fpga9010_SetupFpgaCfg_t;



#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9010_UTILITIES_TYPES_H_ */
