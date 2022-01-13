/**
 * \file adi_ad9528_daughter_board.h
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_AD9528_DAUGHTER_BOARD_H_
#define _ADI_AD9528_DAUGHTER_BOARD_H_

#include "adi_ad9528.h"
#include "adi_motherboard_trx.h"

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
* Runtime functions
****************************************************************************
*/

    
/**
* \brief Performing selected task to initialize the daughterboard.
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param trxDaughterboard a pointer to generic daughterboard structure.
* \param actionFlags a selected task of initialization.
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_clock9528Board_Dispatch(adi_daughterboard_trx_t *trxDaughterboard, adrvtrx_board_action_e actionFlags);

#ifdef __cplusplus
}
#endif

#endif
