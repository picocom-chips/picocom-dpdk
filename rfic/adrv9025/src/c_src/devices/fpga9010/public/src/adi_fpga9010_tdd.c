/**
 * \file: adi_fpga9010_tdd.c
 *
 * \brief Contains top level tdd fpga9010 related functions
 *
 * FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_tdd.h"
#include "adi_fpga9010.h"
#include "../../private/include/fpga9010_tdd.h"
#include "../../private/include/fpga9010_bf_tdd_dp_ctrl.h"
#include "../../private/include/fpga9010_bf_tdd_enable_ctrl.h"
#include "../../private/include/fpga9010_bf_tdd_frame_cnt.h"
#include "../../private/include/fpga9010_bf_orx_pin_encode_tokelau.h"

#define ADI_FPGA9010_TDDENABLECTRL_CNT 24
#define ADI_FPGA9010_TDDDATAPATHCTRL_CNT 5

static const fpga9010_BfTddEnableCtrlChanAddr_e enableCtrlAddrArray[ADI_FPGA9010_TDDENABLECTRL_CNT] = 
{ 
    FPGA9010_BF_TDD_ENABLE_CONTROL_RX1, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_RX2, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_RX3, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_RX4, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_ORX1,
    FPGA9010_BF_TDD_ENABLE_CONTROL_ORX2,
    FPGA9010_BF_TDD_ENABLE_CONTROL_ORX3,
    FPGA9010_BF_TDD_ENABLE_CONTROL_ORX4,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX1, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX2, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX3, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX4, 
    FPGA9010_BF_TDD_ENABLE_CONTROL_EXT1,
    FPGA9010_BF_TDD_ENABLE_CONTROL_EXT2,
    FPGA9010_BF_TDD_ENABLE_CONTROL_EXT3,
    FPGA9010_BF_TDD_ENABLE_CONTROL_EXT4,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4,
    FPGA9010_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4
 };

static const fpga9010_BfTddDpCtrlChanAddr_e datapathctrlAddrArray[ADI_FPGA9010_TDDDATAPATHCTRL_CNT] = 
{ 
    FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0,
    FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1,
    FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2,
    FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0,
    FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1
};

int32_t adi_fpga9010_TddInit(adi_fpga9010_Device_t *device, adi_fpga9010_TddStateMachine_t *fpgaTddStateMachine)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, fpgaTddStateMachine);
    
    /* Frame Counter module setup */
    if (fpgaTddStateMachine->loopCount > 0)
    {
        recoveryAction = fpga9010_TddFrameCntLoopCountEnBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to loop_count_en bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    recoveryAction = fpga9010_TddFrameCntLoopCountBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, fpgaTddStateMachine->loopCount);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to loop_count_en bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_TddFrameCntTriggerBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, fpgaTddStateMachine->syncExtTrig);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to loop_count bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_TddFrameCntEndValueBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, fpgaTddStateMachine->frameCount);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to End_value bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Enable Control module setup */
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->rx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->rx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX2);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->rx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX3);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->rx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX4);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->orx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->orx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX2);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->orx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX3);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->orx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX4);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX2);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX3);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx1ToOrx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx2ToOrx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx1ToOrx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx2ToOrx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx3ToOrx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx4ToOrx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx3ToOrx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->tx4ToOrx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->extTrig1, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->extTrig2, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT2);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->extTrig3, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT3);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    fpga9010_TddEnableControlModuleSet(device, &fpgaTddStateMachine->extTrig4, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT4);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Datapath control module setup */
    recoveryAction = fpga9010_TddDpCtrlEnableBitBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0, fpgaTddStateMachine->rxDatapath0.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0, fpgaTddStateMachine->rxDatapath0.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_TddDpCtrlEnableBitBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1, fpgaTddStateMachine->rxDatapath1.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1, fpgaTddStateMachine->rxDatapath1.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_TddDpCtrlEnableBitBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2, fpgaTddStateMachine->rxDatapath2.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2, fpgaTddStateMachine->rxDatapath2.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_TddDpCtrlEnableBitBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0, fpgaTddStateMachine->txDatapath0.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0, fpgaTddStateMachine->txDatapath0.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    recoveryAction = fpga9010_TddDpCtrlEnableBitBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1, fpgaTddStateMachine->txDatapath1.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfSet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1, fpgaTddStateMachine->txDatapath1.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddInitGet(adi_fpga9010_Device_t *device, adi_fpga9010_TddStateMachine_t *fpgaTddStateMachine)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, fpgaTddStateMachine);

    recoveryAction = fpga9010_TddFrameCntLoopCountBfGet(device, FPGA9010_BF_TDD_FRAME_COUNTER, &fpgaTddStateMachine->loopCount);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to loop_count_en bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddFrameCntTriggerBfGet(device, FPGA9010_BF_TDD_FRAME_COUNTER, &fpgaTddStateMachine->syncExtTrig);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to loop_count bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddFrameCntEndValueBfGet(device, FPGA9010_BF_TDD_FRAME_COUNTER, &fpgaTddStateMachine->frameCount);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to End_value bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Enable Control module setup */
    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->rx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->rx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->rx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->rx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_RX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->orx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->orx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->orx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->orx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_ORX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx1ToOrx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx2ToOrx1EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx1ToOrx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx2ToOrx2EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx3ToOrx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx4ToOrx3EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx3ToOrx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->tx4ToOrx4EnableControl, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->extTrig1, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->extTrig2, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT2);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->extTrig3, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT3);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_TddEnableControlModuleGet(device, &fpgaTddStateMachine->extTrig4, (uint32_t)FPGA9010_BF_TDD_ENABLE_CONTROL_EXT4);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Datapath control module read */
    recoveryAction = fpga9010_TddDpCtrlEnableBitBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0, &fpgaTddStateMachine->rxDatapath0.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0, &fpgaTddStateMachine->rxDatapath0.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddDpCtrlEnableBitBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1, &fpgaTddStateMachine->rxDatapath1.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1, &fpgaTddStateMachine->rxDatapath1.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddDpCtrlEnableBitBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2, &fpgaTddStateMachine->rxDatapath2.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2, &fpgaTddStateMachine->rxDatapath2.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddDpCtrlEnableBitBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0, &fpgaTddStateMachine->txDatapath0.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0, &fpgaTddStateMachine->txDatapath0.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddDpCtrlEnableBitBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1, &fpgaTddStateMachine->txDatapath1.enable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_TddDpCtrlStartValueBfGet(device, FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1, &fpgaTddStateMachine->txDatapath1.startValue);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddEnable(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    recoveryAction = fpga9010_TddFrameCntEnableBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddDisable(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i = 0;
    
#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    recoveryAction = fpga9010_TddFrameCntEnableBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_TddFrameCntLoopCountEnBfSet(device, FPGA9010_BF_TDD_FRAME_COUNTER, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to loop_count_en bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Disable the enable control modules */
    for (i = 0; i < ADI_FPGA9010_TDDENABLECTRL_CNT; i++)
    {
        recoveryAction = fpga9010_TddEnableCtrlEnableBfSet(device, enableCtrlAddrArray[i], 0);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Enable Control module enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9010_TddEnableCtrlSecEnableBfSet(device, enableCtrlAddrArray[i], 0);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Secondary Enable Control module enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Disable the datapath control modules */
    for (i = 0; i < ADI_FPGA9010_TDDDATAPATHCTRL_CNT; i++)
    {
        recoveryAction = fpga9010_TddDpCtrlEnableBitBfSet(device, datapathctrlAddrArray[i], 0);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to Datapath Control enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddDataGate(adi_fpga9010_Device_t *device)
{
    //TODO: implement this
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddEnablesAssertSet(adi_fpga9010_Device_t *device, uint32_t fpgaTddEnables)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    /* Set the enable control modules */
    for (i = 0; i < ADI_FPGA9010_TDDENABLECTRL_CNT; i++)
    {
        recoveryAction = fpga9010_TddEnableCtrlManualEnableBfSet(device, enableCtrlAddrArray[i], (uint8_t)((fpgaTddEnables >> i) & 1));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to manual enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddEnablesAssertGet(adi_fpga9010_Device_t *device, uint32_t *fpgaTddEnables)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i = 0;
    uint8_t enableRead = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, fpgaTddEnables);

    *fpgaTddEnables = 0;

    /* Get the enable control modules */
    for (i = 0; i < ADI_FPGA9010_TDDENABLECTRL_CNT; i++)
    {
        recoveryAction = fpga9010_TddEnableCtrlManualEnableBfGet(device, enableCtrlAddrArray[i], &enableRead);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to manual enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        *fpgaTddEnables |= ((uint32_t)enableRead & 1) << i;
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TddOrxPinCfgSet(adi_fpga9010_Device_t *device, adi_fpga9010_OrxPinEncodeCfg_t *orxPinEncodeCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, orxPinEncodeCfg);

    recoveryAction = fpga9010_OrxPinEncodeTokelauModeSelectBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->modeSelect);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauFastSwitchingEnableBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->fastSwitchingEnable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauMode1aOrxSelectLowBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->mode1aOrxSelectLow);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauMode1aOrxSelectHighBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->mode1aOrxSelectHigh);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauMode3OrxSelectBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->mode3OrxSelect);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauOrxSelectSetupTimeBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->orxSelectSetupTime - 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauOrxEnableHighTimeBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->orxEnableHighTime - 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauOrxEnableLowTimeBfSet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, orxPinEncodeCfg->orxEnableLowTime - 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);

}

