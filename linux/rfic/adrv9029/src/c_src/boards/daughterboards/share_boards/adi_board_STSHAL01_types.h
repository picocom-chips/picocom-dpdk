/**
 * \file adi_board_STSHAL01_types.h
 *
 * API Version: $ADI_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_BOARD_STSHAL01_TYPES_H_
#define _ADI_BOARD_STSHAL01_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif
    
/**
*  \brief Enum of possible Control Modes for STSHAL board type
* STS_PREMCS_INIT = 1000;
* STS_POSTMCS_INIT = 2000;
* STS_POSTMCS_INIT_InitCals = 2100;
* STS_SYSREF_REQUEST = 3000;
* STS_MULTICHIPSYNC = 4000;
* STS_LINK_BRINGUP = 5000;
*/
typedef enum adi_board_stshal_modeSelect
{
    ADI_BOARD_STSHAL01_PREMCS_INIT = 1000,  /*!< Selects a STSHAL PreMcsInit Function */
    ADI_BOARD_STSHAL01_POSTMCS_INIT = 2000, /*!< Selects a STSHAL PostMcsInit Function */
    ADI_BOARD_STSHAL01_POSTMCS_INIT_INITCALS = 2100, /*!< Selects a STSHAL PostMcsInit InitCals Function No Actions Taken */
    ADI_BOARD_STSHAL01_SYSREF_REQUEST = 3000, /*!< Selects a STSHAL SysRef Request Function */
    ADI_BOARD_STSHAL01_MCS_INIT = 4000,      /*!< Selects a STSHAL MCS Init Function No Actions Taken*/
    ADI_BOARD_STSHAL01_JESDBRINGUP = 5000   /*!< Selects a STSHAL JESD BRINGUP of type ATE tester */
} adi_board_stshal_modeSelect_e;


#ifdef __cplusplus
}
#endif

#endif
