/**
 * \file: adi_fpga9025_jesd.c
 *
 * \brief Contains top level tx fpga9025 related functions
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_prbs.h"
#include "adi_fpga9025.h"
#include "../../private/include/fpga9025_bf_jesd204_phy_ads9.h"

int32_t adi_fpga9025_PrbsSerializerEnable(adi_fpga9025_Device_t*       device,
                                          uint8_t                      laneSelMask,
                                          adi_fpga9025_PrbsTestModes_e prbsModeSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    if ((prbsModeSel < ADI_FPGA9025_PRBS_OFF || prbsModeSel > ADI_FPGA9025_PRBS_31) && ((prbsModeSel != ADI_FPGA9025_SQ_2UI) && (prbsModeSel !=
        ADI_FPGA9025_SQ_INT_UI)))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         prbsModeSel,
                         "An invalid PRBS test mode is selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel0TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel1TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel2TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel3TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel4TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel5TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel6TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel7TxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_PrbsDeserializerEnable(adi_fpga9025_Device_t*       device,
                                            uint8_t                      laneSelMask,
                                            adi_fpga9025_PrbsTestModes_e prbsModeSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    if (prbsModeSel < ADI_FPGA9025_PRBS_OFF || prbsModeSel > ADI_FPGA9025_PRBS_31)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         prbsModeSel,
                         "An invalid PRBS test mode is selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel0RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel1RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel2RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel3RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel4RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel5RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel6RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel7RxPrbsSelBfSet(device,
                                                                       FPGA9025_BF_ADS9_JESD_PHY,
                                                                       (uint8_t)prbsModeSel);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting PRBS mode for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_PrbsSerializerErrorInject(adi_fpga9025_Device_t* device,
                                               uint8_t                laneSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel0TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel1TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel2TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel3TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel4TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel5TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel6TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel7TxPrbsInjErrBfSet(device,
                                                                          FPGA9025_BF_ADS9_JESD_PHY,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error injecting an error for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_PrbsErrorCountRead(adi_fpga9025_Device_t* device,
                                        uint32_t*              errCounts)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        errCounts);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel0RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for channel 0");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel1RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[1]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 1");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel2RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[2]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 2");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel3RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[3]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 3");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel4RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[4]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 4");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel5RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[5]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 5");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel6RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[6]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 6");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204PhyAds9Channel7RxPrbsErrCntBfGet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      &errCounts[7]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading PRBS error count for  channel 7");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_PrbsErrorClear(adi_fpga9025_Device_t* device,
                                    uint8_t                laneSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_HAL);
#endif

    if ((laneSelMask & 0x01) == 0x01)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel0RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x02) == 0x02)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel1RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x04) == 0x04)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel2RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x08) == 0x08)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel3RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x10) == 0x10)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel4RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x20) == 0x20)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel5RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x40) == 0x40)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel6RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & 0x80) == 0x80)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel7RxPrbsErrCntRstBfSet(device,
                                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error clearing the error count for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}
