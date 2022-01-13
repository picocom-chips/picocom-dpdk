/**
 * \file adi_ad9528.h
 * \brief Contains function declarations for AD9528 API
 */
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef _ADI_AD9528_H_
#define _ADI_AD9528_H_

#include "adi_ad9528_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* \brief Performs a Hardware Initialization for AD9528 Device.
*
* \pre This function may be called after device->common.devHalInfo has been initialized with
* user values
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param device Pointer to AD9528 device data structure
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_HwOpen(adi_ad9528_Device_t *device);
    
/**
* \brief Performs a hardware shutdown  for AD9528 Device.
*
* \pre This function may be called after device->common.devHalInfo has been initialized with
* user values
*
* \dep_begin
* \dep{device->common.devHalInfo}
* \dep_end
*
* \param device Pointer to AD9528 device data structure
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_HwClose(adi_ad9528_Device_t *device);
    
/**
* \brief Performs a hard reset on the AD9528 DUT
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to the AD9528 data structure containing 
*  devHalInfo
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_HwReset(adi_ad9528_Device_t *device);

/**
* \brief Sets the AD9528 device SPI settings (3wire/4wire, msbFirst, etc).
*
* This function will use the settings in the adi_ad9528_SpiSettings_t structure
* to set SPI stream mode, address auto increment direction, msbFirst/lsbfirst,
* and 3wire/4wire mode.  The AD9528 device always uses SPI MODE 0 (CPHA=0, 
* CPOL=0), uses a 16bit instruction word, and defaults to SPI streaming (auto increment)
*
* <B>Dependencies</B>
* - device->common.devHalInfo
* - spi->msbFirst
* - spi->autoIncAddrUp
* - spi->fourWireMode
*
* \param device is structure pointer to the AD9528 data structure containing 
*  settings
* \param spi is a structure pointer to AD9528 SPI controller settings - not 
*  platform hardware SPI settings
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_SpiCfgSet(adi_ad9528_Device_t *device, adi_ad9528_SpiSettings_t *spi);

/**
* \brief Gets the AD9528 device SPI settings (3wire/4wire, MSBFirst, etc).
*
* This function will read the current SPI settings and load them into the spi 
* input
* parameter. This function only works after the adi_ad9528_SpiCfgSet has been 
* called.
*
* <B>Dependencies</B>
* - device->common.devHalInfo
* - spi->msbFirst
* - spi->enSpiStreaming
* - spi->autoIncAddrUp
* - spi->fourWireMode
*
* \param device is structure pointer to the AD9528 data structure containing
*  settings
* \param spi is a structure pointer to AD9528 SPI controller settings - not 
*  platform hardware SPI settings
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_SpiCfgGet(adi_ad9528_Device_t *device, adi_ad9528_SpiSettings_t *spi);

/**
* \brief Initializes the AD9528 by writing all SPI registers
*
* Initializes the AD9528 using the values passed in through the 
* adi_ad9528_Init_t structure.
*
* <B>Dependencies</B>
* - All parameters in init structure
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param init is a structure pointer to the AD9528 initialization settings
*  structure
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter
*  check
*/
int32_t adi_ad9528_Initialize(adi_ad9528_Device_t *device, adi_ad9528_Init_t *init);

/**
* \brief Send a SPI message to request a SYSREF pulse or continuous SYSREF from
*  the AD9528
*
* Requests a SYSREF from the AD9528.  It will use whatever settings for SYSREF
* that are current configured in the AD9528.  This could be a single pulse,
* multiple pulses, or continuous pulses.
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param enableSYSREF If NSHOT SYSREF mode, this parameter is ignored.  If 
*  PRBS/CONTINUOUS SYSREF mode, 1= enable SYSREF, 0= disable SYSREF.
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_SysrefRequest(adi_ad9528_Device_t *device, uint8_t enableSYSREF);

/**
* \brief Update the Sysref settings for an AD9528 device by writing to the 
*  corresponding configuration registers
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param sysrefSettings is structure pointer to a Sysref settings device 
*  structure containing updated settings
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action
*  required
*/
int32_t adi_ad9528_SysrefSetup(adi_ad9528_Device_t *device, adi_ad9528_SysrefSettings_t *sysrefSettings);

/**
* \brief Update the AD9528 clock outputs that are enabled. The function probes
*  the AD9528 chip to determine the sysref settings.
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param clkEnable Sets which clock outputs are enabled. 
*  Bit per clock output. bit0 = out0, etc.
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_ClockOutputsEnable(adi_ad9528_Device_t *device, uint16_t clkEnable);

/**
* \brief Waits for PLL1 and PLL2 to lock and the REFA and VCXO clocks to be 
*  present
*
* Waits until Reference A clock and VCXO clock input to be detected (present),
* and PLL1 and PLL2 to lock.  Will timeout after 1 second and return 
* AD9528_FAILED.
* If clock are detected and PLLs locked, returns ADI_COMMON_ACT_NO_ACTION.
* Will read the AD9528 status prior.
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param timeout_ms the amount of time to wait for a successful lock before 
*  returning
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
* \retval ADI_AD9528_ACT_PLL_LOCK_FAILED Recover action for a failed PLL lock
*/
int32_t adi_ad9528_PllLockDebounce(adi_ad9528_Device_t *device, uint32_t timeout_ms);

/**
* \brief Reads the Lock Status register of the AD9528
*
* This function will read register 0x508 and load that value into the address 
* pointed to by status parameter.
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device is structure pointer to AD9528 clock device structure
* \param status a pointer to a uint8_t that will be loaded with the value of 
*  register address 0x508
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action 
*  required
*/
int32_t adi_ad9528_PllLockStatusGet(adi_ad9528_Device_t *device, uint8_t *status);


#ifdef __cplusplus
}
#endif

#endif /* _ADI_AD9528_H_ */
