/**
* \file fpga9025_tdd.h
* \brief Contains private tdd related function prototypes for fpga9025_tdd.h
*
* FPGA9025 API Version: 6.0.0.41
*/
/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _FPGA9025_TDD_H_
#define _FPGA9025_TDD_H_

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_tdd_types.h"
#include "adi_fpga9025_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \brief Initializes the FPGA TDD Enable Control module with the values passed in from the structure
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param module is a pointer to structure type adi_fpga_TddTiming_t which contains all
* TDD Enable Control module parameters.  This structure must be pre-loaded before use and is checked for a
* null pointer if not initialized and an error will be thrown.
* \param baseAddress The base address of the module to be loaded in FPGA memory.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_TddEnableControlModuleSet(adi_fpga9025_Device_t* device,
                                           adi_fpga_TddTiming_t*  module,
                                           uint32_t               baseAddress);

/**
* \brief Reads the FPGA TDD Enable Control module into the structure passed into the function
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param module  is a pointer to an empty structure type adi_fpga_TddTiming_t.
* \param baseAddress The base address of the module to be loaded in FPGA memory.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_TddEnableControlModuleGet(adi_fpga9025_Device_t* device,
                                           adi_fpga_TddTiming_t*  module,
                                           uint32_t               baseAddress);

#ifdef __cplusplus
}
#endif

#endif /* _FPGA9025_TDD_H_ */
