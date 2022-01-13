/**
 * \file adi_board_adrv9025ADS8.h
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_BOARD_ADRV9025ADS8_H_
#define _ADI_BOARD_ADRV9025ADS8_H_

#include "adi_adrv9025_daughter_board_types.h"
#include "adi_board_adrv9025ADS8_types.h"
#include "adi_adrv9025_utilities_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* \brief Function to configure the AD9528 init structure for the CE daughtercard based 
*        on the desired device clock. This function will NOT program the AD9528.
*
* \pre This function is called after the devices are Create()
*      Init() have been called
*
* \dep_begin
* \dep{ad9528Device, ad9528Init}
* \dep_end
*
* \param ad9528Device Pointer to AD9528 device data structure
* \param ad9528Init Pointer to AD9528 clock device init structure
* \param deviceClock_kHz Desired device clock in kHz
* \param vcxoFreq_kHz Frequency of the AD9528 Vcxo input in kHz
* \param refAFreq_kHz Frequency of the AD9528 RefA input in kHz
* \param fpgaClock_kHz Desired fpga clock in kHz
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025ADS8_Ad9528Configure(adi_board_adrv9025Ads8_t* adrv9025ADS8,
                                               adi_ad9528_Init_t*        ad9528Init,
                                               uint32_t                  deviceClock_kHz,
                                               uint32_t                  vcxoFreq_kHz,
                                               uint32_t                  refAFreq_kHz,
                                               uint32_t                  fpgaClock_kHz);

/**
* \brief Function to bring up the JESD204 data link for the adrv9025ADS8 eval board.
*
* \pre This function is normally called by the adi_board_adrv9025ADS8_Program_v2 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{adrv9025Device, fpga9010Device, ad9528Device}
* \dep_end
*
* \param adrv9025Device Pointer to ADRV9025 device data structure
* \param fpga9010Device Pointer to FPGA device data structure
* \param ad9528Device Pointer to AD9528 device data structure
* \param txLinkSel Bitmask representing which RF TX links to enable (Bit0=1: Enable Deframer 0, Bit1=1: Enable Deframer 1)
* \param rxLinkSel Bitmask representing which RF RX links to enable (Bit0=1: Enable Framer 0, Bit1=1: Enable Framer 1, Bit2=1: Enable Framer 2)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025ADS8_JesdBringup(adi_adrv9025_Device_t* adrv9025Device,
                                           adi_fpga9010_Device_t* fpgaDevice,
                                           adi_ad9528_Device_t*   ad9528Device,
                                           uint32_t               txLinkSel,
                                           uint32_t               rxLinkSel);

/**
* \brief Function to bring up the JESD204 TX data link for the adrv9025ADS8 eval board.
*
* \pre This function is normally called by the adi_board_adrv9025ADS8_JesdBringup 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{adrv9025Device, fpga9010Device, ad9528Device}
* \dep_end
*
* \param adrv9025Device Pointer to ADRV9025 device data structure
* \param fpga9010Device Pointer to FPGA device data structure
* \param ad9528Device Pointer to AD9528 device data structure
* \param link Bitmask representing which RF TX links to enable (Bit0=1: Enable Deframer 0, Bit1=1: Enable Deframer 1)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025ADS8_JesdTxBringup(adi_adrv9025_Device_t* adrv9025Device,
                                             adi_fpga9010_Device_t* fpga9010Device,
                                             adi_ad9528_Device_t*   ad9528Device,
                                             uint32_t               link);

/**
* \brief Function to bring up the JESD204 RX data link for the adrv9025ADS8 eval board.
*
* \pre This function is normally called by the adi_board_adrv9025ADS8_JesdBringup 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{adrv9025Device, fpga9010Device, ad9528Device}
* \dep_end
*
* \param adrv9025Device Pointer to ADRV9025 device data structure
* \param fpga9010Device Pointer to FPGA device data structure
* \param ad9528Device Pointer to AD9528 device data structure
* \param link Bitmask representing which RF RX links to enable (Bit0=1: Enable Framer 0, Bit1=1: Enable Framer 1, Bit2=1: Enable Framer 2)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025ADS8_JesdRxBringup(adi_adrv9025_Device_t* adrv9025Device,
                                             adi_fpga9010_Device_t* fpga9010Device,
                                             adi_ad9528_Device_t*   ad9528Device,
                                             uint32_t               link);

int32_t adi_board_adrv9025ADS8_Program_Phase1(adi_board_adrv9025Ads8_t*     adrv9025Ce01,
                                              adi_adrv9025_Init_t*          adrv9025Init,
                                              adi_ad9528_Init_t*            ad9528Init,
                                              adi_adrv9025_PlatformFiles_t* adrv9025PlatformFiles);

int32_t adi_board_adrv9025ADS8_Program_Phase2(adi_board_adrv9025Ads8_t*   adrv9025Ce01,
                                              adi_adrv9025_Init_t*        adrv9025Init,
                                              adi_adrv9025_PostMcsInit_t* adrv9025PostMcsInit,
                                              adi_ad9528_Init_t*          ad9528Init);

/**
* \brief Function to reset and bring JESD204 links up using parameters from the init structure
*
* \pre This function is called after the devices are Create()
*      Init() have been called
*
* \dep_begin
* \dep{adrv9025Device, adrv9025Init}
* \dep_end
*
* \param adrv9025ADS8 Pointer to adrv9025ADS8 daughter card instance to be programmed
* \param adrv9025Init Pointer to ADRV9025 Init data structure configured with the profile data
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025ADS8_Jesd204LinkReset(adi_board_adrv9025Ads8_t* adrv9025ADS8,
                                                adi_adrv9025_Init_t*      adrv9025Init);

#ifdef __cplusplus
}
#endif

#endif
