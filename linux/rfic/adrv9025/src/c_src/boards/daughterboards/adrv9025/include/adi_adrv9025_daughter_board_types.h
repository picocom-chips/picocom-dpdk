/**
 * \file adi_adrv9025_daughter_board_types.h
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_ADRV9025_DAUGHTER_BOARD_TYPES_H_
#define _ADI_ADRV9025_DAUGHTER_BOARD_TYPES_H_

#include "adi_adrv9025_types.h"
#include "adi_ad9528_types.h"
//#include "adi_fpga9025_types.h"
#include "adi_adrv9025_utilities_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \brief Enum of possible daughter board types
*/
typedef enum adi_board_adrv9025Sel
{
    ADI_BOARD_ADRV9025_EE01 = 0xEE01,     /*!< Selects a daughter board of type EE01 */
    ADI_BOARD_ADRV9025_CE01 = 0xCE01,     /*!< Selects a daughter board of type CE01 */
    ADI_BOARD_ADRV9026_CE01 = 0xCE01,     /*!< Selects a daughter board of type CE01 */
    ADI_BOARD_ADRV9025_STSHAL01 = 0xFF00, /*!< Selects a daughter board of type stsHal for all non-init actions */
    ADI_BOARD_ADRV9025_ADS8 = 0xAD58,     /*!< Selects a daughter board of type stsHal for all non-init actions */
    ADI_BOARD_ADRV9025_NULL = 0,          /*!< Initial value for board selection */
    ADI_BOARD_ADRV9025_BLANK_EEPROM = 1   /*!< Selects for no daughter board present */
} adi_board_adrv9025Sel_e;

typedef uintptr_t adi_board_GenericBoardType_t;

#ifdef __cplusplus
}
#endif

#endif
