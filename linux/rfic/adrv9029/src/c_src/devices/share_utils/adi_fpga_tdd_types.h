/*!
* \file adi_fpga_tdd_types.h
* \brief Contains FPGA TDD enum and struct definitions
*
* ADRV9025 API Version: $ADI_ADRV_API_VERSION$
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA_TDD_TYPES_H_
#define _ADI_FPGA_TDD_TYPES_H_

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
*  \brief   Structure to hold the FPGA TDD Timing parameters. Located in the TDD Enable
*           Control FPGA module. Includes primary & secondary region parameters.
*/
typedef struct adi_fpga_TddTiming
{
    uint32_t onPtr;             /*!< On pointer (start value) for TDD primary region */
    uint32_t offPtr;            /*!< Off pointer (start value) for TDD primary region */
    uint32_t secondaryOnPtr;    /*!< On pointer (start value) for TDD secondary region */
    uint32_t secondaryOffPtr;   /*!< Off pointer (start value) for TDD secondary region */
    uint32_t offsetFrames;      /*!< Offset frame value for primary & secondary region */
    uint32_t activeFrames;      /*!< Active frame value for primary & secondary region */
    uint32_t inactiveFrames;    /*!< Inactive frame value for primary & secondary region */
} adi_fpga_TddTiming_t;

/**
*  \brief   Structure to hold the FPGA TDD Datapath parameters. Located in the TDD Datapath
*           Control FPGA module.
*/
typedef struct adi_fpga_TddDatapathControl
{
    uint8_t enable;                 /*!< Set this value to 1 to enable this datapath. Otherwise, set to 0 */
    uint32_t startValue;            /*!< Start Value for Datapath Control Module. Effectively the Datapath Delay value */
} adi_fpga_TddDatapathControl_t;

/**
*  \brief   Structure to hold the FPGA TDD state machine parameters
*/
typedef struct adi_fpga_TddStateMachine
{
    uint32_t loopCount;         /*!< Set this value to > 1 to enable looping */
    uint8_t syncExtTrig;        /*!< Set this value to 1 to enable external triggering. Otherwise, set to 0 */
    uint32_t frameCount;        /*!< Number of Tx LaneRate /40 clock cycles in the desired frame time */

    adi_fpga_TddTiming_t rx1EnableControl;
    adi_fpga_TddTiming_t rx2EnableControl;
    adi_fpga_TddTiming_t rx3EnableControl;
    adi_fpga_TddTiming_t rx4EnableControl;

    adi_fpga_TddTiming_t orx1EnableControl;
    adi_fpga_TddTiming_t orx2EnableControl;
    adi_fpga_TddTiming_t orx3EnableControl;
    adi_fpga_TddTiming_t orx4EnableControl;

    adi_fpga_TddTiming_t tx1EnableControl;
    adi_fpga_TddTiming_t tx2EnableControl;
    adi_fpga_TddTiming_t tx3EnableControl;
    adi_fpga_TddTiming_t tx4EnableControl;

    adi_fpga_TddTiming_t tx1ToOrx1EnableControl;
    adi_fpga_TddTiming_t tx2ToOrx1EnableControl;
    adi_fpga_TddTiming_t tx1ToOrx2EnableControl;
    adi_fpga_TddTiming_t tx2ToOrx2EnableControl;
    adi_fpga_TddTiming_t tx3ToOrx3EnableControl;
    adi_fpga_TddTiming_t tx4ToOrx3EnableControl;
    adi_fpga_TddTiming_t tx3ToOrx4EnableControl;
    adi_fpga_TddTiming_t tx4ToOrx4EnableControl;
    
    adi_fpga_TddTiming_t extTrig1;
    adi_fpga_TddTiming_t extTrig2;
    adi_fpga_TddTiming_t extTrig3;
    adi_fpga_TddTiming_t extTrig4;
    
    adi_fpga_TddDatapathControl_t rxDatapath0;
    adi_fpga_TddDatapathControl_t rxDatapath1;
    adi_fpga_TddDatapathControl_t rxDatapath2;
    adi_fpga_TddDatapathControl_t txDatapath0;
    adi_fpga_TddDatapathControl_t txDatapath1;

} adi_fpga_TddStateMachine_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_TDD_TYPES_H_ */
