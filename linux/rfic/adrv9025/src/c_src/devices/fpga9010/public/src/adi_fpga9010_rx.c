/**
 * \file: adi_fpga9010_rx.c
 *
 * \brief Contains top level rx fpga9010 related functions
 *
 * FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_rx.h"
#include "adi_fpga9010.h"
#include "../../private/include/fpga9010_bf_dp_tollgate.h"
#include "../../private/include/fpga9010_bf_dp_rx_dma.h"
#include "../../private/include/fpga9010_bf_dp_capture_control.h"

int32_t adi_fpga9010_RxTollgateSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, adi_fpga9010_RxTollgateCfg_t *tollGateCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, tollGateCfg);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch(dataMoverSel)
        {
            case ADI_FPGA9010_DEFRAMER_0:
                instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
                break;
            case ADI_FPGA9010_DEFRAMER_1:
                instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_1;
                break;
            case ADI_FPGA9010_DEFRAMER_2:
                instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_2;
                break;
            default:
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
                ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTollgateEdgeLevelBfSet(device, instanceAddress, tollGateCfg->tollGateEdgeOrLvl);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to detection register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTollgateHighRisingLowFallingBfSet(device, instanceAddress, tollGateCfg->tollGateHiRiseOrLoFall);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to polarity register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTollgateTriggerSelectBfSet(device, instanceAddress, (uint32_t)tollGateCfg->tollGateTrigSource);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to selection register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxTollgateGet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e rxDatamoverSel, adi_fpga9010_RxTollgateCfg_t *tollGateCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, tollGateCfg);

    switch (rxDatamoverSel)
    {
    case ADI_FPGA9010_DEFRAMER_0:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
        break;
    case ADI_FPGA9010_DEFRAMER_1:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_1;
        break;
    case ADI_FPGA9010_DEFRAMER_2:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, rxDatamoverSel, "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }
    
    recoveryAction = fpga9010_DpTollgateEdgeLevelBfGet(device, baseAddress, &tollGateCfg->tollGateEdgeOrLvl);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to detection register");
    ADI_ERROR_RETURN(device->common.error.newAction);
            
    recoveryAction = fpga9010_DpTollgateHighRisingLowFallingBfGet(device, baseAddress, &tollGateCfg->tollGateHiRiseOrLoFall);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to polarity register");
    ADI_ERROR_RETURN(device->common.error.newAction);
            
    recoveryAction = fpga9010_DpTollgateTriggerSelectBfGet(device, baseAddress, (uint32_t*)&tollGateCfg->tollGateTrigSource);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to selection register");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxTollgateResetSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, uint8_t resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTollgateResetTollgateBfSet(device, instanceAddress, resetVal);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxTollgateResetGet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, uint16_t *resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;
    uint8_t resetBitRead = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, resetVal);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *resetVal = 0;

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTollgateResetTollgateBfGet(device, instanceAddress, &resetBitRead);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read from reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        *resetVal |= (resetBitRead & 1) << i;
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxTollgateTriggerSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, adi_fpga9010_RxTollgateTrigSources_e  triggerSelect)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            adi_fpga9010_RxTollgateResetSet(device, rxDatamoverSelMask, 1);
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            recoveryAction = fpga9010_DpTollgateTriggerSelectBfSet(device, (fpga9010_BfDpTollgateChanAddr_e)instanceAddress, (uint32_t)triggerSelect);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not write to triggerSelect bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            adi_fpga9010_RxTollgateResetSet(device, rxDatamoverSelMask, 0);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxTollgateTriggerGet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e rxDatamoverSel, adi_fpga9010_RxTollgateTrigSources_e  *triggerSelect)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
    uint32_t triggerSelectGet = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, triggerSelect);

    switch (rxDatamoverSel)
    {
    case ADI_FPGA9010_DEFRAMER_0:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
        break;
    case ADI_FPGA9010_DEFRAMER_1:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_1;
        break;
    case ADI_FPGA9010_DEFRAMER_2:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_RX_2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, rxDatamoverSel, "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }
    
    recoveryAction = fpga9010_DpTollgateTriggerSelectBfGet(device, baseAddress, &triggerSelectGet);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to selection register");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    *triggerSelect = (adi_fpga9010_RxTollgateTrigSources_e)triggerSelectGet;
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDmaSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, adi_fpga9010_RxDmaCfg_t *rxDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpRxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, rxDmaCfg);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        
        /* TODO: start address could be changed at runtime by this function, and this length check is not enough to ensure RAM buffers do not overlap */
        if (rxDmaCfg->length > RX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Rx DMA capture length is too large");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpRxDmaEnableEnhancedModeBfSet(device, instanceAddress, rxDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaEnableSgBfSet(device, instanceAddress, rxDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaLengthBfSet(device, instanceAddress, rxDmaCfg->length);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaSgFirstDescriptorBfSet(device, instanceAddress, rxDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* TODO: writing to this seems to be clearing the status register. debug later */
/*            recoveryAction = fpga9010_DpRxDmaSgLastDescriptorBfSet(device, instanceAddress, rxDmaCfg->sgLastDescriptor);
 *            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
 *            ADI_ERROR_RETURN(device->common.error.newAction);
*/

            recoveryAction = fpga9010_DpRxDmaSimpleStartAddrBfSet(device, instanceAddress, rxDmaCfg->simpleStartAddr);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaValidDataWidthStreamBfSet(device, instanceAddress, rxDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDmaInit(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, adi_fpga9010_RxDmaCfg_t *rxDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpRxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, rxDmaCfg);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpRxDmaEnableEnhancedModeBfSet(device, instanceAddress, rxDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaEnableSgBfSet(device, instanceAddress, rxDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaSgFirstDescriptorBfSet(device, instanceAddress, rxDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* TODO: writing to this seems to be clearing the status register. debug later */
/*            recoveryAction = fpga9010_DpRxDmaSgLastDescriptorBfSet(device, instanceAddress, rxDmaCfg->sgLastDescriptor);
 *            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
 *            ADI_ERROR_RETURN(device->common.error.newAction);
*/

            recoveryAction = fpga9010_DpRxDmaSimpleStartAddrBfSet(device, instanceAddress, rxDmaCfg->simpleStartAddr);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpRxDmaValidDataWidthStreamBfSet(device, instanceAddress, rxDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDmaGet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e rxDatamoverSel, adi_fpga9010_RxDmaCfg_t *rxDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpRxDmaChanAddr_e baseAddress = FPGA9010_BF_DP_DMA_RX_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, rxDmaCfg);

    switch (rxDatamoverSel)
    {
    case ADI_FPGA9010_DEFRAMER_0:
        baseAddress = FPGA9010_BF_DP_DMA_RX_0;
        break;
    case ADI_FPGA9010_DEFRAMER_1:
        baseAddress = FPGA9010_BF_DP_DMA_RX_1;
        break;
    case ADI_FPGA9010_DEFRAMER_2:
        baseAddress = FPGA9010_BF_DP_DMA_RX_2;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, rxDatamoverSel, "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9010_DpRxDmaActiveBfGet(device, baseAddress, &rxDmaCfg->active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read active bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaCompleteBfGet(device, baseAddress, &rxDmaCfg->complete);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read complete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaEnableEnhancedModeBfGet(device, baseAddress, &rxDmaCfg->enableEnhancedMode);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read enableEnhancedMode bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaEnableSgBfGet(device, baseAddress, &rxDmaCfg->enableSg);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read enableSg bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaHaltCompleteBfGet(device, baseAddress, &rxDmaCfg->haltComplete);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read haltComplete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaLengthBfGet(device, baseAddress, &rxDmaCfg->length);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read length bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaOverflowBfGet(device, baseAddress, &rxDmaCfg->overflow);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read overflow bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaRunStopBfGet(device, baseAddress, &rxDmaCfg->runStop);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read runStop bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaSgFirstDescriptorBfGet(device, baseAddress, &rxDmaCfg->sgFirstDescriptor);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read sgFirstDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaSgLastDescriptorBfGet(device, baseAddress, &rxDmaCfg->sgLastDescriptor);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read sgLastDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaSimpleStartAddrBfGet(device, baseAddress, &rxDmaCfg->simpleStartAddr);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read simpleStartAddr bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpRxDmaValidDataWidthStreamBfGet(device, baseAddress, &rxDmaCfg->validDataWidthStream);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read validDataWidthStream bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDmaResetSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, uint8_t reset)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpRxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpRxDmaResetBfSet(device, instanceAddress, reset);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDmaRunStopSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, uint8_t runStop)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpRxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpRxDmaRunStopBfSet(device, instanceAddress, runStop);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDmaLengthSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask, uint32_t numBytes)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpRxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e dataMoverSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (rxDatamoverSelMask < 1 || rxDatamoverSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid rx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_DP_DMA_RX_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (numBytes > RX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Rx DMA capture length is too large");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        
        if (((uint32_t)dataMoverSel & rxDatamoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpRxDmaLengthBfSet(device, instanceAddress, numBytes);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDatamoverEnableSet(adi_fpga9010_Device_t *device, uint32_t rxDatamoverSelMask)
{
    UNUSED_PARA(rxDatamoverSelMask);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    return recoveryAction;
}

int32_t adi_fpga9010_RxDataChainConfigure(adi_fpga9010_Device_t *device, uint32_t rxDataMoverSelMask, adi_fpga9010_RxTollgateTrigSources_e  triggerSelect, adi_fpga9010_RxDmaCfg_t *rxDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    /* reset capture control */
    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* set trigger */
    adi_fpga9010_RxTollgateTriggerSet(device, rxDataMoverSelMask, triggerSelect);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /*reset dmas */
    adi_fpga9010_RxDmaResetSet(device, rxDataMoverSelMask, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* configure dmas */
    adi_fpga9010_RxDmaSet(device, rxDataMoverSelMask, rxDmaCfg);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* set run_stop bit */
    adi_fpga9010_RxDmaRunStopSet(device, rxDataMoverSelMask, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* pass token to start dma arbitration */
    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_DpCaptureControlPassTokenBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control PassToken bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDataChainReset(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t active = 0;
    uint8_t haltComplete = 0;
	uint8_t i = 0;
	static const uint8_t RX_DATA_CHAIN_RESET_MAX_COUNT = 5;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    /* reset  */
    recoveryAction = fpga9010_DpCaptureControlDatapathActiveBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Clear DMA 0 */
    recoveryAction = fpga9010_DpRxDmaActiveBfGet(device, FPGA9010_BF_DP_DMA_RX_0, &active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_RxDmaRunStopSet(device, ADI_FPGA9010_DEFRAMER_0, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    if (active == 1)
    {
		haltComplete = 0;
        for (i = 0; i < RX_DATA_CHAIN_RESET_MAX_COUNT; i++)
        {
            recoveryAction = fpga9010_DpRxDmaHaltCompleteBfGet(device, FPGA9010_BF_DP_DMA_RX_0, &haltComplete);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
			if (haltComplete != 0)
			{
				break;
			}
        }

		if (i == RX_DATA_CHAIN_RESET_MAX_COUNT)
		{
			ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "RX0 DMA Halt failed.");
			ADI_ERROR_RETURN(device->common.error.newAction);
		}
    }
    
    adi_fpga9010_RxDmaResetSet(device, ADI_FPGA9010_DEFRAMER_0, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* End DMA 0*/
    
    /* Clear DMA 1 */
    active = 0;
    haltComplete = 0;
    recoveryAction = fpga9010_DpRxDmaActiveBfGet(device, FPGA9010_BF_DP_DMA_RX_1, &active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_RxDmaRunStopSet(device, ADI_FPGA9010_DEFRAMER_1, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    if (active == 1)
    {
        
		for (i = 0; i < RX_DATA_CHAIN_RESET_MAX_COUNT; i++)
        {
            recoveryAction = fpga9010_DpRxDmaHaltCompleteBfGet(device, FPGA9010_BF_DP_DMA_RX_1, &haltComplete);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
			if (haltComplete != 0)
			{
				break;
			}
        }

		if (i == RX_DATA_CHAIN_RESET_MAX_COUNT)
		{
			ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "RX1 DMA Halt failed.");
			ADI_ERROR_RETURN(device->common.error.newAction);
		}
    }
    
    adi_fpga9010_RxDmaResetSet(device, ADI_FPGA9010_DEFRAMER_1, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* End DMA 1*/
    
    /* Clear DMA 2 */
	active = 0;
	haltComplete = 0;
    recoveryAction = fpga9010_DpRxDmaActiveBfGet(device, FPGA9010_BF_DP_DMA_RX_2, &active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_RxDmaRunStopSet(device, ADI_FPGA9010_DEFRAMER_2, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    if (active == 1)
    {
	    for (i = 0; i < RX_DATA_CHAIN_RESET_MAX_COUNT; i++)
        {
            recoveryAction = fpga9010_DpRxDmaHaltCompleteBfGet(device, FPGA9010_BF_DP_DMA_RX_2, &haltComplete);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
	        
	        if (haltComplete != 0)
	        {
		        break;
	        }
        }
	    
	    if (i == RX_DATA_CHAIN_RESET_MAX_COUNT)
	    {
		    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "RX2 DMA Halt failed.");
		    ADI_ERROR_RETURN(device->common.error.newAction);
	    }
    }
    
    adi_fpga9010_RxDmaResetSet(device, ADI_FPGA9010_DEFRAMER_2, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    /* End DMA 2*/
    
    adi_fpga9010_RxTollgateResetSet(device, ADI_FPGA9010_DEFRAMER_ALL, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDatamoverEnableGet(adi_fpga9010_Device_t *device, uint32_t *rxDatamoverSelMask)
{
    UNUSED_PARA(rxDatamoverSelMask);
    //TODO: implement this using adi_fpga_rxChannelSel_e
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_RxCaptureStart(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = fpga9010_DpCaptureControlDatapathActiveBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxCaptureWait(adi_fpga9010_Device_t *device, uint32_t timeMsDelay)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t datapathActive = 0;
    uint32_t i;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    for (i = 0; i < timeMsDelay; i++)
    {
        recoveryAction = fpga9010_DpCaptureControlDatapathActiveBfGet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_RX, &datapathActive);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read DatapathActive bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (datapathActive == 0)
        {
            return ADI_COMMON_ACT_NO_ACTION;
        }
        
        adi_common_hal_Wait_us(&device->common, 1000);
    }

    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_DATA_RX_MOVER_WAIT_TIMEOUT, ADI_COMMON_ACT_ERR_RESET_FEATURE, NULL, "RxCaptureWait timeout");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RxDataGet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e rxDatamoverSel, int32_t data[], uint32_t *dataSize)
{
    UNUSED_PARA(rxDatamoverSel);
    UNUSED_PARA(dataSize);
    UNUSED_PARA(data);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_RxSamplesSet(adi_fpga9010_Device_t *device, uint32_t rxDataMoverSelMask, uint32_t numSamples)
{
    UNUSED_PARA(rxDataMoverSelMask);
    UNUSED_PARA(numSamples);
     //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

