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
#include "adi_fpga9010_jesd.h"
#include "adi_fpga9010.h"
#include "../../private/include/fpga9010_bf_jesd204_rx_lane_xbar.h"
#include "../../private/include/fpga9010_bf_jesd204_tx_lane_xbar.h"
#include "../../private/include/fpga9010_bf_xilinx_jesd204b.h"
#include "../../private/include/fpga9010_bf_jesd204_phy_tokelau_ads8.h"
#include "../../private/include/fpga9010_bf_xilinx_jesd204c.h"
#include "../../private/include/fpga9010_bf_jesd204b_sync_xbar.h"
#include "../../private/include/fpga9010_bf_jesd204_sysref_control.h"
#include "../../private/include/fpga9010_bf_jesd204_phy_tokelau_ads8.h"

#include "../../private/include/fpga9010_jesd.h"

int32_t adi_fpga9010_SerializerCfgSet(adi_fpga9010_Device_t *device, uint8_t laneSelMask, adi_fpga9010_SerializerCfg_t *serializerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t txRateEncodedValue = 0;
    int32_t i = 0;
    int32_t selectBit = 0;

    char serializerErrStr[][64] = {
        "Error setting channel 0 cpll ref clk",
        "Error setting channel 0 tx pll clk sel",
        "Error setting channel 0 tx rate (final divider)",
        "Error setting channel 0 tx polarity",
        "Error setting channel 0 tx precursor",
        "Error setting channel 0 tx postcursor",
        "Error setting channel 0 tx diffCtrl",
        "Error setting channel 0 tx encoder8b10bEnable",
        "Error setting channel 0 tx powerDown"
    };
    uint32_t laneNumPos = 22;
        
    typedef struct {
        int32_t (*CpllRefClkSelBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxPllClkSelBfSet)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxRateBfSet)        (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxPolarityBfSet)    (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxPrecursorBfSet)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxPostcursorBfSet)  (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxDiffControlBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*Tx8b10bEnableBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t (*TxPowerdownBfSet)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaSerializerSet_t;
    
    fpgaSerializerSet_t serializerSetFct[] = {
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel0TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel0TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel0TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel0TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel0TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel0TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel1TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel1TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel1TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel1TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel1TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel1TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel2TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel2TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel2TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel2TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel2TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel2TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel3TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel3TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel3TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel3TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel3TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel3TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel4TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel4TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel4TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel4TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel4TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel4TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel5TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel5TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel5TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel5TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel5TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel5TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel6TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel6TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel6TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel6TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel6TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel6TxPowerdownBfSet
        },
        {
            .CpllRefClkSelBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7CpllRefClkSelBfSet,
            .TxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel7TxPllClkSelBfSet,
            .TxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel7TxRateBfSet,
            .TxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel7TxPolarityBfSet,
            .TxPrecursorBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel7TxPrecursorBfSet,
            .TxPostcursorBfSet  = fpga9010_Jesd204PhyTokelauAds8Channel7TxPostcursorBfSet,
            .TxDiffControlBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7TxDiffControlBfSet,
            .Tx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7Tx8b10bEnableBfSet,
            .TxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel7TxPowerdownBfSet
        }
    };

    uint32_t strIdx = 0;


    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, serializerCfg);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
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
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, serializerCfg->rate, "Invalid tx rate (final divider) value");
            ADI_ERROR_RETURN(device->common.error.newAction);
            break;
    }
    
    for (i = 0; i < ADI_FPGA9010_NUM_LANES; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
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
            recoveryAction = serializerSetFct[i].CpllRefClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->cpllRefClkSel);
            serializerErrStr[strIdx][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set channel clk */
        strIdx++;
        if (serializerSetFct[i].TxPllClkSelBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPllClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->txPllClkSel);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set channel final divider */
        strIdx++;
        if (serializerSetFct[i].TxRateBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxRateBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, txRateEncodedValue);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set polarity */
        strIdx++;
        if (serializerSetFct[i].TxPolarityBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPolarityBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->polarity);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set precursor */
        strIdx++;
        if (serializerSetFct[i].TxPrecursorBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPrecursorBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->precursor);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set postcursor */
        strIdx++;
        if (serializerSetFct[i].TxPostcursorBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPostcursorBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->postcursor);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set differential control */
        strIdx++;
        if (serializerSetFct[i].TxDiffControlBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxDiffControlBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->diffCtrl);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        /* set 8b10b enable */
        strIdx++;
        if (serializerSetFct[i].Tx8b10bEnableBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].Tx8b10bEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->encoder8b10bEnable);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        strIdx++;

        /* Write to DRP to set tx clkDiv25 */
        /* Manually shift the data so it falls within the mask bits*/
        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_TXCLK25DIV_ADDRESS, i, serializerCfg->txClk25Div, ADI_FPGA9010_TXCLK25DIV_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_TXPI_CFG3_ADDRESS, i, serializerCfg->txPiCfg3, ADI_FPGA9010_TXPI_CFG3_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
        {
            adi_fpga9010_DrpWrite(device, ADI_FPGA9010_TXPHDLY_CFG1_ADDRESS, i, serializerCfg->txPhdlyCfg1, ADI_FPGA9010_TXPHDLY_CFG1_MASK);
            ADI_ERROR_RETURN(device->common.error.newAction);

            adi_fpga9010_DrpWrite(device, ADI_FPGA9010_TX_PROGDIV_CFG_ADDRESS, i, serializerCfg->txProgdivCfg, ADI_FPGA9010_TX_PROGDIV_CFG_MASK);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* bring channel out of power down */
        if (serializerSetFct[i].TxPowerdownBfSet != NULL)
        {
            recoveryAction = serializerSetFct[i].TxPowerdownBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, serializerCfg->powerDown);
            serializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_SerializerCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_LaneSel_e laneSel, adi_fpga9010_SerializerCfg_t *serializerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t txPllClkSelReadBack = 0;
    uint8_t txRateEncodedValue = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_NULL_PTR_RETURN(&device->common, serializerCfg);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
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
        "Error reading channel 0 tx powerDown"
    };
    uint32_t laneNumPos = 22;

    typedef struct {
        int32_t(*CpllRefClkSelBf) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxPllClkSelBf)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxRateBf)        (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxPolarityBf)    (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxPrecursorBf)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxPostcursorBf)  (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxDiffControlBf) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*Tx8b10bEnableBf) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*TxPowerdownBf)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
    } fpgaSerializerGet_t;

    fpgaSerializerGet_t serializerGetFct[] = {
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel0CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel0TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel0TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel0TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel0TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel0TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel0TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel0Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel0TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel1CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel1TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel1TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel1TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel1TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel1TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel1TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel1Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel1TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel2CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel2TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel2TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel2TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel2TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel2TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel2TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel2Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel2TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel3CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel3TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel3TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel3TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel3TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel3TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel3TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel3Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel3TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel4CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel4TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel4TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel4TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel4TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel4TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel4TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel4Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel4TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel5CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel5TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel5TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel5TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel5TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel5TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel5TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel5Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel5TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel6CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel6TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel6TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel6TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel6TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel6TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel6TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel6Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel6TxPowerdownBfGet
        },
        {
            .CpllRefClkSelBf = fpga9010_Jesd204PhyTokelauAds8Channel7CpllRefClkSelBfGet,
            .TxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel7TxPllClkSelBfGet,
            .TxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel7TxRateBfGet,
            .TxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel7TxPolarityBfGet,
            .TxPrecursorBf   = fpga9010_Jesd204PhyTokelauAds8Channel7TxPrecursorBfGet,
            .TxPostcursorBf  = fpga9010_Jesd204PhyTokelauAds8Channel7TxPostcursorBfGet,
            .TxDiffControlBf = fpga9010_Jesd204PhyTokelauAds8Channel7TxDiffControlBfGet,
            .Tx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel7Tx8b10bEnableBfGet,
            .TxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel7TxPowerdownBfGet
        }
    };
    uint32_t laneIdx = 0; 

    switch (laneSel)
    {
    case ADI_FPGA9010_LANE_0:
        laneIdx = 0;
        break;
    case ADI_FPGA9010_LANE_1:
        laneIdx = 1;
        break;
    case ADI_FPGA9010_LANE_2:
        laneIdx = 2;
        break;
    case ADI_FPGA9010_LANE_3:
        laneIdx = 3;
        break;
    case ADI_FPGA9010_LANE_4:
        laneIdx = 4;
        break;
    case ADI_FPGA9010_LANE_5:
        laneIdx = 5;
        break;
    case ADI_FPGA9010_LANE_6:
        laneIdx = 6;
        break;
    case ADI_FPGA9010_LANE_7:
        laneIdx = 7;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, laneSelMask, "Invalid lane selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    /* Get cpll ref clk */
    if (serializerGetFct[laneIdx].CpllRefClkSelBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].CpllRefClkSelBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->cpllRefClkSel);
        serializerErrStr[0][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get channel clk */
    if (serializerGetFct[laneIdx].TxPllClkSelBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPllClkSelBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &txPllClkSelReadBack);
        serializerErrStr[1][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        serializerCfg->txPllClkSel = (adi_fpga9010_LaneClkSel_e) txPllClkSelReadBack;
    }

    /* Get channel final divider */
    if (serializerGetFct[laneIdx].TxRateBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxRateBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &txRateEncodedValue);
        serializerErrStr[2][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[2]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        if (txRateEncodedValue > 5)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid tx rate (final divider) value read from FPGA");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        serializerCfg->rate = (1 << txRateEncodedValue) / 2;
    }

    /* Get polarity */
    if (serializerGetFct[laneIdx].TxPolarityBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPolarityBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->polarity);
        serializerErrStr[3][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[3]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get precursor */
    if (serializerGetFct[laneIdx].TxPrecursorBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPrecursorBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->precursor);
        serializerErrStr[4][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[4]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get postcursor */
    if (serializerGetFct[laneIdx].TxPostcursorBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPostcursorBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->postcursor);
        serializerErrStr[5][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[5]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get differential control */
    if (serializerGetFct[laneIdx].TxDiffControlBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxDiffControlBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->diffCtrl);
        serializerErrStr[6][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[6]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get 8b10b enable */
    if (serializerGetFct[laneIdx].Tx8b10bEnableBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].Tx8b10bEnableBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->encoder8b10bEnable);
        serializerErrStr[7][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[7]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get power down status */
    if (serializerGetFct[laneIdx].TxPowerdownBf != NULL)
    {
        recoveryAction = serializerGetFct[laneIdx].TxPowerdownBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &serializerCfg->powerDown);
        serializerErrStr[8][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[8]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_SerializerResetSet(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    char serializerErrStr[][64] = {
        "Error resetting channel 0 tx"
    };
    uint32_t laneNumPos = 24;

    typedef struct {
        int32_t(*TxResetBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaTxResetSet_t;

    fpgaTxResetSet_t txResetSetFct[] = {
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6TxResetBfSet },
        { .TxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7TxResetBfSet }
    };
    int32_t i = 0;
    int32_t selectBit = 0;
    int32_t  loopCnt = sizeof(txResetSetFct) / sizeof(fpgaTxResetSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (txResetSetFct[i].TxResetBfSet != NULL)
        {
            recoveryAction = txResetSetFct[i].TxResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (resetVal & 0x01));
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_SerializerResetDoneGet(adi_fpga9010_Device_t *device, uint8_t *txResetDone)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t resetDoneReadBack = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, txResetDone);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    *txResetDone = 0;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 0 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 0;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 1 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 1;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 2 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 2;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 3 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 3;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 4 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 4;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 5 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 5;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 6 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 6;

    recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7TxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading channel 7 tx reset done");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *txResetDone |= (resetDoneReadBack & 0x01) << 7;

    return recoveryAction;
}

int32_t adi_fpga9010_LaneCpllPdSet(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t pdVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    char serializerErrStr[][64] = {
        "Error setting channel 0 cpll pd bit"
    };
    uint32_t laneNumPos = 22;

    typedef struct {
        int32_t(*CpllPdBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaCpllPdBfSet_t;

    fpgaCpllPdBfSet_t cpllPdBfSetFct[] = {
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6CpllPdBfSet },
        { .CpllPdBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7CpllPdBfSet }
    };
    int32_t i = 0;
    int32_t selectBit = 0;
    int32_t  loopCnt = sizeof(cpllPdBfSetFct) / sizeof(fpgaCpllPdBfSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (cpllPdBfSetFct[i].CpllPdBfSet != NULL)
        {
            recoveryAction = cpllPdBfSetFct[i].CpllPdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, pdVal);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeserializerCfgSet(adi_fpga9010_Device_t *device, uint8_t laneSelMask, adi_fpga9010_DeserializerCfg_t *deserializerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t rxRateEncodedValue = 0;

    int32_t i = 0;
    int32_t selectBit = 0;

    char deserializerErrStr[][64] = {
        "Error setting channel 0 rx pll clk sel",
        "Error setting channel 0 rx rate (final divider)",
        "Error setting channel 0 rx polarity",
        "Error setting channel 0 rx encoder8b10bEnable",
        "Error setting channel 0 rx DFE/LPMr",
        "Error setting channel 0 rx power down"
    };
    uint32_t laneNumPos = 22;

    typedef struct {
        int32_t(*RxPllClkSelBfSet)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*RxRateBfSet)        (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*RxPolarityBfSet)    (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*Rx8b10bEnableBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*RxDfeLpmEnBfSet)    (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
        int32_t(*RxPowerdownBfSet)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaDeserializerSet_t;

    fpgaDeserializerSet_t deserializerSetFct[] = {
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel0RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel0RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel0RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel0RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel1RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel1RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel1RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel1RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel2RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel2RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel2RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel2RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel3RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel3RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel3RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel3RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel4RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel4RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel4RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel4RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel5RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel5RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel5RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel5RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel6RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel6RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel6RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel6RxPowerdownBfSet
        },
        {
            .RxPllClkSelBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel7RxPllClkSelBfSet,
            .RxRateBfSet        = fpga9010_Jesd204PhyTokelauAds8Channel7RxRateBfSet,
            .RxPolarityBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel7RxPolarityBfSet,
            .Rx8b10bEnableBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7Rx8b10bEnableBfSet,
            .RxDfeLpmEnBfSet    = fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmEnBfSet,
            .RxPowerdownBfSet   = fpga9010_Jesd204PhyTokelauAds8Channel7RxPowerdownBfSet
        }
    };

    uint32_t strIdx = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, deserializerCfg);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
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
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, deserializerCfg->rate, "Invalid rx rate (final divider) value");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    for (i = 0; i < ADI_FPGA9010_NUM_LANES; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
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
            recoveryAction = deserializerSetFct[i].RxPllClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, deserializerCfg->rxPllClkSel);
            deserializerErrStr[strIdx][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set channel final divider */
        strIdx++;
        if (deserializerSetFct[i].RxRateBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxRateBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, rxRateEncodedValue);
            deserializerErrStr[strIdx][laneNumPos] = i + 48; 
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set polarity */
        strIdx++;
        if (deserializerSetFct[i].RxPolarityBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxPolarityBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, deserializerCfg->polarity);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set 8b10b enable */
        strIdx++;
        if (deserializerSetFct[i].Rx8b10bEnableBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].Rx8b10bEnableBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, deserializerCfg->encoder8b10bEnable);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* set dfe_lpm enable */
        strIdx++;
        if (deserializerSetFct[i].RxDfeLpmEnBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxDfeLpmEnBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, deserializerCfg->rxDfeLpmEn);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* Write to DRP to set tx clkDiv25 */
        /* Address, mask come from FPGA User Guide Appendix A */
        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RXCLK25DIV_ADDRESS, i, deserializerCfg->rxClk25Div, ADI_FPGA9010_RXCLK25DIV_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_PMA_RSV1_ADDRESS, i, deserializerCfg->pmaRsv1, ADI_FPGA9010_PMA_RSV1_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RXCDR_CFG2_ADDRESS, i, deserializerCfg->rxCdrCfg2, ADI_FPGA9010_RXCDR_CFG2_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RXDFE_GC_CFG1_ADDRESS, i, deserializerCfg->rxDfeGcCfg1, ADI_FPGA9010_RXDFE_GC_CFG1_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RXPI_CFG4_ADDRESS, i, deserializerCfg->rxPiCfg4, ADI_FPGA9010_RXPI_CFG4_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RXPI_CFG5_ADDRESS, i, deserializerCfg->rxPiCfg5, ADI_FPGA9010_RXPI_CFG5_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RX_EN_HI_LR_ADDRESS, i, deserializerCfg->rxEnHiLr, ADI_FPGA9010_RX_EN_HI_LR_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RX_WIDEMODE_CDR_ADDRESS, i, deserializerCfg->rxWidemodeCdr, ADI_FPGA9010_RX_WIDEMODE_CDR_MASK);
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
        {
            adi_fpga9010_DrpWrite(device, ADI_FPGA9010_RX_PROGDIV_CFG_ADDRESS, i, deserializerCfg->rxProgdivCfg, ADI_FPGA9010_RX_PROGDIV_CFG_MASK);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* bring channel out of power down */
        strIdx++;
        if (deserializerSetFct[i].RxPowerdownBfSet != NULL)
        {
            recoveryAction = deserializerSetFct[i].RxPowerdownBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, deserializerCfg->powerDown);
            deserializerErrStr[strIdx][laneNumPos] = i + 48;
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[strIdx]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeserializerCfgGet(adi_fpga9010_Device_t *device, const adi_fpga9010_LaneSel_e laneSel, adi_fpga9010_DeserializerCfg_t *deserializerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t rxPllClkSelReadBack = 0;
    uint8_t rxRateEncodedValue = 0;

    char deserializerErrStr[][64] = {
        "Error reading channel 0 rx pll clk sel",
        "Error reading channel 0 rx rate (final divider)",
        "Error reading channel 0 rx polarity",
        "Error reading channel 0 rx encoder8b10bEnable",
        "Error reading channel 0 rx DFE/LPM",
        "Error reading channel 0 rx power down"
    };
    uint32_t laneNumPos = 22;

    typedef struct {
        int32_t(*RxPllClkSelBf)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*RxRateBf)        (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*RxPolarityBf)    (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*Rx8b10bEnableBf) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*RxDfeLpmEnBf)    (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
        int32_t(*RxPowerdownBf)   (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
    } fpgaDeserializerGet_t;

    fpgaDeserializerGet_t deserializerGetFct[] = {
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel0RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel0RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel0RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel0Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel0RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel1RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel1RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel1RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel1Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel1RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel2RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel2RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel2RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel2Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel2RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel3RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel3RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel3RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel3Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel3RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel4RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel4RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel4RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel4Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel4RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel5RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel5RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel5RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel5Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel5RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel6RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel6RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel6RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel6Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel6RxPowerdownBfGet
        },
        {
            .RxPllClkSelBf   = fpga9010_Jesd204PhyTokelauAds8Channel7RxPllClkSelBfGet,
            .RxRateBf        = fpga9010_Jesd204PhyTokelauAds8Channel7RxRateBfGet,
            .RxPolarityBf    = fpga9010_Jesd204PhyTokelauAds8Channel7RxPolarityBfGet,
            .Rx8b10bEnableBf = fpga9010_Jesd204PhyTokelauAds8Channel7Rx8b10bEnableBfGet,
            .RxDfeLpmEnBf    = fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmEnBfGet,
            .RxPowerdownBf   = fpga9010_Jesd204PhyTokelauAds8Channel7RxPowerdownBfGet
        }
    };
    uint32_t laneIdx = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, deserializerCfg);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    switch (laneSel)
    {
    case ADI_FPGA9010_LANE_0:
        laneIdx = 0;
        break;
    case ADI_FPGA9010_LANE_1:
        laneIdx = 1;
        break;
    case ADI_FPGA9010_LANE_2:
        laneIdx = 2;
        break;
    case ADI_FPGA9010_LANE_3:
        laneIdx = 3;
        break;
    case ADI_FPGA9010_LANE_4:
        laneIdx = 4;
        break;
    case ADI_FPGA9010_LANE_5:
        laneIdx = 5;
        break;
    case ADI_FPGA9010_LANE_6:
        laneIdx = 6;
        break;
    case ADI_FPGA9010_LANE_7:
        laneIdx = 7;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, laneSel, "Invalid lane selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    /* Get channel clk */
    if (deserializerGetFct[laneIdx].RxPllClkSelBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxPllClkSelBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &rxPllClkSelReadBack);
        deserializerCfg->rxPllClkSel = (adi_fpga9010_LaneClkSel_e) rxPllClkSelReadBack;
        deserializerErrStr[0][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[0]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get channel final divider */
    if (deserializerGetFct[laneIdx].RxRateBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxRateBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &rxRateEncodedValue);
        deserializerErrStr[1][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[1]);
        ADI_ERROR_RETURN(device->common.error.newAction);
        if (rxRateEncodedValue > 5)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid rx rate (final divider) value read from FPGA");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        deserializerCfg->rate = (1 << rxRateEncodedValue) / 2;
    }

    /* Get polarity */
    if (deserializerGetFct[laneIdx].RxPolarityBf != NULL)
    {
        
        recoveryAction = deserializerGetFct[laneIdx].RxPolarityBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &deserializerCfg->polarity);
        deserializerErrStr[2][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[2]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Get 8b10b enable */
    if (deserializerGetFct[laneIdx].Rx8b10bEnableBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].Rx8b10bEnableBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &deserializerCfg->encoder8b10bEnable);
        deserializerErrStr[3][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[3]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* set dfe_lpm enable */
    if (deserializerGetFct[laneIdx].RxDfeLpmEnBf != NULL)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmEnBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &deserializerCfg->rxDfeLpmEn);
        deserializerErrStr[4][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[4]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* bring channel out of power down */
    if (deserializerGetFct[laneIdx].RxPowerdownBf != NULL)
    {
        recoveryAction = deserializerGetFct[laneIdx].RxPowerdownBf(device, FPGA9010_BF_TOKELAU_JESD_PHY, &deserializerCfg->powerDown);
        deserializerErrStr[5][laneNumPos] = laneIdx + 48;
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)deserializerErrStr[5]);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_DeserializerResetSet(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    char serializerErrStr[][64] = {
        "Error resetting channel 0 rx"
    };
    uint32_t laneNumPos = 24;

    typedef struct {
        int32_t(*RxResetBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaRxResetBfSet_t;

    fpgaRxResetBfSet_t rxResetBfSetFct[] = {
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6RxResetBfSet },
        { .RxResetBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7RxResetBfSet }
    };
    int32_t i = 0;
    int32_t selectBit = 0;
    int32_t  loopCnt = sizeof(rxResetBfSetFct) / sizeof(fpgaRxResetBfSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (rxResetBfSetFct[i].RxResetBfSet != NULL)
        {
            recoveryAction = rxResetBfSetFct[i].RxResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (resetVal & 0x01));
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeserializerResetDoneGet(adi_fpga9010_Device_t *device, uint8_t *rxResetDone)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t resetDoneReadBack = 0;
    char serializerErrStr[][64] = {"Error reading channel 0 rx reset done"};
    uint32_t laneNumPos = 22;

    typedef struct {
        int32_t(*RxResetDoneBfGet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t *);
    } fpgaRxResetDoneBfGet_t;

    fpgaRxResetDoneBfGet_t rxResetDoneBfGetFct[] = {
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel0RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel1RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel2RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel3RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel4RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel5RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel6RxResetDoneBfGet },
        { .RxResetDoneBfGet = fpga9010_Jesd204PhyTokelauAds8Channel7RxResetDoneBfGet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(rxResetDoneBfGetFct) / sizeof(fpgaRxResetDoneBfGet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    *rxResetDone = 0;
    for (i = 0; i < loopCnt; i++)
    {
        if (rxResetDoneBfGetFct[i].RxResetDoneBfGet != NULL)
        {
            recoveryAction = rxResetDoneBfGetFct[i].RxResetDoneBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &resetDoneReadBack);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        *rxResetDone |= ((resetDoneReadBack & 0x01) << i); /* shift bit result to the left then save it. */
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeframerCfgSet(adi_fpga9010_Device_t *device, uint32_t deframerSelMask, adi_fpga9010_DeframerCfg_t *deframerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, deframerCfg);
    
    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BDeframerCfgSet(device, deframerSelMask, deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CDeframerCfgSet(device, deframerSelMask, deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeframerCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e deframerSel, adi_fpga9010_DeframerCfg_t *deframerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, deframerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BDeframerCfgGet(device, deframerSel, deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CDeframerCfgGet(device, deframerSel, deframerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeframerResetGet(adi_fpga9010_Device_t *device, uint32_t deframerSelMask, uint8_t *resetBits)
{
    UNUSED_PARA(deframerSelMask);
    UNUSED_PARA(resetBits);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    //uint8_t resetGet = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    return recoveryAction;
}

int32_t adi_fpga9010_FramerCfgSet(adi_fpga9010_Device_t *device, uint8_t framerSelMask, adi_fpga9010_FramerCfg_t *framerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, framerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BFramerCfgSet(device, framerSelMask, framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CFramerCfgSet(device, framerSelMask, framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_FramerCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e framerSel, adi_fpga9010_FramerCfg_t *framerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, framerCfg);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BFramerCfgGet(device, framerSel, framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CFramerCfgGet(device, framerSel, framerCfg);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_FramerResetGet(adi_fpga9010_Device_t *device, uint32_t framerSelMask, uint8_t *resetBits)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, resetBits);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BFramerResetGet(device, framerSelMask, resetBits);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CFramerResetGet(device, framerSelMask, resetBits);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_TxLaneXBarCfgSet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e framerSel, uint8_t *laneXBar)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfJesd204TxLaneXbarChanAddr_e baseAddr = FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_0;
    char serializerErrStr[][64] = { "Error writing Lane 0 configuration" };
    uint32_t laneNumPos = 19;

    typedef struct {
        int32_t(*TxXbarLaneSelectBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204TxLaneXbarChanAddr_e baseAddr, uint8_t);
    } fpgaTxXbarLaneSelectBfSet_t;

    fpgaTxXbarLaneSelectBfSet_t txXbarLaneSelectBfSetFct[] = {
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane0SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane1SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane2SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane3SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane4SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane5SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane6SelectBfSet },
        { .TxXbarLaneSelectBfSet = fpga9010_Jesd204TxLaneXbarLane7SelectBfSet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(txXbarLaneSelectBfSetFct) / sizeof(fpgaTxXbarLaneSelectBfSet_t);
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, laneXBar);

    /* Set correct addresses for the framer selected */
    if (framerSel == ADI_FPGA9010_FRAMER_0)
    {
        baseAddr = FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_0;
    }
    else if (framerSel == ADI_FPGA9010_FRAMER_1)
    {
        baseAddr = FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_1;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, framerSel, "Invalid framer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (txXbarLaneSelectBfSetFct[i].TxXbarLaneSelectBfSet != NULL)
        {
            recoveryAction = txXbarLaneSelectBfSetFct[i].TxXbarLaneSelectBfSet(device, baseAddr, laneXBar[i]);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_RxLaneXBarCfgSet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e deframerSel, uint8_t *laneXBar)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfJesd204RxLaneXbarChanAddr_e baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_0;
    char serializerErrStr[][64] = { "Error writing Lane 0 configuration" };
    uint32_t laneNumPos = 19;

    typedef struct {
        int32_t(*RxXbarLaneSelectBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204RxLaneXbarChanAddr_e baseAddr, uint8_t);
    } fpgaRxXbarLaneSelectBfSet_t;

    fpgaRxXbarLaneSelectBfSet_t rxXbarLaneSelectBfSetFct[] = {
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane0SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane1SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane2SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane3SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane4SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane5SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane6SelectBfSet },
        { .RxXbarLaneSelectBfSet = fpga9010_Jesd204RxLaneXbarLane7SelectBfSet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(rxXbarLaneSelectBfSetFct) / sizeof(fpgaRxXbarLaneSelectBfSet_t);
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, laneXBar);

    /* Set correct addresses for the deframer selected */
    if (deframerSel == ADI_FPGA9010_DEFRAMER_0)
    {
        baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_0;
    }
    else if (deframerSel == ADI_FPGA9010_DEFRAMER_1)
    {
        baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_1;
    }
    else if (deframerSel == ADI_FPGA9010_DEFRAMER_2)
    {
        baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_2;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, deframerSel, "Invalid deframer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (rxXbarLaneSelectBfSetFct[i].RxXbarLaneSelectBfSet != NULL)
        {
            recoveryAction = rxXbarLaneSelectBfSetFct[i].RxXbarLaneSelectBfSet(device, baseAddr, laneXBar[i]);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_TxLaneXBarCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e framerSel, uint8_t *laneXBar)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfJesd204TxLaneXbarChanAddr_e baseAddr = FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_0;
    char serializerErrStr[][64] = { "Error reading Lane 0 configuration" };
    uint32_t laneNumPos = 19;

    typedef struct {
        int32_t(*TxXbarLaneSelectBfGet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204TxLaneXbarChanAddr_e baseAddr, uint8_t *);
    } fpgaTxXbarLaneSelectBfGet_t;

    fpgaTxXbarLaneSelectBfGet_t txXbarLaneSelectBfGetFct[] = {
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane0SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane1SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane2SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane3SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane4SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane5SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane6SelectBfGet },
        { .TxXbarLaneSelectBfGet = fpga9010_Jesd204TxLaneXbarLane7SelectBfGet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(txXbarLaneSelectBfGetFct) / sizeof(fpgaTxXbarLaneSelectBfGet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, laneXBar);

    /* Set correct addresses for the framer selected */
    if (framerSel == ADI_FPGA9010_FRAMER_0)
    {
        baseAddr = FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_0;
    }
    else if (framerSel == ADI_FPGA9010_FRAMER_1)
    {
        baseAddr = FPGA9010_BF_JESD204_TX_LANE_XBAR_LINK_1;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, framerSel, "Invalid framer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < loopCnt; i++)
    {
        if (txXbarLaneSelectBfGetFct[i].TxXbarLaneSelectBfGet != NULL)
        {
            recoveryAction = txXbarLaneSelectBfGetFct[i].TxXbarLaneSelectBfGet(device, baseAddr, &laneXBar[i]);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_RxLaneXBarCfgGet(adi_fpga9010_Device_t *device, adi_fpga9010_DeframerSel_e deframerSel, uint8_t *laneXBar)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfJesd204RxLaneXbarChanAddr_e baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_0;
    char serializerErrStr[][64] = { "Error reading Lane 0 configuration" };
    uint32_t laneNumPos = 19;

    typedef struct {
        int32_t(*RxXbarLaneSelectBfGet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204RxLaneXbarChanAddr_e baseAddr, uint8_t *);
    } fpgaRxXbarLaneSelectBfGet_t;

    fpgaRxXbarLaneSelectBfGet_t rxXbarLaneSelectBfGetFct[] = {
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane0SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane1SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane2SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane3SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane4SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane5SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane6SelectBfGet },
        { .RxXbarLaneSelectBfGet = fpga9010_Jesd204RxLaneXbarLane7SelectBfGet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(rxXbarLaneSelectBfGetFct) / sizeof(fpgaRxXbarLaneSelectBfGet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, laneXBar);

    /* Set correct addresses for the deframer selected */
    if (deframerSel == ADI_FPGA9010_DEFRAMER_0)
    {
        baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_0;
    }
    else if (deframerSel == ADI_FPGA9010_DEFRAMER_1)
    {
        baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_1;
    }
    else if (deframerSel == ADI_FPGA9010_DEFRAMER_2)
    {
        baseAddr = FPGA9010_BF_JESD204_RX_LANE_XBAR_LINK_2;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, deframerSel, "Invalid deframer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (rxXbarLaneSelectBfGetFct[i].RxXbarLaneSelectBfGet != NULL)
        {
            recoveryAction = rxXbarLaneSelectBfGetFct[i].RxXbarLaneSelectBfGet(device, baseAddr, &laneXBar[i]);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_FramerReset(adi_fpga9010_Device_t *device, uint8_t framerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BFramerReset(device, framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CFramerReset(device, framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_FramerDisable(adi_fpga9010_Device_t *device, uint8_t framerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BFramerDisable(device, framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CFramerDisable(device, framerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeframerReset(adi_fpga9010_Device_t *device, uint8_t deframerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BDeframerReset(device, deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CDeframerReset(device, deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeframerDisable(adi_fpga9010_Device_t *device, uint8_t deframerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BDeframerDisable(device, deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CDeframerDisable(device, deframerSelMask);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_DeframerStatusGet(adi_fpga9010_Device_t *device, uint8_t deframerSelMask, uint8_t *status)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204BDeframerStatusGet(device, deframerSelMask, status);
        ADI_ERROR_RETURN(device->common.error.newAction);

    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        recoveryAction = fpga9010_Jesd204CDeframerStatusGet(device, deframerSelMask, status);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device not initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t adi_fpga9010_ChannelLoopbackEnable(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t loopbackValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    char serializerErrStr[][64] = {
        "Error setting loopback for channel 0 "
    };
    uint32_t laneNumPos = 35;

    typedef struct {
        int32_t(*LoopbackBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaLoopbackBfSet_t;

    fpgaLoopbackBfSet_t loopbackBfSetFct[] = {
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6LoopbackBfSet },
        { .LoopbackBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7LoopbackBfSet }
    };
    int32_t i = 0;
    int32_t selectBit = 0;
    int32_t  loopCnt = sizeof(loopbackBfSetFct) / sizeof(fpgaLoopbackBfSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (loopbackBfSetFct[i].LoopbackBfSet != NULL)
        {
            recoveryAction = loopbackBfSetFct[i].LoopbackBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, (loopbackValue & 0x07));
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_ChannelDfeLpmOverrideSet(adi_fpga9010_Device_t *device, uint8_t laneSelMask, uint8_t value)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    char serializerErrStr[][64] = {
        "Error setting RxDfeLpmOverride for channel 0 "
    };
    uint32_t laneNumPos = 43;

    typedef struct {
        int32_t(*RxDfeLpmOverrideBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, uint8_t);
    } fpgaRxDfeLpmOverrideBfSet_t;

    fpgaRxDfeLpmOverrideBfSet_t rxDfeLpmOverrideBfSetFct[] = {
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmOverrideBfSet },
        { .RxDfeLpmOverrideBfSet = fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmOverrideBfSet }
    };
    int32_t i = 0;
    int32_t selectBit = 0;
    int32_t  loopCnt = sizeof(rxDfeLpmOverrideBfSetFct) / sizeof(fpgaRxDfeLpmOverrideBfSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (laneSelMask == 0)
        {
            break;  /* Already processed all mask bits. */
        }

        selectBit = 1 << i; /* process each bit from right most to left most. */

        if ((laneSelMask & selectBit) == 0)
        {
            continue; /* If current bit mask is not set then go to next bit mask */
        }

        laneSelMask &= ~selectBit; /* mark off the select bit that is currently processing. */

        if (rxDfeLpmOverrideBfSetFct[i].RxDfeLpmOverrideBfSet != NULL)
        {
            recoveryAction = rxDfeLpmOverrideBfSetFct[i].RxDfeLpmOverrideBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, value);
            serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_SyncXBarCfgSet(adi_fpga9010_Device_t *device, uint8_t polarity, uint8_t *inputSyncSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t maxIndex = ADI_FPGA9010_NUM_OF_DEFRAMERS + ADI_FPGA9010_NUM_OF_FRAMERS;
    char serializerErrStr[][64] = { "Error setting output sync 0 configuration" };
    uint32_t laneNumPos = 26;

    typedef struct {
        int32_t(*SyncXbarSyncOutSelectBfSet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, uint8_t);
    } fpgaSyncXbarSyncOutSelectBfSet_t;

    fpgaSyncXbarSyncOutSelectBfSet_t syncXbarSyncOutSelectBfSetFct[] = {
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut0SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut1SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut2SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut3SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut4SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut5SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut6SelectBfSet },
        { .SyncXbarSyncOutSelectBfSet = fpga9010_Jesd204bSyncXbarSyncOut7SelectBfSet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(syncXbarSyncOutSelectBfSetFct) / sizeof(fpgaSyncXbarSyncOutSelectBfSet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, inputSyncSel);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (syncXbarSyncOutSelectBfSetFct[i].SyncXbarSyncOutSelectBfSet != NULL)
        {
            if (maxIndex > 0)
            {
                recoveryAction = syncXbarSyncOutSelectBfSetFct[i].SyncXbarSyncOutSelectBfSet(device, FPGA9010_BF_JESD204B_SYNC_XBAR, inputSyncSel[i]);
                serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
                ADI_ERROR_RETURN(device->common.error.newAction);
                maxIndex--;
            }
            else {
                break;
            }
        }
    }

    recoveryAction = fpga9010_Jesd204bSyncXbarSyncInPolarityBfSet(device, FPGA9010_BF_JESD204B_SYNC_XBAR, polarity);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sync xbar polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_SyncXBarCfgGet(adi_fpga9010_Device_t *device, uint8_t *polarity, uint8_t *inputSyncSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t maxIndex = ADI_FPGA9010_NUM_OF_DEFRAMERS + ADI_FPGA9010_NUM_OF_FRAMERS;
    char serializerErrStr[][64] = { "Error reading output sync 0 configuration" };
    uint32_t laneNumPos = 26;

    typedef struct {
        int32_t(*SyncXbarSyncOutSelectBfGet) (adi_fpga9010_Device_t *device, fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, uint8_t *);
    } fpgaSyncXbarSyncOutSelectBfGet_t;

    fpgaSyncXbarSyncOutSelectBfGet_t syncXbarSyncOutSelectBfGetFct[] = {
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut0SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut1SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut2SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut3SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut4SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut5SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut6SelectBfGet },
        { .SyncXbarSyncOutSelectBfGet = fpga9010_Jesd204bSyncXbarSyncOut7SelectBfGet }
    };
    int32_t i = 0;
    int32_t  loopCnt = sizeof(syncXbarSyncOutSelectBfGetFct) / sizeof(fpgaSyncXbarSyncOutSelectBfGet_t);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, inputSyncSel);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < loopCnt; i++)
    {
        if (syncXbarSyncOutSelectBfGetFct[i].SyncXbarSyncOutSelectBfGet != NULL)
        {
            if (maxIndex > 0)
            {
                recoveryAction = syncXbarSyncOutSelectBfGetFct[i].SyncXbarSyncOutSelectBfGet(device, FPGA9010_BF_JESD204B_SYNC_XBAR, &inputSyncSel[i]);
                serializerErrStr[0][laneNumPos] = i + 48; /* convert a number to ascii character of the number i.e. 0 --> '0' */
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, (const char *)serializerErrStr[0]);
                ADI_ERROR_RETURN(device->common.error.newAction);
                maxIndex--;
            }
            else {
                break;
            }
        }
    }

    recoveryAction = fpga9010_Jesd204bSyncXbarSyncInPolarityBfGet(device, FPGA9010_BF_JESD204B_SYNC_XBAR, polarity);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading sync xbar polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_SysRefEnableSet(adi_fpga9010_Device_t *device, uint8_t framerSelMask, uint8_t deframerSelMask, uint8_t enable)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t outputEnableRegisterVal = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9010_Jesd204SysrefControlOutputEnableBfGet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, &outputEnableRegisterVal);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting output enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Force only the bits we care about */
    framerSelMask = (ADI_FPGA9010_FRAMER_ALL & framerSelMask);
    deframerSelMask = (ADI_FPGA9010_DEFRAMER_ALL & deframerSelMask);

    if (enable == ADI_ENABLE)
    {
        outputEnableRegisterVal |= (uint32_t)deframerSelMask;
        outputEnableRegisterVal |= (uint32_t)framerSelMask << ADI_FPGA9010_NUM_OF_DEFRAMERS;
    }
    else if (enable == ADI_DISABLE)
    {
        outputEnableRegisterVal &= ~((uint32_t)deframerSelMask);
        outputEnableRegisterVal &= ~((uint32_t)framerSelMask << ADI_FPGA9010_NUM_OF_DEFRAMERS);
    }
    
    recoveryAction = fpga9010_Jesd204SysrefControlOutputEnableBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, outputEnableRegisterVal);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting output enable bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_SysRefControlSet(adi_fpga9010_Device_t *device, adi_fpga9010_SysRefClkCfg_t *sysRefCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, sysRefCfg);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9010_Jesd204SysrefControlExtSysrefPolarityBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, sysRefCfg->externalSysrefPolarity);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204SysrefControlExtSysrefSampleEdgeBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, sysRefCfg->externalSysrefSampleEdge);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref sample edge");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204SysrefControlIntSysrefEnableBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, sysRefCfg->internalSysrefEnable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref enable");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write (actual value) - 1 to register */
    recoveryAction = fpga9010_Jesd204SysrefControlIntSysrefGenPeriodBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, sysRefCfg->internalSysRefGeneratorFrequency - 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref generator");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

int32_t adi_fpga9010_SysRefControlGet(adi_fpga9010_Device_t *device, adi_fpga9010_SysRefClkCfg_t *sysRefCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, sysRefCfg);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    recoveryAction = fpga9010_Jesd204SysrefControlExtSysrefPolarityBfGet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->externalSysrefPolarity);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204SysrefControlExtSysrefSampleEdgeBfGet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->externalSysrefSampleEdge);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref sample edge");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_Jesd204SysrefControlIntSysrefEnableBfGet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->internalSysrefEnable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref enable");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write (actual value) - 1 to register */
    recoveryAction = fpga9010_Jesd204SysrefControlIntSysrefGenPeriodBfGet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, &sysRefCfg->internalSysRefGeneratorFrequency);
    sysRefCfg->internalSysRefGeneratorFrequency++;
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref generator");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

int32_t adi_fpga9010_SysRefRequest(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t internalSysrefEnable = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    recoveryAction = fpga9010_Jesd204SysrefControlIntSysrefEnableBfGet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, &internalSysrefEnable);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading sync xbar polarity");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    if (internalSysrefEnable == 1)
    {
        recoveryAction = fpga9010_Jesd204SysrefControlIntSysrefRequestBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting internal sysref request");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        recoveryAction = fpga9010_Jesd204SysrefControlExtSysrefRequestBfSet(device, FPGA9010_BF_JESD204_SYSREF_CONTROL, 1);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting external sysref request");
        ADI_ERROR_RETURN(device->common.error.newAction); 
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_Jesd204cLinkLayerIrqEnSet(adi_fpga9010_Device_t *device, uint8_t linkSelMask, uint16_t interruptBitMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
    int32_t i = 0;
    uint8_t linkSelect = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    for (i = 0; i < (ADI_FPGA9010_NUM_OF_DEFRAMERS + ADI_FPGA9010_NUM_OF_FRAMERS); i++)
    {
        linkSelect = (1 << i);

        switch (linkSelect)
        {
        case 0x1:
            instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
            break;
        case 0x2:
            instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_1;
            break;
        case 0x4:
            instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_2;
            break;
        case 0x8:
            instanceAddress = FPGA9010_BF_JESD204C_FRAMER_0;
            break;
        case 0x10:
            instanceAddress = FPGA9010_BF_JESD204C_FRAMER_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Unsupported link selected.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if ((linkSelect & linkSelMask) > 0)
        {
            if ((interruptBitMask & ADI_FPGA9010_GLOBAL) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnGlobalBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting global irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_SYSREF_RECEIVED) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnSysrefReceivedBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sysref received irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_SYSREF_ERROR) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnSysrefErrorBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sysref error irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_LOSS_SYNC_HEADER_LOCK) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnLossSyncHeaderLockBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loss sync header irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_LOSS_MB_LOCK) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnLossMbLockBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loss mb lock irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_BLOCK_SYNC_ERROR) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnBlockSyncErrorBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting block sync error irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_MB_ERROR) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnMbErrorBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting mb error irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_CRC_ERROR) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnCrcErrorBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting crc error irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_FEC_ERROR) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnFecErrorBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting fec error irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            if ((interruptBitMask & ADI_FPGA9010_OVERFLOW_ERROR) > 0)
            {
                recoveryAction = fpga9010_XilinxJesd204cIrqEnOverflowErrorBfSet(device, instanceAddress, 1);
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting overflow error irq enable");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_Jesd204cLinkLayerIrqEnGet(adi_fpga9010_Device_t *device, uint8_t linkSel, uint16_t *interruptBitMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
    uint8_t interruptEnReadback = 0;


    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, interruptBitMask);

    *interruptBitMask = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Logic to ensure only one bit is set in byte. */
    if ((linkSel & (linkSel - 1)) > 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Only one link is allowed to be selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    switch (linkSel)
    {
    case 0x1:
        instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
        break;
    case 0x2:
        instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_1;
        break;
    case 0x4:
        instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_2;
        break;
    case 0x8:
        instanceAddress = FPGA9010_BF_JESD204C_FRAMER_0;
        break;
    case 0x10:
        instanceAddress = FPGA9010_BF_JESD204C_FRAMER_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Unsupported link selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9010_XilinxJesd204cIrqEnGlobalBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting global irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 1);
            
    recoveryAction = fpga9010_XilinxJesd204cIrqEnSysrefReceivedBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sysref received irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 2);

    recoveryAction = fpga9010_XilinxJesd204cIrqEnSysrefErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sysref error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 3);

    recoveryAction = fpga9010_XilinxJesd204cIrqEnLossSyncHeaderLockBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loss sync header irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 5);

    recoveryAction = fpga9010_XilinxJesd204cIrqEnLossMbLockBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loss mb lock irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 6);

    recoveryAction = fpga9010_XilinxJesd204cIrqEnBlockSyncErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting block sync error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 7);

    recoveryAction = fpga9010_XilinxJesd204cIrqEnMbErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting mb error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 8);
        
    recoveryAction = fpga9010_XilinxJesd204cIrqEnCrcErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting crc error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 9);
           
    recoveryAction = fpga9010_XilinxJesd204cIrqEnFecErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting fec error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 10);
            
    recoveryAction = fpga9010_XilinxJesd204cIrqEnOverflowErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting overflow error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= ((uint16_t)interruptEnReadback << 11);

    return recoveryAction;
}

int32_t adi_fpga9010_Jesd204cLinkLayerIrqStatusGet(adi_fpga9010_Device_t *device, uint8_t linkSel, uint16_t *interruptBitMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
    uint8_t interruptEnReadback = 0;


    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, interruptBitMask);

    *interruptBitMask = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Logic to ensure only one bit is set in byte. */
    if ((linkSel & (linkSel - 1)) > 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Only one link is allowed to be selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    switch (linkSel)
    {
    case 0x1:
        instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
        break;
    case 0x2:
        instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_1;
        break;
    case 0x4:
        instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_2;
        break;
    case 0x8:
        instanceAddress = FPGA9010_BF_JESD204C_FRAMER_0;
        break;
    case 0x10:
        instanceAddress = FPGA9010_BF_JESD204C_FRAMER_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Unsupported link selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = fpga9010_XilinxJesd204cIrqSysrefReceivedBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sysref received irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 2);

    recoveryAction = fpga9010_XilinxJesd204cIrqSysrefErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting sysref error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 3);

    recoveryAction = fpga9010_XilinxJesd204cIrqLossSyncHeaderLockBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loss sync header irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 5);

    recoveryAction = fpga9010_XilinxJesd204cIrqLossMbLockBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting loss mb lock irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 6);

    recoveryAction = fpga9010_XilinxJesd204cIrqBlockSyncErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting block sync error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 7);

    recoveryAction = fpga9010_XilinxJesd204cIrqMbErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting mb error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 8);

    recoveryAction = fpga9010_XilinxJesd204cIrqCrcErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting crc error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 9);

    recoveryAction = fpga9010_XilinxJesd204cIrqFecErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting fec error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 10);

    recoveryAction = fpga9010_XilinxJesd204cIrqOverflowErrorBfGet(device, instanceAddress, &interruptEnReadback);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting overflow error irq enable");
    ADI_ERROR_RETURN(device->common.error.newAction);
    *interruptBitMask |= (interruptEnReadback << 11);
    
    return recoveryAction;
}

int32_t adi_fpga9010_Jesd204CDeframerCmdDataSet(adi_fpga9010_Device_t *device, uint32_t deframerSelMask, uint8_t cmdEnable, uint8_t dataEnable)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
    uint32_t i = 0;
    adi_fpga9010_DeframerSel_e deframerSel = ADI_FPGA9010_DEFRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (deframerSelMask < 1 || deframerSelMask > 7)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_DEFRAMERS; i++)
    {
        deframerSel = (adi_fpga9010_DeframerSel_e)((uint8_t)(1 << i));

        switch (deframerSel)
        {
        case ADI_FPGA9010_DEFRAMER_0:
            instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
            break;
        case ADI_FPGA9010_DEFRAMER_1:
            instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_1;
            break;
        case ADI_FPGA9010_DEFRAMER_2:
            instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)deframerSel & deframerSelMask) > 0)
        {
            recoveryAction = fpga9010_XilinxJesd204cEnableCmdInterfaceBfSet(device, instanceAddress, cmdEnable);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Unable to set cmd interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_XilinxJesd204cEnableDataInterfaceBfSet(device, instanceAddress, dataEnable);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Unable to set data interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_Jesd204CFramerCmdDataSet(adi_fpga9010_Device_t *device, uint32_t framerSelMask, uint8_t cmdEnable, uint8_t dataEnable)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9010_BF_JESD204C_DEFRAMER_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e framerSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (framerSelMask < 1 || framerSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        framerSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (framerSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_JESD204C_FRAMER_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_JESD204C_FRAMER_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)framerSel & framerSelMask) > 0)
        {
            recoveryAction = fpga9010_XilinxJesd204cEnableCmdInterfaceBfSet(device, instanceAddress, cmdEnable);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Unable to set cmd interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_XilinxJesd204cEnableDataInterfaceBfSet(device, instanceAddress, dataEnable);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Unable to set data interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}