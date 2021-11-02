/**
 * \file: adi_fpga9025_rx.c
 *
 * \brief Contains top level rx fpga9025 related functions
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_rx.h"
#include "adi_fpga9025.h"
#include "../../private/include/fpga9025_bf_dp_tollgate.h"
#include "../../private/include/fpga9025_bf_dp_rx_dma.h"
#include "../../private/include/fpga9025_bf_dp_capture_control.h"

int32_t adi_fpga9025_RxTollgateSet(adi_fpga9025_Device_t*        device,
                                   uint32_t                      rxDatamoverSelMask,
                                   adi_fpga9025_RxTollgateCfg_t* tollGateCfg)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_RxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        tollGateCfg);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTollgateEdgeLevelBfSet(device,
                                                               instanceAddress,
                                                               tollGateCfg->tollGateEdgeOrLvl);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to detection register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTollgateHighRisingLowFallingBfSet(device,
                                                                          instanceAddress,
                                                                          tollGateCfg->tollGateHiRiseOrLoFall);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to polarity register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTollgateTriggerSelectBfSet(device,
                                                                   instanceAddress,
                                                                   (uint32_t)tollGateCfg->tollGateTrigSource);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to selection register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxTollgateGet(adi_fpga9025_Device_t*        device,
                                   adi_fpga9025_RxDatamoverSel_e rxDatamoverSel,
                                   adi_fpga9025_RxTollgateCfg_t* tollGateCfg)
{
    int32_t                         recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e baseAddress    = FPGA9025_BF_DP_TOLLGATE_RX_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        tollGateCfg);

    switch (rxDatamoverSel)
    {
    case ADI_FPGA9025_RX_DATAMOVER_0:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
        break;
    case ADI_FPGA9025_RX_DATAMOVER_1:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_RX_1;
        break;
    case ADI_FPGA9025_RX_DATAMOVER_2:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_RX_2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         rxDatamoverSel,
                         "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9025_DpTollgateEdgeLevelBfGet(device,
                                                       baseAddress,
                                                       &tollGateCfg->tollGateEdgeOrLvl);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to detection register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTollgateHighRisingLowFallingBfGet(device,
                                                                  baseAddress,
                                                                  &tollGateCfg->tollGateHiRiseOrLoFall);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to polarity register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTollgateTriggerSelectBfGet(device,
                                                           baseAddress,
                                                           (uint32_t*)&tollGateCfg->tollGateTrigSource);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to selection register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxTollgateResetSet(adi_fpga9025_Device_t* device,
                                        uint32_t               rxDatamoverSelMask,
                                        uint8_t                resetVal)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_RxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTollgateResetTollgateBfSet(device,
                                                                   instanceAddress,
                                                                   resetVal);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxTollgateResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               rxDatamoverSelMask,
                                        uint16_t*              resetVal)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_RxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;
    uint8_t                         resetBitRead    = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        resetVal);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *resetVal = 0;

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTollgateResetTollgateBfGet(device,
                                                                   instanceAddress,
                                                                   &resetBitRead);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not read from reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        *resetVal |= (resetBitRead & 1) << i;
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxTollgateTriggerSet(adi_fpga9025_Device_t*               device,
                                          uint32_t                             rxDatamoverSelMask,
                                          adi_fpga9025_RxTollgateTrigSources_e triggerSelect)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_RxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = adi_fpga9025_RxTollgateResetSet(device,
                                                             rxDatamoverSelMask,
                                                             1);
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTollgateTriggerSelectBfSet(device,
                                                                   (fpga9025_BfDpTollgateChanAddr_e)instanceAddress,
                                                                   (uint32_t)triggerSelect);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Could not write to triggerSelect bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9025_RxTollgateResetSet(device,
                                                             rxDatamoverSelMask,
                                                             0);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxTollgateTriggerGet(adi_fpga9025_Device_t*                device,
                                          adi_fpga9025_RxDatamoverSel_e         rxDatamoverSel,
                                          adi_fpga9025_RxTollgateTrigSources_e* triggerSelect)
{
    int32_t                         recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e baseAddress      = FPGA9025_BF_DP_TOLLGATE_RX_0;
    uint32_t                        triggerSelectGet = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        triggerSelect);

    switch (rxDatamoverSel)
    {
    case ADI_FPGA9025_RX_DATAMOVER_0:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_RX_0;
        break;
    case ADI_FPGA9025_RX_DATAMOVER_1:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_RX_1;
        break;
    case ADI_FPGA9025_RX_DATAMOVER_2:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_RX_2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         rxDatamoverSel,
                         "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9025_DpTollgateTriggerSelectBfGet(device,
                                                           baseAddress,
                                                           &triggerSelectGet);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to selection register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    *triggerSelect = (adi_fpga9025_RxTollgateTrigSources_e)triggerSelectGet;

    return recoveryAction;
}

int32_t adi_fpga9025_RxDmaSet(adi_fpga9025_Device_t*   device,
                              uint32_t                 rxDatamoverSelMask,
                              adi_fpga9025_RxDmaCfg_t* rxDmaCfg)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpRxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_RxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;
    uint32_t                      tempWorkAround  = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        rxDmaCfg);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* TODO: start address could be changed at runtime by this function, and this length check is not enough to ensure RAM buffers do not overlap */
        if (rxDmaCfg->length > ADI_FPGA9025_RX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Rx DMA capture length is too large");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpRxDmaEnableEnhancedModeBfSet(device,
                                                                     instanceAddress,
                                                                     rxDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaEnableSgBfSet(device,
                                                           instanceAddress,
                                                           rxDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaLengthBfSet(device,
                                                         instanceAddress,
                                                         rxDmaCfg->length);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaSgFirstDescriptorBfSet(device,
                                                                    instanceAddress,
                                                                    rxDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* TODO: writing to this seems to be clearing the status register. debug later */
            /*            recoveryAction = fpga9025_DpRxDmaSgLastDescriptorBfSet(device, instanceAddress, rxDmaCfg->sgLastDescriptor);
             *            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9025_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
             *            ADI_ERROR_RETURN(device->common.error.newAction);
            */
            recoveryAction = adi_hal_BbicRegisterRead(device->common.devHalInfo,
                                                      instanceAddress + 0x2C,
                                                      &tempWorkAround);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             recoveryAction,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             spicrAddress,
                             "Error");
            ADI_ERROR_RETURN(device->common.error.newAction);
            tempWorkAround &= (0xFFFF0000);
            tempWorkAround |= (0x4000);
            recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                                       instanceAddress + 0x2C,
                                                       tempWorkAround);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             recoveryAction,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             spissrAddress,
                             "Error selecting all Tokelau devices");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaSimpleStartAddrBfSet(device,
                                                                  instanceAddress,
                                                                  (uint32_t)(rxDmaCfg->simpleStartAddr & 0x00000000FFFFFFFF));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaSimpleStartAddrMswBfSet(device,
                                                                     instanceAddress,
                                                                     (uint32_t)(rxDmaCfg->simpleStartAddr >> 32));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddrMsw bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaValidDataWidthStreamBfSet(device,
                                                                       instanceAddress,
                                                                       rxDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxDmaInit(adi_fpga9025_Device_t*   device,
                               uint32_t                 rxDatamoverSelMask,
                               adi_fpga9025_RxDmaCfg_t* rxDmaCfg)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpRxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_RxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        rxDmaCfg);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpRxDmaEnableEnhancedModeBfSet(device,
                                                                     instanceAddress,
                                                                     rxDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaEnableSgBfSet(device,
                                                           instanceAddress,
                                                           rxDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaSgFirstDescriptorBfSet(device,
                                                                    instanceAddress,
                                                                    rxDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* TODO: writing to this seems to be clearing the status register. debug later */
            /*            recoveryAction = fpga9025_DpRxDmaSgLastDescriptorBfSet(device, instanceAddress, rxDmaCfg->sgLastDescriptor);
             *            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9025_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
             *            ADI_ERROR_RETURN(device->common.error.newAction);
            */

            recoveryAction = fpga9025_DpRxDmaSimpleStartAddrBfSet(device,
                                                                  instanceAddress,
                                                                  (uint32_t)(rxDmaCfg->simpleStartAddr & 0x00000000FFFFFFFF));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaSimpleStartAddrMswBfSet(device,
                                                                     instanceAddress,
                                                                     (uint32_t)(rxDmaCfg->simpleStartAddr >> 32));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddrMsw bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpRxDmaValidDataWidthStreamBfSet(device,
                                                                       instanceAddress,
                                                                       rxDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxDmaGet(adi_fpga9025_Device_t*        device,
                              adi_fpga9025_RxDatamoverSel_e rxDatamoverSel,
                              adi_fpga9025_RxDmaCfg_t*      rxDmaCfg)
{
    int32_t                      recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpRxDmaChanAddr_e baseAddress      = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                     addressReadValue = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        rxDmaCfg);

    switch (rxDatamoverSel)
    {
    case ADI_FPGA9025_RX_DATAMOVER_0:
        baseAddress = FPGA9025_BF_DP_DMA_RX_0;
        break;
    case ADI_FPGA9025_RX_DATAMOVER_1:
        baseAddress = FPGA9025_BF_DP_DMA_RX_1;
        break;
    case ADI_FPGA9025_RX_DATAMOVER_2:
        baseAddress = FPGA9025_BF_DP_DMA_RX_2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         rxDatamoverSel,
                         "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9025_DpRxDmaActiveBfGet(device,
                                                 baseAddress,
                                                 &rxDmaCfg->active);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read active bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaCompleteBfGet(device,
                                                   baseAddress,
                                                   &rxDmaCfg->complete);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read complete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaEnableEnhancedModeBfGet(device,
                                                             baseAddress,
                                                             &rxDmaCfg->enableEnhancedMode);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read enableEnhancedMode bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaEnableSgBfGet(device,
                                                   baseAddress,
                                                   &rxDmaCfg->enableSg);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read enableSg bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaHaltCompleteBfGet(device,
                                                       baseAddress,
                                                       &rxDmaCfg->haltComplete);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read haltComplete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaLengthBfGet(device,
                                                 baseAddress,
                                                 &rxDmaCfg->length);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read length bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    //    recoveryAction = fpga9025_DpRxDmaOverflowBfGet(device, baseAddress, &rxDmaCfg->overflow);
    //    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9025_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read overflow bitfield");
    //    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaRunStopBfGet(device,
                                                  baseAddress,
                                                  &rxDmaCfg->runStop);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read runStop bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaSgFirstDescriptorBfGet(device,
                                                            baseAddress,
                                                            &rxDmaCfg->sgFirstDescriptor);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read sgFirstDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaSgLastDescriptorBfGet(device,
                                                           baseAddress,
                                                           &rxDmaCfg->sgLastDescriptor);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read sgLastDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpRxDmaSimpleStartAddrBfGet(device,
                                                          baseAddress,
                                                          &addressReadValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read simpleStartAddr bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    rxDmaCfg->simpleStartAddr = addressReadValue;

    recoveryAction = fpga9025_DpRxDmaSimpleStartAddrMswBfGet(device,
                                                             baseAddress,
                                                             &addressReadValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read simpleStartAddrMsw bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    rxDmaCfg->simpleStartAddr |= (uint64_t)addressReadValue << 32;

    recoveryAction = fpga9025_DpRxDmaValidDataWidthStreamBfGet(device,
                                                               baseAddress,
                                                               &rxDmaCfg->validDataWidthStream);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read validDataWidthStream bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxDmaResetSet(adi_fpga9025_Device_t* device,
                                   uint32_t               rxDatamoverSelMask,
                                   uint8_t                reset)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpRxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_RxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpRxDmaResetBfSet(device,
                                                        instanceAddress,
                                                        reset);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxDmaRunStopSet(adi_fpga9025_Device_t* device,
                                     uint32_t               rxDatamoverSelMask,
                                     uint8_t                runStop)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpRxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_RxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpRxDmaRunStopBfSet(device,
                                                          instanceAddress,
                                                          runStop);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxDmaLengthSet(adi_fpga9025_Device_t* device,
                                    uint32_t               rxDatamoverSelMask,
                                    uint32_t               numBytes)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpRxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_RxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (numBytes > ADI_FPGA9025_RX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Rx DMA capture length is too large");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpRxDmaLengthBfSet(device,
                                                         instanceAddress,
                                                         numBytes);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_RxDatamoverEnableSet(adi_fpga9025_Device_t* device,
                                          uint32_t               rxDatamoverSelMask)
{
    UNUSED_PARA(rxDatamoverSelMask);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    return recoveryAction;
}

int32_t adi_fpga9025_RxDataChainConfigure(adi_fpga9025_Device_t*               device,
                                          uint32_t                             rxDataMoverSelMask,
                                          adi_fpga9025_RxTollgateTrigSources_e triggerSelect,
                                          adi_fpga9025_RxDmaCfg_t*             rxDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* reset capture control */

    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* set trigger */
    recoveryAction = adi_fpga9025_RxTollgateTriggerSet(device,
                                                       rxDataMoverSelMask,
                                                       triggerSelect);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /*reset dmas */
    recoveryAction = adi_fpga9025_RxDmaResetSet(device,
                                                rxDataMoverSelMask,
                                                1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* configure dmas */
    recoveryAction = adi_fpga9025_RxDmaSet(device,
                                           rxDataMoverSelMask,
                                           rxDmaCfg);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* set run_stop bit */
    recoveryAction = adi_fpga9025_RxDmaRunStopSet(device,
                                                  rxDataMoverSelMask,
                                                  1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* pass token to start dma arbitration */
    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_DpCaptureControlPassTokenBfSet(device,
                                                             FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                             1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control PassToken bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxDataChainReset(adi_fpga9025_Device_t* device)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    uint8_t                       active          = 0;
    uint8_t                       haltComplete    = 0;
    fpga9025_BfDpRxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_RxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_RX_DATAMOVER_0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* reset  */
    recoveryAction = fpga9025_DpCaptureControlDatapathActiveBfSet(device,
                                                                  FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                                  0);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_RxDatamoverSel_e)((uint8_t)(1 << i));
        active       = 0;
        haltComplete = 0;

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_RX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9025_RX_DATAMOVER_2:
            instanceAddress = FPGA9025_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        recoveryAction = fpga9025_DpRxDmaActiveBfGet(device,
                                                     instanceAddress,
                                                     &active);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Capture Control Reset bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = adi_fpga9025_RxDmaRunStopSet(device,
                                                      dataMoverSel,
                                                      0);
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (active == 1)
        {
            while (haltComplete == 0)
            {
                recoveryAction = fpga9025_DpRxDmaHaltCompleteBfGet(device,
                                                                   instanceAddress,
                                                                   &haltComplete);
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                                 recoveryAction,
                                 NULL,
                                 "Error setting Capture Control Reset bitfield");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }

        recoveryAction = adi_fpga9025_RxDmaResetSet(device,
                                                    dataMoverSel,
                                                    1);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = adi_fpga9025_RxTollgateResetSet(device,
                                                     ADI_FPGA9025_RX_DATAMOVER_ALL,
                                                     1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxCaptureStart(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = fpga9025_DpCaptureControlDatapathActiveBfSet(device,
                                                                  FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                                  1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxCaptureWait(adi_fpga9025_Device_t* device,
                                   uint32_t               timeMsDelay)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t  datapathActive = 0;
    uint32_t i;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    for (i = 0; i < timeMsDelay; i++)
    {
        recoveryAction = fpga9025_DpCaptureControlDatapathActiveBfGet(device,
                                                                      FPGA9025_BF_DP_CAPTURE_CONTROL_RX,
                                                                      &datapathActive);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Could not read DatapathActive bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (datapathActive == 0)
        {
            return ADI_COMMON_ACT_NO_ACTION;
        }

        adi_common_hal_Wait_us(&device->common,
                               1000);
    }

    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_DATA_RX_MOVER_WAIT_TIMEOUT,
                     ADI_COMMON_ACT_ERR_RESET_FEATURE,
                     NULL,
                     "RxCaptureWait timeout");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxDatamoverEnableGet(adi_fpga9025_Device_t* device,
                                          uint32_t*              rxDatamoverSelMask)
{
    UNUSED_PARA(device);
    UNUSED_PARA(rxDatamoverSelMask);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    return recoveryAction;
}

int32_t adi_fpga9025_RxSamplesSet(adi_fpga9025_Device_t* device,
                                  uint32_t               rxDataMoverSelMask,
                                  uint32_t               numSamples)
{
    UNUSED_PARA(rxDataMoverSelMask);
    UNUSED_PARA(numSamples);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}
