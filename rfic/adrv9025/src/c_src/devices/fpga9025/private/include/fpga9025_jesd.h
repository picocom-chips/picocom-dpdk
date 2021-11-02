/**
* \file fpga9025_jesd.h
* \brief Contains private JESD related function prototypes for fpga9025_jesd.c
*
* FPGA9025 API Version: 6.0.0.41
*/
/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _FPGA9025_JESD_H_
#define _FPGA9025_JESD_H_

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t adi_fpga9025_SerializerCfgSet(adi_fpga9025_Device_t*        device,
                                      uint8_t                       laneSelMask,
                                      adi_fpga9025_SerializerCfg_t* serializerCfg);

int32_t adi_fpga9025_SerializerCfgGet(adi_fpga9025_Device_t*        device,
                                      adi_fpga9025_LaneSel_e        laneSel,
                                      adi_fpga9025_SerializerCfg_t* serializerCfg);

/**
* \brief JESD204B implementation for adi_fpga9025_DeframerCfgSet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param deframerCfg a pointer to an adi_fpga9025_DeframerCfg_t structure that contains the deframer configuration settings
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BDeframerCfgSet(adi_fpga9025_Device_t*      device,
                                        uint32_t                    deframerSelMask,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg);

/**
* \brief JESD204B implementation for adi_fpga9025_DeframerCfgGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSel an adi_fpga9025_DeframerSel_e enum value selecting which deframer to read
* \param deframerCfg a pointer to an empty adi_fpga9025_DeframerCfg_t structure
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BDeframerCfgGet(adi_fpga9025_Device_t*      device,
                                        adi_fpga9025_DeframerSel_e  deframerSel,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg);

/**
* \brief JESD204B implementation for adi_fpga9025_FramerCfgSet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param framerCfg pointer to an adi_fpga9025_FramerCfg_t structure that contains the deserializer configuration settings
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BFramerCfgSet(adi_fpga9025_Device_t*    device,
                                      uint8_t                   framerSelMask,
                                      adi_fpga9025_FramerCfg_t* framerCfg);

/**
* \brief  JESD204B implementation for adi_fpga9025_FramerCfgGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSel an adi_fpga9025_FramerSel_e enum value selecting a single framer
* \param framerCfg pointer to an empty adi_fpga9025_FramerCfg_t structure
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BFramerCfgGet(adi_fpga9025_Device_t*    device,
                                      adi_fpga9025_FramerSel_e  framerSel,
                                      adi_fpga9025_FramerCfg_t* framerCfg);

/**
* \brief  JESD204B helper function for FramerResetGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param resetBits uint8_t pointer for the reset bits of the selected deframers that will correspond with their adi_fpga9025_FramerSel_e bit locations
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BFramerResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               framerSelMask,
                                        uint8_t*               resetBits);

/**
* \brief  JESD204B helper function for FramerReset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BFramerReset(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask);

/**
* \brief JESD204B helper function for DeframerReset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BDeframerReset(adi_fpga9025_Device_t* device,
                                       uint8_t                deframerSelMask);

/**
* \brief JESD204B helper function for DeframerDisable.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BDeframerDisable(adi_fpga9025_Device_t* device,
                                         uint8_t                deframerSelMask);

/**
* \brief  JESD204B helper function for FramerDisable.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BFramerDisable(adi_fpga9025_Device_t* device,
                                       uint8_t                framerSelMask);

/**
* \brief JESD204B helper function for DeframerStatusGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param status uint8_t pointer for the Sync status bits of the selected deframers that will correspond with their adi_fpga9025_DeframerSel_e bit locations
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204BDeframerStatusGet(adi_fpga9025_Device_t* device,
                                           uint8_t                deframerSelMask,
                                           uint8_t*               status);

/**
* \brief  JESD204C implementation for adi_fpga9025_DeframerCfgSet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param deframerCfg a pointer to an adi_fpga9025_DeframerCfg_t structure that contains the deframer configuration settings
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CDeframerCfgSet(adi_fpga9025_Device_t*      device,
                                        uint32_t                    deframerSelMask,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg);

/**
* \brief  JESD204C implementation for adi_fpga9025_DeframerCfgGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device pointer to the FPGA9025 device data structure.
* \param deframerSel an adi_fpga9025_DeframerSel_e enum value selecting which deframer to read
* \param deframerCfg a pointer to an empty adi_fpga9025_DeframerCfg_t structure
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CDeframerCfgGet(adi_fpga9025_Device_t*      device,
                                        adi_fpga9025_DeframerSel_e  deframerSel,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg);

/**
* \brief JESD204C implementation for adi_fpga9025_FramerCfgSet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param framerCfg pointer to an adi_fpga9025_FramerCfg_t structure that contains the deserializer configuration settings
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CFramerCfgSet(adi_fpga9025_Device_t*    device,
                                      uint32_t                  framerSelMask,
                                      adi_fpga9025_FramerCfg_t* framerCfg);

/**
* \brief  JESD204C implementation for adi_fpga9025_FramerCfgGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSel an adi_fpga9025_FramerSel_e enum value selecting a single framer
* \param framerCfg pointer to an empty adi_fpga9025_FramerCfg_t structure
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CFramerCfgGet(adi_fpga9025_Device_t*    device,
                                      adi_fpga9025_FramerSel_e  framerSel,
                                      adi_fpga9025_FramerCfg_t* framerCfg);

/**
* \brief  JESD204C helper function for FramerResetGet.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
* \param resetBits uint8_t pointer to reset bits of the selected deframers which will correspond with their adi_fpga9025_FramerSel_e bit locations
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CFramerResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               framerSelMask,
                                        uint8_t*               resetBits);

/**
* \brief  JESD204C helper function for FramerReset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CFramerReset(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask);

/**
* \brief JESD204C helper function for DeframerReset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CDeframerReset(adi_fpga9025_Device_t* device,
                                       uint8_t                deframerSelMask);

/**
* \brief JESD204C helper function for DeframerDisable.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CDeframerDisable(adi_fpga9025_Device_t* device,
                                         uint8_t                deframerSelMask);

/**
* \brief  JESD204C helper function for FramerDisable.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param framerSelMask an or'd combination of one or more adi_fpga9025_FramerSel_e enum values
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CFramerDisable(adi_fpga9025_Device_t* device,
                                       uint8_t                framerSelMask);

/**
* \brief  JESD204C helper function for DeframerStatusGet. The status bit for each link will be a logical
*           and of mb_lock & sync_header_lock bitfield values.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param deframerSelMask an or'd combination of one or more adi_fpga9025_DeframerSel_e enum values
* \param status uint8_t pointer for the Sync status bits of the selected deframers that will correspond with their adi_fpga9025_DeframerSel_e bit locations
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_Jesd204CDeframerStatusGet(adi_fpga9025_Device_t* device,
                                           uint8_t                deframerSelMask,
                                           uint8_t*               status);

#ifdef __cplusplus
}
#endif

#endif /* _FPGA9025_JESD_H_ */
