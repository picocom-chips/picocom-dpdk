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

#ifndef _ADI_FPGA9010_H_
#define _ADI_FPGA9010_H_

#include "adi_fpga9010_types.h"
#include "adi_fpga9010_error.h"

#ifdef __cplusplus
extern "C" {
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
int32_t adi_fpga9010_HwOpen(adi_fpga9010_Device_t *device);
    
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
int32_t adi_fpga9010_HwClose(adi_fpga9010_Device_t *device);

/**
* \brief    Reads the Major, Minor, & Design ID bitfields and stores these values
*           in the device->devStateInfo structure.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_VersionRead(adi_fpga9010_Device_t *device);
     
/**
* \brief Unimplemented.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param detectedRefClock_kHz FPGA high speed serial reference clock frequency returned in this parameter in kHz.
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_RefClockFreqRead(adi_fpga9010_Device_t *device, uint32_t *detectedRefClock_kHz);
    
/**
* \brief Unimplemented.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_RegisterReset(adi_fpga9010_Device_t *device);
    
/**
* \brief Unimplemented.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param IpToReset is a bit mask comprised of fpgaIpBlockResets_t enum types which select the FPGA IP blocks
* to be reset
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_IpReset(adi_fpga9010_Device_t *device, uint32_t IpToReset);
 
/**
* \brief    Dynamic Reconfiguration Port (DRP) read helper function. After a successful
*           DRP read the rdMask value is applied to the register address value and the value
*           written to the address pointed to by rdWord.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param addr is a uint32_t DRP address word
* \param drp selects the DRP interface to read from based on the adi_fpga_DrpInterface_e enum type
* \param rdWord is uint32_t pointer to the register read value
* \param rdMask is applied to the word read from the DRP register
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_DrpRead(adi_fpga9010_Device_t *device, adi_fpga9010_DrpAddress_e addr, uint8_t drp, uint16_t *rdWord, adi_fpga9010_DrpMask_e rdMask);

/**
* \brief    Dynamic Reconfiguration Port (DRP) write helper function. The addr, wrWord, and wrMask are written to the
*           appropriate DRP bitfields based on the drp parameter.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param addr is a uint32_t DRP address word
* \param drp selects the DRP interface to write to based on the adi_fpga_DrpInterface_e enum type
* \param wrWord is a uint32_t register write value
* \param wrMask is written to a DRP configuration register and is applied internally
* 
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_DrpWrite(adi_fpga9010_Device_t *device, adi_fpga9010_DrpAddress_e addr, uint8_t drp, uint16_t wrWord, adi_fpga9010_DrpMask_e wrMask);

/**
* \brief Initializes the FPGA based on the settings in initSettings. 
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param initSettings initialisation settings for fpga.
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_InitSet(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *initSettings);

/**
* \brief Populates the initSettings structure based on the values read back from the FPGA.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param initsettings initialisation settings for fpga.
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_InitGet(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *initsettings);
    
    
/**
* \brief Initializes the FPGA9010 device based on the desired device settings.
*
* This function initializes the ADRV9010 device, digital clocks, JESD204b settings .    
* It leaves the FPGA9010 in a state ready to run
*
* \pre This function is the very first API to be called by the user to configure the FPGA9010
* after all dependent data structures have been initialized
*
* \dep_begin
* \dep{device (all members)}
* \dep{init (all members)}
* \dep_end
*
* \param device Pointer to FPGA9010 device data structure
* \param fpgaInit Pointer to FPGA9010 initialization settings structures
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*/
int32_t adi_fpga9010_Initialize(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *fpgaInit);
    
#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_H_ */
