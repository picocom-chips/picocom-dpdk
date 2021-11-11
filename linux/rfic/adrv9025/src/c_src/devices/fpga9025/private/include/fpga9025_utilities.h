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

#ifndef _FPGA9025_UTILITIES_H_
#define _FPGA9025_UTILITIES_H_

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \brief Configures the Qpll DRP registers based on the clock configuration.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param refClk_kHz The input clock rate in kHz
* \param qpllVco_kHz Frequency of the QPLL Vco
* \param qpllDivideRatio 1 = Full rate, 0 = half rate
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_QpllDrpCfg(adi_fpga9025_Device_t* device,
                            const uint32_t         refClk_kHz,
                            const uint32_t         qpllVcoOut_kHz,
                            const uint8_t          qpllDivideRatio);

/**
* \brief Configures the 204B & 204C Serializer DRP registers based on the clock configuration for the specified lane.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param refClk_kHz The input clock rate in kHz
* \param laneRate The lane rate for fpgaLane
* \param qpllVco_kHz Frequency of the QPLL Vco
* \param fpgaLane The FPGA lane to apply the settings for
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_SerializerDrpCfg(adi_fpga9025_Device_t* device,
                                  const uint32_t         refClk_kHz,
                                  const uint32_t         laneRate,
                                  const uint32_t         qpllVcoOut_kHz,
                                  const uint8_t          fpgaLane);

/**
* \brief Configures the 204B Deserializer DRP registers based on the clock configuration for the specified lane.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param refClk_kHz The input clock rate in kHz
* \param laneRate The lane rate for fpgaLane
* \param qpllVco_kHz Frequency of the QPLL Vco
* \param fpgaLane The FPGA lane to apply the settings for
*
* \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t fpga9025_DeserializerDrpCfg(adi_fpga9025_Device_t* device,
                                    const uint32_t         refClk_kHz,
                                    const uint32_t         laneRate,
                                    const uint32_t         qpllVcoOut_kHz,
                                    const uint8_t          fpgaLane);

#ifdef __cplusplus
}
#endif

#endif /* _FPGA9025_UTILITIES_H_ */
