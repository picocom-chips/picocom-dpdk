
/*!
* \file adi_fpga9010.c
* \brief Contains FPGA9010 API configuration and run-time type definitions
*
* ADRV9010 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 *
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010.h"
#include "adi_fpga9010_error.h"
#include "../../private/include/fpga9010_bf_axi_tokelau.h"
#include "../../private/include/fpga9010_bf_jesd204_phy_tokelau_ads8.h"
#include "../../private/include/fpga9010_bf_dp_capture_control.h"
#include "../../private/include/fpga9010_bf_jesd204_rx_lane_xbar.h"
#include "../../private/include/fpga9010_bf_jesd204_tx_lane_xbar.h"
#include "../../private/include/fpga9010_bf_xilinx_jesd204b.h"
#include "../../private/include/fpga9010_bf_xilinx_jesd204b.h"

#include "adi_fpga9010_jesd.h"
#include "adi_fpga9010_rx.h"
#include "adi_fpga9010_tx.h"
#include "adi_fpga9010_clk.h"
#include "adi_fpga9010_utilities.h"
#include "adi_fpga9010_hal.h"
#include "adi_fpga9010_tdd.h"

//kluge
#include "adi_platform.h"

int32_t adi_fpga9010_HwOpen(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);

    adi_common_LogLevelSet(&device->common, ADI_FPGA9010_LOGGING);
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

    adi_common_hal_HwOpen(&device->common);
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

int32_t adi_fpga9010_HwClose(adi_fpga9010_Device_t *device)
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

int32_t adi_fpga9010_VersionRead(adi_fpga9010_Device_t *device)
{
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    fpga9010_AxiTokelauDesignIdBfGet(device, FPGA9010_BF_AXI_TOKELAU, &device->devStateInfo.designId);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_AxiTokelauVersionMajorBfGet(device, FPGA9010_BF_AXI_TOKELAU, &device->devStateInfo.versionMajor);
    ADI_ERROR_RETURN(device->common.error.newAction);

    fpga9010_AxiTokelauVersionMinorBfGet(device, FPGA9010_BF_AXI_TOKELAU, &device->devStateInfo.versionMinor);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RefClockFreqRead(adi_fpga9010_Device_t *device, uint32_t *detectedRefClock_kHz)
{
    UNUSED_PARA(detectedRefClock_kHz);
    //TODO: implement this
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return (device->common.error.newAction);
}


int32_t adi_fpga9010_RegisterReset(adi_fpga9010_Device_t *device)
{
    //TODO: implement this
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return (device->common.error.newAction);
}


int32_t adi_fpga9010_IpReset(adi_fpga9010_Device_t *device, uint32_t IpToResetMask)
{
    UNUSED_PARA(IpToResetMask);
    //TODO: implement this
    //normally use a int32_t as a mask for this but there are likely to be too many for a uint64_t so use struct
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_DrpRead(adi_fpga9010_Device_t *device, adi_fpga9010_DrpAddress_e addr, uint8_t drp, uint16_t *rdWord, adi_fpga9010_DrpMask_e rdMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i = 0;
    uint8_t drpReady = 0;
    uint8_t drpError = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    switch (drp)
    {
    case ADI_FPGA9010_PHY_CH0:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH1:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH2:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH3:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH4:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH5:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH6:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_CH7:
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;

    case ADI_FPGA9010_PHY_QUAD0:

        /*Write address, clear write_enable bit then set enable bit*/
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0DrpAddressBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (uint16_t)addr);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, addr, "Invalid DRP addr");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to DRP write enable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0DrpEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error enabling DRP transaction");
        ADI_ERROR_RETURN(device->common.error.newAction);

        for (i = 0; i < ADI_FPGA9010_DRP_TIMEOUT_MS; i++)
        {
            /* kluge to get drp read functionality working. after fpga has been updated to prevent the entire drp_read_data
            *  register from clearing when reading just the drp_ready bit remove this code and uncomment out the bf function below
            */
            uint32_t debugData = 0;
            adi_hal_BbicRegisterRead(device->common.devHalInfo, 0x4340094c, &debugData);

            drpReady = (debugData >> 16) & 0x1;
            *rdWord = debugData & 0xFFFF;
            //fpga9010_Jesd204PhyTokelauAds8Quad0DrpReadyBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &drpReady);
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

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0DrpErrorBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &drpError);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading DRP error bit");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if ((drpReady == 0) || (drpError == 1))
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_DRP_ERROR, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Quad DRP error: requires full reset");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            /* kluged- see comment above */
            //fpga9010_Jesd204PhyTokelauAds8Quad0DrpReadDataBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, rdWord);
            //ADI_ERROR_RETURN(device->common.error.newAction);
            *rdWord = *rdWord & (uint16_t)rdMask;
        }

        break;

    case ADI_FPGA9010_PHY_QUAD1:

        /*Write address, clear write_enable bit then set enable bit*/
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1DrpAddressBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (uint16_t)addr);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, addr, "Invalid DRP addr");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to DRP write enable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1DrpEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error enabling DRP transaction");
        ADI_ERROR_RETURN(device->common.error.newAction);

        for (i = 0; i < ADI_FPGA9010_DRP_TIMEOUT_MS; i++)
        {
            /* kluge to get drp read functionality working. after fpga has been updated to prevent the entire drp_read_data
            *  register from clearing when reading just the drp_ready bit remove this code and uncomment out the bf function below
            */
            uint32_t debugData = 0;
            adi_hal_BbicRegisterRead(device->common.devHalInfo, 0x43400a4c, &debugData);
            drpReady = (debugData >> 16) & 0x1;
            *rdWord = debugData & 0xFFFF;
            //fpga9010_Jesd204PhyTokelauAds8Quad1DrpReadyBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &drpReady);
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

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1DrpErrorBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &drpError);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading DRP error bit");
        ADI_ERROR_RETURN(device->common.error.newAction);

        if ((drpReady == 0) || (drpError == 1))
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_DRP_ERROR, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Quad DRP error: requires full reset");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            /* kluged- see comment above */
            //fpga9010_Jesd204PhyTokelauAds8Quad1DrpReadDataBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, rdWord);
            //ADI_ERROR_RETURN(device->common.error.newAction);
            *rdWord = *rdWord & (uint16_t)rdMask;
        }

        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid DRP selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
        
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_DrpWrite(adi_fpga9010_Device_t *device, adi_fpga9010_DrpAddress_e addr, uint8_t drp, uint16_t wrWord, adi_fpga9010_DrpMask_e wrMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t i = 0;
    uint8_t drpReady = 0;
    uint8_t drpError = 0;

    typedef struct {
        int32_t(*DrpWriteDataBfSet)     (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint16_t);
        int32_t(*DrpWriteDataMaskBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint16_t);
        int32_t(*DrpAddressBfSet)       (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint16_t);
        int32_t(*DrpWriteEnableBfSet)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*DrpEnableBfSet)        (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*DrpReadyBfGet)         (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*DrpErrorBfGet)         (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
    } fpgaDrpWriteBf_t;

    fpgaDrpWriteBf_t fpgaDrpWriteFct[] = {
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel0DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel0DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel0DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel0DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel1DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel1DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel1DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel1DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel2DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel2DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel2DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel2DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel3DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel3DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel3DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel3DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel4DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel4DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel4DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel4DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel5DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel5DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel5DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel5DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel6DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel6DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel6DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel6DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Channel7DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel7DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel7DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Channel7DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Quad0DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Quad0DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Quad0DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Quad0DrpErrorBfGet
        },
        {
            .DrpWriteDataBfSet     = fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteDataBfSet,
            .DrpWriteDataMaskBfSet = fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteDataMaskBfSet,
            .DrpAddressBfSet       = fpga9010_Jesd204PhyTokelauAds8Quad1DrpAddressBfSet,
            .DrpWriteEnableBfSet   = fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteEnableBfSet,
            .DrpEnableBfSet        = fpga9010_Jesd204PhyTokelauAds8Quad1DrpEnableBfSet,
            .DrpReadyBfGet         = fpga9010_Jesd204PhyTokelauAds8Quad1DrpReadyBfGet,
            .DrpErrorBfGet         = fpga9010_Jesd204PhyTokelauAds8Quad1DrpErrorBfGet
        }
    };

    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (drp > ADI_FPGA9010_PHY_QUAD1)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid DRP selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write data bitfields */
    if (fpgaDrpWriteFct[drp].DrpWriteDataBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpWriteDataBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, wrWord);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, wrWord, "Invalid DRP data word");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write mask bitfields */
    if (fpgaDrpWriteFct[drp].DrpWriteDataMaskBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpWriteDataMaskBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (uint16_t)wrMask);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, wrMask, "Invalid DRP data mask");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write address */
    if (fpgaDrpWriteFct[drp].DrpAddressBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpAddressBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (uint16_t)addr);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, addr, "Invalid DRP addr");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Write enable bit */
    if (fpgaDrpWriteFct[drp].DrpWriteEnableBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpWriteEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to DRP write enable");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Set enable bit */
    if (fpgaDrpWriteFct[drp].DrpEnableBfSet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error enabling DRP transaction");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Looping and wait for channel ready */
    drpReady = 0;
    for (i = 0; i < ADI_FPGA9010_DRP_TIMEOUT_MS; i++)
    {
        if (fpgaDrpWriteFct[drp].DrpReadyBfGet != NULL)
        {
            recoveryAction = fpgaDrpWriteFct[drp].DrpReadyBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &drpReady);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading DRP ready bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (drpReady)
        {
            break;
        }
        else
        {
            adi_common_hal_Wait_ms(&device->common, 1);
        }
    }

    drpError = 0;
    if (fpgaDrpWriteFct[drp].DrpErrorBfGet != NULL)
    {
        recoveryAction = fpgaDrpWriteFct[drp].DrpErrorBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &drpError);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading DRP error bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* If not ready or error occurred then report error. */
    if ((drpReady == 0) || (drpError == 1))
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_DRP_ERROR, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Quad DRP error: requires full reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_InitSet(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *initSettings)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t i = 0;
    uint8_t helperMask8bit = 0;
    uint8_t deserializerChannelMask = 0;
    uint8_t serializerChannelMask = 0;
    uint8_t lockBit = 0;
    uint8_t resetDone = 0;
    uint32_t deframer0LaneXbarReset = 0;
    uint32_t deframer1LaneXbarReset = 0;
    uint32_t deframer2LaneXbarReset = 0;
    uint32_t framer0LaneXbarReset = 0; 
    uint32_t framer1LaneXbarReset = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, initSettings);

    /* reset lane xbars. Do this first to prevent any deframer settings from affecting the PHY */
    recoveryAction = fpga9010_Jesd204RxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_0, 0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204RxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_1, 0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204RxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_2, 0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204TxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_0, 0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204TxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_1, 0xFFFFFFFF);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Physical layer
    ***************************************************************************************************************************************/
    /* Place all PHY channels in reset */
    adi_fpga9010_DeserializerResetSet(device, 0xFF, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    adi_fpga9010_SerializerResetSet(device, 0xFF, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* qpll setup */
    adi_fpga9010_QpllSet(device, initSettings->clocks.qpll.quadSelect, &initSettings->clocks.qpll);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* serializer/deserializer channel setup */
    for (i = 0; i < ADI_FPGA9010_NUM_LANES; i++)
    {
        helperMask8bit = (0x01 << i);
        if (initSettings->datapath.serializerCfg[i].powerDown == 0)
        {
            adi_fpga9010_SerializerCfgSet(device, helperMask8bit, &initSettings->datapath.serializerCfg[i]);
            ADI_ERROR_RETURN(device->common.error.newAction);
            serializerChannelMask |= (0x01 << i);
        }
        if (initSettings->datapath.deserializerCfg[i].powerDown == 0)
        {
            adi_fpga9010_DeserializerCfgSet(device, helperMask8bit, &initSettings->datapath.deserializerCfg[i]);
            ADI_ERROR_RETURN(device->common.error.newAction);
            deserializerChannelMask |= (0x01 << i);
        }
    }
    
    /* release the desired channels from reset based on the power down bits */
    adi_fpga9010_DeserializerResetSet(device, deserializerChannelMask, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    adi_fpga9010_SerializerResetSet(device, serializerChannelMask, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* check for qpll locks */
    if ((initSettings->clocks.qpll.quadSelect & ADI_FPGA9010_QPLL_QUAD0) > 0)
    {
        lockBit = 0;
        adi_fpga9010_QpllLockGet(device, ADI_FPGA9010_QPLL_QUAD0, initSettings->clocks.qpll.band, &lockBit);
        if (lockBit != 1)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_RESET_INTERFACE, ADI_FPGA9010_QPLLCLK0, "Error Quad0 Qpll not locked");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    if ((initSettings->clocks.qpll.quadSelect & ADI_FPGA9010_QPLL_QUAD1) > 0)
    {
        lockBit = 0;
        adi_fpga9010_QpllLockGet(device, ADI_FPGA9010_QPLL_QUAD1, initSettings->clocks.qpll.band, &lockBit);
        if (lockBit != 1)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_RESET_INTERFACE, ADI_FPGA9010_QPLLCLK1, "Error Quad1 Qpll not locked");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    /* check PHY layer has finished reset routine */
    adi_fpga9010_DeserializerResetDoneGet(device, &resetDone);
    ADI_ERROR_RETURN(device->common.error.newAction);
    if (resetDone != deserializerChannelMask)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_RESET_INTERFACE, NULL, "Deserializer channels have not reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    adi_fpga9010_SerializerResetDoneGet(device, &resetDone);
    ADI_ERROR_RETURN(device->common.error.newAction);
    if (resetDone != serializerChannelMask)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_RESET_INTERFACE, NULL, "Serializer channels have not reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /***************************************************************************************************************************************
    * MMCM
    ***************************************************************************************************************************************/
    /* Disable TDD FSM before calling MmcmSet */
    recoveryAction = adi_fpga9010_TddDisable(device);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_API_FAIL, recoveryAction, NULL, "Error disabling TDD during FPGA init");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* RX must be setup prior to TX since the final output of RX feeds TX mmcm*/
    recoveryAction = adi_fpga9010_MmcmSet(device, ADI_FPGA9010_CORE_MMCM, &initSettings->clocks.coreMmcm);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, initSettings->clocks.coreMmcm, "Error setting up Core MMCM");
    ADI_ERROR_RETURN(device->common.error.newAction);

    lockBit = 0;
    adi_fpga9010_MmcmLockGet(device, ADI_FPGA9010_CORE_MMCM, &lockBit);
    if (lockBit != 1)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_RESET_INTERFACE, ADI_FPGA9010_CORE_MMCM, "Error Core MMCM not locked");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /***************************************************************************************************************************************
    * Lane Xbars
    ***************************************************************************************************************************************/
    
    /* build up the link layer's lane xbar resets based on which phy lanes they're using */
    /* can't use dserializerChannelMask here because we need to reset based on which channels go to which
    *  link layer. the dserializerChannelMask shows us all the channels that are active, not how they map onto the link layers */
    for (i = 0; i < ADI_FPGA9010_NUM_LANES; i++)
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
    framer0LaneXbarReset = ~framer0LaneXbarReset;
    framer1LaneXbarReset = ~framer1LaneXbarReset;
    
    /* Remove the reset on the lanes in use in lane xbars */
    recoveryAction = fpga9010_Jesd204RxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_0, deframer0LaneXbarReset);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204RxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_1, deframer1LaneXbarReset);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204RxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_2, deframer2LaneXbarReset);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Rx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204TxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_0, framer0LaneXbarReset);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_Jesd204TxLaneXbarLaneResetBfSet(device, FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_1, framer1LaneXbarReset);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting Tx Lane XBar Reset");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /***************************************************************************************************************************************
    * Link layer
    ***************************************************************************************************************************************/
    /* Disable all framers/deframers */
    adi_fpga9010_DeframerDisable(device, ADI_FPGA9010_DEFRAMER_ALL);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adi_fpga9010_FramerDisable(device, ADI_FPGA9010_FRAMER_ALL);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* deframers & framers setup (only configure those that are in use) */
    if (initSettings->datapath.deframerCfg[0].lanesInUse != 0)
    {
        adi_fpga9010_DeframerCfgSet(device, ADI_FPGA9010_DEFRAMER_0, &initSettings->datapath.deframerCfg[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9010_XilinxJesd204bResetFixedBfSet(device, FPGA9010_BF_JESD204B_DEFRAMER_0, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error holding used FPGA deframer0 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    if (initSettings->datapath.deframerCfg[1].lanesInUse != 0)
    {
        adi_fpga9010_DeframerCfgSet(device, ADI_FPGA9010_DEFRAMER_1, &initSettings->datapath.deframerCfg[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9010_XilinxJesd204bResetFixedBfSet(device, FPGA9010_BF_JESD204B_DEFRAMER_1, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error holding used FPGA deframer1 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (initSettings->datapath.deframerCfg[2].lanesInUse != 0)
    {
        adi_fpga9010_DeframerCfgSet(device, ADI_FPGA9010_DEFRAMER_2, &initSettings->datapath.deframerCfg[2]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9010_XilinxJesd204bResetFixedBfSet(device, FPGA9010_BF_JESD204B_DEFRAMER_2, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error holding used FPGA deframer2 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    if (initSettings->datapath.framerCfg[0].lanesInUse != 0)
    {
        adi_fpga9010_FramerCfgSet(device, ADI_FPGA9010_FRAMER_0, &initSettings->datapath.framerCfg[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9010_XilinxJesd204bResetFixedBfSet(device, FPGA9010_BF_JESD204B_FRAMER_0, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error holding used FPGA framer0 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    if (initSettings->datapath.framerCfg[1].lanesInUse != 0)
    {
        adi_fpga9010_FramerCfgSet(device, ADI_FPGA9010_FRAMER_1, &initSettings->datapath.framerCfg[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Hold unused deframer in reset (reset bit in FPGA is read by PerformTx to know if link is used) */
        recoveryAction = fpga9010_XilinxJesd204bResetFixedBfSet(device, FPGA9010_BF_JESD204B_FRAMER_1, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error holding used FPGA framer1 in reset");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    /***************************************************************************************************************************************
    * Sync XBar
    ***************************************************************************************************************************************/
    adi_fpga9010_SyncXBarCfgSet(device, initSettings->datapath.syncBPolarity, &initSettings->datapath.syncBSel[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Sysref
    ***************************************************************************************************************************************/
    adi_fpga9010_SysRefControlSet(device, &initSettings->sysref);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Set the static information in DMAs
    ***************************************************************************************************************************************/
    adi_fpga9010_RxDmaInit(device, ADI_FPGA9010_DEFRAMER_0, &initSettings->datapath.rxDmaCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_RxDmaInit(device, ADI_FPGA9010_DEFRAMER_1, &initSettings->datapath.rxDmaCfg[1]);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_RxDmaInit(device, ADI_FPGA9010_DEFRAMER_2, &initSettings->datapath.rxDmaCfg[2]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adi_fpga9010_TxDmaInit(device, ADI_FPGA9010_FRAMER_0, &initSettings->datapath.txDmaCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adi_fpga9010_TxDmaInit(device, ADI_FPGA9010_FRAMER_1, &initSettings->datapath.txDmaCfg[1]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /***************************************************************************************************************************************
    * Reset datapaths
    ***************************************************************************************************************************************/
    adi_fpga9010_RxDataChainReset(device);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_TxDataChainReset(device);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

int32_t adi_fpga9010_InitGet(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *initSettings)
{
    uint8_t i = 0;
    uint8_t laneSel = 1;
    uint16_t dataMoverSel = 1;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, initSettings);
    
    
    for (i=0; i< 8; i++)
    {
       // int32_t adi_fpga9010_SerializerCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_LaneSel_e laneSel, adi_fpga9010_SerializerCfg_t *serializerCfg)
        adi_fpga9010_SerializerCfgGet(device, (adi_fpga9010_LaneSel_e)laneSel, &initSettings->datapath.serializerCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        adi_fpga9010_DeserializerCfgGet(device, (adi_fpga9010_LaneSel_e)laneSel, &initSettings->datapath.deserializerCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        laneSel = laneSel << 1;
    }

     // get the framer configurations
    adi_fpga9010_FramerCfgGet(device, ADI_FPGA9010_FRAMER_0, &initSettings->datapath.framerCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    // get the 2 deframer configurations
    adi_fpga9010_DeframerCfgGet(device, ADI_FPGA9010_DEFRAMER_0, &initSettings->datapath.deframerCfg[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adi_fpga9010_DeframerCfgGet(device, ADI_FPGA9010_DEFRAMER_1, &initSettings->datapath.deframerCfg[1]);
    ADI_ERROR_RETURN(device->common.error.newAction);


    // get the 8 txdataMover configurations
    dataMoverSel = 1;
    for (i = 0; i < ADI_FPGA9010_NUM_OF_TX_DATAMOVERS; i++)
    {
        adi_fpga9010_TxDmaGet(device, (adi_fpga9010_FramerSel_e)dataMoverSel, &initSettings->datapath.txDmaCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        dataMoverSel = dataMoverSel << 1;
    }

    //get the 16 rxdataMover configurations
    dataMoverSel = 1;
    for (i = 0; i < ADI_FPGA9010_NUM_OF_RX_DATAMOVERS; i++)
    {
        adi_fpga9010_RxDmaGet(device, (adi_fpga9010_DeframerSel_e)dataMoverSel, &initSettings->datapath.rxDmaCfg[i]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        dataMoverSel = dataMoverSel << 1;
    }

    //the configuration of all tollgates must be the same so we only need to store one of each 
    adi_fpga9010_TxTollgateGet(device, ADI_FPGA9010_FRAMER_0, &initSettings->datapath.txTollgateCfg);
    ADI_ERROR_REPORT(&device->common,
                     device->common.error.errSource,
                     device->common.error.errCode,
                     device->common.error.newAction,
                     device->common.error.varName,
                     device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adi_fpga9010_RxTollgateGet(device, ADI_FPGA9010_DEFRAMER_0, &initSettings->datapath.rxTollgateCfg);
    ADI_ERROR_REPORT(&device->common,
                     device->common.error.errSource,
                     device->common.error.errCode,
                     device->common.error.newAction,
                     device->common.error.varName,
                     device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}


int32_t adi_fpga9010_Initialize(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *fpgaInit)
{

    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
//    uint32_t refClk_kHz = 245760;
//    uint32_t fastestLaneRate_kHz = 1228800;
    uint8_t lockBit = 0;
    uint8_t resetDone = 0;
   // uint8_t phyLayerMask = 0;

    uint8_t laneSelMask = 0x55;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
     //todo fpgaInit is null and will be for some time
    //ADI_NULL_PTR_RETURN(&device->common, fpgaInit); 
   
    adi_fpga9010_InitSet(device, fpgaInit);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /*check the qplls & mmcm for lock */
    lockBit = 0;
    recoveryAction = adi_fpga9010_MmcmLockGet(device, ADI_FPGA9010_CORE_MMCM, &lockBit);
    if (lockBit == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error RX MMCM not locked");
    }
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* quad 0 */
    lockBit = 0;
    recoveryAction = adi_fpga9010_QpllLockGet(device, 0, fpgaInit->clocks.qpll.band, &lockBit);
    if (lockBit == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error QPLL0 not locked");
    }
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* quad 1 */
    lockBit = 0;
    recoveryAction = adi_fpga9010_QpllLockGet(device, 1, fpgaInit->clocks.qpll.band, &lockBit);
    if (lockBit == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error QPLL1 not locked");
    }
    ADI_ERROR_RETURN(device->common.error.newAction);

    //PHY reset done bits getting set?
    recoveryAction = adi_fpga9010_DeserializerResetDoneGet(device, &resetDone);
    if (resetDone!= laneSelMask)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, resetDone, "Error Deserializer not reset");
    }
    ADI_ERROR_RETURN(device->common.error.newAction);

    resetDone = 0;
    recoveryAction = adi_fpga9010_SerializerResetDoneGet(device, &resetDone);
    if (resetDone != laneSelMask)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, resetDone, "Error Deserializer not reset");
    }
    ADI_ERROR_RETURN(device->common.error.newAction);
    return (device->common.error.newAction);
}

//int32_t adi_fpga9010_Initialize(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *fpgaInit)
//{
//
//    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
//    uint32_t refClk_kHz = 245760;
//    uint32_t fastestLaneRate_kHz = 1228800;
//    uint32_t i = 0;
//    uint32_t j = 0;
//
//    ADI_NULL_DEVICE_PTR_RETURN(device);
//
//#if ADI_FPGA9010_VERBOSE > 0
//    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
//#endif
//
//    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
//     //todo fpgaInit is null and will be for some time
//    //ADI_NULL_PTR_RETURN(&device->common, fpgaInit); 
//
//    uint8_t lockBit = 0;
//    uint8_t resetDone = 0;
//    uint8_t laneSelMask;
//
//    refClk_kHz = 245760;
//    fastestLaneRate_kHz = 1228800;
//    laneSelMask = 0x55;
//
//    recoveryAction = adi_fpga9010_CalculateQpllSettings(device, refClk_kHz, fastestLaneRate_kHz, &fpgaInit->clocks.qpll);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    for (i = 0; i < ADI_FPGA9010_NUM_MMCM_OUTPUT_CLOCKS - 1; i++)
//    {
//        fpgaInit->clocks.rxMmcm.outputClkFreq_kHz[i] = refClk_kHz * 3;
//        fpgaInit->clocks.txMmcm.outputClkFreq_kHz[i] = refClk_kHz * 3;
//    }
//    /* Force channel 6 to refClk because of the FPGA implementation constraint */
//    fpgaInit->clocks.rxMmcm.outputClkFreq_kHz[ADI_FPGA9010_NUM_MMCM_OUTPUT_CLOCKS - 1] = refClk_kHz;
//    /* Force channel 6 on the tx one also because it's conveneient */
//    fpgaInit->clocks.txMmcm.outputClkFreq_kHz[ADI_FPGA9010_NUM_MMCM_OUTPUT_CLOCKS - 1] = refClk_kHz;
//
//    recoveryAction = adi_fpga9010_CalculateMmcmSettings(device, refClk_kHz, &fpgaInit->clocks.rxMmcm);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//    recoveryAction = adi_fpga9010_CalculateMmcmSettings(device, refClk_kHz, &fpgaInit->clocks.txMmcm);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    /*default serializer/deserializer values */
//    for (i = 0; i < 8; i++)
//    {
//        fpgaInit->datapath.deserializerCfg[i].rxPllClkSel = ADI_FPGA9010_QPLLCLK0;
//        fpgaInit->datapath.deserializerCfg[i].rate = 1;
//        fpgaInit->datapath.deserializerCfg[i].polarity = 0;
//        fpgaInit->datapath.deserializerCfg[i].encoder8b10bEnable = 1;
//        fpgaInit->datapath.deserializerCfg[i].usrClk2Div = 1;
//        fpgaInit->datapath.deserializerCfg[i].powerDown = 0;
//        fpgaInit->datapath.deserializerCfg[i].rxDfeLpmEn = 1;
//
//        fpgaInit->datapath.serializerCfg[i].cpllRefClkSel = 0x01;
//        fpgaInit->datapath.serializerCfg[i].txPllClkSel = ADI_FPGA9010_QPLLCLK0;
//        fpgaInit->datapath.serializerCfg[i].rate = 1;
//        fpgaInit->datapath.serializerCfg[i].polarity = 0;
//        fpgaInit->datapath.serializerCfg[i].encoder8b10bEnable = 1;
//        fpgaInit->datapath.serializerCfg[i].precursor = 0;
//        fpgaInit->datapath.serializerCfg[i].postcursor = 0;
//        fpgaInit->datapath.serializerCfg[i].diffCtrl = 4;
//        fpgaInit->datapath.serializerCfg[i].usrClk2Div = 1;
//        fpgaInit->datapath.serializerCfg[i].powerDown = 0;
//    }
//
//    /* default deframer values */
//    for (i = 0; i < 3; i++)
//    {
//        for (j = 0; j < ADI_FPGA9010_NUM_LANES; j++)
//        {
//            fpgaInit->datapath.deframerCfg[i].laneXbar[j] = j;
//        }
//        fpgaInit->datapath.deframerCfg[i].scramblingEn = 0;
//        fpgaInit->datapath.deframerCfg[i].cfgF = 1;
//        fpgaInit->datapath.deframerCfg[i].cfgK = 0x1F;
//        fpgaInit->datapath.deframerCfg[i].subclassV = 2;
//        fpgaInit->datapath.deframerCfg[i].rxBufferDly = 0;
//        fpgaInit->datapath.deframerCfg[i].errReportingDisable = 0;
//        fpgaInit->datapath.deframerCfg[i].ilaSupportEn = 0;
//        fpgaInit->datapath.deframerCfg[i].lanesInUse = 0x00;
//        fpgaInit->datapath.deframerCfg[i].sysRefAlways = 0;
//        fpgaInit->datapath.deframerCfg[i].sysRefDelay = 0;
//        fpgaInit->datapath.deframerCfg[i].sysRefRequiredOnResync = 0;
//        fpgaInit->datapath.deframerCfg[i].mode = 0;
//    }
//
//    /* default deframer values */
//    for (i = 0; i < 2; i++)
//    {
//        for (j = 0; j < ADI_FPGA9010_NUM_LANES; j++)
//        {
//            fpgaInit->datapath.framerCfg[i].laneXbar[j] = j;
//        }
//        fpgaInit->datapath.framerCfg[i].deviceId = 0;
//        fpgaInit->datapath.framerCfg[i].bankId = 1;
//        fpgaInit->datapath.framerCfg[i].scramblingEn = 1;
//        fpgaInit->datapath.framerCfg[i].ilaMultiFrames = 4;
//        fpgaInit->datapath.framerCfg[i].cfgF = 1;
//        fpgaInit->datapath.framerCfg[i].cfgK = 1;
//        fpgaInit->datapath.framerCfg[i].ilaM = 0;
//        fpgaInit->datapath.framerCfg[i].ilaN = 0;
//        fpgaInit->datapath.framerCfg[i].ilaCs = 0;
//        fpgaInit->datapath.framerCfg[i].ilaNp = 0;
//        fpgaInit->datapath.framerCfg[i].ilaS = 0;
//        fpgaInit->datapath.framerCfg[i].ilaCf = 0;
//        fpgaInit->datapath.framerCfg[i].ilaHd = 0;
//        fpgaInit->datapath.framerCfg[i].subclassV = 0;
//        fpgaInit->datapath.framerCfg[i].ilaSupportEn = 0;
//        fpgaInit->datapath.framerCfg[i].sysRefAlways = 0;
//        fpgaInit->datapath.framerCfg[i].sysRefDelay = 0;
//        fpgaInit->datapath.framerCfg[i].sysRefRequiredOnResync = 0;
//        fpgaInit->datapath.framerCfg[i].lanesInUse = 0x00;
//    }
//
//    /* set rx datamovers */
//    for (i = 0; i < 16; i++)
//    {
//        fpgaInit->datapath.rxdmCfg[i].dmaCfg.dataPathEnhancedModeEn = 0;
//        fpgaInit->datapath.rxdmCfg[i].dmaCfg.dataPathScatterGatherEn = 0;
//        fpgaInit->datapath.rxdmCfg[i].dmaCfg.dataPathStartAddr = i * 0x1000000; //16MB each
//        fpgaInit->datapath.rxdmCfg[i].dmaCfg.dataPathLength = 0;
//        fpgaInit->datapath.rxdmCfg[i].dmaCfg.dataPathSGFirstDesc = 0;
//        fpgaInit->datapath.rxdmCfg[i].dmaCfg.dataPathSGLastDesc = 0;
//
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkCfgF = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkCfgNP = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkCfgL = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkCfgS = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkConfigJesdV = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkConfigM = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkConfigLinkId = 1;
//        fpgaInit->datapath.rxdmCfg[i].tplCfg.linkConfigConvId = 1;
//    }
//
//    /* set tx datamovers */
//    for (i = 0; i < 8; i++)
//    {
//        fpgaInit->datapath.txdmCfg[i].dmaCfg.dataPathEnhancedModeEn = 0;
//        fpgaInit->datapath.txdmCfg[i].dmaCfg.dataPathScatterGatherEn = 0;
//        fpgaInit->datapath.txdmCfg[i].dmaCfg.dataPathStartAddr = (i + 16) * 0x1000000; //16MB each
//        fpgaInit->datapath.txdmCfg[i].dmaCfg.dataPathLength = 0;
//        fpgaInit->datapath.txdmCfg[i].dmaCfg.dataPathSGFirstDesc = 0;
//        fpgaInit->datapath.txdmCfg[i].dmaCfg.dataPathSGLastDesc = 0;
//
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkCfgF = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkCfgNP = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkCfgL = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkCfgS = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkConfigJesdV = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkConfigM = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkConfigLinkId = 1;
//        fpgaInit->datapath.txdmCfg[i].tplCfg.linkConfigConvId = 1;
//    }
//
//    /* tollgates */
//    fpgaInit->datapath.rxTollgateCfg.tollGateEdgeOrLvl = 1;
//    fpgaInit->datapath.rxTollgateCfg.tollGateHiRiseOrLoFall = 1;
//    fpgaInit->datapath.rxTollgateCfg.tollgateReset = 1;
//    fpgaInit->datapath.rxTollgateCfg.tollGateTrigSource = ADI_FPGA9010_IMM_TRIG;
//
//    fpgaInit->datapath.txTollgateCfg.tollGateEdgeOrLvl = 1;
//    fpgaInit->datapath.txTollgateCfg.tollGateHiRiseOrLoFall = 1;
//    fpgaInit->datapath.txTollgateCfg.tollgateReset = 1;
//    fpgaInit->datapath.txTollgateCfg.tollGateTrigSource = ADI_FPGA9010_TX_IMM_TRIG;
//
//    //place all tx & rx channels in reset
//    recoveryAction = adi_fpga9010_DeserializerResetSet(device, 0xFF, 1);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//    recoveryAction = adi_fpga9010_SerializerResetSet(device, 0xFF, 1);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    recoveryAction = adi_fpga9010_InitSet(device, fpgaInit);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    //release channel reset
//    recoveryAction = adi_fpga9010_DeserializerResetSet(device, laneSelMask, 0);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//    recoveryAction = adi_fpga9010_SerializerResetSet(device, laneSelMask, 0);
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    /*check the qplls & mmcm for lock */
//    lockBit = 0;
//    recoveryAction = adi_fpga9010_MmcmLockGet(device, ADI_FPGA9010_RX_MMCM, &lockBit);
//    if (lockBit == 0)
//    {
//        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error RX MMCM not locked");
//    }
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    lockBit = 0;
//    recoveryAction = adi_fpga9010_MmcmLockGet(device, ADI_FPGA9010_TX_MMCM, &lockBit);
//    if (lockBit == 0)
//    {
//        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error TX MMCM not locked");
//    }
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    /* quad 0 */
//    lockBit = 0;
//    recoveryAction = adi_fpga9010_QpllLockGet(device, 0, fpgaInit->clocks.qpll.band, &lockBit);
//    if (lockBit == 0)
//    {
//        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error QPLL0 not locked");
//    }
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    /* quad 1 */
//    lockBit = 0;
//    recoveryAction = adi_fpga9010_QpllLockGet(device, 1, fpgaInit->clocks.qpll.band, &lockBit);
//    if (lockBit == 0)
//    {
//        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, lockBit, "Error QPLL1 not locked");
//    }
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    //PHY reset done bits getting set?
//    recoveryAction = adi_fpga9010_DeserializerResetDoneGet(device, &resetDone);
//    if (resetDone != laneSelMask)
//    {
//        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, resetDone, "Error Deserializer not reset");
//    }
//    ADI_ERROR_RETURN(device->common.error.newAction);
//
//    resetDone = 0;
//    recoveryAction = adi_fpga9010_SerializerResetDoneGet(device, &resetDone);
//    if (resetDone != laneSelMask)
//    {
//        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, resetDone, "Error Deserializer not reset");
//    }
//    ADI_ERROR_RETURN(device->common.error.newAction);
//    return (device->common.error.newAction);
//}
