/**
* \file adi_fpga9025_user.h
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

#ifndef _ADI_FPGA9025_USER_H_
#define _ADI_FPGA9025_USER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *****************************************
 * FPGA Interface Macros
 ******************************************
 */

#ifndef ADI_FPGA9025_VERBOSE
#define ADI_FPGA9025_VERBOSE 1                       /*Use strings 0 not use, 1 use */
#endif /* !ADI_FPGA9025_VERBOSE */

#ifndef ADI_FPGA9025_VARIABLE_USAGE
#define ADI_FPGA9025_VARIABLE_USAGE 1                    /*Use strings 0 not use, 1 use */
#endif /* !ADI_FPGA9025_VARIABLE_USAGE */

#ifndef ADI_FPGA9025_LOGGING
#define ADI_FPGA9025_LOGGING 0x7F                       /*LogLevel Set to API, Messages, Warnings, Error*/
#endif /* !ADI_FPGA9025_LOGGING */

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_USER_H_ */
