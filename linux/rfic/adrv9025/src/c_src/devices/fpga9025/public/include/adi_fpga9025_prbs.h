/**
* \file adi_fpga9025.h
* \brief Contains top level fpga9025 related function prototypes for
*        adi_fpga9025.c
*
* FPGA9025 API Version: 6.0.0.41
*/
/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_PRBS_H_
#define _ADI_FPGA9025_PRBS_H_

#include "adi_fpga9025_prbs_types.h"
#include "adi_fpga9025_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \brief Enable PRBS generator on the selected TX lanes with the desired PRBS mode
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
* \param prbsSel 4 bit value selecting the prbs mode
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_PrbsSerializerEnable(adi_fpga9025_Device_t*       device,
                                          uint8_t                      laneSelMask,
                                          adi_fpga9025_PrbsTestModes_e prbsModeSel);

/**
* \brief Enable PRBS checker on the selected lanes RX with the desired PRBS mode
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
* \param prbsSel 4 bit value selecting the prbs mode
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_PrbsDeserializerEnable(adi_fpga9025_Device_t*       device,
                                            uint8_t                      laneSelMask,
                                            adi_fpga9025_PrbsTestModes_e prbsModeSel);

/**
* \brief Inject errors on the selected TX lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_PrbsSerializerErrorInject(adi_fpga9025_Device_t* device,
                                               uint8_t                laneSelMask);

/**
* \brief  Reads FPGA deserializer PRBS error counts on all lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param errCounts an array of uint32_t of length 8. Will be set with the error count per lane
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_PrbsErrorCountRead(adi_fpga9025_Device_t* device,
                                        uint32_t*              errCounts);

/**
* \brief  Clears the error counter on the selected RX lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_PrbsErrorClear(adi_fpga9025_Device_t* device,
                                    uint8_t                laneSelMask);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_PRBS_H_ */
