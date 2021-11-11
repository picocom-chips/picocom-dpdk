/**
 * \file adi_adrv9025_daughter_board.h
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_ADRV9025_DAUGHTER_BOARD_H_
#define _ADI_ADRV9025_DAUGHTER_BOARD_H_


#include "adi_adrv9025_daughter_board_types.h"
#include "adi_adrv9025_types.h"
#include "adi_common_macros.h"
#include "adi_adrv9025_user.h"
#include "adi_adrv9025_utilities.h"
#include "adi_fpga9025.h"
#include "adi_ad9528.h"
#include "adi_motherboard_trx.h"

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* Runtime functions
****************************************************************************
*/
/**
* \brief This function reads the board EEPROM and updates the global genericBoardHandle
*        if initializing or a new board has been placed on the platform. In both of those
*        cases it will also call adi_adrv9025Board_Create and adi_adrv9025Board_Init.
*        If the board has not changed since the previous call nothing will be done.
*
* \dep_begin
* \dep_end
*
* \param genericBoardHandle Address of the global genericBoardHandle
* \param adrv9025BoardSel Address of the global adrv9025BoardSel enum
*        (currently supported boards are EE01 and CE01)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_adrv9025Board_Discover(adi_board_GenericBoardType_t*** genericBoardHandle,
                                   adi_board_adrv9025Sel_e*        adrv9025BoardSel);

/**
* \brief Returns the iqRate for the selected ADRV9025 Framer. If the selected Framer has an M equal to 0,
*        the function will return 0 for iqRate.
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param device Pointer to the ADRV9025 device data structure containing settings
* \param adrv9025Init Pointer to the ADRV9025 init structure
* \param framerSel Select the framer to read
* \param iqRate_kHz Pointer to uint32_t where the iqRate_kHz will be written
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_adrv9025Board_RxLinkSamplingRateFind(adi_fpga9025_Device_t*   device,
                                                 adi_adrv9025_Init_t*     adrv9025Init,
                                                 adi_adrv9025_FramerSel_e framerSel,
                                                 uint32_t*                iqRate_kHz);

/**
* \brief Returns the iqRate for the selected ADRV9025 Deframer. If the selected Deframer has an M equal to 0,
*        the function will return 0 for iqRate.
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param device Pointer to the ADRV9025 device data structure containing settings
* \param adrv9025Init Pointer to the ADRV9025 init structure
* \param deframerSel Select the deframer to read
* \param iqRate_kHz Pointer to uint32_t where the iqRate_kHz will be written
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_adrv9025Board_TxLinkSamplingRateFind(adi_fpga9025_Device_t*     device,
                                                 adi_adrv9025_Init_t*       adrv9025Init,
                                                 adi_adrv9025_DeframerSel_e deframerSel,
                                                 uint32_t*                  iqRate_kHz);

/**
* \brief Using the ADI daughter card EEPROM BOM REV (3rd custom FMC) field, this function will 
*        override the profile ldoSelect setting with the correct setting for the EEPROM contents.
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param adrv9025Init Pointer to the ADRV9025 init structure
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_adrv9025Board_LdoSelectOverRide(adi_adrv9025_Init_t* adrv9025Init);

/**
* \brief Resets the Data Interface with the appropriate procedure based on the daughterboard
*        type.
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param adrv9025Board adi_board_GenericBoardType_t Pointer to the ADRV9025 daughter card instance
*                                                   to be programmed
* \param adrv9025BoardSel is the enum to select the daughter card (EE01 / CE01)
* \param adrv9025Init Pointer to the ADRV9025 init structure
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_adrv9025Board_DataInterfaceReset(adi_board_GenericBoardType_t* adrv9025Board,
                                             adi_board_adrv9025Sel_e       adrv9025BoardSel,
                                             adi_adrv9025_Init_t*          adrv9025Init);

/**
* \brief Function to configure the AD9528 init structure for the daughtercard based 
*        on the desired device clock. This function will NOT program the AD9528.
*
* \pre This function is called after the devices are Create()
*      Init() have been called
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
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
int32_t adi_board_adrv9025_Ad9528Configure(adi_daughterboard_trx_t* trxDaughterboard,
                                           uint32_t                 deviceClock_kHz,
                                           uint32_t                 vcxoFreq_kHz,
                                           uint32_t                 refAFreq_kHz,
                                           uint32_t                 fpgaClock_kHz);

/**
* \brief Function to bring up the JESD204 data link for the ADRV9025 eval board.
*
* \pre This function is normally called by the adi_board_adrv9025_Program_Phase2 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
* \param txLinkSel Bitmask representing which RF TX links to enable (Bit0=1: Enable Deframer 0, Bit1=1: Enable Deframer 1)
* \param rxLinkSel Bitmask representing which RF RX links to enable (Bit0=1: Enable Framer 0, Bit1=1: Enable Framer 1, Bit2=1: Enable Framer 2)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025_JesdBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                       uint32_t                 txLinkSel,
                                       uint32_t                 rxLinkSel);

/**
* \brief Function to bring up the JESD204 TX data link for the ADRV9025CE01 eval board.
*
* \pre This function is normally called by the adi_board_adrv9025_JesdBringup 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
* \param link Bitmask representing which RF TX links to enable (Bit0=1: Enable Deframer 0, Bit1=1: Enable Deframer 1)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025_JesdTxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                         uint32_t                 link);

/**
* \brief Function to bring up the JESD204 RX data link for the ADRV9025CE01 eval board.
*
* \pre This function is normally called by the adi_board_adrv9025CE01_JesdBringup 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
* \param link Bitmask representing which RF RX links to enable (Bit0=1: Enable Framer 0, Bit1=1: Enable Framer 1, Bit2=1: Enable Framer 2)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025CE01_JesdRxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                             uint32_t                 link);

/**
* \brief Function to reset and bring JESD204 links up using parameters from the daughterboard structure
*
* \pre This function is called after the devices are Create()
*      Init() have been called
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025CE01_Jesd204LinkReset(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Function to initialize the clock device
*
* \pre This function is called during the daughtercard initialization.
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_board_adrv9025_Ad9528Init(adi_daughterboard_trx_t* trxDaughterboard);

#ifdef __cplusplus
}
#endif

#endif
