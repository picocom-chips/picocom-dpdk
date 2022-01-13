/*!
* \file adi_fpga9025.c
* \brief Contains FPGA9025 API configuration and run-time type definitions
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 *
 */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025.h"
#include "adi_fpga9025_error.h"

#include "adi_fpga9025_jesd.h"
#include "adi_fpga9025_rx.h"
#include "adi_fpga9025_tx.h"
#include "adi_fpga9025_clk.h"
#include "adi_fpga9025_utilities.h"
#include "adi_fpga9025_hal.h"
#include "adi_fpga9025_tdd.h"
#include "../../private/include/fpga9025_bf_ads9v2.h"
#include "../../private/include/fpga9025_bf_axi_adrv9025.h"
#include "../../private/include/fpga9025_bf_dp_capture_control.h"
#include "../../private/include/fpga9025_bf_jesd204_rx_lane_xbar.h"
#include "../../private/include/fpga9025_bf_jesd204_tx_lane_xbar.h"
#include "../../private/include/fpga9025_bf_xilinx_jesd204b.h"
#include "../../private/include/fpga9025_bf_xilinx_jesd204b.h"
#include "../../private/include/fpga9025_bf_jesd204_phy_ads9.h"

//kluge
#include "adi_platform.h"

int32_t adi_fpga9025_HwOpen(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    adi_common_LogLevelSet(&device->common,
                           ADI_FPGA9025_LOGGING);
    if (device->common.error.errCode != ADI_COMMON_HAL_OK)
    {
        switch (device->common.error.errCode)
        {
        case ADI_COMMON_HAL_LOGGING_FAIL:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_DEVICEHAL,
                             device->common.error.errCode,
                             ADI_COMMON_ACT_WARN_RESET_LOG,
                             NULL,
                             "Logging error");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_COMMON_HAL_LOGGGING_LEVEL_FAIL:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_DEVICEHAL,
                             device->common.error.errCode,
                             ADI_COMMON_ACT_WARN_RESET_LOG,
                             NULL,
                             "Logging Level error");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        case ADI_COMMON_HAL_GEN_SW: /* fall through */
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_DEVICEHAL,
                             device->common.error.errCode,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             NULL,
                             "Param error");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
        }
    }

    recoveryAction = adi_common_hal_HwOpen(&device->common);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_DEVICEHAL,
                         device->common.error.errCode,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "Param error");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9025_HwClose(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

    //LOG_FUNCTION_ENTRY_REPORT(ADI_COMMON_LOG_API);

    recoveryAction = adi_common_hal_HwClose(&device->common);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_DEVICEHAL,
                         device->common.error.errCode,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "Param error");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9025_VersionRead(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_AxiAdrv9025DesignIdBfGet(device,
                                                       FPGA9025_BF_AXI_ADRV9025,
                                                       &device->devStateInfo.designId);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_AxiAdrv9025VersionMajorBfGet(device,
                                                           FPGA9025_BF_AXI_ADRV9025,
                                                           &device->devStateInfo.versionMajor);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_AxiAdrv9025VersionMinorBfGet(device,
                                                           FPGA9025_BF_AXI_ADRV9025,
                                                           &device->devStateInfo.versionMinor);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RefClockFreqRead(adi_fpga9025_Device_t* device,
                                      uint32_t*              detectedRefClock_kHz)
{
    UNUSED_PARA(detectedRefClock_kHz);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_RegisterReset(adi_fpga9025_Device_t* device)
{
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_IpReset(adi_fpga9025_Device_t* device,
                             uint32_t               IpToResetMask)
{
    UNUSED_PARA(IpToResetMask);
    //TODO: implement this
    //normally use a int32_t as a mask for this but there are likely to be too many for a uint64_t so use struct
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_DrpRead(adi_fpga9025_Device_t*    device,
                             adi_fpga9025_DrpAddress_e addr,
                             uint8_t                   drp,
                             uint16_t*                 rdWord,
                             adi_fpga9025_DrpMask_e    rdMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i              = 0;
    uint8_t drpReady       = 0;
    uint8_t drpError       = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    switch (drp)
    {
    case ADI_FPGA9025_PHY_CH0:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH1:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH2:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH3:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH4:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH5:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH6:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_CH7:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9025_PHY_QUAD0:

        /*Write address, clear write_enable bit then set enable bit*/
        recoveryAction = fpga9025_Jesd204PhyAds9Quad0DrpAddressBfSet(device,
                                                                     FPGA9025_BF_ADS9_JESD_PHY,
                                                                     (uint16_t)addr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         addr,
                         "Invalid DRP addr");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_Jesd204PhyAds9Quad0DrpWriteEnableBfSet(device,
                                                                         FPGA9025_BF_ADS9_JESD_PHY,
                                                                         0);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error writing to DRP write enable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_Jesd204PhyAds9Quad0DrpEnableBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error enabling DRP transaction");
        ADI_ERROR_RETURN(device->common.error.newAction);

        for (i = 0; i < ADI_FPGA9025_DRP_TIMEOUT_MS; i++)
        {
            /* kluge to get drp read functionality working. after fpga has been updated to prevent the entire drp_read_data
            *  register from clearing when reading just the drp_ready bit remove this code and uncomment out the bf function below
            */
            uint32_t debugData = 0;
            adi_hal_BbicRegisterRead(device->common.devHalInfo,
                                     0x4340094c,
                                     &debugData);

            drpReady = (debugData >> 16) & 0x1;
            *rdWord  = debugData & 0xFFFF;
            //fpga9025_Jesd204PhyAds9Quad0DrpReadyBfGet(device, FPGA9025_BF_ADS9_JESD_PHY, &drpReady);
            //ADI_ERROR_RETURN(device->common.error.newAction);

            if (drpReady)
            {
                break;
            }
            else
            {
                //todo: platform wait 1ms
            }
        }

        recoveryAction = fpga9025_Jesd204PhyAds9Quad0DrpErrorBfGet(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &drpError);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading DRP error bit");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if ((drpReady == 0) || (drpError == 1))
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_DRP_ERROR,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Quad DRP error: requires full reset");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            /* kluged- see comment above */
            //fpga9025_Jesd204PhyAds9Quad0DrpReadDataBfGet(device, FPGA9025_BF_ADS9_JESD_PHY, rdWord);
            //ADI_ERROR_RETURN(device->common.error.newAction);
            *rdWord = *rdWord & (uint16_t)rdMask;
        }

        break;

    case ADI_FPGA9025_PHY_QUAD1:

        /*Write address, clear write_enable bit then set enable bit*/
        recoveryAction = fpga9025_Jesd204PhyAds9Quad1DrpAddressBfSet(device,
                                                                     FPGA9025_BF_ADS9_JESD_PHY,
                                                                     (uint16_t)addr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         addr,
                         "Invalid DRP addr");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_Jesd204PhyAds9Quad1DrpWriteEnableBfSet(device,
                                                                         FPGA9025_BF_ADS9_JESD_PHY,
                                                                         0);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error writing to DRP write enable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_Jesd204PhyAds9Quad1DrpEnableBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error enabling DRP transaction");
        ADI_ERROR_RETURN(device->common.error.newAction);

        for (i = 0; i < ADI_FPGA9025_DRP_TIMEOUT_MS; i++)
        {
            /* kluge to get drp read functionality working. after fpga has been updated to prevent the entire drp_read_data
            *  register from clearing when reading just the drp_ready bit remove this code and uncomment out the bf function below
            */
            uint32_t debugData = 0;
            adi_hal_BbicRegisterRead(device->common.devHalInfo,
                                     0x43400a4c,
                                     &debugData);
            drpReady = (debugData >> 16) & 0x1;
            *rdWord  = debugData & 0xFFFF;
            //fpga9025_Jesd204PhyAds9Quad1DrpReadyBfGet(device, FPGA9025_BF_ADS9_JESD_PHY, &drpReady);
            //ADI_ERROR_RETURN(device->common.error.newAction);

            if (drpReady)
            {
                break;
            }
            else
            {
                //todo: platform wait 1ms
            }
        }

        recoveryAction = fpga9025_Jesd204PhyAds9Quad1DrpErrorBfGet(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &drpError);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading DRP error bit");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if ((drpReady == 0) || (drpError == 1))
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_DRP_ERROR,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Quad DRP error: requires full reset");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            /* kluged- see comment above */
            //fpga9025_Jesd204PhyAds9Quad1DrpReadDataBfGet(device, FPGA9025_BF_ADS9_JESD_PHY, rdWord);
            //ADI_ERROR_RETURN(device->common.error.newAction);
            *rdWord = *rdWord & (uint16_t)rdMask;
        }

        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "Invalid DRP selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DrpWrite(adi_fpga9025_Device_t* device,
                              uint32_t               addr,
                              uint8_t                drp,
                              uint16_t               wrWord,
                              uint16_t               wrMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i              = 0;
    uint8_t drpReady       = 0;
    uint8_t drpError       = 0;

    typedef struct
    {
        int32_t (*DrpWriteDataBfSet)(adi_fpga9025_Device_t*              device,
                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                     uint16_t                            );

        int32_t (*DrpWriteDataMaskBfSet)(adi_fpga9025_Device_t*              device,
                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                         uint16_t                            );

        int32_t (*DrpAddressBfSet)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint16_t                            );

        int32_t (*DrpWriteEnableBfSet)(adi_fpga9025_Device_t*              device,
                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                       uint8_t                             );

        int32_t (*DrpEnableBfSet)(adi_fpga9025_Device_t*              device,
                                  fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                  uint8_t                             );

        int32_t (*DrpReadyBfGet)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );

        int32_t (*DrpErrorBfGet)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );
    } fpgaDrpWriteBf_t;

    fpgaDrpWriteBf_t fpgaDrpWriteFct[] = {
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel0DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel0DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel0DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel0DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel0DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel0DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel0DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel1DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel1DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel1DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel1DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel1DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel1DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel1DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel2DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel2DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel2DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel2DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel2DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel2DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel2DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel3DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel3DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel3DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel3DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel3DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel3DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel3DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel4DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel4DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel4DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel4DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel4DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel4DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel4DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel5DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel5DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel5DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel5DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel5DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel5DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel5DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel6DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel6DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel6DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel6DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel6DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel6DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel6DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Channel7DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Channel7DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Channel7DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Channel7DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Channel7DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Channel7DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Channel7DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Quad0DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Quad0DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Quad0DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Quad0DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Quad0DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Quad0DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Quad0DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet = fpga9025_Jesd204PhyAds9Quad1DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9025_Jesd204PhyAds9Quad1DrpWriteDataMaskBfSet,
            .DrpAddressBfSet = fpga9025_Jesd204PhyAds9Quad1DrpAddressBfSet,
            .DrpWriteEnableBfSet = fpga9025_Jesd204PhyAds9Quad1DrpWriteEnableBfSet,
            .DrpEnableBfSet = fpga9025_Jesd204PhyAds9Quad1DrpEnableBfSet,
            .DrpReadyBfGet = fpga9025_Jesd204PhyAds9Quad1DrpReadyBfGet,
            .DrpErrorBfGet = fpga9025_Jesd204PhyAds9Quad1DrpErrorBfGet
        }
    };

    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (drp > ADI_FPGA9025_PHY_QUAD1)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "Invalid DRP selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write data bitfields */
    if (fpgaDrpWriteFct[drp].DrpWriteDataBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpWriteDataBfSet(device,
                                                                FPGA9025_BF_ADS9_JESD_PHY,
                                                                wrWord);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         wrWord,
                         "Invalid DRP data word");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write mask bitfields */
    if (fpgaDrpWriteFct[drp].DrpWriteDataMaskBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpWriteDataMaskBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    (uint16_t)wrMask);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         wrMask,
                         "Invalid DRP data mask");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write address */
    if (fpgaDrpWriteFct[drp].DrpAddressBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpAddressBfSet(device,
                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                              (uint16_t)addr);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         addr,
                         "Invalid DRP addr");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write enable bit */
    if (fpgaDrpWriteFct[drp].DrpWriteEnableBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpWriteEnableBfSet(device,
                                                                  FPGA9025_BF_ADS9_JESD_PHY,
                                                                  1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error writing to DRP write enable");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Set enable bit */
    if (fpgaDrpWriteFct[drp].DrpEnableBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpEnableBfSet(device,
                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                             1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error enabling DRP transaction");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Looping and wait for channel ready */
    drpReady = 0;
    for (i = 0; i < ADI_FPGA9025_DRP_TIMEOUT_MS; i++)
    {
        if (fpgaDrpWriteFct[drp].DrpReadyBfGet != NULL)
        {
            recoveryAction = fpgaDrpWriteFct[drp].DrpReadyBfGet(device,
                                                                FPGA9025_BF_ADS9_JESD_PHY,
                                                                &drpReady);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error reading DRP ready bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (drpReady)
        {
            break;
        }
        else
        {
            adi_common_hal_Wait_ms(&device->common,
                                   1);
        }
    }

    drpError = 0;
    if (fpgaDrpWriteFct[drp].DrpErrorBfGet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpErrorBfGet(device,
                                                            FPGA9025_BF_ADS9_JESD_PHY,
                                                            &drpError);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading DRP error bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* If not ready or error occurred then report error. */
    if ((drpReady == 0) || (drpError == 1))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_DRP_ERROR,
                         ADI_COMMON_ACT_ERR_RESET_FULL,
                         NULL,
                         "Quad DRP error: requires full reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_InitSet(adi_fpga9025_Device_t* device,
                             adi_fpga9025_Init_t*   initSettings)
{
    int32_t  recoveryAction          = ADI_COMMON_ACT_NO_ACTION;
    uint8_t  i                       = 0;
    uint8_t  helperMask8bit          = 0;
    uint8_t  deserializerChannelMask = 0;
    uint8_t  serializerChannelMask   = 0;
    uint8_t  lockBit                 = 0;
    uint8_t  resetDone               = 0;
    uint32_t deframer0LaneXbarReset  = 0;
    uint32_t deframer1LaneXbarReset  = 0;
    uint32_t deframer2LaneXbarReset  = 0;
    uint32_t framer0LaneXbarReset    = 0;
    uint32_t framer1LaneXbarReset    = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        initSettings);

    /* reset lane xbars. Do this first to prevent any deframer settings from affecting the PHY */
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_0,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_1,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_2,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204TxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_0,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204TxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_1,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Physical layer
    ***************************************************************************************************************************************/
    /* Place all PHY channels in reset */
    recoveryAction = adi_fpga9025_DeserializerResetSet(device,
                                                       0xFF,
                                                       1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_fpga9025_SerializerResetSet(device,
                                                     0xFF,
                                                     1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* qpll setup */
    recoveryAction = adi_fpga9025_QpllSet(device,
                                          initSettings->clocks.qpll.quadSelect,
                                          &initSettings->clocks.qpll);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* serializer/deserializer channel setup */
    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        helperMask8bit = (0x01 << i);
        if (initSettings->datapath.serializerCfg[i].powerDown == 0)
        {
            recoveryAction = adi_fpga9025_SerializerCfgSet(device,
                                                           helperMask8bit,
                                                           &initSettings->datapath.serializerCfg[i]);
            ADI_ERROR_RETURN(device->common.error.newAction);
            serializerChannelMask |= (0x01 << i);
        }
        if (initSettings->datapath.deserializerCfg[i].powerDown == 0)
        {
            recoveryAction = adi_fpga9025_DeserializerCfgSet(device,
                                                             helperMask8bit,
                                                             &initSettings->datapath.deserializerCfg[i]);
            ADI_ERROR_RETURN(device->common.error.newAction);
            deserializerChannelMask |= (0x01 << i);
        }
    }

    /* release the desired channels from reset based on the power down bits */
    recoveryAction = adi_fpga9025_DeserializerResetSet(device,
                                                       deserializerChannelMask,
                                                       0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = adi_fpga9025_SerializerResetSet(device,
                                                     serializerChannelMask,
                                                     0);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* check for qpll locks */
    if ((initSettings->clocks.qpll.quadSelect & ADI_FPGA9025_QPLL_QUAD0) > 0)
    {
        lockBit = 0;
        for (i = 0; i < 5; i++)
        {
            recoveryAction = adi_fpga9025_QpllLockGet(device,
                                                      ADI_FPGA9025_QPLL_QUAD0,
                                                      initSettings->clocks.qpll.band,
                                                      &lockBit);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error reading qpll quad 0 lock bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            if (lockBit == 1)
            {
                break;
            }
            else
            {
                recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                        10);
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 device->common.error.errCode,
                                 device->common.error.newAction,
                                 NULL,
                                 device->common.error.errormessage);
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }

        if (lockBit != 1)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_CLOCK_FAILURE,
                             ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                             ADI_FPGA9025_QPLLCLK0,
                             "Error Qpll0 not locked");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    if ((initSettings->clocks.qpll.quadSelect & ADI_FPGA9025_QPLL_QUAD1) > 0)
    {
        lockBit = 0;
        for (i = 0; i < 5; i++)
        {
            recoveryAction = adi_fpga9025_QpllLockGet(device,
                                                      ADI_FPGA9025_QPLL_QUAD1,
                                                      initSettings->clocks.qpll.band,
                                                      &lockBit);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error reading qpll quad 1 lock bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            if (lockBit == 1)
            {
                break;
            }
            else
            {
                recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                        10);
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 device->common.error.errCode,
                                 device->common.error.newAction,
                                 NULL,
                                 device->common.error.errormessage);
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }

        if (lockBit != 1)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_CLOCK_FAILURE,
                             ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                             ADI_FPGA9025_QPLLCLK1,
                             "Error Qpll1 not locked");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    /* check PHY layer has finished reset routine */
    resetDone = 0;
    for (i = 0; i < 5; i++)
    {
        recoveryAction = adi_fpga9025_DeserializerResetDoneGet(device,
                                                               &resetDone);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading deserializer channel reset done bits");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (resetDone == deserializerChannelMask)
        {
            break;
        }
        else
        {
            recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                    10);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             device->common.error.errCode,
                             device->common.error.newAction,
                             NULL,
                             device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    if (resetDone != deserializerChannelMask)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_PHY_RESET_FAIL,
                         ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                         NULL,
                         "Deserializer channels have not reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    resetDone = 0;
    for (i = 0; i < 5; i++)
    {
        recoveryAction = adi_fpga9025_SerializerResetDoneGet(device,
                                                             &resetDone);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading serializer channel reset done bits");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (resetDone == serializerChannelMask)
        {
            break;
        }
        else
        {
            recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                    10);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             device->common.error.errCode,
                             device->common.error.newAction,
                             NULL,
                             device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    if (resetDone != serializerChannelMask)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_PHY_RESET_FAIL,
                         ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                         NULL,
                         "Serializer channels have not reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /***************************************************************************************************************************************
    * MMCM
    ***************************************************************************************************************************************/
    /* Disable TDD FSM before calling MmcmSet */
    recoveryAction = adi_fpga9025_TddDisable(device);
    ADI_ERROR_REPORT(&device->common,
                     device->common.error.errSource,
                     device->common.error.errCode,
                     device->common.error.newAction,
                     NULL,
                     device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* RX must be setup prior to TX since the final output of RX feeds TX mmcm*/
    recoveryAction = adi_fpga9025_MmcmSet(device,
                                          ADI_FPGA9025_CORE_MMCM,
                                          &initSettings->clocks.coreMmcm);
    ADI_ERROR_REPORT(&device->common,
                     device->common.error.errSource,
                     device->common.error.errCode,
                     device->common.error.newAction,
                     NULL,
                     device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    lockBit = 0;
    for (i = 0; i < 5; i++)
    {
        recoveryAction = adi_fpga9025_MmcmLockGet(device,
                                                  ADI_FPGA9025_CORE_MMCM,
                                                  &lockBit);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading mmcm lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (lockBit == 1)
        {
            break;
        }
        else
        {
            recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                    10);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             device->common.error.errCode,
                             device->common.error.newAction,
                             NULL,
                             device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    if (lockBit != 1)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_CLOCK_FAILURE,
                         ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                         ADI_FPGA9025_CORE_MMCM,
                         "Error Core MMCM not locked");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /***************************************************************************************************************************************
    * Lane Xbars
    ***************************************************************************************************************************************/
    /* reset lane xbars */
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_0,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_1,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_2,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204TxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_0,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204TxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_1,
                                                              0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* build up the link layer's lane xbar resets based on which phy lanes they're using */
    /* can't use dserializerChannelMask here because we need to reset based on which channels go to which
    *  link layer. the dserializerChannelMask shows us all the channels that are active, not how they map onto the link layers */
    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        /* The reset bit location maps to the PHY lane # for tx & rx. */
        /* For rx, the value in the laneXBar array is used to 
         * determine the PHY lane #*/
        if (((initSettings->datapath.deframerCfg[0].lanesInUse >> i) & 0x01) == 0x01)
        {
            deframer0LaneXbarReset |= (0x01 << initSettings->datapath.deframerCfg[0].laneXbar[i]);
        }

        if (((initSettings->datapath.deframerCfg[1].lanesInUse >> i) & 0x01) == 0x01)
        {
            deframer1LaneXbarReset |= (0x01 << initSettings->datapath.deframerCfg[1].laneXbar[i]);
        }

        if (((initSettings->datapath.deframerCfg[2].lanesInUse >> i) & 0x01) == 0x01)
        {
            deframer2LaneXbarReset |= (0x01 << initSettings->datapath.deframerCfg[2].laneXbar[i]);
        }

        /* For tx, the index of the laneXBar maps to the PHY lane #. 
         * If the laneXBar value is not the initial value (0x1F) that means this index corresponds to a PHY lane
         * connected to this framer */
        if (initSettings->datapath.framerCfg[0].laneXbar[i] != 0x1F)
        {
            framer0LaneXbarReset |= (0x01 << i);
        }
        if (initSettings->datapath.framerCfg[1].laneXbar[i] != 0x1F)
        {
            framer1LaneXbarReset |= (0x01 << i);
        }
    }

    deframer0LaneXbarReset = ~deframer0LaneXbarReset;
    deframer1LaneXbarReset = ~deframer1LaneXbarReset;
    deframer2LaneXbarReset = ~deframer2LaneXbarReset;
    framer0LaneXbarReset   = ~framer0LaneXbarReset;
    framer1LaneXbarReset   = ~framer1LaneXbarReset;

    /* Remove the reset on the lanes in use in lane xbars */
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_0,
                                                              deframer0LaneXbarReset);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_1,
                                                              deframer1LaneXbarReset);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204RxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_2,
                                                              deframer2LaneXbarReset);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204TxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_0,
                                                              framer0LaneXbarReset);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_Jesd204TxLaneXbarLaneResetBfSet(device,
                                                              FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_1,
                                                              framer1LaneXbarReset);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Link layer
    ***************************************************************************************************************************************/
    /* Disable all framers/deframers */
    recoveryAction = adi_fpga9025_DeframerDisable(device,
                                                  ADI_FPGA9025_DEFRAMER_ALL);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_FramerDisable(device,
                                                ADI_FPGA9025_FRAMER_ALL);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* deframers & framers setup (only configure those that are in use) */
    if (initSettings->datapath.deframerCfg[0].lanesInUse != 0)
    {
        recoveryAction = adi_fpga9025_DeframerCfgSet(device,
                                                     ADI_FPGA9025_DEFRAMER_0,
                                                     &initSettings->datapath.deframerCfg[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error holding used FPGA deframer0 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (initSettings->datapath.deframerCfg[1].lanesInUse != 0)
    {
        recoveryAction = adi_fpga9025_DeframerCfgSet(device,
                                                     ADI_FPGA9025_DEFRAMER_1,
                                                     &initSettings->datapath.deframerCfg[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error holding used FPGA deframer1 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (initSettings->datapath.deframerCfg[2].lanesInUse != 0)
    {
        recoveryAction = adi_fpga9025_DeframerCfgSet(device,
                                                     ADI_FPGA9025_DEFRAMER_2,
                                                     &initSettings->datapath.deframerCfg[2]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error holding used FPGA deframer2 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (initSettings->datapath.framerCfg[0].lanesInUse != 0)
    {
        recoveryAction = adi_fpga9025_FramerCfgSet(device,
                                                   ADI_FPGA9025_FRAMER_0,
                                                   &initSettings->datapath.framerCfg[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_FRAMER_0,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error holding used FPGA framer0 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (initSettings->datapath.framerCfg[1].lanesInUse != 0)
    {
        recoveryAction = adi_fpga9025_FramerCfgSet(device,
                                                   ADI_FPGA9025_FRAMER_1,
                                                   &initSettings->datapath.framerCfg[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_FRAMER_1,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error holding used FPGA framer1 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /***************************************************************************************************************************************
    * Sync XBar
    ***************************************************************************************************************************************/
    recoveryAction = adi_fpga9025_SyncXBarCfgSet(device,
                                                 initSettings->datapath.syncBPolarity,
                                                 &initSettings->datapath.syncBSel[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Sysref
    ***************************************************************************************************************************************/
    recoveryAction = adi_fpga9025_SysRefControlSet(device,
                                                   &initSettings->sysref);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Set the static information in DMAs
    ***************************************************************************************************************************************/
    recoveryAction = adi_fpga9025_RxDmaInit(device,
                                            ADI_FPGA9025_DEFRAMER_0,
                                            &initSettings->datapath.rxDmaCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_RxDmaInit(device,
                                            ADI_FPGA9025_DEFRAMER_1,
                                            &initSettings->datapath.rxDmaCfg[1]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_RxDmaInit(device,
                                            ADI_FPGA9025_DEFRAMER_2,
                                            &initSettings->datapath.rxDmaCfg[2]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_TxDmaInit(device,
                                            ADI_FPGA9025_FRAMER_0,
                                            &initSettings->datapath.txDmaCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_TxDmaInit(device,
                                            ADI_FPGA9025_FRAMER_1,
                                            &initSettings->datapath.txDmaCfg[1]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Reset datapaths
    ***************************************************************************************************************************************/
    recoveryAction = adi_fpga9025_RxDataChainReset(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_TxDataChainReset(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_InitGet(adi_fpga9025_Device_t* device,
                             adi_fpga9025_Init_t*   initSettings)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t  i              = 0;
    uint8_t  laneSel        = 1;
    uint16_t dataMoverSel   = 1;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        initSettings);

    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        // int32_t adi_fpga9025_SerializerCfgGet(adi_fpga9025_Device_t *device, adi_fpga9025_LaneSel_e laneSel, adi_fpga9025_SerializerCfg_t *serializerCfg)
        recoveryAction = adi_fpga9025_SerializerCfgGet(device,
                                                       (adi_fpga9025_LaneSel_e)laneSel,
                                                       &initSettings->datapath.serializerCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = adi_fpga9025_DeserializerCfgGet(device,
                                                         (adi_fpga9025_LaneSel_e)laneSel,
                                                         &initSettings->datapath.deserializerCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        laneSel = laneSel << 1;
    }

    // get the framer configurations
    recoveryAction = adi_fpga9025_FramerCfgGet(device,
                                               ADI_FPGA9025_FRAMER_0,
                                               &initSettings->datapath.framerCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    // get the 2 deframer configurations
    recoveryAction = adi_fpga9025_DeframerCfgGet(device,
                                                 ADI_FPGA9025_DEFRAMER_0,
                                                 &initSettings->datapath.deframerCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_DeframerCfgGet(device,
                                                 ADI_FPGA9025_DEFRAMER_1,
                                                 &initSettings->datapath.deframerCfg[1]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    // get the 8 txdataMover configurations
    dataMoverSel = 1;
    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        recoveryAction = adi_fpga9025_TxDmaGet(device,
                                               (adi_fpga9025_TxDatamoverSel_e)dataMoverSel,
                                               &initSettings->datapath.txDmaCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        dataMoverSel = dataMoverSel << 1;
    }

    //get the 16 rxdataMover configurations
    dataMoverSel = 1;
    for (i = 0; i < ADI_FPGA9025_NUM_OF_RX_DATAMOVERS; i++)
    {
        recoveryAction = adi_fpga9025_RxDmaGet(device,
                                               (adi_fpga9025_RxDatamoverSel_e)dataMoverSel,
                                               &initSettings->datapath.rxDmaCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        dataMoverSel = dataMoverSel << 1;
    }

    //the configuration of all tollgates must be the same so we only need to store one of each 
    recoveryAction = adi_fpga9025_TxTollgateGet(device,
                                                ADI_FPGA9025_TX_DATAMOVER_0,
                                                &initSettings->datapath.txTollgateCfg);
    ADI_ERROR_REPORT(&device->common,
                     device->common.error.errSource,
                     device->common.error.errCode,
                     device->common.error.newAction,
                     device->common.error.varName,
                     device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = adi_fpga9025_RxTollgateGet(device,
                                                ADI_FPGA9025_RX_DATAMOVER_0,
                                                &initSettings->datapath.rxTollgateCfg);
    ADI_ERROR_REPORT(&device->common,
                     device->common.error.errSource,
                     device->common.error.errCode,
                     device->common.error.newAction,
                     device->common.error.varName,
                     device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}
