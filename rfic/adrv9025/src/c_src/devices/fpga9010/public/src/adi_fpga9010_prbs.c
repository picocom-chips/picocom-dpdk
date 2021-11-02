/**
 * \file: adi_fpga9010_jesd.c
 *
 * \brief Contains top level tx fpga9010 related functions
 *
 * FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_prbs.h"
#include "adi_fpga9010.h"
#include "../../private/include/fpga9010_bf_jesd204_phy_tokelau_ads8.h"

int32_t adi_fpga9010_PrbsSerializerEnable(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t prbsSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);  
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7TxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_PrbsDeserializerEnable(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t prbsSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);  
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (prbsSel & 0x0F));
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting PRBS mode for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_PrbsSerializerErrorInject(adi_fpga9010_Device_t *device, uint8_t laneSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);  
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7TxPrbsInjErrBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error injecting an error for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_PrbsErrorCountRead(adi_fpga9010_Device_t *device, uint32_t *errCounts)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[0]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for channel 0");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[1]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 1");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[2]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 2");
    ADI_ERROR_RETURN(device->common.error.newAction);  

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[3]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 3");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[4]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 4");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[5]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 5");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[6]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 6");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsErrCntBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &errCounts[7]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading PRBS error count for  channel 7");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

int32_t adi_fpga9010_PrbsErrorClear(adi_fpga9010_Device_t *device, uint8_t laneSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);  
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsErrCntRstBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error clearing the error count for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}
