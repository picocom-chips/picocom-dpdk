/*!
* \file adi_fpga9025_tdd_types.h
* \brief Contains FPGA9025 TDD enum and struct definitions
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_TDD_TYPES_H_
#define _ADI_FPGA9025_TDD_TYPES_H_

#include <stdint.h>
//#include "adi_fpga9025_tdd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
*   \brief  Enumumerated list of the Orx Pin Encode modes
*/
typedef enum adi_fpga9025_OrxPinEncodeModes
{
    ADI_FPGA9025_ORXPINENCODE_MODE1     = 0,    /* 3 pin mode (ORx_Enable and ORx_Select[1:0] pins) */
    ADI_FPGA9025_ORXPINENCODE_MODE1A    = 1,   /* 2 pin mode (ORx_Enable and ORx_Select pins) */
    ADI_FPGA9025_ORXPINENCODE_MODE2     = 2,    /* 4 pin mode (2 ORx_Enable pins and 2 ORx Select pins) */
    ADI_FPGA9025_ORXPINENCODE_MODE3     = 3,    /* 1 pin mode (ORx selection is accomplished via SPI bits) */
    ADI_FPGA9025_ORXPINENCODE_MODE4     = 4     /* 2 pin mode (ORx selection is accomplished via SPI bits) */
} adi_fpga9025_OrxPinEncodeModes_e;

/**
*  \brief   Structure to hold the FPGA TDD Timing parameters. Located in the TDD Enable
*           Control FPGA module. Includes primary & secondary region parameters.
*/
typedef struct adi_fpga_TddTiming
{
    uint32_t onPtr;           /*!< On pointer (start value) for TDD primary region */
    uint32_t offPtr;          /*!< Off pointer (start value) for TDD primary region */
    uint32_t secondaryOnPtr;  /*!< On pointer (start value) for TDD secondary region */
    uint32_t secondaryOffPtr; /*!< Off pointer (start value) for TDD secondary region */
    uint32_t offsetFrames;    /*!< Offset frame value for primary & secondary region */
    uint32_t activeFrames;    /*!< Active frame value for primary & secondary region */
    uint32_t inactiveFrames;  /*!< Inactive frame value for primary & secondary region */
} adi_fpga_TddTiming_t;

/**
*  \brief   Structure to hold the FPGA TDD Datapath parameters. Located in the TDD Datapath
*           Control FPGA module.
*/
typedef struct adi_fpga_TddDatapathControl
{
    uint8_t  enable;     /*!< Set this value to 1 to enable this datapath. Otherwise, set to 0 */
    uint32_t startValue; /*!< Start Value for Datapath Control Module. Effectively the Datapath Delay value */
} adi_fpga_TddDatapathControl_t;

/**
*  \brief   Structure to hold the FPGA TDD state machine parameters
*/
typedef struct adi_fpga_TddStateMachine
{
    uint32_t loopCount;   /*!< Set this value to > 1 to enable looping */
    uint8_t  syncExtTrig; /*!< Set this value to 1 to enable external triggering. Otherwise, set to 0 */
    uint32_t frameCount;  /*!< Number of Tx LaneRate /40 clock cycles in the desired frame time */

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

typedef enum adi_fpga9025_TddGpioModule
{
    ADI_FPGA9025_ENABLE1CONTROL,
    ADI_FPGA9025_ENABLE2CONTROL,
    ADI_FPGA9025_ENABLE3CONTROL,
    ADI_FPGA9025_ENABLE4CONTROL,
    ADI_FPGA9025_SELECT1CONTROL,
    ADI_FPGA9025_SELECT2CONTROL,
    ADI_FPGA9025_SELECT3CONTROL,
    ADI_FPGA9025_SELECT4CONTROL
} adi_fpga9025_TddModule_e;

/**
*  \brief   Structure to hold the FPGA TDD Orx Pin Encode module parameters
*/
typedef struct adi_fpga9025_OrxPinEncodeCfg
{
    adi_fpga9025_OrxPinEncodeModes_e modeSelect;            /*!< Selects the ORX Pin mode encoding. */
    uint8_t                          fastSwitchingEnable;   /*!< Enables fast switching when changing ORX Select.  When set to 1, ORX Select is allowed to change with ORX Enable high.  When set to 0, ORX Enable is brought low before switching the ORX Select bits. */
    uint8_t mode1aOrxSelectLow;                             /*!< When in Mode 1A, this bit field identifies which ORX channel is enabled when the ORX Select pin is low. The valid values are:0b00 - ORX1; 0b01 - ORX2; 0b10 - ORX3; 0b11 - ORX4; */
    uint8_t mode1aOrxSelectHigh;                            /*!< When in Mode 1A, this bit field identifies which ORX channel is enabled when the ORX Select pin is high. The valid values are:0b00 - ORX1; 01 - ORX2; 0b10 - ORX3; 0b11 - ORX4; */
    uint8_t mode3OrxSelect;                                 /*!< When in Mode 3, this bit field identifies the ORX channel that is enabled. The valid values are:0b00 - ORX1; 01 - ORX2; 0b10 - ORX3; 0b11 - ORX4; */
    uint16_t orxSelectSetupTime;                            /*!< This bit field sets the amount of time, in TDD State Machine clock periods, that the state machine waits after setting the ORX Select pins before raising ORX Enable.  If the state machine is configured to allow fast switching, this setup time is performed before ORX Enable raises.  Once high, the ORX Select is switched immediately.  Should be written value minus 1. */
    uint16_t orxEnableHighTime;                             /*!< Sets the minimum amount of time that ORX Enable is high in 10s of nanoseconds.  Should be written value minus 1. */
    uint16_t orxEnableLowTime;                              /*!< Sets the minimum amount of time that ORX Enable is low in 10s of nanoseconds.  Should be written value minus 1. */
} adi_fpga9025_OrxPinEncodeCfg_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_TDD_TYPES_H_ */
