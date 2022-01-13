/**
* \file adi_fpga9010_utilities.h
* \brief Contains top level fpga9010 related function prototypes for
*        adi_fpga9010_utilities.c
*
* FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_UTILITIES_H_
#define _ADI_FPGA9010_UTILITIES_H_

#include "adi_fpga9010_types.h"
#include "adi_fpga9010_utilities_types.h"
#include "adi_common_log.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* \brief Platform FPGA command to calculate the FPGA SERDES QPLL settings
*
* \dep_begin
* \dep{device}
* \dep{divisors}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param refClk_kHz The input clock rate in kHz
* \param fastestLaneRate_kHz The fastest lane rate in kHz
* \param qplls A pointer to a QPLL configuration structure
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_CalculateQpllSettings(adi_fpga9010_Device_t *device, const uint32_t refClk_kHz, const uint32_t fastestLaneRate_kHz, adi_fpga9010_QpllCfg_t *qplls);

/**
* \brief Platform FPGA helper function to setup the QPLL lane rate divisors
*
* \dep_begin
* \dep{device}
* \dep{divisors}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param qpllVcoFreq_kHz Output of the QPLL in kHz
* \param desiredLaneRate_kHz  desired lane rate in kHz
* \param dVal divisors value
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_CalculateQpllDivisor(adi_fpga9010_Device_t *device, uint32_t qpllVcoFreq_kHz, const uint32_t desiredLaneRate_kHz, uint8_t *dVal);

/**
* \brief Platform FPGA command calculate the Mmcm settings
* 
* FPGA implementation constraint: RX MMCM Channel 6 is the refClk for TX MMCM. This means
* RX MMCM channel 6 output frequency must be set to refClk and RX MMCM must be configured
* and locked prior to the TX MMCM
*
* \dep_begin
* \dep{device}
* \dep{mmcmConfig->clkFreq_kHz}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param refClk_kHz The input clock rate in kHz
* \param mmcmConfig Pointer to the adi_fpga9010_MmcmCfg_t data structure
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_CalculateMmcmSettings(adi_fpga9010_Device_t *device, const uint32_t refClk_kHz, adi_fpga9010_MmcmCfg_t *mmcmConfig);
    
/**
* \brief Platform FPGA command calculate the Mmcm settings
* 
* Fills the given init structure with values whyich should cover the majority of use cases.
* The values are based on a few essential values given by the fpgaCfg structure 
*
* \dep_begin
* \dep{device}
* \dep{mmcmConfig->clkFreq_kHz}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param fpgaCfg contains the essential values in order to configure the fpga
* \param fpgaInit the resulting structure which can be modified if required or 
* passed to adi_fpga9010_Initialize to initialise the part
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_InitConfig(adi_fpga9010_Device_t *device, adi_fpga9010_SetupFpgaCfg_t *fpgaCfg, adi_fpga9010_Init_t *fpgaInit);

int32_t adi_fpga9010_FpgaConfigurationPrint(adi_fpga9010_Device_t *device);
    
int32_t adi_fpga9010_FpgaDatapathCfgPrint(adi_fpga9010_Device_t *device);

    
#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_UTILITIES_H_ */