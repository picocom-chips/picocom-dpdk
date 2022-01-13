/**
 * \file: adi_fpga9025_jesd.h
 *
 * \brief Contains top level tx fpga9025 related prototypes
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_JESD_H_
#define _ADI_FPGA9025_JESD_H_

#include "adi_fpga9025_types.h"
#include "adi_fpga9025_jesd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t adi_fpga9025_SerializerCfgSet(adi_fpga9025_Device_t*        device,
                                      uint8_t                       laneSelMask,
                                      adi_fpga9025_SerializerCfg_t* serializerCfg);

/**
* \brief reads  the configuration to one or more FPGA JESD204B Serializer
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSel an  adi_fpga9025_LaneSel_e enum value
* \param serializerCfg  contains the serializer configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SerializerCfgGet(adi_fpga9025_Device_t*        device,
                                      adi_fpga9025_LaneSel_e        laneSel,
                                      adi_fpga9025_SerializerCfg_t* serializerCfg);

/**
* \brief Sets the reset bit for both rx & tx channel in the selected lanes
*        Used as part of PHY bring up
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask an  adi_fpga9025_LaneSel_e enum value
* \param resetVal  either 0 or 1. Value to be written to the reset bit (1 to reset; 0 to release reset)
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SerializerResetSet(adi_fpga9025_Device_t* device,
                                        uint8_t                laneSelMask,
                                        uint8_t                resetVal);

/**
* \brief Returns the tx reset done for all eight PHY lanes
*        Note: channels must have stable clock input for Reset Done to be set
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txResetDone pointer that will be assigned each lanes tx reset done bit
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SerializerResetDoneGet(adi_fpga9025_Device_t* device,
                                            uint8_t*               txResetDone);

/**
* \brief Sets the lane cpll power down bit
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask mask to select which channels to apply pdVal
* \param pdVal  either 0 or 1. Value to be written to the cpll power down bit (1 to reset; 0 to release reset)
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_LaneCpllPdSet(adi_fpga9025_Device_t* device,
                                   uint8_t                laneSelMask,
                                   uint8_t                pdVal);

/**
* \brief writes  the configuration of one or more FPGA JESD204B Deserializers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask an or'd combination of one or more adi_fpga9025_LaneSel_e enum values
* \param deserializerCfg  contains the deserializer configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeserializerCfgSet(adi_fpga9025_Device_t*          device,
                                        uint8_t                         laneSelMask,
                                        adi_fpga9025_DeserializerCfg_t* deserializerCfg);

/**
* \brief reads  the configuration to one or more FPGA JESD204B Deserializer
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSel an  adi_fpga9025_LaneSel_e enum value
* \param deserializerCfg  contains the deserializer configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeserializerCfgGet(adi_fpga9025_Device_t*          device,
                                        const adi_fpga9025_LaneSel_e    laneSel,
                                        adi_fpga9025_DeserializerCfg_t* deserializerCfg);

/**
* \brief Sets the reset bit for both rx channel in the selected lanes
*        Used as part of PHY bring up
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask an  adi_fpga9025_LaneSel_e enum value
* \param resetVal  either 0 or 1. Value to be written to the reset bit (1 to reset; 0 to release reset)
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeserializerResetSet(adi_fpga9025_Device_t* device,
                                          uint8_t                laneSelMask,
                                          uint8_t                resetVal);

/**
* \brief Returns the rx reset done for all eight lanes
*        Note: channels must have stable clock input for Reset Done to be set
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxResetDone pointer that will be assigned each lanes rx reset done bit
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeserializerResetDoneGet(adi_fpga9025_Device_t* device,
                                              uint8_t*               rxResetDone);

/**
* \brief    This function writes the adi_fpga9025_DeframerCfg_t structure to the framer modules
 *          selected in the deframerSelMask, where the bit location corresponds to the rx link number.
 *          This function is used in the link bringup sequence just prior to reset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param deframerCfg  contains the deserializer configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeframerCfgSet(adi_fpga9025_Device_t*      device,
                                    uint32_t                    deframerSelMask,
                                    adi_fpga9025_DeframerCfg_t* deframerCfg);

/**
* \brief    Reads the configuration for a single deframer module and populates the empty adi_fpga9025_DeframerCfg_t
*           structure pointed to by deframerCfg.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSel an  adi_fpga9025_LinkSel_e enum value
* \param deframerCfg  contains the deframer configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeframerCfgGet(adi_fpga9025_Device_t*      device,
                                    adi_fpga9025_DeframerSel_e  deframerSel,
                                    adi_fpga9025_DeframerCfg_t* deframerCfg);

/**
* \brief Unimplemented
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param resetBits the reset bits of the selected deframers will correspond with their adi_fpga9025_DeframerSel_e bit locations
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeframerResetGet(adi_fpga9025_Device_t* device,
                                      uint32_t               deframerSelMask,
                                      uint8_t*               resetBits);

/**
* \brief   This function writes the adi_fpga9025_FramerCfg_t structure to the framer modules
*          selected in the framerSelMask, where the bit location corresponds to the tx link number.
*          This function is used in the link bringup sequence just prior to reset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param framerCfg  contains the deserializer configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_FramerCfgSet(adi_fpga9025_Device_t*    device,
                                  uint8_t                   framerSelMask,
                                  adi_fpga9025_FramerCfg_t* framerCfg);

/**
* \brief    Reads the configuration for a single framer module and populates the empty adi_fpga9025_FramerCfg_t
*           structure pointed to by framerCfg.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSel an adi_fpga9025_FramerSel_e enum value selecting a single framer
* \param framerCfg pointer to an empty adi_fpga9025_FramerCfg_t structure
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_FramerCfgGet(adi_fpga9025_Device_t*    device,
                                  adi_fpga9025_FramerSel_e  framerSel,
                                  adi_fpga9025_FramerCfg_t* framerCfg);

/**
* \brief    Reads the reset bit for the selected framers in framerSelMask and sets the corresponding bit
*           in resetBits.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param resetBits the reset bits of the selected deframers will correspond with their adi_fpga9025_FramerSel_e bit locations
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_FramerResetGet(adi_fpga9025_Device_t* device,
                                    uint32_t               framerSelMask,
                                    uint8_t*               resetBits);

/**
* \brief    Sets the configuration for the first eight outputs of the Lane XBar for the selected link using
*           framerSel.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSel adi_fpga9025_FramerSel_e enum value to select the laneXBar
* \param laneXBar  an eight element array holding the PHY lane assignments for each output lane
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxLaneXBarCfgSet(adi_fpga9025_Device_t*   device,
                                      adi_fpga9025_FramerSel_e framerSel,
                                      uint8_t*                 laneXBar);

/**
* \brief Sets the configuration for the first eight outputs of the Lane XBar
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSel adi_fpga9025_DeframerSel_e enum value to select which deframer
* \param laneXBar  an eight element array holding the PHY lane assignments for each output lane
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxLaneXBarCfgSet(adi_fpga9025_Device_t*     device,
                                      adi_fpga9025_DeframerSel_e deframerSel,
                                      uint8_t*                   laneXBar);

/**
* \brief    Reads the configuration for the first eight outputs of the Lane XBar for the selected link using
*           framerSel and stores them in the eight-element laneXBar array.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSel adi_fpga9025_FramerSel_e enum value to select which framer
* \param laneXBar  an eight element array where the lane assignments will be written to
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxLaneXBarCfgGet(adi_fpga9025_Device_t*   device,
                                      adi_fpga9025_FramerSel_e framerSel,
                                      uint8_t*                 laneXBar);

/**
* \brief Gets the configuration for the first eight outputs of the Lane XBar
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSel adi_fpga9025_DeframerSel_e enum value to select which deframer
* \param laneXBar  an eight element array where the lane assignments will be written to
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxLaneXBarCfgGet(adi_fpga9025_Device_t*     device,
                                      adi_fpga9025_DeframerSel_e deframerSel,
                                      uint8_t*                   laneXBar);

/**
* \brief    This function goes through the reset sequence for the selected framers in 
*           framerSelMask, where the bit location corresponds to the tx link number. This
*           function should be called after adi_fpga9025_FramerCfgSet as part of link bringup.
*           After this function the framer is ready for sysref signal.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_FramerReset(adi_fpga9025_Device_t* device,
                                 uint8_t                framerSelMask);

/**
* \brief    This function disables all framers selected through the framerSelMask by setting
*           the fixed reset bit.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_FramerDisable(adi_fpga9025_Device_t* device,
                                   uint8_t                framerSelMask);

/**
* \brief Enables the FPGA JESD204B Rx deframer
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeframerReset(adi_fpga9025_Device_t* device,
                                   uint8_t                deframerSelMask);

/**
* \brief Disables the FPGA JESD204B Rx deframer
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeframerDisable(adi_fpga9025_Device_t* device,
                                     uint8_t                deframerSelMask);

/**
* \brief    For JESD204B returns the Sync status bit for the selected deframers in deframerSelMask.
*           For JESD204C The status bit for each link will be a logical
*           and of mb_lock & sync_header_lock bitfield values.           
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param status the Sync status bits of the selected deframers will correspond with their adi_fpga9025_DeframerSel_e bit locations
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DeframerStatusGet(adi_fpga9025_Device_t* device,
                                       uint8_t                deframerSelMask,
                                       uint8_t*               status);

/**
* \brief sets the loopback value for the selected lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
* \param loopbackValue sets the loopback mode, eg 2 for near-end PCS loopback
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_ChannelLoopbackEnable(adi_fpga9025_Device_t* device,
                                           uint8_t                laneSelMask,
                                           uint8_t                loopbackValue);

/**
* \brief sets the DFE LPM Override value for the selected lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
* \param value sets the DFE LPM Override value (1 to override, 0 to disable override)
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_ChannelDfeLpmOverrideSet(adi_fpga9025_Device_t* device,
                                              uint8_t                laneSelMask,
                                              uint8_t                value);

/**
* \brief Sets the configuration for the sync crossbar
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param polarity The sync xbar polarity.
* \param inputSyncSel  an array of eight 3-bit values indicating the input sync selection for each sync crossbar output
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SyncXBarCfgSet(adi_fpga9025_Device_t* device,
                                    uint8_t                polarity,
                                    uint8_t*               inputSyncSel);

/**
* \brief Reads the configuration for the sync crossbar
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param polarity Pointer to the sync xbar polarity.
* \param inputSyncSel  an array of eight uin8_t types. Will be filled with the 3-bit values from the input select registers
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SyncXBarCfgGet(adi_fpga9025_Device_t* device,
                                    uint8_t*               polarity,
                                    uint8_t*               inputSyncSel);

/**
* \brief Setup the FPGA JESD204 reference clock and SYSREF settings
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param    device Pointer to the FPGA9025 device data structure.
* \param    sysRefCfg FPGA JESD204B clock structure settings for the reference clock
*           frequency and SYSREF configuration
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SysRefControlSet(adi_fpga9025_Device_t*       device,
                                      adi_fpga9025_SysRefClkCfg_t* sysRefCfg);

/**
* \brief Enable or disable Sysref for the selected Framers and Deframers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param    device Pointer to the FPGA9025 device data structure.
* \param    framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param    deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param    enable ADI_ENABLE or ADI_DISABLE to enable or disable respectively
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SysRefEnableSet(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask,
                                     uint8_t                deframerSelMask,
                                     uint8_t                enable);

/**
* \brief Reads the FPGA JESD204 reference clock and SYSREF settings
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param    device Pointer to the FPGA9025 device data structure.
* \param    sysRefCfg FPGA JESD204B clock structure settings for the reference clock
*           frequency and SYSREF configuration
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SysRefControlGet(adi_fpga9025_Device_t*       device,
                                      adi_fpga9025_SysRefClkCfg_t* sysRefCfg);

/**
* \brief Requests a SYSREF to be issued
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SysRefRequest(adi_fpga9025_Device_t* device);

/**
* \brief    This function will set the interrupt enabled register in the JESD204C link layer. The parameter
*           interruptBitMask is an or'd combination of the adi_fpga9025_Jesd204cIrq_e enum.
*           The linkSelMask parameter is a bitmask that encapsulates the Rx & Tx links, ie:
*
*         linkSelMask   |  Link
* ----------------------|------------------------------------
*   Bit 0               | RX Link 0
*   Bit 1               | RX Link 1
*   Bit 2               | RX Link 2
*   Bit 3               | TX Link 0
*   Bit 4               | TX Link 1
*
*           For the Set function, any number of links can be set with the same interruptBitMask value.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param interruptBitMask uint16_t bitmask of adi_fpga9025_Jesd204cIrq_e indicating the IRQs to be enabled/disabled.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_Jesd204cLinkLayerIrqEnSet(adi_fpga9025_Device_t* device,
                                               uint8_t                linkSelMask,
                                               uint16_t               interruptBitMask);

/**
* \brief    This function will read the interrupt enabled register in the JESD204C link layer. The parameter
*           interruptBitMask will be a bitmask indicating which IRQs are enabled. It is structured off the
*           adi_fpga9025_Jesd204cIrq_e enum.
*           The linkSel parameter is a bitmask that encapsulates the Rx & Tx links, ie:
*
*         linkSel       |  Link
* ----------------------|------------------------------------
*   Bit 0               | RX Link 0
*   Bit 1               | RX Link 1
*   Bit 2               | RX Link 2
*   Bit 3               | TX Link 0
*   Bit 4               | TX Link 1
*
            For the Get functions, only one bit can be set in linkSel per function call.

* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param linkSelMask a bitmask to choose between Rx & Tx links
* \param interruptBitMask uint16_t pointer that will contain which IRQs are enabled/disabled.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_Jesd204cLinkLayerIrqEnGet(adi_fpga9025_Device_t* device,
                                               uint8_t                linkSelMask,
                                               uint16_t*              interruptBitMask);

/**
* \brief    This function will read the interrupt status register in the JESD204C link layer. The parameter
*           interruptBitMask will be a bitmask indicating which IRQs have been triggered. It is structured off the
*           adi_fpga9025_Jesd204cIrq_e enum.
*           The linkSel parameter is a bitmask that encapsulates the Rx & Tx links, ie:
*
*         linkSel       |  Link
* ----------------------|------------------------------------
*   Bit 0               | RX Link 0
*   Bit 1               | RX Link 1
*   Bit 2               | RX Link 2
*   Bit 3               | TX Link 0
*   Bit 4               | TX Link 1
*
            For the Get functions, only one bit can be set in linkSel per function call.

* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param linkSel a bitmask to choose a single Rx or Tx link
* \param interruptBitMask uint16_t pointer that will contain which IRQs are triggered with a 1 in their respective bit location.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_Jesd204cLinkLayerIrqStatusGet(adi_fpga9025_Device_t* device,
                                                   uint8_t                linkSel,
                                                   uint16_t*              interruptBitMask);

/**
* \brief Enables or disables the Command and Data interface of the Deframer's selected through the deframerSelMask bitmask.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param cmdEnable ADI_ENABLE or ADI_DISABLE to enable and disable the command interface 
* \param dataEnable ADI_ENABLE or ADI_DISABLE to enable and disable the data interface 
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_Jesd204CDeframerCmdDataSet(adi_fpga9025_Device_t* device,
                                                uint32_t               deframerSelMask,
                                                uint8_t                cmdEnable,
                                                uint8_t                dataEnable);

/**
* \brief Enables or disables the Command and Data interface of the Framer's selected through the framerSelMask bitmask.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param cmdEnable ADI_ENABLE or ADI_DISABLE to enable and disable the command interface
* \param dataEnable ADI_ENABLE or ADI_DISABLE to enable and disable the data interface
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_Jesd204CFramerCmdDataSet(adi_fpga9025_Device_t* device,
                                              uint32_t               framerSelMask,
                                              uint8_t                cmdEnable,
                                              uint8_t                dataEnable);

/**
* \brief Enable or disable Sysref for the selected Framers and Deframers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param    device Pointer to the FPGA9025 device data structure.
* \param    framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param    deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param    enable ADI_ENABLE or ADI_DISABLE to enable or disable respectively
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_SysRefEnableSet(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask,
                                     uint8_t                deframerSelMask,
                                     uint8_t                enable);

int32_t adi_fpga9025_InternalSysrefEnableSet(adi_fpga9025_Device_t* device,
                                             uint8_t                enable);

int32_t adi_fpga9025_InternalSysrefRequest(adi_fpga9025_Device_t* device);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_JESD_H_ */
