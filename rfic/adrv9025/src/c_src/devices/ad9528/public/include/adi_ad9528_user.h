/**
* \file adi_AD9528_user.h
* \brief Contains top level AD9528 related function prototypes for
*        adi_ad9528.c
*
* AD9528 API Version: $ADI_AD9528_API_VERSION$
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the AD9528 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_AD9528_USER_H_
#define _ADI_AD9528_USER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *****************************************
 * AD9528 Interface Macros
 ******************************************
 */

#ifndef ADI_AD9528_VERBOSE
#define ADI_AD9528_VERBOSE 1                           /*Use strings 0 not use, 1 use */
#endif /* !ADI_AD9528_VERBOSE */

#ifndef ADI_AD9528_VARIABLE_USAGE
#define ADI_AD9528_VARIABLE_USAGE 1                    /*Use strings 0 not use, 1 use */
#endif /* !ADI_AD9528_VARIABLE_USAGE */

#ifndef ADI_AD9528_LOGGING
#define ADI_AD9528_LOGGING 0xFF                        /*LogLevel Set to API, Messages, Warnings, Error*/
#endif /* !ADI_AD9528_LOGGING */

#ifdef __cplusplus
}
#endif

#endif /* _ADI_AD9528_USER_H_ */
