/**
* \file adi_fpga9010_error.h
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

#ifndef _ADI_FPGA9010_ERROR_H_
#define _ADI_FPGA9010_ERROR_H_

#include "adi_common_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Extending Common error for FPGA9010 */
#define ADI_FPGA9010_ERR_INV_NULL_INIT_PARAM                    0x3001                
#define ADI_FPGA9010_ERR_DRP_ERROR                              0x3002                    
#define ADI_FPGA9010_ERR_CHANNEL_POWER_GOOD_FAILURE             0x3003
#define ADI_FPGA9010_ERR_API_FAIL                               0x3004
#define ADI_FPGA9010_ERR_NUMBER_OF_ERRORS                       0x3005 
#define ADI_FPGA9010_ERR_REGISTER_IO_FAIL                       0x3006
#define  ADI_FPGA9010_ERR_DATA_RX_MOVER_WAIT_TIMEOUT            0x3007      /*!< API NG - Timeout occurred during Rx transaction */
#define  ADI_FPGA9010_ERR_LINK_LAYER_RESET_FAIL                 0x3008
#define ADI_FPGA9010_ERR_INVALID_FPGA_IMAGE                     0x3009

/* Extending Common Actions for FPGA9010 */
#define  ADI_FPGA9010_ACT_WARN_RESET_GPIO                 (3)               /*!< API OK - GPIO Not working */
#define  ADI_FPGA9010_ACT_ERR_FLUSH_CACHE                (15)               /*!< API NG - Bitfield CACHE requires flushing */
#define  ADI_FPGA9010_ACT_ERR_NULL_POINTER               (16)               /*!< API NG - Null pointer has been detected */
#define  ADI_FPGA9010_ACT_INV_TX_DATA_MOVER_TRIGGER      (17)               /*!< API NG - An invalid tx data mover trigger selected */
#define  ADI_FPGA9010_ACT_INV_TDD_ASSERT_SELECT          (18)               /*!< API NG - Invalid bits were selected when asserting TDD pins */
#define  ADI_FPGA9010_ACT_INV_RX_DATA_MOVER_SETUP        (19)               /*!< API NG - An invalid rx move type selected */
#define  ADI_FPGA9010_ACT_INV_RX_DATA_MOVER_TRIGGER      (20)               /*!< API NG - An invalid rx data mover trigger selected */
#define  ADI_FPGA9010_ACT_INV_RX_DATA_MOVER_ENABLE       (21)               /*!< API NG - An invalid rx data mover trigger selected */

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_ERROR_H_ */
