/**
* \file adi_board_identify.h
* \brief Contains ADI Transceiver Hardware Abstraction functions interface
*        Analog Devices maintains and provides updates to this code layer.
*        The end user should not modify this file or any code in this directory.
*/

/**
* \Page Disclaimer Legal Disclaimer
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#ifndef __ADI_PLATFORM_IDENTIFY_H__
#define __ADI_PLATFORM_IDENTIFY_H__

#include "adi_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
* \brief Probe and identity the motherboard.
*
* \pre 
*
* \dep_begin
* \dep_end
*
*
* \param platform Pointer to return the platform identification
*
* \retval ADI_HAL_GEN_SW Recovery action for bad parameter check
* \retval ADI_HAL_OK Function completed successfully, no action required
*/
int32_t adi_platform_Identify(uint32_t* platform);

#ifdef __cplusplus
}
#endif
#endif /* __ADI_PLATFORM_IDENTIFY_H__ */
