/*!
* \file adi_adrv9010_tx_types.h
* \brief Contains FPGA9010 PRBS enum and struct definitions
*
* ADRV9010 API Version: $ADI_FPGA9010_API_VERSION$
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */


#ifndef _ADI_FPGA9010_PRBS_TYPES_H_
#define _ADI_FPGA9010_PRBS_TYPES_H_


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum adi_fpga_prbsLaneSel
{
    ADI_FPGA9010_PRBS_DUMMYPIN = 0        /*!< TODO: fix this */

} adi_fpga_prbsLaneSel_e;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9010_PRBS_TYPES_H_ */