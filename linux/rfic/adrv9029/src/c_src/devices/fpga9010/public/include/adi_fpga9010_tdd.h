/**
* \file adi_fpga9010.h
* \brief Contains top level fpga9010 related function prototypes for
*        adi_fpga9010_tdd.c
*
* FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
*/
/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_TDD_H_
#define _ADI_FPGA9010_TDD_H_

#include "adi_fpga9010_tdd_types.h"
#include "adi_fpga9010_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* \brief Initializes the FPGA TDD state machine
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param fpgaTddStateMachine is a pointer to structure type fpgaTddStateMachine_t which contains all
* TDD state machine parameters.  This structure must be pre-loaded before use and is checked for a
* null pointer if not initialized and an error will be thrown.
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_TddInit(adi_fpga9010_Device_t *device, adi_fpga9010_TddStateMachine_t *fpgaTddStateMachine);

/**
* \brief Reads the FPGA TDD state machine from the FPGA modules and loads the values into the structure
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param fpgaTddStateMachine is a pointer to an empty structure type fpgaTddStateMachine_t.
*
* \retval ADI_FPGA9010_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_TddInitGet(adi_fpga9010_Device_t *device, adi_fpga9010_TddStateMachine_t *fpgaTddStateMachine);

/**
* \brief Enables the TDD state machine by setting the Frame Counter module enable bit
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_TddEnable(adi_fpga9010_Device_t *device);

/**
* \brief Disables the TDD state machine by clearing the Frame Counter enable bit
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_TddDisable(adi_fpga9010_Device_t *device);


int32_t adi_fpga9010_TddDataGate(adi_fpga9010_Device_t *device);

/**
* \brief    Manually asserts the TDD enable pins indicated in the fpgaTddEnables parameter
*           using the following bitmapping:
*
* fpgaTddEnables[bit]  |  TDD Enable signal
* ---------------------|------------------------
*        0             |        Rx1
*        1             |        Rx2
*        2             |        Rx3
*        3             |        Rx4
*        4             |        Orx1
*        5             |        Orx2
*        6             |        Orx3
*        7             |        Orx4
*        8             |        Tx1
*        9             |        Tx2
*        10            |        Tx3
*        11            |        Tx4
*        12            |        Ext1
*        13            |        Ext2
*        14            |        Ext3
*        15            |        Ext4
*        16            |        Tx1 to Orx1
*        17            |        Tx2 to Orx1
*        18            |        Tx1 to Orx2
*        19            |        Tx2 to Orx2
*        20            |        Tx3 to Orx3
*        21            |        Tx4 to Orx3
*        22            |        Tx3 to Orx4
*        23            |        Tx4 to Orx4
*
*           This is a manual control used for debug and is overridden
*           anytime the TDD state machine is enabled. The function will
*           NOT disable all TDD modules prior to asserting the enables, it
*           is incumbent on the user to disable TDD prior to using manual
*           enable assertion. The value of the bit for each TDD enable module
*           is what will be written to the manual assert value.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param fpgaTddEnables is a uint32_t bit field which contains the TDD enable
* bits for assertion.  
*
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
* \retval ADI_FPGA9010_ACT_INV_TDD_ASSERT_SELECT Invalid bits were selected when asserting TDD pins
*
*/
int32_t adi_fpga9010_TddEnablesAssertSet(adi_fpga9010_Device_t *device, uint32_t fpgaTddEnables);

/**
* \brief    This function will read back the manual enable assert value that is currently written in each
*           Enable Control module. Note: If TDD is not properly disabled, the manual enable value might not
*           correspond with the actual pin logic state.
*
* fpgaTddEnables[bit]  |  TDD Enable signal
* ---------------------|------------------------
*        0             |        Rx1
*        1             |        Rx2
*        2             |        Rx3
*        3             |        Rx4
*        4             |        Orx1
*        5             |        Orx2
*        6             |        Orx3
*        7             |        Orx4
*        8             |        Tx1
*        9             |        Tx2
*        10            |        Tx3
*        11            |        Tx4
*        12            |        Ext1
*        13            |        Ext2
*        14            |        Ext3
*        15            |        Ext4
*        16            |        Tx1 to Orx1
*        17            |        Tx2 to Orx1
*        18            |        Tx1 to Orx2
*        19            |        Tx2 to Orx2
*        20            |        Tx3 to Orx3
*        21            |        Tx4 to Orx3
*        22            |        Tx3 to Orx4
*        23            |        Tx4 to Orx4
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param fpgaTddEnables is a uint32_t bit field which will hold the TDD enable
* bits currently set in the module.
*
* \retval ADI_FPGA9010_ACT_NO_ACTION Function completed successfully, no action required
* \retval ADI_FPGA9010_ACT_INV_TDD_ASSERT_SELECT Invalid bits were selected when asserting TDD pins
*
*/
int32_t adi_fpga9010_TddEnablesAssertGet(adi_fpga9010_Device_t *device, uint32_t *fpgaTddEnables);

/**
* \brief This function will setup the Orx Pin Encode module with the values passed in
*        through the orxPinEncodeCfg structure.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param orxPinEncodeCfg Pointer to a filled out adi_fpga9010_OrxPinEncodeCfg_t structure 
*
* \retval ADI_FPGA9010_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_TddOrxPinCfgSet(adi_fpga9010_Device_t *device, adi_fpga9010_OrxPinEncodeCfg_t *orxPinEncodeCfg);

/**
* \brief This function will read the Orx Pin Encode module and write the values to the
*        orxPinEncodeCfg structure passed in.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9010 device data structure.
* \param orxPinEncodeCfg Pointer to a adi_fpga9010_OrxPinEncodeCfg_t structure to be filled with current module values
*
* \retval ADI_FPGA9010_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9010_TddOrxPinCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_OrxPinEncodeCfg_t *orxPinEncodeCfg);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_TDD_H_ */