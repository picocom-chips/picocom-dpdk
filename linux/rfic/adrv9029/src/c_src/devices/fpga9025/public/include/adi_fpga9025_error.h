/**
* \file adi_fpga9025_error.h
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

#ifndef _ADI_FPGA9025_ERROR_H_
#define _ADI_FPGA9025_ERROR_H_

#include "adi_common_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Extending Common error for FPGA9025 */
#define ADI_FPGA9025_ERR_INV_NULL_INIT_PARAM                    0x3001
#define ADI_FPGA9025_ERR_DRP_ERROR                              0x3002
#define ADI_FPGA9025_ERR_CHANNEL_POWER_GOOD_FAILURE             0x3003
#define ADI_FPGA9025_ERR_API_FAIL                               0x3004
#define ADI_FPGA9025_ERR_NUMBER_OF_ERRORS                       0x3005
#define ADI_FPGA9025_ERR_REGISTER_IO_FAIL                       0x3006
#define ADI_FPGA9025_ERR_DATA_RX_MOVER_WAIT_TIMEOUT             0x3007      /*!< API NG - Timeout occurred during Rx transaction */
#define ADI_FPGA9025_ERR_LINK_LAYER_RESET_FAIL                  0x3008
#define ADI_FPGA9025_ERR_INVALID_FPGA_IMAGE                     0x3009
#define ADI_FPGA9025_ERR_CLOCK_FAILURE                          0x300A
#define ADI_FPGA9025_ERR_PHY_RESET_FAIL                         0x300B
#define ADI_FPGA9025_ERR_INVALID_CLK_CONFIG                     0x300C

/* Extending Common Actions for FPGA9025 */

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_ERROR_H_ */
