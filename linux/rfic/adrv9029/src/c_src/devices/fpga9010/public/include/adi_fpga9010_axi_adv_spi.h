/**
* \file adi_fpga9010_axi_adv_spi.h
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

#ifndef _ADI_FPGA9010_axi_adv_spi_H_
#define _ADI_FPGA9010_axi_adv_spi_H_

#include "adi_fpga9010_axi_adv_spi_types.h"
#include <stdint.h>
#include "adi_fpga9010.h"
//#include "adi_common_macros.h"

#ifdef __cplusplus
extern "C" {
#endif


int32_t adi_fpga9010_AxiAdvSpiCfgSet(adi_fpga9010_Device_t *device, adi_fpga9010_AxiAdvSpiFeatConfig_t *advSpiCfg, uint8_t slaveSelect);
int32_t adi_fpga9010_AxiAdvSpiChipSelectAll(adi_fpga9010_Device_t *device, uint8_t enable);

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9010_axi_adv_spi_H_ */