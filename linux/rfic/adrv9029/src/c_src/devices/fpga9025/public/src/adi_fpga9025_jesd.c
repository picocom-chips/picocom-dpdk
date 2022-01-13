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
#include "adi_fpga9025_jesd.h"
#include "adi_fpga9025.h"
#include "../../private/include/fpga9025_bf_axi_adrv9025.h"
#include "../../private/include/fpga9025_bf_jesd204_phy_ads9.h"
#include "../../private/include/fpga9025_jesd.h"
#include "../../private/include/fpga9025_bf_xilinx_jesd204b.h"
#include "../../private/include/fpga9025_bf_xilinx_jesd204c.h"
#include "../../private/include/fpga9025_bf_jesd204_sysref_control.h"
#include "../../private/include/fpga9025_bf_jesd204b_sync_xbar.h"
#include "../../private/include/fpga9025_bf_jesd204_rx_lane_xbar.h"
#include "../../private/include/fpga9025_bf_jesd204_tx_lane_xbar.h"

int32_t adi_fpga9025_SerializerCfgSet(adi_fpga9025_Device_t*        device,
                                      uint8_t                       laneSelMask,
                                      adi_fpga9025_SerializerCfg_t* serializerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    uint8_t txRateEncodedValue = 0;
    int32_t i                  = 0;
    int32_t selectBit          = 0;

    char serializerErrStr[][64] = {
        "Error setting channel 0 cpll ref clk",
        "Error setting channel 0 tx pll clk sel",
        "Error setting channel 0 tx rate (final divider)",
        "Error setting channel 0 tx polarity",
        "Error setting channel 0 tx precursor",
        "Error setting channel 0 tx postcursor",
        "Error setting channel 0 tx diffCtrl",
        "Error setting channel 0 tx encoder8b10bEnable",
        "Error setting channel 0 tx clk out",
        "Error setting channel 0 tx powerDown" /* Leave this as the last element. The order here matches the order in which they are called below */
    };
    uint32_t laneNumPos = 22;

    typedef struct
    {
        int32_t (*CpllRefClkSelBfSet)(adi_fpga9025_Device_t*              device,
                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                      uint8_t                             );

        int32_t (*TxPllClkSelBfSet)(adi_fpga9025_Device_t*              device,
                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                    uint8_t                             );

        int32_t (*TxRateBfSet)(adi_fpga9025_Device_t*              device,
                               fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                               uint8_t                             );

        int32_t (*TxPolarityBfSet)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t                             );

        int32_t (*TxPrecursorBfSet)(adi_fpga9025_Device_t*              device,
                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                    uint8_t                             );

        int32_t (*TxPostcursorBfSet)(adi_fpga9025_Device_t*              device,
                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                     uint8_t                             );

        int32_t (*TxDiffControlBfSet)(adi_fpga9025_Device_t*              device,
                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                      uint8_t                             );

        int32_t (*Tx8b10bEnableBfSet)(adi_fpga9025_Device_t*              device,
                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                      uint8_t                             );

        int32_t (*TxClkOutBfSet)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t                             );

        int32_t (*TxPowerdownBfSet)(adi_fpga9025_Device_t*              device,
                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                    uint8_t                             );
    } fpgaSerializerSet_t;

    fpgaSerializerSet_t serializerSetFct[] = {
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel0CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel0TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel0TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel0TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel0TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel0TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel0TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel0Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel0TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel0TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel1CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel1TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel1TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel1TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel1TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel1TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel1TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel1Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel1TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel1TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel2CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel2TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel2TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel2TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel2TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel2TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel2TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel2Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel2TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel2TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel3CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel3TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel3TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel3TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel3TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel3TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel3TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel3Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel3TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel3TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel4CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel4TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel4TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel4TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel4TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel4TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel4TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel4Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel4TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel4TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel5CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel5TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel5TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel5TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel5TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel5TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel5TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel5Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel5TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel5TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel6CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel6TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel6TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel6TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel6TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel6TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel6TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel6Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel6TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel6TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9025_Jesd204PhyAds9Channel7CpllRefClkSelBfSet,
            .TxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel7TxPllClkSelBfSet,
            .TxRateBfSet = fpga9025_Jesd204PhyAds9Channel7TxRateBfSet,
            .TxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel7TxPolarityBfSet,
            .TxPrecursorBfSet = fpga9025_Jesd204PhyAds9Channel7TxPrecursorBfSet,
            .TxPostcursorBfSet = fpga9025_Jesd204PhyAds9Channel7TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9025_Jesd204PhyAds9Channel7TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel7Tx8b10bEnableBfSet,
            .TxClkOutBfSet = fpga9025_Jesd204PhyAds9Channel7TxOutClkSelBfSet,
            .TxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel7TxPowerdownBfSet
        }
    };

    uint32_t strIdx = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        serializerCfg);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    switch (serializerCfg->rate)
    {
    case 0:
        txRateEncodedValue = 0;
        break;
    case 1:
        txRateEncodedValue = 1;
        break;
    case 2:
        txRateEncodedValue = 2;
        break;
    case 4:
        txRateEncodedValue = 3;
        break;
    case 8:
        txRateEncodedValue = 4;
        break;
    case 16:
        txRateEncodedValue = 5;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         serializerCfg->rate,
                         "Invalid tx rate (final divider) value");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        if (laneSelMask == 0)
        {
            break; /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        /* set cpll ref clk */
        strIdx = 0;
        if (serializerSetFct[i].CpllRefClkSelBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].CpllRefClkSelBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    serializerCfg->cpllRefClkSel);
            serializerErrStr[strIdx][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set channel clk */
        strIdx++;
        if (serializerSetFct[i].TxPllClkSelBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPllClkSelBfSet(device,
                                                                  FPGA9025_BF_ADS9_JESD_PHY,
                                                                  serializerCfg->txPllClkSel);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set channel final divider */
        strIdx++;
        if (serializerSetFct[i].TxRateBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxRateBfSet(device,
                                                             FPGA9025_BF_ADS9_JESD_PHY,
                                                             txRateEncodedValue);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set polarity */
        strIdx++;
        if (serializerSetFct[i].TxPolarityBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPolarityBfSet(device,
                                                                 FPGA9025_BF_ADS9_JESD_PHY,
                                                                 serializerCfg->polarity);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set precursor */
        strIdx++;
        if (serializerSetFct[i].TxPrecursorBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPrecursorBfSet(device,
                                                                  FPGA9025_BF_ADS9_JESD_PHY,
                                                                  serializerCfg->precursor);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set postcursor */
        strIdx++;
        if (serializerSetFct[i].TxPostcursorBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPostcursorBfSet(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   serializerCfg->postcursor);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set differential control */
        strIdx++;
        if (serializerSetFct[i].TxDiffControlBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxDiffControlBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    serializerCfg->diffCtrl);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set 8b10b enable */
        strIdx++;
        if (serializerSetFct[i].Tx8b10bEnableBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].Tx8b10bEnableBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    serializerCfg->encoder8b10bEnable);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        strIdx++;
        /* clk out select */
        if (serializerSetFct[i].TxClkOutBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxClkOutBfSet(device,
                                                               FPGA9025_BF_ADS9_JESD_PHY,
                                                               serializerCfg->txOutClkSel);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        strIdx++;

        /* bring channel out of power down */
        if (serializerSetFct[i].TxPowerdownBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPowerdownBfSet(device,
                                                                  FPGA9025_BF_ADS9_JESD_PHY,
                                                                  serializerCfg->powerDown);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_SerializerCfgGet(adi_fpga9025_Device_t*        device,
                                      adi_fpga9025_LaneSel_e        laneSel,
                                      adi_fpga9025_SerializerCfg_t* serializerCfg)
{
    int32_t recoveryAction      = ADI_COMMON_ACT_NO_ACTION;
    uint8_t txPllClkSelReadBack = 0;
    uint8_t txRateEncodedValue  = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        serializerCfg);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    char serializerErrStr[][64] = {
        "Error reading channel 0 cpll ref clk",
        "Error reading channel 0 tx pll clk sel",
        "Error reading channel 0 tx rate (final divider)",
        "Error reading channel 0 tx polarity",
        "Error reading channel 0 tx precursor",
        "Error reading channel 0 tx postcursor",
        "Error reading channel 0 tx diffCtrl",
        "Error reading channel 0 tx encoder8b10bEnable",
        "Error setting channel 0 tx clk out",
        "Error reading channel 0 tx powerDown"
    };
    uint32_t laneNumPos = 22;

    typedef struct
    {
        int32_t (*CpllRefClkSelBf)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t*                            );

        int32_t (*TxPllClkSelBf)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );

        int32_t (*TxRateBf)(adi_fpga9025_Device_t*              device,
                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                            uint8_t*                            );

        int32_t (*TxPolarityBf)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t*                            );

        int32_t (*TxPrecursorBf)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );

        int32_t (*TxPostcursorBf)(adi_fpga9025_Device_t*              device,
                                  fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                  uint8_t*                            );

        int32_t (*TxDiffControlBf)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t*                            );

        int32_t (*Tx8b10bEnableBf)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t*                            );

        int32_t (*TxClkOutBf)(adi_fpga9025_Device_t*              device,
                              fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                              uint8_t*                            );

        int32_t (*TxPowerdownBf)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );
    } fpgaSerializerGet_t;

    fpgaSerializerGet_t serializerGetFct[] = {
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel0CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel0TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel0TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel0TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel0TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel0TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel0TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel0Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel0TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel0TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel1CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel1TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel1TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel1TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel1TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel1TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel1TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel1Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel1TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel1TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel2CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel2TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel2TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel2TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel2TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel2TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel2TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel2Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel2TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel2TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel3CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel3TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel3TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel3TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel3TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel3TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel3TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel3Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel3TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel3TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel4CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel4TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel4TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel4TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel4TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel4TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel4TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel4Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel4TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel4TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel5CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel5TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel5TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel5TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel5TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel5TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel5TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel5Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel5TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel5TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel6CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel6TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel6TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel6TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel6TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel6TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel6TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel6Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel6TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel6TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9025_Jesd204PhyAds9Channel7CpllRefClkSelBfGet,
            .TxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel7TxPllClkSelBfGet,
            .TxRateBf = fpga9025_Jesd204PhyAds9Channel7TxRateBfGet,
            .TxPolarityBf = fpga9025_Jesd204PhyAds9Channel7TxPolarityBfGet,
            .TxPrecursorBf = fpga9025_Jesd204PhyAds9Channel7TxPrecursorBfGet,
            .TxPostcursorBf = fpga9025_Jesd204PhyAds9Channel7TxPostcursorBfGet,
            .TxDiffControlBf = fpga9025_Jesd204PhyAds9Channel7TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel7Tx8b10bEnableBfGet,
            .TxClkOutBf = fpga9025_Jesd204PhyAds9Channel7TxOutClkSelBfGet,
            .TxPowerdownBf = fpga9025_Jesd204PhyAds9Channel7TxPowerdownBfGet
        }
    };
    uint32_t laneIdx = 0;

    switch (laneSel)
    {
    case ADI_FPGA9025_LANE_0:
        laneIdx = 0;
        break;
    case ADI_FPGA9025_LANE_1:
        laneIdx = 1;
        break;
    case ADI_FPGA9025_LANE_2:
        laneIdx = 2;
        break;
    case ADI_FPGA9025_LANE_3:
        laneIdx = 3;
        break;
    case ADI_FPGA9025_LANE_4:
        laneIdx = 4;
        break;
    case ADI_FPGA9025_LANE_5:
        laneIdx = 5;
        break;
    case ADI_FPGA9025_LANE_6:
        laneIdx = 6;
        break;
    case ADI_FPGA9025_LANE_7:
        laneIdx = 7;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         laneSelMask,
                         "Invalid lane selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    /* Get cpll ref clk */
    if (serializerGetFct[laneIdx].CpllRefClkSelBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].CpllRefClkSelBf(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &serializerCfg->cpllRefClkSel);
        serializerErrStr[0][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get channel clk */
    if (serializerGetFct[laneIdx].TxPllClkSelBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPllClkSelBf(device,
                                                                 FPGA9025_BF_ADS9_JESD_PHY,
                                                                 &txPllClkSelReadBack);
        serializerErrStr[1][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        serializerCfg->txPllClkSel = (adi_fpga9025_LaneClkSel_e)txPllClkSelReadBack;
    }

    /* Get channel final divider */
    if (serializerGetFct[laneIdx].TxRateBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxRateBf(device,
                                                            FPGA9025_BF_ADS9_JESD_PHY,
                                                            &txRateEncodedValue);
        serializerErrStr[2][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[2]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        if (txRateEncodedValue > 5)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             NULL,
                             "Invalid tx rate (final divider) value read from FPGA");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        serializerCfg->rate = (1 << txRateEncodedValue) / 2;
    }

    /* Get polarity */
    if (serializerGetFct[laneIdx].TxPolarityBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPolarityBf(device,
                                                                FPGA9025_BF_ADS9_JESD_PHY,
                                                                &serializerCfg->polarity);
        serializerErrStr[3][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[3]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get precursor */
    if (serializerGetFct[laneIdx].TxPrecursorBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPrecursorBf(device,
                                                                 FPGA9025_BF_ADS9_JESD_PHY,
                                                                 &serializerCfg->precursor);
        serializerErrStr[4][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[4]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get postcursor */
    if (serializerGetFct[laneIdx].TxPostcursorBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPostcursorBf(device,
                                                                  FPGA9025_BF_ADS9_JESD_PHY,
                                                                  &serializerCfg->postcursor);
        serializerErrStr[5][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[5]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get differential control */
    if (serializerGetFct[laneIdx].TxDiffControlBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxDiffControlBf(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &serializerCfg->diffCtrl);
        serializerErrStr[6][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[6]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get 8b10b enable */
    if (serializerGetFct[laneIdx].Tx8b10bEnableBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].Tx8b10bEnableBf(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &serializerCfg->encoder8b10bEnable);
        serializerErrStr[7][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[7]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get power down status */
    if (serializerGetFct[laneIdx].TxClkOutBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxClkOutBf(device,
                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                              &serializerCfg->txOutClkSel);
        serializerErrStr[8][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[8]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get power down status */
    if (serializerGetFct[laneIdx].TxPowerdownBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPowerdownBf(device,
                                                                 FPGA9025_BF_ADS9_JESD_PHY,
                                                                 &serializerCfg->powerDown);
        serializerErrStr[9][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)serializerErrStr[9]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_SerializerResetSet(adi_fpga9025_Device_t* device,
                                        uint8_t                laneSelMask,
                                        uint8_t                resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    char serializerErrStr[][64] = {
        "Error resetting channel 0 tx"
    };
    uint32_t laneNumPos = 24;

    typedef struct
    {
        int32_t (*TxResetBfSet)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t                             );
    } fpgaTxResetSet_t;

    fpgaTxResetSet_t txResetSetFct[] = {
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel0TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel1TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel2TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel3TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel4TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel5TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel6TxResetBfSet},
        {.TxResetBfSet = fpga9025_Jesd204PhyAds9Channel7TxResetBfSet}
    };
    int32_t i         = 0;
    int32_t selectBit = 0;
    int32_t loopCnt   = sizeof(txResetSetFct) / sizeof(fpgaTxResetSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_fpga9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break; /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (txResetSetFct[i].TxResetBfSet != NULL)
        {
            recoveryAction = txResetSetFct[i].TxResetBfSet(device,
                                                           FPGA9025_BF_ADS9_JESD_PHY,
                                                           (resetVal & 0x01));
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_SerializerResetDoneGet(adi_fpga9025_Device_t* device,
                                            uint8_t*               txResetDone)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t resetBitRead   = 0;

    char serializerErrStr[][64] = {
        "Error resetting channel 0 tx"
    };
    uint32_t laneNumPos = 24;

    typedef struct
    {
        int32_t (*TxResetBfGet)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t*                            );
    } fpgaTxResetSet_t;

    fpgaTxResetSet_t txResetGetFct[] = {
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel0TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel1TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel2TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel3TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel4TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel5TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel6TxResetDoneBfGet},
        {.TxResetBfGet = fpga9025_Jesd204PhyAds9Channel7TxResetDoneBfGet}
    };
    int32_t i       = 0;
    int32_t loopCnt = sizeof(txResetGetFct) / sizeof(fpgaTxResetSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        txResetDone);

#if ADI_fpga9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    *txResetDone = 0;

    for (i = 0; i < loopCnt; i++)
    {
        if (txResetGetFct[i].TxResetBfGet != NULL)
        {
            recoveryAction = txResetGetFct[i].TxResetBfGet(device,
                                                           FPGA9025_BF_ADS9_JESD_PHY,
                                                           &resetBitRead);
            *txResetDone |= (uint8_t)(resetBitRead << i);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_LaneCpllPdSet(adi_fpga9025_Device_t* device,
                                   uint8_t                laneSelMask,
                                   uint8_t                pdVal)
{
    UNUSED_PARA(device);
    UNUSED_PARA(laneSelMask);
    UNUSED_PARA(pdVal);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    return recoveryAction;
}

int32_t adi_fpga9025_DeserializerCfgSet(adi_fpga9025_Device_t*          device,
                                        uint8_t                         laneSelMask,
                                        adi_fpga9025_DeserializerCfg_t* deserializerCfg)
{
    int32_t recoveryAction     = ADI_COMMON_ACT_NO_ACTION;
    uint8_t rxRateEncodedValue = 0;

    int32_t i         = 0;
    int32_t selectBit = 0;

    char deserializerErrStr[][64] = {
        "Error setting channel 0 rx pll clk sel",
        "Error setting channel 0 rx rate (final divider)",
        "Error setting channel 0 rx polarity",
        "Error setting channel 0 rx encoder8b10bEnable",
        "Error setting channel 0 rx DFE/LPMr",
        "Error setting channel 0 rx clock out",
        "Error setting channel 0 rx power down"
    };
    uint32_t laneNumPos = 22;

    typedef struct
    {
        int32_t (*RxPllClkSelBfSet)(adi_fpga9025_Device_t*              device,
                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                    uint8_t                             );

        int32_t (*RxRateBfSet)(adi_fpga9025_Device_t*              device,
                               fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                               uint8_t                             );

        int32_t (*RxPolarityBfSet)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t                             );

        int32_t (*Rx8b10bEnableBfSet)(adi_fpga9025_Device_t*              device,
                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                      uint8_t                             );

        int32_t (*RxDfeLpmEnBfSet)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t                             );

        int32_t (*RxOutClkSelBfSet)(adi_fpga9025_Device_t*              device,
                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                    uint8_t                             );

        int32_t (*RxPowerdownBfSet)(adi_fpga9025_Device_t*              device,
                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                    uint8_t                             );
    } fpgaDeserializerSet_t;

    fpgaDeserializerSet_t deserializerSetFct[] = {
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel0RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel0RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel0RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel0Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel0RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel0RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel0RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel1RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel1RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel1RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel1Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel1RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel1RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel1RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel2RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel2RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel2RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel2Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel2RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel2RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel2RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel3RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel3RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel3RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel3Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel3RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel3RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel3RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel4RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel4RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel4RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel4Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel4RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel4RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel4RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel5RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel5RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel5RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel5Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel5RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel5RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel5RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel6RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel6RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel6RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel6Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel6RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel6RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel6RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet = fpga9025_Jesd204PhyAds9Channel7RxPllClkSelBfSet,
            .RxRateBfSet = fpga9025_Jesd204PhyAds9Channel7RxRateBfSet,
            .RxPolarityBfSet = fpga9025_Jesd204PhyAds9Channel7RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9025_Jesd204PhyAds9Channel7Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet = fpga9025_Jesd204PhyAds9Channel7RxDfeLpmEnBfSet,
            .RxOutClkSelBfSet = fpga9025_Jesd204PhyAds9Channel7RxOutClkSelBfSet,
            .RxPowerdownBfSet = fpga9025_Jesd204PhyAds9Channel7RxPowerdownBfSet
        }
    };

    uint32_t strIdx = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deserializerCfg);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    switch (deserializerCfg->rate)
    {
    case 0:
        rxRateEncodedValue = 0;
        break;
    case 1:
        rxRateEncodedValue = 1;
        break;
    case 2:
        rxRateEncodedValue = 2;
        break;
    case 4:
        rxRateEncodedValue = 3;
        break;
    case 8:
        rxRateEncodedValue = 4;
        break;
    case 16:
        rxRateEncodedValue = 5;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deserializerCfg->rate,
                         "Invalid rx rate (final divider) value");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        if (laneSelMask == 0)
        {
            break; /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        /* set channel clk */
        strIdx = 0;
        if (deserializerSetFct[i].RxPllClkSelBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxPllClkSelBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    deserializerCfg->rxPllClkSel);
            deserializerErrStr[strIdx][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set channel final divider */
        strIdx++;
        if (deserializerSetFct[i].RxRateBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxRateBfSet(device,
                                                               FPGA9025_BF_ADS9_JESD_PHY,
                                                               rxRateEncodedValue);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set polarity */
        strIdx++;
        if (deserializerSetFct[i].RxPolarityBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxPolarityBfSet(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   deserializerCfg->polarity);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set 8b10b enable */
        strIdx++;
        if (deserializerSetFct[i].Rx8b10bEnableBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].Rx8b10bEnableBfSet(device,
                                                                      FPGA9025_BF_ADS9_JESD_PHY,
                                                                      deserializerCfg->encoder8b10bEnable);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set dfe_lpm enable */
        strIdx++;
        if (deserializerSetFct[i].RxDfeLpmEnBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxDfeLpmEnBfSet(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   deserializerCfg->rxDfeLpmEn);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set rx clk out */
        strIdx++;
        if (deserializerSetFct[i].RxOutClkSelBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxOutClkSelBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    deserializerCfg->rxOutClkSel);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* bring channel out of power down */
        strIdx++;
        if (deserializerSetFct[i].RxPowerdownBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxPowerdownBfSet(device,
                                                                    FPGA9025_BF_ADS9_JESD_PHY,
                                                                    deserializerCfg->powerDown);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeserializerCfgGet(adi_fpga9025_Device_t*          device,
                                        const adi_fpga9025_LaneSel_e    laneSel,
                                        adi_fpga9025_DeserializerCfg_t* deserializerCfg)
{
    int32_t recoveryAction      = ADI_COMMON_ACT_NO_ACTION;
    uint8_t rxPllClkSelReadBack = 0;
    uint8_t rxRateEncodedValue  = 0;

    char deserializerErrStr[][64] = {
        "Error reading channel 0 rx pll clk sel",
        "Error reading channel 0 rx rate (final divider)",
        "Error reading channel 0 rx polarity",
        "Error reading channel 0 rx encoder8b10bEnable",
        "Error reading channel 0 rx DFE/LPM",
        "Error setting channel 0 rx clock out",
        "Error reading channel 0 rx power down"
    };
    uint32_t laneNumPos = 22;

    typedef struct
    {
        int32_t (*RxPllClkSelBf)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );

        int32_t (*RxRateBf)(adi_fpga9025_Device_t*              device,
                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                            uint8_t*                            );

        int32_t (*RxPolarityBf)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t*                            );

        int32_t (*Rx8b10bEnableBf)(adi_fpga9025_Device_t*              device,
                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                   uint8_t*                            );

        int32_t (*RxDfeLpmEnBf)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t*                            );

        int32_t (*RxOutClkSelBf)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );

        int32_t (*RxPowerdownBf)(adi_fpga9025_Device_t*              device,
                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                 uint8_t*                            );
    } fpgaDeserializerGet_t;

    fpgaDeserializerGet_t deserializerGetFct[] = {
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel0RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel0RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel0RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel0Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel0RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel0RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel0RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel1RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel1RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel1RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel1Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel1RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel1RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel1RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel2RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel2RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel2RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel2Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel2RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel2RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel2RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel3RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel3RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel3RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel3Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel3RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel3RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel3RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel4RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel4RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel4RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel4Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel4RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel4RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel4RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel5RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel5RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel5RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel5Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel5RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel5RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel5RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel6RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel6RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel6RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel6Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel6RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel6RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel6RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf = fpga9025_Jesd204PhyAds9Channel7RxPllClkSelBfGet,
            .RxRateBf = fpga9025_Jesd204PhyAds9Channel7RxRateBfGet,
            .RxPolarityBf = fpga9025_Jesd204PhyAds9Channel7RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9025_Jesd204PhyAds9Channel7Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf = fpga9025_Jesd204PhyAds9Channel7RxDfeLpmEnBfGet,
            .RxOutClkSelBf = fpga9025_Jesd204PhyAds9Channel7RxOutClkSelBfGet,
            .RxPowerdownBf = fpga9025_Jesd204PhyAds9Channel7RxPowerdownBfGet
        }
    };
    uint32_t laneIdx = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deserializerCfg);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    switch (laneSel)
    {
    case ADI_FPGA9025_LANE_0:
        laneIdx = 0;
        break;
    case ADI_FPGA9025_LANE_1:
        laneIdx = 1;
        break;
    case ADI_FPGA9025_LANE_2:
        laneIdx = 2;
        break;
    case ADI_FPGA9025_LANE_3:
        laneIdx = 3;
        break;
    case ADI_FPGA9025_LANE_4:
        laneIdx = 4;
        break;
    case ADI_FPGA9025_LANE_5:
        laneIdx = 5;
        break;
    case ADI_FPGA9025_LANE_6:
        laneIdx = 6;
        break;
    case ADI_FPGA9025_LANE_7:
        laneIdx = 7;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         laneSel,
                         "Invalid lane selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    /* Get channel clk */
    if (deserializerGetFct[laneIdx].RxPllClkSelBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxPllClkSelBf(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &rxPllClkSelReadBack);
        deserializerCfg->rxPllClkSel      = (adi_fpga9025_LaneClkSel_e)rxPllClkSelReadBack;
        deserializerErrStr[0][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get channel final divider */
    if (deserializerGetFct[laneIdx].RxRateBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxRateBf(device,
                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                              &rxRateEncodedValue);
        deserializerErrStr[1][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        if (rxRateEncodedValue > 5)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             NULL,
                             "Invalid rx rate (final divider) value read from FPGA");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        deserializerCfg->rate = (1 << rxRateEncodedValue) / 2;
    }

    /* Get polarity */
    if (deserializerGetFct[laneIdx].RxPolarityBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxPolarityBf(device,
                                                                  FPGA9025_BF_ADS9_JESD_PHY,
                                                                  &deserializerCfg->polarity);
        deserializerErrStr[2][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[2]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get 8b10b enable */
    if (deserializerGetFct[laneIdx].Rx8b10bEnableBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].Rx8b10bEnableBf(device,
                                                                     FPGA9025_BF_ADS9_JESD_PHY,
                                                                     &deserializerCfg->encoder8b10bEnable);
        deserializerErrStr[3][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[3]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* set dfe_lpm enable */
    if (deserializerGetFct[laneIdx].RxDfeLpmEnBf != NULL)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel0RxDfeLpmEnBfGet(device,
                                                                        FPGA9025_BF_ADS9_JESD_PHY,
                                                                        &deserializerCfg->rxDfeLpmEn);
        deserializerErrStr[4][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[4]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* reading rx clk out */
    if (deserializerGetFct[laneIdx].RxOutClkSelBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxOutClkSelBf(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &deserializerCfg->rxOutClkSel);
        deserializerErrStr[5][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[5]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* bring channel out of power down */
    if (deserializerGetFct[laneIdx].RxPowerdownBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxPowerdownBf(device,
                                                                   FPGA9025_BF_ADS9_JESD_PHY,
                                                                   &deserializerCfg->powerDown);
        deserializerErrStr[6][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         (const char *)deserializerErrStr[6]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeserializerResetSet(adi_fpga9025_Device_t* device,
                                          uint8_t                laneSelMask,
                                          uint8_t                resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    char deserializerErrStr[][64] = {
        "Error resetting channel 0 Rx"
    };
    uint32_t laneNumPos = 24;

    typedef struct
    {
        int32_t (*RxResetBfSet)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t                             );
    } fpgaRxResetSet_t;

    fpgaRxResetSet_t RxResetSetFct[] = {
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel0RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel1RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel2RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel3RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel4RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel5RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel6RxResetBfSet},
        {.RxResetBfSet = fpga9025_Jesd204PhyAds9Channel7RxResetBfSet}
    };
    int32_t i         = 0;
    int32_t selectBit = 0;
    int32_t loopCnt   = sizeof(RxResetSetFct) / sizeof(fpgaRxResetSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_fpga9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break; /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (RxResetSetFct[i].RxResetBfSet != NULL)
        {
            recoveryAction = RxResetSetFct[i].RxResetBfSet(device,
                                                           FPGA9025_BF_ADS9_JESD_PHY,
                                                           (resetVal & 0x01));
            deserializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeserializerResetDoneGet(adi_fpga9025_Device_t* device,
                                              uint8_t*               rxResetDone)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t resetBitRead   = 0;

    char deserializerErrStr[][64] = {
        "Error resetting channel 0 rx"
    };
    uint32_t laneNumPos = 24;

    typedef struct
    {
        int32_t (*RxResetBfGet)(adi_fpga9025_Device_t*              device,
                                fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                uint8_t*                            );
    } fpgaRxResetSet_t;

    fpgaRxResetSet_t rxResetGetFct[] = {
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel0RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel1RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel2RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel3RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel4RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel5RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel6RxResetDoneBfGet},
        {.RxResetBfGet = fpga9025_Jesd204PhyAds9Channel7RxResetDoneBfGet}
    };
    int32_t i       = 0;
    int32_t loopCnt = sizeof(rxResetGetFct) / sizeof(fpgaRxResetSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        rxResetDone);

#if ADI_fpga9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    *rxResetDone = 0;

    for (i = 0; i < loopCnt; i++)
    {
        if (rxResetGetFct[i].RxResetBfGet != NULL)
        {
            recoveryAction = rxResetGetFct[i].RxResetBfGet(device,
                                                           FPGA9025_BF_ADS9_JESD_PHY,
                                                           &resetBitRead);
            *rxResetDone |= (uint8_t)(resetBitRead << i);
            deserializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             (const char *)deserializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeframerCfgSet(adi_fpga9025_Device_t*      device,
                                    uint32_t                    deframerSelMask,
                                    adi_fpga9025_DeframerCfg_t* deframerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deframerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BDeframerCfgSet(device,
                                                         deframerSelMask,
                                                         deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CDeframerCfgSet(device,
                                                         deframerSelMask,
                                                         deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeframerCfgGet(adi_fpga9025_Device_t*      device,
                                    adi_fpga9025_DeframerSel_e  deframerSel,
                                    adi_fpga9025_DeframerCfg_t* deframerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deframerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BDeframerCfgGet(device,
                                                         deframerSel,
                                                         deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CDeframerCfgGet(device,
                                                         deframerSel,
                                                         deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeframerResetGet(adi_fpga9025_Device_t* device,
                                      uint32_t               deframerSelMask,
                                      uint8_t*               resetBits)
{
    UNUSED_PARA(device);
    UNUSED_PARA(deframerSelMask);
    UNUSED_PARA(resetBits);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    //    //uint8_t resetGet = 0;
    //
    //#if ADI_FPGA9025_VERBOSE > 0
    //    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
    //#endif
    //
    return recoveryAction;
}

int32_t adi_fpga9025_FramerCfgSet(adi_fpga9025_Device_t*    device,
                                  uint8_t                   framerSelMask,
                                  adi_fpga9025_FramerCfg_t* framerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        framerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BFramerCfgSet(device,
                                                       framerSelMask,
                                                       framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CFramerCfgSet(device,
                                                       framerSelMask,
                                                       framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_FramerCfgGet(adi_fpga9025_Device_t*    device,
                                  adi_fpga9025_FramerSel_e  framerSel,
                                  adi_fpga9025_FramerCfg_t* framerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        framerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BFramerCfgGet(device,
                                                       framerSel,
                                                       framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CFramerCfgGet(device,
                                                       framerSel,
                                                       framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_FramerResetGet(adi_fpga9025_Device_t* device,
                                    uint32_t               framerSelMask,
                                    uint8_t*               resetBits)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        resetBits);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BFramerResetGet(device,
                                                         framerSelMask,
                                                         resetBits);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CFramerResetGet(device,
                                                         framerSelMask,
                                                         resetBits);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxLaneXBarCfgSet(adi_fpga9025_Device_t*   device,
                                      adi_fpga9025_FramerSel_e framerSel,
                                      uint8_t*                 laneXBar)
{
    int32_t                                recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfJesd204TxLaneXbarChanAddr_e baseAddr       = FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        laneXBar);

    /* Set correct addresses for the framer selected */
    if (framerSel == ADI_FPGA9025_FRAMER_0)
    {
        baseAddr = FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_0;
    }
    else if (framerSel == ADI_FPGA9025_FRAMER_1)
    {
        baseAddr = FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_1;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSel,
                         "Invalid framer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane0SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 0 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane1SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[1]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 1 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane2SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[2]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 2 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane3SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[3]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 3 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane4SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[4]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 4 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane5SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[5]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 5 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane6SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[6]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 6 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane7SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[7]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 7 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxLaneXBarCfgSet(adi_fpga9025_Device_t*     device,
                                      adi_fpga9025_DeframerSel_e deframerSel,
                                      uint8_t*                   laneXBar)
{
    int32_t                                recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfJesd204RxLaneXbarChanAddr_e baseAddr       = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        laneXBar);

    /* Set correct addresses for the deframer selected */
    if (deframerSel == ADI_FPGA9025_DEFRAMER_0)
    {
        baseAddr = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_0;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_1)
    {
        baseAddr = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_1;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_2)
    {
        baseAddr = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_2;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSel,
                         "Invalid deframer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane0SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 0 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane1SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[1]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 1 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane2SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[2]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 2 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane3SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[3]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 3 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane4SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[4]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 4 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane5SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[5]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 5 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane6SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[6]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 6 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane7SelectBfSet(device,
                                                                baseAddr,
                                                                laneXBar[7]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 7 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxLaneXBarCfgGet(adi_fpga9025_Device_t*   device,
                                      adi_fpga9025_FramerSel_e framerSel,
                                      uint8_t*                 laneXBar)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t baseAddr       = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        laneXBar);

    /* Set correct addresses for the framer selected */
    if (framerSel == ADI_FPGA9025_FRAMER_0)
    {
        baseAddr = FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_0;
    }
    else if (framerSel == ADI_FPGA9025_FRAMER_1)
    {
        baseAddr = FPGA9025_BF_JESD204_TX_LANE_XBAR_LINK_1;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSel,
                         "Invalid framer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane0SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 0 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane1SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[1]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 1 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane2SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[2]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 2 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane3SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[3]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 3 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane4SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[4]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 4 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane5SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[5]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 5 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane6SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[6]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 6 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204TxLaneXbarLane7SelectBfGet(device,
                                                                (fpga9025_BfJesd204TxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[7]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 7 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RxLaneXBarCfgGet(adi_fpga9025_Device_t*     device,
                                      adi_fpga9025_DeframerSel_e deframerSel,
                                      uint8_t*                   laneXBar)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t baseAddr       = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        laneXBar);

    /* Set correct addresses for the deframer selected */
    if (deframerSel == ADI_FPGA9025_DEFRAMER_0)
    {
        baseAddr = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_0;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_1)
    {
        baseAddr = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_1;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_2)
    {
        baseAddr = FPGA9025_BF_JESD204_RX_LANE_XBAR_LINK_2;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSel,
                         "Invalid deframer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane0SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 0 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane1SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[1]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 1 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane2SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[2]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 2 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane3SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[3]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 3 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane4SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[4]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 4 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane5SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[5]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 5 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane6SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[6]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 6 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204RxLaneXbarLane7SelectBfGet(device,
                                                                (fpga9025_BfJesd204RxLaneXbarChanAddr_e)baseAddr,
                                                                &laneXBar[7]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading Lane 7 configuration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_FramerReset(adi_fpga9025_Device_t* device,
                                 uint8_t                framerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BFramerReset(device,
                                                      framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CFramerReset(device,
                                                      framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_FramerDisable(adi_fpga9025_Device_t* device,
                                   uint8_t                framerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BFramerDisable(device,
                                                        framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CFramerDisable(device,
                                                        framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeframerReset(adi_fpga9025_Device_t* device,
                                   uint8_t                deframerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BDeframerReset(device,
                                                        deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CDeframerReset(device,
                                                        deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeframerDisable(adi_fpga9025_Device_t* device,
                                     uint8_t                deframerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BDeframerDisable(device,
                                                          deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CDeframerDisable(device,
                                                          deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_DeframerStatusGet(adi_fpga9025_Device_t* device,
                                       uint8_t                deframerSelMask,
                                       uint8_t*               status)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9025_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204BDeframerStatusGet(device,
                                                            deframerSelMask,
                                                            status);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else if (device->devStateInfo.designId == ADI_FPGA9025_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9025_Jesd204CDeframerStatusGet(device,
                                                            deframerSelMask,
                                                            status);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_ChannelLoopbackEnable(adi_fpga9025_Device_t* device,
                                           uint8_t                laneSelMask,
                                           uint8_t                loopbackValue)
{
    UNUSED_PARA(device);
    UNUSED_PARA(laneSelMask);
    UNUSED_PARA(loopbackValue);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    //
    //    ADI_NULL_DEVICE_PTR_RETURN(device);
    //
    //#if ADI_FPGA9025_VERBOSE > 0
    //    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
    //#endif
    //    
    //    if ((laneSelMask & ADI_FPGA9025_LANE_0) == ADI_FPGA9025_LANE_0)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel0LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for channel 0");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_1) == ADI_FPGA9025_LANE_1)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel1LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for  channel 1");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_2) == ADI_FPGA9025_LANE_2)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel2LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resettingsetting loopback for  channel 2");
    //        ADI_ERROR_RETURN(device->common.error.newAction);  
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_3) == ADI_FPGA9025_LANE_3)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel3LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for  channel 3");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_4) == ADI_FPGA9025_LANE_4)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel4LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for  channel 4");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_5) == ADI_FPGA9025_LANE_5)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel5LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for  channel 5");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_6) == ADI_FPGA9025_LANE_6)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel6LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for  channel 6");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    if ((laneSelMask & ADI_FPGA9025_LANE_7) == ADI_FPGA9025_LANE_7)
    //    {
    //        recoveryAction = fpga9025_Jesd204PhyAds9Channel7LoopbackBfSet(device, FPGA9025_BF_ADS9_JESD_PHY, (loopbackValue & 0x07));
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loopback for  channel 7");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    
    return recoveryAction;
}

int32_t adi_fpga9025_ChannelDfeLpmOverrideSet(adi_fpga9025_Device_t* device,
                                              uint8_t                laneSelMask,
                                              uint8_t                value)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    if (laneSelMask == ADI_FPGA9025_ZERO)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         laneSelMask,
                         "Error laneSelMask cannot be zero");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_0) == ADI_FPGA9025_LANE_0)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel0RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for channel 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_1) == ADI_FPGA9025_LANE_1)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel1RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for  channel 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_2) == ADI_FPGA9025_LANE_2)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel2RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error resettingsetting RxDfeLpmOverride for  channel 2");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_3) == ADI_FPGA9025_LANE_3)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel3RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for  channel 3");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_4) == ADI_FPGA9025_LANE_4)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel4RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for  channel 4");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_5) == ADI_FPGA9025_LANE_5)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel5RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for  channel 5");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_6) == ADI_FPGA9025_LANE_6)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel6RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for  channel 6");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((laneSelMask & ADI_FPGA9025_LANE_7) == ADI_FPGA9025_LANE_7)
    {
        recoveryAction = fpga9025_Jesd204PhyAds9Channel7RxDfeLpmOverrideBfSet(device,
                                                                              FPGA9025_BF_ADS9_JESD_PHY,
                                                                              value);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error setting RxDfeLpmOverride for  channel 7");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9025_SyncXBarCfgSet(adi_fpga9025_Device_t* device,
                                    uint8_t                polarity,
                                    uint8_t*               inputSyncSel)
{
    int32_t  recoveryAction         = ADI_COMMON_ACT_NO_ACTION;
    uint8_t  maxIndex               = ADI_FPGA9025_NUM_OF_DEFRAMERS + ADI_FPGA9025_NUM_OF_FRAMERS;
    char     serializerErrStr[][64] = {"Error setting output sync 0 configuration"};
    uint32_t laneNumPos             = 26;

    typedef struct
    {
        int32_t (*SyncXbarSyncOutSelectBfSet)(adi_fpga9025_Device_t*                device,
                                              fpga9025_BfJesd204bSyncXbarChanAddr_e baseAddr,
                                              uint8_t                               );
    } fpgaSyncXbarSyncOutSelectBfSet_t;

    fpgaSyncXbarSyncOutSelectBfSet_t syncXbarSyncOutSelectBfSetFct[] = {
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut0SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut1SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut2SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut3SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut4SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut5SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut6SelectBfSet},
        {.SyncXbarSyncOutSelectBfSet = fpga9025_Jesd204bSyncXbarSyncOut7SelectBfSet}
    };
    int32_t i       = 0;
    int32_t loopCnt = sizeof(syncXbarSyncOutSelectBfSetFct) / sizeof(fpgaSyncXbarSyncOutSelectBfSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        inputSyncSel);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (syncXbarSyncOutSelectBfSetFct[i].SyncXbarSyncOutSelectBfSet != NULL)
        {
            if (maxIndex > 0)
            {
                recoveryAction = syncXbarSyncOutSelectBfSetFct[i].SyncXbarSyncOutSelectBfSet(device,
                                                                                             FPGA9025_BF_JESD204B_SYNC_XBAR,
                                                                                             inputSyncSel[i]);
                serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_INV_PARAM,
                                 recoveryAction,
                                 NULL,
                                 (const char *)serializerErrStr[0]);
                ADI_ERROR_RETURN(device->common.error.newAction);
                maxIndex--;
            }
            else
            {
                break;
            }
        }
    }

    recoveryAction = fpga9025_Jesd204bSyncXbarSyncInPolarityBfSet(device,
                                                                  FPGA9025_BF_JESD204B_SYNC_XBAR,
                                                                  polarity);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting sync xbar polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_SyncXBarCfgGet(adi_fpga9025_Device_t* device,
                                    uint8_t*               polarity,
                                    uint8_t*               inputSyncSel)
{
    int32_t  recoveryAction         = ADI_COMMON_ACT_NO_ACTION;
    uint8_t  maxIndex               = ADI_FPGA9025_NUM_OF_DEFRAMERS + ADI_FPGA9025_NUM_OF_FRAMERS;
    char     serializerErrStr[][64] = {"Error reading output sync 0 configuration"};
    uint32_t laneNumPos             = 26;

    typedef struct
    {
        int32_t (*SyncXbarSyncOutSelectBfGet)(adi_fpga9025_Device_t*                device,
                                              fpga9025_BfJesd204bSyncXbarChanAddr_e baseAddr,
                                              uint8_t*                              );
    } fpgaSyncXbarSyncOutSelectBfGet_t;

    fpgaSyncXbarSyncOutSelectBfGet_t syncXbarSyncOutSelectBfGetFct[] = {
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut0SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut1SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut2SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut3SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut4SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut5SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut6SelectBfGet},
        {.SyncXbarSyncOutSelectBfGet = fpga9025_Jesd204bSyncXbarSyncOut7SelectBfGet}
    };
    int32_t i       = 0;
    int32_t loopCnt = sizeof(syncXbarSyncOutSelectBfGetFct) / sizeof(fpgaSyncXbarSyncOutSelectBfGet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        inputSyncSel);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (syncXbarSyncOutSelectBfGetFct[i].SyncXbarSyncOutSelectBfGet != NULL)
        {
            if (maxIndex > 0)
            {
                recoveryAction = syncXbarSyncOutSelectBfGetFct[i].SyncXbarSyncOutSelectBfGet(device,
                                                                                             FPGA9025_BF_JESD204B_SYNC_XBAR,
                                                                                             &inputSyncSel[i]);
                serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_INV_PARAM,
                                 recoveryAction,
                                 NULL,
                                 (const char *)serializerErrStr[0]);
                ADI_ERROR_RETURN(device->common.error.newAction);
                maxIndex--;
            }
            else
            {
                break;
            }
        }
    }

    recoveryAction = fpga9025_Jesd204bSyncXbarSyncInPolarityBfGet(device,
                                                                  FPGA9025_BF_JESD204B_SYNC_XBAR,
                                                                  polarity);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error reading sync xbar polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_SysRefControlSet(adi_fpga9025_Device_t*       device,
                                      adi_fpga9025_SysRefClkCfg_t* sysRefCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        sysRefCfg);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204SysrefControlExtSysrefPolarityBfSet(device,
                                                                         FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                         sysRefCfg->externalSysrefPolarity);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting external sysref polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204SysrefControlExtSysrefSampleEdgeBfSet(device,
                                                                           FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                           sysRefCfg->externalSysrefSampleEdge);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting external sysref sample edge");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefEnableBfSet(device,
                                                                       FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                       sysRefCfg->internalSysrefEnable);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting internal sysref enable");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write (actual value) - 1 to register */
    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefGenPeriodBfSet(device,
                                                                          FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                          sysRefCfg->internalSysRefGeneratorFrequency - 1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting internal sysref generator");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_SysRefControlGet(adi_fpga9025_Device_t*       device,
                                      adi_fpga9025_SysRefClkCfg_t* sysRefCfg)
{
    UNUSED_PARA(device);
    UNUSED_PARA(sysRefCfg);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    //
    //    ADI_NULL_DEVICE_PTR_RETURN(device);
    //
    //    ADI_NULL_PTR_RETURN(&device->common, sysRefCfg);
    //
    //#if ADI_FPGA9025_VERBOSE > 0
    //    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
    //#endif
    //
    //    recoveryAction = fpga9025_Jesd204SysrefControlExtSysrefPolarityBfGet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->externalSysrefPolarity);
    //    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref polarity");
    //    ADI_ERROR_RETURN(device->common.error.newAction);
    //
    //    recoveryAction = fpga9025_Jesd204SysrefControlExtSysrefSampleEdgeBfGet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->externalSysrefSampleEdge);
    //    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref sample edge");
    //    ADI_ERROR_RETURN(device->common.error.newAction);
    //
    //    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefEnableBfGet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->internalSysrefEnable);
    //    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref enable");
    //    ADI_ERROR_RETURN(device->common.error.newAction);
    //
    //    /* Write (actual value) - 1 to register */
    //    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefGenPeriodBfGet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->internalSysRefGeneratorFrequency);
    //    sysRefCfg->internalSysRefGeneratorFrequency++;
    //    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref generator");
    //    ADI_ERROR_RETURN(device->common.error.newAction);
    //    
    return recoveryAction;
}

//
int32_t adi_fpga9025_SysRefRequest(adi_fpga9025_Device_t* device)
{
    UNUSED_PARA(device);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    //    uint8_t internalSysrefEnable = 0;
    //
    //    ADI_NULL_DEVICE_PTR_RETURN(device);
    //
    //#if ADI_FPGA9025_VERBOSE > 0
    //    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
    //#endif
    //    
    //    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefEnableBfGet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, &internalSysrefEnable);
    //    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading sync xbar polarity");
    //    ADI_ERROR_RETURN(device->common.error.newAction);
    //    
    //    if (internalSysrefEnable == 1)
    //    {
    //        recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefRequestBfSet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, 1);
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref request");
    //        ADI_ERROR_RETURN(device->common.error.newAction);
    //    }
    //    else
    //    {
    //        recoveryAction = fpga9025_Jesd204SysrefControlExtSysrefRequestBfSet(device, FPGA9025_BF_JESD204_SYSREF_CONTROL, 1);
    //        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref request");
    //        ADI_ERROR_RETURN(device->common.error.newAction); 
    //    }
    //    
    return recoveryAction;
}

//
//int32_t adi_fpga9025_SyncbStatus(adi_fpga9025_Device_t *device, uint32_t *status)
//{
//    //TODO: implement this
//    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
//    return recoveryAction;
//}

int32_t adi_fpga9025_Jesd204CDeframerCmdDataSet(adi_fpga9025_Device_t* device,
                                                uint32_t               deframerSelMask,
                                                uint8_t                cmdEnable,
                                                uint8_t                dataEnable)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
    uint32_t                            i               = 0;
    adi_fpga9025_DeframerSel_e          deframerSel     = ADI_FPGA9025_DEFRAMER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (deframerSelMask < ADI_FPGA9025_DEFRAMER_0 || deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_DEFRAMERS; i++)
    {
        deframerSel = (adi_fpga9025_DeframerSel_e)((uint8_t)(1 << i));

        switch (deframerSel)
        {
        case ADI_FPGA9025_DEFRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
            break;
        case ADI_FPGA9025_DEFRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_1;
            break;
        case ADI_FPGA9025_DEFRAMER_2:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_2;
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

        if (((uint32_t)deframerSel & deframerSelMask) > 0)
        {
            recoveryAction = fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet(device,
                                                                            instanceAddress,
                                                                            cmdEnable);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set cmd interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cEnableDataInterfaceBfSet(device,
                                                                             instanceAddress,
                                                                             dataEnable);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set data interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_Jesd204CFramerCmdDataSet(adi_fpga9025_Device_t* device,
                                              uint32_t               framerSelMask,
                                              uint8_t                cmdEnable,
                                              uint8_t                dataEnable)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
    uint32_t                            i               = 0;
    adi_fpga9025_FramerSel_e            framerSel       = ADI_FPGA9025_FRAMER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (framerSelMask < ADI_FPGA9025_FRAMER_0 || framerSelMask > ADI_FPGA9025_FRAMER_ALL)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_FRAMERS; i++)
    {
        framerSel = (adi_fpga9025_FramerSel_e)((uint8_t)(1 << i));

        switch (framerSel)
        {
        case ADI_FPGA9025_FRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
            break;
        case ADI_FPGA9025_FRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_1;
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

        if (((uint32_t)framerSel & framerSelMask) > 0)
        {
            recoveryAction = fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet(device,
                                                                            instanceAddress,
                                                                            cmdEnable);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set cmd interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cEnableDataInterfaceBfSet(device,
                                                                             instanceAddress,
                                                                             dataEnable);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set data interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_SysRefEnableSet(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask,
                                     uint8_t                deframerSelMask,
                                     uint8_t                enable)
{
    int32_t  recoveryAction          = ADI_COMMON_ACT_NO_ACTION;
    uint32_t outputEnableRegisterVal = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204SysrefControlOutputEnableBfGet(device,
                                                                    FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                    &outputEnableRegisterVal);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting output enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Force only the bits we care about */
    framerSelMask   = (ADI_FPGA9025_FRAMER_ALL & framerSelMask);
    deframerSelMask = (ADI_FPGA9025_DEFRAMER_ALL & deframerSelMask);

    if (enable == ADI_ENABLE)
    {
        outputEnableRegisterVal |= (uint32_t)deframerSelMask;
        outputEnableRegisterVal |= (uint32_t)framerSelMask << ADI_FPGA9025_NUM_OF_DEFRAMERS;
    }
    else if (enable == ADI_DISABLE)
    {
        outputEnableRegisterVal &= ~((uint32_t)deframerSelMask);
        outputEnableRegisterVal &= ~((uint32_t)framerSelMask << ADI_FPGA9025_NUM_OF_DEFRAMERS);
    }

    recoveryAction = fpga9025_Jesd204SysrefControlOutputEnableBfSet(device,
                                                                    FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                    outputEnableRegisterVal);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting output enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_InternalSysrefEnableSet(adi_fpga9025_Device_t* device,
                                             uint8_t                enable)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefEnableBfSet(device,
                                                                       FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                       enable);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting internal sysref enable");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_InternalSysrefRequest(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9025_Jesd204SysrefControlIntSysrefRequestBfSet(device,
                                                                        FPGA9025_BF_JESD204_SYSREF_CONTROL,
                                                                        1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     NULL,
                     "Error setting internal sysref request");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}
