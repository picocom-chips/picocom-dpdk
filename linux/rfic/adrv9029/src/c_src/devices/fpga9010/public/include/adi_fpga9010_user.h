/**
* \file adi_fpga9010_user.h
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

#ifndef _ADI_FPGA9010_USER_H_
#define _ADI_FPGA9010_USER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *****************************************
 * FPGA Interface Macros
 ******************************************
 */
    
#ifndef ADI_FPGA9010_VERBOSE
    #define ADI_FPGA9010_VERBOSE 1                       /*Use strings 0 not use, 1 use */
#endif /* !ADI_FPGA9010_VERBOSE */
    
#ifndef ADI_FPGA9010_VARIABLE_USAGE
#define ADI_FPGA9010_VARIABLE_USAGE 1                    /*Use strings 0 not use, 1 use */
#endif /* !ADI_FPGA9010_VARIABLE_USAGE */
    
#ifndef ADI_FPGA9010_LOGGING
#define ADI_FPGA9010_LOGGING 0x7F                       /*LogLevel Set to API, Messages, Warnings, Error*/
#endif /* !ADI_FPGA9010_LOGGING */

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_USER_H_ */
