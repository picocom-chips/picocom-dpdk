/**
 * \file: fpga9025_tdd.c
 *
 * \brief Contains private tdd related functions
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025.h"
#include "adi_fpga9025_error.h"
#include "../../private/include/fpga9025_tdd.h"
#include "../../private/include/fpga9025_bf_tdd_dp_ctrl.h"
#include "../../private/include/fpga9025_bf_tdd_dp_ctrl_types.h"
#include "../../private/include/fpga9025_bf_tdd_enable_ctrl.h"
#include "../../private/include/fpga9025_bf_tdd_enable_ctrl_types.h"
#include "../../private/include/fpga9025_bf_tdd_frame_cnt.h"
#include "../../private/include/fpga9025_bf_tdd_frame_cnt_types.h"

int32_t fpga9025_TddEnableControlModuleSet(adi_fpga9025_Device_t* device,
                                           adi_fpga_TddTiming_t*  module,
                                           uint32_t               baseAddress)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        module);

    if (module->offPtr != module->onPtr)
    {
        recoveryAction = fpga9025_TddEnableCtrlEnableBfSet(device,
                                                           (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                           0x01);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlStartValueBfSet(device,
                                                               (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                               module->onPtr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module start bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlEndValueBfSet(device,
                                                             (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                             module->offPtr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module end bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        recoveryAction = fpga9025_TddEnableCtrlEnableBfSet(device,
                                                           (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                           0x00);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlStartValueBfSet(device,
                                                               (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                               0x00);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module start bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlEndValueBfSet(device,
                                                             (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                             0x00);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module end bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (module->secondaryOffPtr != module->secondaryOnPtr)
    {
        recoveryAction = fpga9025_TddEnableCtrlSecEnableBfSet(device,
                                                              (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                              0x01);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlSecStartValueBfSet(device,
                                                                  (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                                  module->secondaryOnPtr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module start bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlSecEndValueBfSet(device,
                                                                (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                                module->secondaryOffPtr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module end bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        recoveryAction = fpga9025_TddEnableCtrlSecEnableBfSet(device,
                                                              (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                              0x00);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module enable bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlSecStartValueBfSet(device,
                                                                  (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                                  0x00);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module start bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_TddEnableCtrlSecEndValueBfSet(device,
                                                                (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                                0x00);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Could not write to Rx4 Enable Control module end bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9025_TddEnableCtrlFramesOffsetBfSet(device,
                                                             (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                             module->offsetFrames);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlFramesInactiveBfSet(device,
                                                               (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                               module->inactiveFrames);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlFramesActiveBfSet(device,
                                                             (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                             module->activeFrames);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t fpga9025_TddEnableControlModuleGet(adi_fpga9025_Device_t* device,
                                           adi_fpga_TddTiming_t*  module,
                                           uint32_t               baseAddress)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        module);

    recoveryAction = fpga9025_TddEnableCtrlStartValueBfGet(device,
                                                           (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                           &module->onPtr);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlEndValueBfGet(device,
                                                         (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                         &module->offPtr);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module end bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlSecStartValueBfGet(device,
                                                              (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                              &module->secondaryOnPtr);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlSecEndValueBfGet(device,
                                                            (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                            &module->secondaryOffPtr);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module end bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlFramesOffsetBfGet(device,
                                                             (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                             &module->offsetFrames);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlFramesInactiveBfGet(device,
                                                               (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                               &module->inactiveFrames);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_TddEnableCtrlFramesActiveBfGet(device,
                                                             (fpga9025_BfTddEnableCtrlChanAddr_e)baseAddress,
                                                             &module->activeFrames);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Could not write to Rx4 Enable Control module start bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}
