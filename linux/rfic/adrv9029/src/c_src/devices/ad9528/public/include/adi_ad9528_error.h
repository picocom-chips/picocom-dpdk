/**
* \file adi_ad9528_error.h
* \brief AD9528 ERROR header file
*
* Extension of adi_common_error
*
* API Version: 6.0.0.41
*/

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADI API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/

#ifndef _ADI_AD9528_ERROR_H_
#define _ADI_AD9528_ERROR_H_

#include "adi_common_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Extending Common error for AD9528 */
#define ADI_AD9528_ERR_PLL_LOCK_FAILED           0x2001
#define ADI_AD9528_ERR_NUMBER_OF_ERRORS          0x2002

#ifdef __cplusplus
}
#endif

#endif /* _ADI_AD9528_ERROR_H_ */