int32_t adi_fpga9010_TddOrxPinCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_OrxPinEncodeCfg_t *orxPinEncodeCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint16_t rawRegisterValue = 0;
    uint8_t modeSelectReadback = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, orxPinEncodeCfg);

    recoveryAction = fpga9010_OrxPinEncodeTokelauModeSelectBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &modeSelectReadback);
    orxPinEncodeCfg->modeSelect = (adi_fpga9010_OrxPinEncodeModes_e)modeSelectReadback;
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauFastSwitchingEnableBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &orxPinEncodeCfg->fastSwitchingEnable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauMode1aOrxSelectLowBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &orxPinEncodeCfg->mode1aOrxSelectLow);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauMode1aOrxSelectHighBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &orxPinEncodeCfg->mode1aOrxSelectHigh);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauMode3OrxSelectBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &orxPinEncodeCfg->mode3OrxSelect);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauOrxSelectSetupTimeBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &rawRegisterValue);
    orxPinEncodeCfg->orxSelectSetupTime = rawRegisterValue + 1;
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauOrxEnableHighTimeBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &rawRegisterValue);
    orxPinEncodeCfg->orxEnableHighTime = rawRegisterValue + 1;
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_OrxPinEncodeTokelauOrxEnableLowTimeBfGet(device, FPGA9010_BF_TDD_ORX_PIN_ENCODE, &rawRegisterValue);
    orxPinEncodeCfg->orxEnableLowTime = rawRegisterValue + 1;
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to mode select bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);

}

