/*!
* \file adi_adrv9025_tx_types.h
* \brief Contains FPGA9025 PRBS enum and struct definitions
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_PRBS_TYPES_H_
#define _ADI_FPGA9025_PRBS_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum adi_fpga9025_PrbsTestModes
{
    ADI_FPGA9025_PRBS_OFF   = 0,
    ADI_FPGA9025_PRBS_7     = 1,
    ADI_FPGA9025_PRBS_9     = 2,
    ADI_FPGA9025_PRBS_15    = 3,
    ADI_FPGA9025_PRBS_23    = 4,
    ADI_FPGA9025_PRBS_31    = 5,
    ADI_FPGA9025_SQ_2UI     = 9,
    ADI_FPGA9025_SQ_INT_UI  = 10
} adi_fpga9025_PrbsTestModes_e;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_PRBS_TYPES_H_ */
