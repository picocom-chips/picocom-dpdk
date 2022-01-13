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

#ifndef _ADI_FPGA9025_CLK_H_
#define _ADI_FPGA9025_CLK_H_

#include <stdint.h>
#include "adi_fpga9025_types.h"
#include "adi_fpga9025_clk_types.h"

#ifdef __cplusplus
extern "C"
{
#endif
/**
* \brief writes the configuration to the FPGA MMCM via the Dynamic Reconfiguration Port (DRP)
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param mmcmSel selection of the mmcm device to config
* \param mmcm is a adi_fpga_MmcmCfg_t used to configure the mmcm
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_MmcmSet(adi_fpga9025_Device_t*  device,
                             adi_fpga9025_MmcmSel_e  mmcmSel,
                             adi_fpga9025_MmcmCfg_t* mmcm);

/**
* \brief reads the configuration to the FPGA MMCM clock tile via the Dynamic Reconfiguration Port (DRP)
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param mmcmSel selection of the mmcm device to config
* \param mmcm is a adi_fpga_MmcmCfg_t used to configure the mmcm
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_MmcmGet(adi_fpga9025_Device_t*  device,
                             adi_fpga9025_MmcmSel_e  mmcmSel,
                             adi_fpga9025_MmcmCfg_t* mmcm);

/**
* \brief Returns the value of the MMCM lock bit
*
* \dep_begin
* \dep{device}
* \dep{mmcm}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param mmcmSel selection of the mmcm device to config, rx or tx
* \param lockBit Pointer to return lock bit value
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_MmcmLockGet(adi_fpga9025_Device_t* device,
                                 adi_fpga9025_MmcmSel_e mmcmSel,
                                 uint8_t*               lockBit);

/**
* \brief Peforms a soft reset on the selected MMCM. The reset is self-clearing.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param mmcmSel selection of the mmcm device to config
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_MmcmResetSet(adi_fpga9025_Device_t* device,
                                  adi_fpga9025_MmcmSel_e mmcmSel);

/**
* \brief writes the configuration to the FPGA QPLL via the Dynamic Reconfiguration Port (DRP)
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param quadMask selection of the Qpll device to config
* \param qPll is a adi_fpga9025_QpllCfg_t used to configure the Qpll
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_QpllSet(adi_fpga9025_Device_t*  device,
                             uint8_t                 quadMask,
                             adi_fpga9025_QpllCfg_t* qPll);

/**
* \brief reads the configuration to the FPGA QPLL via the Dynamic Reconfiguration Port (DRP)
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param quadSel one of adi_fpga9025_QPLL_Quad_e enum values
* \param bandSel one of adi_fpga9025_LaneClkSel_e enum values
* \param qPll is a adi_fpga9025_QpllCfg_t used to configure the Qpll
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_QpllGet(adi_fpga9025_Device_t*    device,
                             adi_fpga9025_Qpll_Quad_e  quadSel,
                             adi_fpga9025_LaneClkSel_e bandSel,
                             adi_fpga9025_QpllCfg_t*   qPll);

/**
* \brief Returns the valueo of the QPLL lock bit pointed to by the quadMask and bandSel
*
* \dep_begin
* \dep{device}
* \dep{qPll->band}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param quadSel selecting either 0 for quad 0 or 1 for quad 1
* \param bandSel selecting either 0 for qpll0 or 1 for qpll1
* \param lockBit will be set with the lock bit bitfield value, either 0 or 1
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_QpllLockGet(adi_fpga9025_Device_t* device,
                                 uint8_t                quadSel,
                                 uint8_t                bandSel,
                                 uint8_t*               lockBit);

/**
* \brief Reads the power good bit for each lane
*
* This function will return a mask indicating the status of each channel's power good bit
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param quadSel 0 for quad 0; 1 for quad 1
* \param powerGood status an 8-bit mask of each channels power good bit, bit 7 = channel 7's power good, etc.
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action
*  required
*/
int32_t adi_fpga9025_LanePowerGoodGet(adi_fpga9025_Device_t* device,
                                      uint8_t                quadSel,
                                      uint8_t*               powerGood); //todo: move this to jesd.h

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_CLK_H_ */
