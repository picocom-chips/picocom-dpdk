/**
 * \file: fpga9025_jesd.c
 *
 * \brief Contains private jesd related functions
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025.h"
#include "../../private/include/fpga9025_utilities.h"
#define EXCELSHEET 1

int32_t fpga9025_QpllDrpCfg(adi_fpga9025_Device_t* device,
                            const uint32_t         refClk_kHz,
                            const uint32_t         qpllVcoOut_kHz,
                            const uint8_t          qpllDivideRatio)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 12288000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 11059200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x33f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x33f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 14745600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 14745600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x333c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x333c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x31d,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x31d,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 12288000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 11059200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 491520 && qpllVcoOut_kHz == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x27f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x27f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 9123840 && qpllDivideRatio == 1)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x23f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x23f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x3,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x3,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21d,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21d,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 16220160 && qpllDivideRatio == 2)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x0,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x0,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x0,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x0,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && qpllDivideRatio == 1)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x23f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x23f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 9123840 && qpllDivideRatio == 1)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x23f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x23f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x3,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x3,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21d,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21d,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && qpllDivideRatio == 1)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x33f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x33f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 12165120 && qpllDivideRatio == 1)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 16220160 && qpllDivideRatio == 2)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x0,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x0,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x31d,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x31d,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x0,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x0,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x333c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x333c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && qpllDivideRatio == 1)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc1,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x3,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x37f,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x1,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x400,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x331c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 491520 && qpllVcoOut_kHz == 16220160 && qpllDivideRatio == 2)
    {
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x600,
                              0xffff); /* ppf1Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf1Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x0,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x0,
                              0x1); /* qpll0ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x001b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc0,
                              0xffff); /* qpll0Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0030,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll0Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x31d,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0019,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x31d,
                              0x03ff); /* qpll0Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x0,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008e,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x0,
                              0x1); /* qpll1ClkOutRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1ClkOutRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0091,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009b,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xfc3,
                              0xffff); /* qpll1Cfg2G3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg2G3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x2,
                              0xffff); /* qpll1Cfg4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Cfg4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0099,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x21f,
                              0x03ff); /* qpll1Lpf */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll1Lpf");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x000d,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0xb00,
                              0xffff); /* ppf0Cfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ppf0Cfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD0,
                              0x333c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0008,
                              (uint32_t)ADI_FPGA9025_PHY_QUAD1,
                              0x333c,
                              0xffff); /* qpll0Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to qpll0Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }

    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_INVALID_CLK_CONFIG,
                     ADI_COMMON_ACT_WARN_CHECK_PARAM,
                     NULL,
                     "WARNING: Clock config is not supported. Performance may suffer.");
    return recoveryAction;
}

int32_t fpga9025_SerializerDrpCfg(adi_fpga9025_Device_t* device,
                                  const uint32_t         refClk_kHz,
                                  const uint32_t         laneRate,
                                  const uint32_t         qpllVcoOut_kHz,
                                  const uint8_t          fpgaLane)
{
#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 4915200 && laneRate == 4915200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x723,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x300,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 4915200 && laneRate == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x300,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 6144000 && laneRate == 6144000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x723,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 6144000 && laneRate == 12288000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 5529600 && laneRate == 11059200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 7372800 && laneRate == 7372800)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x723,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 7372800 && laneRate == 14745600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 4915200 && laneRate == 4915200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x723,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x300,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 4915200 && laneRate == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x300,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 7372800 && laneRate == 14745600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 6144000 && laneRate == 6144000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x723,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 6144000 && laneRate == 12288000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 5529600 && laneRate == 11059200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 491520 && qpllVcoOut_kHz == 4915200 && laneRate == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x300,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 8110080 && laneRate == 16220160)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 8110080 && laneRate == 4055040)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 8110080 && laneRate == 8110080)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && laneRate == 10137600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && laneRate == 20275200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x600,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c6,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x40,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && laneRate == 5068800)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && laneRate == 12165120)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && laneRate == 24330240)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x600,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c6,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x40,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && laneRate == 6082560)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 9123840 && laneRate == 18247680)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 9123840 && laneRate == 9123840)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 12165120 && laneRate == 12165120)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 12165120 && laneRate == 24330240)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x600,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c6,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x40,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 8110080 && laneRate == 16220160)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 8110080 && laneRate == 4055040)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 8110080 && laneRate == 8110080)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && laneRate == 10137600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && laneRate == 20275200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x600,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c6,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x40,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && laneRate == 5068800)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 9123840 && laneRate == 18247680)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 9123840 && laneRate == 9123840)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0x6c00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xf,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x1000,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 491520 && qpllVcoOut_kHz == 8110080 && laneRate == 16220160)
    {
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c2,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x0,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe200,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x1,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }

    /* Default cases Logs a warning if the code gets to here but allows init to continue since the configuration may work OK. */
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        /* Uses the settings from refClk == 245.76 & laneRate == 14.7G */
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x200,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xaa00,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x008f,
                              fpgaLane,
                              0x323,
                              0xffff); /* TxphCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3100,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x2,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);

        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_INVALID_CLK_CONFIG,
                         ADI_COMMON_ACT_WARN_CHECK_PARAM,
                         NULL,
                         "WARNING: Clock config is not supported. Performance may suffer.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        /* Uses the settings from refClk == 245.76 & laneRate == 24.3G */
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x600,
                              0x0600); /* TxdrvFreqband */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxdrvFreqband");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x009d,
                              fpgaLane,
                              0x3c6,
                              0xffff); /* TxfeCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a1,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0053,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0054,
                              fpgaLane,
                              0xf800,
                              0xffff); /* TxfeCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxfeCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a7,
                              fpgaLane,
                              0x3000,
                              0xffff); /* TxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fa,
                              fpgaLane,
                              0x40,
                              0x0040); /* TxswbstEn */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxswbstEn");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x4,
                              0x0006); /* TxpiBiasset */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiBiasset");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0057,
                              fpgaLane,
                              0xe218,
                              0xffff); /* TxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0105,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x006f,
                              fpgaLane,
                              0xe,
                              0xffff); /* TxphdlyCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxphdlyCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a8,
                              fpgaLane,
                              0x0,
                              0xffff); /* TxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to TxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);

        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_INVALID_CLK_CONFIG,
                         ADI_COMMON_ACT_WARN_CHECK_PARAM,
                         NULL,
                         "WARNING: Clock config is not supported. Performance may suffer.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_INVALID_CLK_CONFIG,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "Could not find valid DRP settings for this FPGA configuration.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return ADI_COMMON_ACT_NO_ACTION;
}

int32_t fpga9025_DeserializerDrpCfg(adi_fpga9025_Device_t* device,
                                    const uint32_t         refClk_kHz,
                                    const uint32_t         laneRate,
                                    const uint32_t         qpllVcoOut_kHz,
                                    const uint8_t          fpgaLane)
{
#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 4915200 && laneRate == 4915200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x2020,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x3,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x100,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 4915200 && laneRate == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x2020,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x3,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x100,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 6144000 && laneRate == 6144000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x102,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 6144000 && laneRate == 12288000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x102,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 5529600 && laneRate == 11059200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x102,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 7372800 && laneRate == 7372800)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 7372800 && laneRate == 14745600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 4915200 && laneRate == 4915200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x2020,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x3,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x100,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 4915200 && laneRate == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x2020,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x3,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x100,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 7372800 && laneRate == 14745600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 6144000 && laneRate == 6144000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x102,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 6144000 && laneRate == 12288000)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x102,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 5529600 && laneRate == 11059200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x102,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID && refClk_kHz == 491520 && qpllVcoOut_kHz == 4915200 && laneRate == 9830400)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x2020,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x0,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x3,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x4800,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x12,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x100,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x0,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 8110080 && laneRate == 16220160)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 8110080 && laneRate == 4055040)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x249,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 122880 && qpllVcoOut_kHz == 8110080 && laneRate == 8110080)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && laneRate == 20275200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x1040,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x40,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && laneRate == 10137600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 153600 && qpllVcoOut_kHz == 10137600 && laneRate == 5068800)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x249,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && laneRate == 24330240)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x1040,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x40,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && laneRate == 12165120)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 12165120 && laneRate == 6082560)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x249,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 9123840 && laneRate == 18247680)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x104,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x600,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1800,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 184320 && qpllVcoOut_kHz == 9123840 && laneRate == 9123840)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x104,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x600,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1800,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 12165120 && laneRate == 24330240)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x1040,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x40,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 12165120 && laneRate == 12165120)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 8110080 && laneRate == 16220160)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 8110080 && laneRate == 4055040)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x249,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 245760 && qpllVcoOut_kHz == 8110080 && laneRate == 8110080)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && laneRate == 20275200)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x1040,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x40,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && laneRate == 10137600)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 307200 && qpllVcoOut_kHz == 10137600 && laneRate == 5068800)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xf81c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x0,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x249,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x249,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 9123840 && laneRate == 18247680)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x104,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x600,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1800,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 368640 && qpllVcoOut_kHz == 9123840 && laneRate == 9123840)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x104,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x1000,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x600,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x259,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x259,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x2,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1800,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID && refClk_kHz == 491520 && qpllVcoOut_kHz == 8110080 && laneRate == 16220160)
    {
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x10c0,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0xc0c0,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x80c0,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x5,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x0,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x200,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4101,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x54,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe200,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x1,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        return ADI_COMMON_ACT_NO_ACTION;
    }

    /* Default cases Logs a warning if the code gets to here but allows init to continue since the configuration may work OK. */
    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        /* Uses the settings from refClk == 245.76 & laneRate == 14.7G */
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x4040,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x10,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x4,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0011,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x8c00,
                              0xfc00); /* RxcdrCfg3Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a5,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x011c,
                              fpgaLane,
                              0x23,
                              0xffff); /* RxcdrCfg3Gen4 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg3Gen4");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3002,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x4,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        /* Uses the settings from refClk == 245.76 & laneRate == 24.3G */
        adi_fpga9025_DrpWrite(device,
                              0x0116,
                              fpgaLane,
                              0x6060,
                              0xffff); /* ChHspmux */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to ChHspmux");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f7,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal1Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f8,
                              fpgaLane,
                              0x1040,
                              0xffff); /* Ckcal1Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal1Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00f9,
                              fpgaLane,
                              0x4040,
                              0xffff); /* Ckcal2Cfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0101,
                              fpgaLane,
                              0x40,
                              0xffff); /* Ckcal2Cfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Ckcal2Cfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00fb,
                              fpgaLane,
                              0x20,
                              0x0030); /* PreiqFreqBst */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PreiqFreqBst");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00dd,
                              fpgaLane,
                              0x6,
                              0x0007); /* RtxBufCmlCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RtxBufCmlCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0010,
                              fpgaLane,
                              0x1e9,
                              0xffff); /* RxcdrCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010a,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1IqLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1IqLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0108,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1ILoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1ILoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0109,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal1QLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal1QLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010e,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DxLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DxLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010b,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2DLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2DLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010d,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2SLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2SLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x010c,
                              fpgaLane,
                              0x4,
                              0xffff); /* Rxckcal2XLoopRstCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to Rxckcal2XLoopRstCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b1,
                              fpgaLane,
                              0x281c,
                              0xffff); /* RxdfeKhCfg2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00b0,
                              fpgaLane,
                              0x4120,
                              0xffff); /* RxdfeKhCfg3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxdfeKhCfg3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0075,
                              fpgaLane,
                              0x3004,
                              0xffff); /* RxpiCfg0 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d2,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxpiCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxpiCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c6,
                              fpgaLane,
                              0xe218,
                              0xffff); /* RxProgdivCfg */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivCfg");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0103,
                              fpgaLane,
                              0x0,
                              0xffff); /* RxProgdivRate */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxProgdivRate");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0066,
                              fpgaLane,
                              0x8,
                              0x000c); /* RxWidemodeCdr */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxWidemodeCdr");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0092,
                              fpgaLane,
                              0xfb1c,
                              0xffff); /* AdaptCfg1 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to AdaptCfg1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00c3,
                              fpgaLane,
                              0x3500,
                              0xffff); /* PcieBufgDivCtrl */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PcieBufgDivCtrl");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x400,
                              0x0600); /* PciePllSelModeGen12 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen12");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x0135,
                              fpgaLane,
                              0x269,
                              0x03ff); /* RxcdrCfg2Gen2 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen2");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00a4,
                              fpgaLane,
                              0x269,
                              0xffff); /* RxcdrCfg2Gen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxcdrCfg2Gen3");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00d3,
                              fpgaLane,
                              0x0,
                              0x0002); /* RxXmodeSel */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to RxXmodeSel");
        ADI_ERROR_RETURN(device->common.error.newAction);
        adi_fpga9025_DrpWrite(device,
                              0x00ad,
                              fpgaLane,
                              0x1000,
                              0x0300); /* PciePllSelModeGen3 */
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         device->common.error.errCode,
                         device->common.error.newAction,
                         NULL,
                         "Could not write to PciePllSelModeGen3");
        ADI_ERROR_RETURN(device->common.error.newAction);

        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_INVALID_CLK_CONFIG,
                         ADI_COMMON_ACT_WARN_CHECK_PARAM,
                         NULL,
                         "WARNING: Clock config is not supported. Performance may suffer.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_INVALID_CLK_CONFIG,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "Could not find valid DRP settings for this FPGA configuration.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return ADI_COMMON_ACT_NO_ACTION;
}
