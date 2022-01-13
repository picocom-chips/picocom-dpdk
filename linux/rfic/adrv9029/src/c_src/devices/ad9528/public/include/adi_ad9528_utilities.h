/**
* \file adi_ad9528_utilities.h
* \brief Contains prototypes and macro definitions for utility helper
*        functions implemented in adi_ad9528_utilities.c
*
*/
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef _ADI_AD9528_UTILITIES_H_
#define _ADI_AD9528_UTILITIES_H_

#include "adi_ad9528.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
#define GET_TOKEN(x, n, ret, line, int32Ptr, int32) \
        {(ret) = sscanf((line), " <" #n "=%u>", (int32Ptr));\
        if ((ret) == 1) {\
                x.n = (int32);\
                continue;\
        }}

#define GET_TOKEN_CAST(x, n, ca, ret, line, int32Ptr, int32) \
        {(ret) = sscanf((line), " <" #n "=%u>", (int32Ptr));\
        if ((ret) == 1) {\
                x.n = (ca)(int32);\
                continue;\
        }}
#else
#define GET_TOKEN(x, n, ret, line, int32Ptr, int32) \
        {(ret) = sscanf_s((line), " <" #n "=%u>", (int32Ptr));\
        if ((ret) == 1) {\
                x.n = (int32);\
                continue;\
        }}

#define GET_TOKEN_CAST(x, n, ca, ret, line, int32Ptr, int32) \
        {(ret) = sscanf_s((line), " <" #n "=%u>", (int32Ptr));\
        if ((ret) == 1) {\
                x.n = (ca)(int32);\
                continue;\
        }}
#endif

#ifdef __GNUC__
#define sscanf_s sscanf
#endif
    
#define ADI_AD9528_MAX_BUFFER 250

/**
* \brief Utility function that will initialize an AD9528 using the 
*  Configuration Wizard 
*
* This reads the configuration file to scan for AD9528 settings. It 
* constructs an AD9528 init structure
* and calls the AD9528 API Initialize function
*
* <B>Dependencies</B>
* - None
*
* \param configFile The absolute filepath of the Configuration File
* \param init Pointer to the AD9528 init device structure to initialize
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no 
*  action required
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter
*  check
*/
int32_t adi_ad9528_ConfigFileLoad(const char *configFile, adi_ad9528_Init_t *init);

/**
* \brief Helper function for ADI transceiver eval boards to init the AD9528
*  data structure
*
* This function inits the AD9528 device data structure with defaults that
* are known to work with the ADI AD9369 and AD9370 evaluation boards.  
* NOTE: This function will modify the contents of the AD9528 device data 
* structure.
*
* <B>Dependencies</B>
* - device->common.devHalInfo
*
* \param device Pointer to the AD9528 device data structure to initialize
* \param clockFrequencies The adi_ad9528_ClockFrequencySettings_t data structure.
*  vcxoFrequency_Hz The VCXO frequency that is connected to the AD9528
*  refAFrequency_Hz The reference clock frequency being input into 
*  the AD9528 REFCLK A input
*  outputDeviceClock_Hz Desired output clock frequency to the FPGA 
*  and transceiver device
* \param init Point to the adi_ad9528_Init_t data structure.
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no 
*  action required
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter 
*  check
*/
int32_t adi_ad9528_InitStructConfig(adi_ad9528_Device_t *device, adi_ad9528_ClockFrequencySettings_t *clockFrequencies, adi_ad9528_Init_t *init);

#ifdef __cplusplus
}
#endif

#endif /* ADI_AD9528_UTILITIES_H_ */