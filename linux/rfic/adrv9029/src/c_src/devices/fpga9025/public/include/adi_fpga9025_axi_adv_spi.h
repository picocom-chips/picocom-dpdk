/**
* \file adi_fpga9025_axi_adv_spi.h
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

#ifndef _ADI_FPGA9025_axi_adv_spi_H_
#define _ADI_FPGA9025_axi_adv_spi_H_

#include "adi_fpga9025_axi_adv_spi_types.h"
#include <stdint.h>
#include "adi_fpga9025.h"
//#include "adi_common_macros.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t adi_fpga9025_AxiAdvSpiCfgSet(adi_fpga9025_Device_t*              device,
                                     adi_fpga9025_AxiAdvSpiFeatConfig_t* advSpiCfg,
                                     uint8_t                             slaveSelect);

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_axi_adv_spi_H_ */
