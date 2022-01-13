/**
* \file adi_fpga9010.h
* \brief Contains top level fpga9010 related function prototypes for
*        adi_fpga9010.c
*
* FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
*/
/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_PRBS_H_
#define _ADI_FPGA9010_PRBS_H_

#include "adi_fpga9010_prbs_types.h"
#include "adi_fpga9010_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* \brief Enable PRBS generator on the selected TX lanes with the desired PRBS mode
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
* \param prbsSel 4 bit value selecting the prbs mode
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_PrbsSerializerEnable(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t prbsSel);

/**
* \brief Enable PRBS checker on the selected lanes RX with the desired PRBS mode
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
* \param prbsSel 4 bit value selecting the prbs mode
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_PrbsDeserializerEnable(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t prbsSel);

/**
* \brief Inject errors on the selected TX lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_PrbsSerializerErrorInject(adi_fpga9010_Device_t *device, uint8_t laneSelMask);

/**
* \brief  Reads FPGA deserializer PRBS error counts on all lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param errCounts an array of uint32_t of length 8. Will be set with the error count per lane
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_PrbsErrorCountRead(adi_fpga9010_Device_t *device, uint32_t *errCounts);

/**
* \brief  Clears the error counter on the selected RX lanes
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param laneSelMask to enable prbs on a lane set the corresponding bit to 1
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_PrbsErrorClear(adi_fpga9010_Device_t *device, uint8_t laneSelMask);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_PRBS_H_ */