/*!
* \file adi_fpga9025_types.h
* \brief Contains ADRV9025 API configuration and run-time type definitions
*
* ADRV9025 API Version: 6.0.0.41
*
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_CLK_TYPES_H_
#define _ADI_FPGA9025_CLK_TYPES_H_

#include <stdint.h>
#include "adi_fpga9025_jesd_types.h"

#define ADI_FPGA9025_NUM_MMCM_OUTPUT_CLOCKS 7
#define ADI_FPGA9025_PHY_NUM_CHANNELS 8

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum adi_fpga9025_Qpll_Band
{
    ADI_FPGA9025_QPLL_BAND0 = 0x0,
    ADI_FPGA9025_QPLL_BAND1 = 0x1
} adi_fpga9025_Qpll_Band_e;

typedef enum adi_fpga9025_QpllClkSel
{
    ADI_FPGA9025_QPLL_GTREFCLK0         = 0x1,
    ADI_FPGA9025_QPLL_GTREFCLK1         = 0x2,
    ADI_FPGA9025_QPLL_GTNORTHREFCLK0    = 0x3,
    ADI_FPGA9025_QPLL_GTNORTHREFCLK1    = 0x4,
    ADI_FPGA9025_QPLL_GTSOUTHREFCLK0    = 0x5,
    ADI_FPGA9025_QPLL_GTSOUTHREFCLK1    = 0x6,
    ADI_FPGA9025_QPLL_GTGREFCLK         = 0x7
} adi_fpga9025_QpllClkSel_e;

typedef enum adi_fpga9025_MmcmSel
{
    ADI_FPGA9025_CORE_MMCM
} adi_fpga9025_MmcmSel_e;

typedef struct adi_fpga9025_QpllCfg
{
    uint8_t                   quadSelect;      /*! Apply these settings to the selected quads (0x3 for both; 0x2 for quad 1; 0x1 for quad 0) */
    adi_fpga9025_LaneClkSel_e band;            /*! GTX QPLL upper or lower band VCO select,  */
    adi_fpga9025_QpllClkSel_e refClkSelect[2]; /*! GTX QPLL Ref Clk select */
    uint16_t                  mVal;            /*! reference clock divisor value,  */
    uint16_t                  nVal;            /*! loop divisor value,  */
    uint32_t                  qpllVco_kHz;     /*! GTX QPLL upper or lower band VCO select,  */
    uint32_t                  qpllVcoOut_kHz;  /*! The actual output freq of the QPLL  */
    uint16_t                  lpf;             /*! Value determined by FPGA reference clock & lane rate */
    uint16_t                  cfg4;            /*! Value determined by FPGA reference clock & lane rate */
    uint16_t                  cp;              /*! Value determined by FPGA reference clock & lane rate */
    uint16_t                  lockCfg;         /*! Value determined by FPGA reference clock & lane rate */
    uint16_t                  lockCfgG3;       /*! Value determined by FPGA reference clock & lane rate */
    uint8_t                   qpllClkOutRate;  /*! 0: Out freq = Vcxo / 2; 1: Out freq = Vcxo */
} adi_fpga9025_QpllCfg_t;

typedef struct adi_fpga9025_MmcmCfg
{
    uint8_t  mVal;
    uint8_t  dVal;
    uint8_t  outputClkDiv[7];
    uint32_t outputClkFreq_kHz[7];
} adi_fpga9025_MmcmCfg_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_CLK_TYPES_H_ */
