#ifndef _ADI_DAUGHTERBOARD_TRX_DEV_H_
#define _ADI_DAUGHTERBOARD_TRX_DEV_H_

#include "adi_daughterboard_trx_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
* Runtime functions
****************************************************************************
*/

/**
* \brief This function implements the following
*        Closes Device drivers in use by the requested board
*        Deallocates memory consumed by device HAL instances
*        Removes the daughter board instance from the list of daughter cards instantiated
*        Deallocates memory for device instances in the board requested
*        Updates the list of daughter boards active
*
* \dep_begin
* \dep{genericBoardHandle}
* \dep_end
*
* \param genericBoardHandle Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_daughterboard_Destroy(adi_daughterboard_trx_t* genericBoardHandle);

/**
* \brief This function creates a device board instance for daughter card
*        This function will create the clock instance
*        This function will also create the FPGA instance for motherboard
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_HAL_GEN_SW Recovery action returned in case of error (null pointer or unable to allocate structures)
* \retval ADI_COMMON_HAL_OK Function completed successfully

*/
int32_t adi_daughterboard_Create(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Function to Initialize the devices
*        This function will create the platform layer structures for the different devices
*        This function will open the HW needed for the devices
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_daughterboard_Init(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Function to Program the daughter card board
*        This function will program the devices that are contained in the daughter card board
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
int32_t adi_daughterboard_Program(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Function to execute Program Phase 1 the daughter card board
*        This function will program the devices that are contained in the daughter card board
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
int32_t adi_daughterboard_ProgramPhase1(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Function to execute Program Phase 2 the daughter card board
*        This function will program the devices that are contained in the daughter card board
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
int32_t adi_daughterboard_ProgramPhase2(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Function to Confgiure Board Clock Settings
*        This function will configure the Clock settings for the board
*
* \dep_begin
* \dep{ad9528Init}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
* \param clockInit Pointer to AD9528 clock device init structure.
* \param deviceClock_kHz Device clock frequency in kHz
* \param vcxoFreq_kHz VCXO clock frequency in kHz
* \param refAFreq_kHz RefA clock frequency in kHz
* \param fpgaClock_kHz FPGA clock frequency in kHz
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_daughterboard_ClockConfig(adi_daughterboard_trx_t* trxDaughterboard,
                                      uintptr_t                clockInit,
                                      uint32_t                 deviceClock_kHz,
                                      uint32_t                 vcxoFreq_kHz,
                                      uint32_t                 refAFreq_kHz,
                                      uint32_t                 fpgaClock_kHz);

/**
* \brief Function to bring up the JESD204 data link for the motherboard eval board.
*
* \pre This function is normally called by the Program_v2 
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
int32_t adi_daughterboard_JesdBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                      uint32_t                 txLinkSel,
                                      uint32_t                 rxLinkSel);

/**
* \brief Function to bring up the JESD204 TX data link for the motherboard eval board.
*
* \pre This function is normally called by the adi_daughterboard_JesdBringup 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
* \param txLinkSel Bitmask representing which RF TX links to enable (Bit0=1: Enable Deframer 0, Bit1=1: Enable Deframer 1)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_daughterboard_JesdTxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                        uint32_t                 txLinkSel);

/**
* \brief Function to bring up the JESD204 RX data link for the motherboard eval board.
*
* \pre This function is normally called by the adi_daughterboard_JesdBringup 
*      function and is not required by the end user.  It would be called after
*      post MCS init.
*
* \dep_begin
* \dep{trxDaughterboard}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
* \param rxLinkSel Bitmask representing which RF RX links to enable (Bit0=1: Enable Framer 0, Bit1=1: Enable Framer 1, Bit2=1: Enable Framer 2)
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_daughterboard_JesdRxBringup(adi_daughterboard_trx_t* trxDaughterboard,
                                        uint32_t                 rxLinkSel);

/**
* \brief Resets the Data Interface with the appropriate procedure based on the daughterboard
*        type.
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_daughterboard_DataInterfaceReset(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Initializes the AD9528 by writing all SPI registers
*
* Initializes the AD9528 using the values passed in through the adi_daughterboard_trx_t structure.
*
* <B>Dependencies</B>
* - All parameters in init structure
* - device->common.devHalInfo
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter
*  check
*/
int32_t adi_daughterboard_Ad9528Init(adi_daughterboard_trx_t* trxDaughterboard);

/**
* \brief Initializes the FPGA device
*
* Initializes the FPGA using the values passed in through the adi_daughterboard_trx_t structure.
*
* \pre adi_fpga9010Board_Dispatch API invoked and completed successfully
*
* \param trxDaughterboard Pointer to the generic board instance
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
*/
int32_t adi_daughterboard_FpgaInit(adi_daughterboard_trx_t* trxDaughterboard);

#ifdef __cplusplus
}
#endif

#endif
