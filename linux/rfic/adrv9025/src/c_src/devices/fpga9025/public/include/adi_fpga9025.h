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

#ifndef _ADI_FPGA9025_H_
#define _ADI_FPGA9025_H_

#include "adi_fpga9025_types.h"
#include "adi_fpga9025_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \brief Performs a Hardware Initialization for FPGA Device.
*
* \pre This function may be called after device->common.devHalInfo has been initialized with
* user values
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param device Pointer to FPGA device data structure
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_fpga9025_HwOpen(adi_fpga9025_Device_t* device);

/**
* \brief Performs a hardware shutdown  for FPGA Device.
*
* \pre This function may be called after device->common.devHalInfo has been initialized with
* user values
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param device Pointer to FPGA device data structure
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_fpga9025_HwClose(adi_fpga9025_Device_t* device);

/**
* \brief    Reads the Major, Minor, & Design ID bitfields and stores these values
*           in the device->devStateInfo structure.
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
int32_t adi_fpga9025_VersionRead(adi_fpga9025_Device_t* device);

/**
* \brief Unimplemented.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param detectedRefClock_kHz FPGA high speed serial reference clock frequency returned in this parameter in kHz.
* 
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RefClockFreqRead(adi_fpga9025_Device_t* device,
                                      uint32_t*              detectedRefClock_kHz);

/**
* \brief Unimplemented.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* 
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RegisterReset(adi_fpga9025_Device_t* device);

/**
* \brief Unimplemented.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param IpToReset is a bit mask comprised of fpgaIpBlockResets_t enum types which select the FPGA IP blocks
* to be reset
* 
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_IpReset(adi_fpga9025_Device_t* device,
                             uint32_t               IpToReset);

/**
* \brief    Dynamic Reconfiguration Port (DRP) read helper function. After a successful
*           DRP read the rdMask value is applied to the register address value and the value
*           written to the address pointed to by rdWord.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param addr is a uint32_t DRP address word
* \param drp is a adi_fpga_DrpInterface_e enum type for DRP selection
* \param rdWord is uint32_t pointer to the register read value
* \param rdMask is applied to the word read from the DRP register
* 
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DrpRead(adi_fpga9025_Device_t*    device,
                             adi_fpga9025_DrpAddress_e addr,
                             uint8_t                   drp,
                             uint16_t*                 rdWord,
                             adi_fpga9025_DrpMask_e    rdMask);

/**
* \brief    Dynamic Reconfiguration Port (DRP) write helper function. The addr, wrWord, and wrMask are written to the
*           appropriate DRP bitfields based on the drp parameter.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param addr is a uint32_t DRP address word
* \param drp is a uin32_t for DRP selection. See adi_fpga_DrpInterface_e for valid values.
* \param wrWord is a uint32_t register write value
* \param wrMask is written to a DRP configuration register and is applied internally
* 
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_DrpWrite(adi_fpga9025_Device_t* device,
                              uint32_t               addr,
                              uint8_t                drp,
                              uint16_t               wrWord,
                              uint16_t               wrMask);

/**
* \brief Initializes the FPGA based on the settings in initSettings. 
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param initSettings initialisation settings for fpga.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_InitSet(adi_fpga9025_Device_t* device,
                             adi_fpga9025_Init_t*   initSettings);

/**
* \brief Populates the initSettings structure based on the values read back from the FPGA.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param initsettings initialisation settings for fpga.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_InitGet(adi_fpga9025_Device_t* device,
                             adi_fpga9025_Init_t*   initsettings);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_H_ */
