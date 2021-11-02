
/*!
* \file adi_fpga9010_utilities.c
* \brief Contains FPGA9010 API configuration and run-time type definitions for utitility functions
*
* ADRV9010 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_utilities.h"
#include "adi_fpga9010_rx.h"
#include "adi_fpga9010_tx.h"

#include "adi_common_error.h"
#include "adi_fpga9010_hal.h"

int32_t adi_fpga9010_CalculateQpllSettings(adi_fpga9010_Device_t *device, const uint32_t refClk_kHz, const uint32_t fastestLaneRate_kHz, adi_fpga9010_QpllCfg_t *qplls)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t _N[] = { 16, 20, 32, 40, 60, 64, 66, 75, 80, 84, 90, 96, 100, 112, 120, 125, 150 };
    uint8_t _NLength = 16;
    uint8_t n = 0;
    uint8_t _M[] = { 1, 2, 3, 4 };
    uint8_t _MLength = 3;
    uint8_t m = 0;
    uint8_t _D[] = { 1, 2, 4, 8, 16 };
    uint8_t _DLength = 5;
    uint8_t d = 0;
    uint32_t qpllVcoFreq_kHz = 0;
    uint32_t qpllVcoOutFreq_kHz = 0;
    adi_fpga9010_LaneClkSel_e qpllBand = ADI_FPGA9010_QPLLCLK0;
    uint8_t validConfigFound = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, qplls);

    for(m = _MLength ; m >= 0 && m <= 3 ; m--)
    {
        for(n = _NLength ; n >= 0 && n <= _NLength ; n--)
        {
            for(d = 0 ; d < _DLength ; d++)
            {
                qpllVcoFreq_kHz = refClk_kHz * _N[n] / _M[m];
                qpllVcoOutFreq_kHz = qpllVcoFreq_kHz / 2;

                if ((qpllVcoFreq_kHz >= 9800000) && (qpllVcoFreq_kHz <= 16300000))
                {
                    qpllBand = ADI_FPGA9010_QPLLCLK0;
                }
                else if ((qpllVcoFreq_kHz >= 8000000) && (qpllVcoFreq_kHz <= 13000000))
                {
                    qpllBand = ADI_FPGA9010_QPLLCLK1;
                }
                else
                {
                    continue;
                }

                if (qpllVcoOutFreq_kHz * 2 / _D[d] == fastestLaneRate_kHz)
                {
                    qplls->mVal = _M[m];
                    qplls->nVal = _N[n];
                    qplls->band = qpllBand;
                    qplls->qpllVco_kHz = qpllVcoFreq_kHz;
                    
                    validConfigFound = 1;
                }
            }
        }
    }

    if (validConfigFound == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Could not find a valid configuration for qpll");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* These are magic numbers derived from observation of the values Xilinx produces for various
    *  refClk_kHz and fastestLaneRate_kHz combinations.
    */
    if (qplls->qpllVco_kHz < 10000000)
    {
        qplls->cfg4 = 0x0000;
        qplls->lockCfg = 0x21E8;
        qplls->lockCfgG3 = 0x21E8;
    }
    else if (qplls->qpllVco_kHz < 14000000)
    {
        qplls->cfg4 = 0x0009;
        qplls->lockCfg = 0x21E8;
        qplls->lockCfgG3 = 0x21E8;
    }
    else
    {
        qplls->cfg4 = 0x001B;
        qplls->lockCfg = 0x25E8;
        qplls->lockCfgG3 = 0x25E8;
    }

    if (qplls->nVal < 80)
    {
        qplls->cp = 0x001F;
    }
    else
    {
        qplls->cp = 0x01FF;
    }

    qplls->lpf = 0x03FC;
    
    return recoveryAction;
}

int32_t adi_fpga9010_CalculateQpllDivisor(adi_fpga9010_Device_t *device, uint32_t qpllVcoFreq_kHz, const uint32_t desiredLaneRate_kHz, uint8_t *dVal)
{
    uint8_t _D[] = { 1, 2, 4, 8, 16 };
    uint8_t _DLength = 5;
    uint8_t d = 0;
    uint8_t desiredDVal = 1;
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, dVal);

    /* Prevent divide by 0 */
    if (desiredLaneRate_kHz == 0)
    {
        *dVal = 1; /* Return valid divide by 1 setting */
        return recoveryAction;
        
    }
    else
    {
        desiredDVal = (uint8_t)(qpllVcoFreq_kHz / desiredLaneRate_kHz);
    }
    
    for (d = 0; d < _DLength; d++)
    {
        if (desiredDVal == _D[d])
        {
            *dVal = _D[d];
            return recoveryAction;
        }
    }

    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Desired PLL divisor invalid");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return device->common.error.newAction;
}

int32_t adi_fpga9010_CalculateMmcmSettings(adi_fpga9010_Device_t *device, const uint32_t refClk_kHz, adi_fpga9010_MmcmCfg_t *mmcmConfig)
{
    uint32_t mmcmVcoFreq_kHz = 0;
    uint32_t m;
    uint32_t d;
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, mmcmConfig);
    
    for (m = 0; m < ADI_FPGA9010_NUM_MMCM_OUTPUT_CLOCKS; m++)
    {
        if (mmcmConfig->outputClkFreq_kHz[m] == 0)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Cannot have a 0 value for any output clocks in mmcm");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    /* find an m & d value that works for all output clocks */
    for (d = 1; d < 256; d++)
    {
        for (m = 255; m > 0; m--)
        {
            mmcmVcoFreq_kHz = refClk_kHz * m / d;

            if (mmcmVcoFreq_kHz > 1600000 || mmcmVcoFreq_kHz < 600000)
            {
                continue;
            }

            /* with the current m & d, make sure the output clocks can be achieved within the channel divider limits */
            if (((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[0]) == 0) && ((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[1]) == 0) && ((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[2]) == 0) &&
                ((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[3]) == 0) && ((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[4]) == 0) && ((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[5]) == 0) &&
                ((mmcmVcoFreq_kHz % mmcmConfig->outputClkFreq_kHz[6]) == 0) &&
                
                ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[0]) < 256) && ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[1]) < 256) && ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[2]) < 256) &&
                ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[3]) < 256) && ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[4]) < 256) && ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[5]) < 256) &&
                ((mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[6]) < 256))
            {
                mmcmConfig->mVal = m;
                mmcmConfig->dVal = d;
                mmcmConfig->outputClkDiv[0] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[0];
                mmcmConfig->outputClkDiv[1] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[1];
                mmcmConfig->outputClkDiv[2] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[2];
                mmcmConfig->outputClkDiv[3] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[3];
                mmcmConfig->outputClkDiv[4] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[4];
                mmcmConfig->outputClkDiv[5] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[5];
                mmcmConfig->outputClkDiv[6] = mmcmVcoFreq_kHz / mmcmConfig->outputClkFreq_kHz[6];

                return recoveryAction;
            }
        }
    }

    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Could not find a valid configuration for mmcm");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

/* Returns 1 if a PN invert is needed for the specified ADRV9010 serializer lane number,
 *  correcting the lane swaps on the daughtercard.  Returns 0 if no invert necessary.
 */
static uint8_t fpga9010_applyPcbDesLanePnInvert(uint8_t adrv9010SerLane)
{
    uint8_t fpgaDesLanePnInvert = 0;
    switch (adrv9010SerLane)
    {
        /* only includes daughtercard lane PN invert for ADRV9010EE01A */
        case 0: fpgaDesLanePnInvert = 1; break;
        case 1: fpgaDesLanePnInvert = 1; break;
        case 2: fpgaDesLanePnInvert = 1; break;
        case 3: fpgaDesLanePnInvert = 1; break;
        case 4: fpgaDesLanePnInvert = 1; break;
        case 5: fpgaDesLanePnInvert = 1; break;
        case 6: fpgaDesLanePnInvert = 1; break;
        case 7: fpgaDesLanePnInvert = 1; break;
        default: fpgaDesLanePnInvert = 0; break;
    }

    return fpgaDesLanePnInvert;
}

/* Returns 1 if a PN invert is needed for the specified ADRV9010 deserializer lane number,
 * correcting the lane swaps on the daughtercard. Returns 0 if no invert necessary.
 */
static uint8_t fpga9010_applyPcbSerLanePnInvert(uint8_t adrv9010DesLane)
{
    uint8_t fpgaSerLanePnInvert = 0;
    switch (adrv9010DesLane)
    {
        /* TODO: Move this up to board layer where lane swaps are set, as it is specific to the eval board, not the FPGA driver */
        /* only includes daughtercard lane PN invert for ADRV9010EE01A */
        case 0: fpgaSerLanePnInvert = 1; break;
        case 1: fpgaSerLanePnInvert = 0; break;
        case 2: fpgaSerLanePnInvert = 1; break;
        case 3: fpgaSerLanePnInvert = 0; break;
        case 4: fpgaSerLanePnInvert = 1; break;
        case 5: fpgaSerLanePnInvert = 0; break;
        case 6: fpgaSerLanePnInvert = 1; break;
        case 7: fpgaSerLanePnInvert = 0; break;
        default: fpgaSerLanePnInvert = 0; break;
        
    }

    return fpgaSerLanePnInvert;
}

int32_t static fpga9010_SerializerCfg(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *fpgaInit, uint8_t laneIndex, uint8_t frmOutputIndex, uint8_t dVal, uint32_t refClk_kHz, uint8_t framerSel)
{
    uint8_t fpgaLane = fpgaInit->datapath.pcbSerLaneSwap[laneIndex];
    uint32_t laneRate = fpgaInit->clocks.qpll.qpllVco_kHz / dVal;

    fpgaInit->datapath.framerCfg[framerSel].laneXbar[fpgaLane] = frmOutputIndex;

    fpgaInit->datapath.serializerCfg[fpgaLane].cpllRefClkSel = 0x01;
    fpgaInit->datapath.serializerCfg[fpgaLane].txPllClkSel = (fpgaInit->clocks.qpll.band == ADI_FPGA9010_QPLLCLK0) ? ADI_FPGA9010_QPLLCLK0 : ADI_FPGA9010_QPLLCLK1;
    fpgaInit->datapath.serializerCfg[fpgaLane].rate = dVal;
    fpgaInit->datapath.serializerCfg[fpgaLane].polarity = fpga9010_applyPcbSerLanePnInvert(laneIndex);
    fpgaInit->datapath.serializerCfg[fpgaLane].precursor = 4;
    fpgaInit->datapath.serializerCfg[fpgaLane].diffCtrl = 12;
    fpgaInit->datapath.serializerCfg[fpgaLane].powerDown = 0;
    fpgaInit->datapath.serializerCfg[fpgaLane].txClk25Div = ((uint16_t)((refClk_kHz + 25000) / 25000) - 1) << 11; /* 25000 here since Clk25 expects refClk in MHz. Also need to integer round */

    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        fpgaInit->datapath.serializerCfg[fpgaLane].postcursor = 12;
        fpgaInit->datapath.serializerCfg[fpgaLane].encoder8b10bEnable = 1;

        if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_9_GHZ && laneRate == ADI_FPGA9010_4P91_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0040;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_9P2_GHZ && laneRate == ADI_FPGA9010_9P2_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0040;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_9_GHZ && laneRate == ADI_FPGA9010_9_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0040;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_11_GHZ && laneRate == ADI_FPGA9010_11_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P28_GHZ && laneRate == ADI_FPGA9010_6P14_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P28_GHZ && laneRate == ADI_FPGA9010_12P28_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_14_GHZ && laneRate == ADI_FPGA9010_7_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_14_GHZ && laneRate == ADI_FPGA9010_14_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
        }
        else
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Unsupported FPGA clock configuration");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        fpgaInit->datapath.serializerCfg[fpgaLane].postcursor = 16;
        fpgaInit->datapath.serializerCfg[fpgaLane].encoder8b10bEnable = 0;

        if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_10_GHZ && laneRate == ADI_FPGA9010_2P53_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0040;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC388;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_10_GHZ && laneRate == ADI_FPGA9010_5_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0040;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC288;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_10_GHZ && laneRate == ADI_FPGA9010_10_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0040;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC208;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P16_GHZ && laneRate == ADI_FPGA9010_3_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC388;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P16_GHZ && laneRate == ADI_FPGA9010_6P08_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC288;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P16_GHZ && laneRate == ADI_FPGA9010_12P16_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC208;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_2P02_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC388;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_4P05_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC388;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_8_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC288;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_16_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x00D5;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC208;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_8_GHZ && laneRate == ADI_FPGA9010_8_GHZ)
        {
            fpgaInit->datapath.serializerCfg[fpgaLane].txPhdlyCfg1 = 0x0075;
            fpgaInit->datapath.serializerCfg[fpgaLane].txPiCfg3 = 0x0000;
            fpgaInit->datapath.serializerCfg[fpgaLane].txProgdivCfg = 0xC288;
        }
        else
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Unsupported FPGA clock configuration");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return ADI_COMMON_ACT_NO_ACTION;
}

int32_t static fpga9010_DeserializerCfg(adi_fpga9010_Device_t *device, adi_fpga9010_Init_t *fpgaInit, uint8_t adrv9010FramerLanexbarVal, uint8_t defInputIndex, uint8_t dVal, uint32_t refClk_kHz, uint8_t deframerSel)
{
    uint8_t fpgaLane = fpgaInit->datapath.pcbDesLaneSwap[adrv9010FramerLanexbarVal];
    uint32_t laneRate = fpgaInit->clocks.qpll.qpllVco_kHz / dVal;

    fpgaInit->datapath.deframerCfg[deframerSel].laneXbar[defInputIndex++] = fpgaInit->datapath.pcbDesLaneSwap[adrv9010FramerLanexbarVal];
    //for each deserializer used by deframer 0 setup its parameters
    fpgaInit->datapath.deserializerCfg[fpgaLane].rxPllClkSel =  (fpgaInit->clocks.qpll.band == ADI_FPGA9010_QPLLCLK0) ? ADI_FPGA9010_QPLLCLK0 : ADI_FPGA9010_QPLLCLK1;
    fpgaInit->datapath.deserializerCfg[fpgaLane].rate = dVal;
    fpgaInit->datapath.deserializerCfg[fpgaLane].polarity = fpga9010_applyPcbDesLanePnInvert(adrv9010FramerLanexbarVal);
    fpgaInit->datapath.deserializerCfg[fpgaLane].powerDown = 0;
    fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeLpmEn = 1;
    fpgaInit->datapath.deserializerCfg[fpgaLane].rxClk25Div = ((uint16_t)((refClk_kHz + 25000) / 25000) - 1) << 3; /* 25000 here since Clk25 expects refClk in MHz. Also need to integer round */
    
    if (device->devStateInfo.designId == ADI_FPGA9010_JESD204B_DEVICEID)
    {
        fpgaInit->datapath.deserializerCfg[fpgaLane].encoder8b10bEnable = 1;

        if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_9_GHZ && laneRate == ADI_FPGA9010_4P91_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0756;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0200;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;

        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_9_GHZ && laneRate == ADI_FPGA9010_9_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0766;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0200;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_9P2_GHZ && laneRate == ADI_FPGA9010_9P2_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0766;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0200;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_11_GHZ && laneRate == ADI_FPGA9010_11_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0766;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7860;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0400;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P28_GHZ && laneRate == ADI_FPGA9010_6P14_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0756;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0200;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P28_GHZ && laneRate == ADI_FPGA9010_12P28_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0766;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7860;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0200;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0400;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_14_GHZ && laneRate == ADI_FPGA9010_7_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0756;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_14_GHZ && laneRate == ADI_FPGA9010_14_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x0766;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7860;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0400;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Unsupported FPGA clock configuration");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    else if (device->devStateInfo.designId == ADI_FPGA9010_JESD204C_DEVICEID)
    {
        fpgaInit->datapath.deserializerCfg[fpgaLane].encoder8b10bEnable = 0;

        if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_10_GHZ && laneRate == ADI_FPGA9010_2P53_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07C6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC388;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_10_GHZ && laneRate == ADI_FPGA9010_5_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07D6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC288;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_10_GHZ && laneRate == ADI_FPGA9010_10_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07E6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0400;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC208;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P16_GHZ && laneRate == ADI_FPGA9010_3_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07C6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC388;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P16_GHZ && laneRate == ADI_FPGA9010_6P08_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07D6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC288;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_12P16_GHZ && laneRate == ADI_FPGA9010_12P16_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07E6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7860;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0100;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0400;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC208;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_2P02_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07B6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC388;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_4P05_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07C6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC388;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0000;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_8_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07D6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC288;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_16_GHZ && laneRate == ADI_FPGA9010_16_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0x3800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07E6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7860;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0400;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg = 0xC208;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr = 0x0004;
        }
        else if (fpgaInit->clocks.qpll.qpllVco_kHz == ADI_FPGA9010_8_GHZ && laneRate == ADI_FPGA9010_8_GHZ)
        {
            fpgaInit->datapath.deserializerCfg[fpgaLane].pmaRsv1 = 0xF800;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxCdrCfg2 = 0x07D6;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxDfeGcCfg1 = 0x7870;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg4 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxPiCfg5 = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxEnHiLr = 0x0000;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxProgdivCfg =  0xC288;
            fpgaInit->datapath.deserializerCfg[fpgaLane].rxWidemodeCdr =  0x0004;
        }
        else
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Unsupported FPGA clock configuration");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return ADI_COMMON_ACT_NO_ACTION;
}

int32_t static fpga9010_FindValidUnusedClk(uint32_t defrm0CoreClk_kHz, uint32_t defrm1CoreClk_kHz, uint32_t defrm2CoreClk_kHz, uint32_t frm0CoreClk_kHz, uint32_t frm1CoreClk_kHz)
{
    if (defrm0CoreClk_kHz != 0)
    {
        return defrm0CoreClk_kHz;
    }
    else if (defrm1CoreClk_kHz != 0)
    {
        return defrm1CoreClk_kHz;
    }
    else if (defrm2CoreClk_kHz != 0)
    {
        return defrm2CoreClk_kHz;
    }
    else if (frm0CoreClk_kHz != 0)
    {
        return frm0CoreClk_kHz;
    }
    else if (frm1CoreClk_kHz != 0)
    {
        return frm1CoreClk_kHz;
    }
    else
    {
        return 0;
    }
}

int32_t adi_fpga9010_InitConfig(adi_fpga9010_Device_t *device, adi_fpga9010_SetupFpgaCfg_t *fpgaCfg, adi_fpga9010_Init_t *fpgaInit)
{
    int32_t i = 0;

    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t fastestLaneRate_kHz = 0;
    uint32_t refClk_kHz = fpgaCfg->deviceClk_kHz;

    /* Lane rate declarations */
    uint32_t defrm0LaneRate_kHz = 0;
    uint32_t defrm1LaneRate_kHz = 0;
    uint32_t defrm2LaneRate_kHz = 0;
    uint32_t frm0LaneRate_kHz = 0;
    uint32_t frm1LaneRate_kHz = 0;

    /* Framer/Deframer clock rate declarations */
    uint32_t defrm0CoreClk_kHz = 0; // lanerate /40 for JESD204B, lanerate/66 for JESD204C
    uint32_t defrm1CoreClk_kHz = 0;
    uint32_t defrm2CoreClk_kHz = 0;
    uint32_t frm0CoreClk_kHz = 0;// lanerate /40 for JESD204B, lanerate/66 for JESD204C
    uint32_t frm1CoreClk_kHz = 0;
    uint32_t mmcmUnusedClk_kHz = 0;

    uint8_t jesd204F = 0;
    uint8_t adrv9010LanesEnabled = 0;
    uint8_t dVal = 0;

    uint8_t defrm0L = 0;
    uint8_t defrm1L = 0;
    uint8_t defrm2L = 0;
    uint8_t frm0L = 0;
    uint8_t frm1L = 0;

    uint8_t adrv9010SerLaneIndex = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);
    ADI_NULL_DEVICE_PTR_RETURN(fpgaCfg);
    ADI_NULL_PTR_RETURN(&device->common, fpgaInit);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Check that the parameters that could cause divide-by-0 faults */
    if (device->devStateInfo.linkLayerDataWidth == 0 || device->devStateInfo.encodingLowValue == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "FPGA device has not been initialized.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if (fpgaCfg->deviceClk_kHz == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, fpgaCfg->deviceClk_kHz, "deviceClk_kHz should not be 0. Verify init structures are set");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    refClk_kHz = fpgaCfg->deviceClk_kHz;

    /* Calculate L */
    for ( i = 0; i < 8; i++)
    {
        defrm0L = (defrm0L + ((fpgaCfg->deframerlink0.lanesEnabled >> i) & 1));
        defrm1L = (defrm1L + ((fpgaCfg->deframerlink1.lanesEnabled >> i) & 1));
        defrm2L = (defrm2L + ((fpgaCfg->deframerlink2.lanesEnabled >> i) & 1));
        frm0L = (frm0L + ((fpgaCfg->framerlink0.lanesEnabled >> i) & 1));
        frm1L = (frm1L + ((fpgaCfg->framerlink1.lanesEnabled >> i) & 1));
    }

    /* init the mmcm settings */
    /* calculate the framer/deframer lane rates in order to determine 
    a Qpll rate which will support all of them.*/
    if (defrm0L != 0)
    {
        defrm0LaneRate_kHz = (fpgaCfg->deframerlink0.iqRate_kHz
            * fpgaCfg->deframerlink0.jesd204M
            * fpgaCfg->deframerlink0.jesd204Np
            * device->devStateInfo.encodingHighValue) / (device->devStateInfo.encodingLowValue * defrm0L);

        defrm0CoreClk_kHz = defrm0LaneRate_kHz / device->devStateInfo.linkLayerDataWidth;
    }

    if (defrm1L != 0)
    {

        defrm1LaneRate_kHz = (fpgaCfg->deframerlink1.iqRate_kHz
            * fpgaCfg->deframerlink1.jesd204M
            * fpgaCfg->deframerlink1.jesd204Np
            * device->devStateInfo.encodingHighValue) / (device->devStateInfo.encodingLowValue * defrm1L);
        defrm1CoreClk_kHz = defrm1LaneRate_kHz / device->devStateInfo.linkLayerDataWidth;
    }

    if (defrm2L != 0)
    {
        defrm2LaneRate_kHz = fpgaCfg->deframerlink2.iqRate_kHz
            * fpgaCfg->deframerlink2.jesd204M
            * fpgaCfg->deframerlink2.jesd204Np
            * device->devStateInfo.encodingHighValue / (device->devStateInfo.encodingLowValue * defrm2L);
        defrm2CoreClk_kHz = defrm2LaneRate_kHz / device->devStateInfo.linkLayerDataWidth;
    }

    if (frm0L != 0)
    {
        frm0LaneRate_kHz = (fpgaCfg->framerlink0.iqRate_kHz
            * fpgaCfg->framerlink0.jesd204M
            * fpgaCfg->framerlink0.jesd204Np
            * device->devStateInfo.encodingHighValue) / (device->devStateInfo.encodingLowValue * frm0L);
        frm0CoreClk_kHz = frm0LaneRate_kHz / device->devStateInfo.linkLayerDataWidth;
    }

    if (frm1L != 0)
    {
        frm1LaneRate_kHz = fpgaCfg->framerlink1.iqRate_kHz
            * fpgaCfg->framerlink1.jesd204M
            * fpgaCfg->framerlink1.jesd204Np
            * device->devStateInfo.encodingHighValue / (device->devStateInfo.encodingLowValue * frm1L);
        frm1CoreClk_kHz = frm1CoreClk_kHz / device->devStateInfo.linkLayerDataWidth;
    }

    /* init the qpll settings */
    fastestLaneRate_kHz = defrm0LaneRate_kHz > defrm1LaneRate_kHz ? defrm0LaneRate_kHz : defrm1LaneRate_kHz;
    fastestLaneRate_kHz = defrm2LaneRate_kHz > fastestLaneRate_kHz ? defrm2LaneRate_kHz : fastestLaneRate_kHz;
    fastestLaneRate_kHz = frm0LaneRate_kHz > fastestLaneRate_kHz ? frm0LaneRate_kHz : fastestLaneRate_kHz;
    fastestLaneRate_kHz = frm1LaneRate_kHz > fastestLaneRate_kHz ? frm1LaneRate_kHz : fastestLaneRate_kHz;
    if (fastestLaneRate_kHz == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, serializerCfg->txPllClkSel, "All lane rates are 0 Gbps (disabled)");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = adi_fpga9010_CalculateQpllSettings(device, refClk_kHz, fastestLaneRate_kHz, &fpgaInit->clocks.qpll);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpgaInit->clocks.qpll.quadSelect = (ADI_FPGA9010_QPLL_QUAD0 | ADI_FPGA9010_QPLL_QUAD1); /* Default to setting */
    fpgaInit->clocks.qpll.refClkSelect[0] = ADI_FPGA9010_QPLL_GTNORTHREFCLK0;
    fpgaInit->clocks.qpll.refClkSelect[1] = ADI_FPGA9010_QPLL_GTREFCLK0;    

    mmcmUnusedClk_kHz = fpga9010_FindValidUnusedClk(defrm0CoreClk_kHz, defrm1CoreClk_kHz, defrm2CoreClk_kHz, frm0CoreClk_kHz, frm1CoreClk_kHz);

    /* add the required mmsm setting to support the deserializers and deframers. */
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[0] = (defrm0CoreClk_kHz == 0) ? mmcmUnusedClk_kHz : defrm0CoreClk_kHz;
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[1] = (defrm1CoreClk_kHz == 0) ? mmcmUnusedClk_kHz : defrm1CoreClk_kHz;
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[2] = (defrm2CoreClk_kHz == 0) ? mmcmUnusedClk_kHz : defrm2CoreClk_kHz;

    /* TODO: FPGA was updated to use frm0 clock for lanes 1-4, and frm1 clk for 4-7.  If framer 0 uses all 8 lanes, both clocks must be set */
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[3] = (frm0CoreClk_kHz == 0) ? ((frm1CoreClk_kHz == 0) ? mmcmUnusedClk_kHz : frm1CoreClk_kHz) : frm0CoreClk_kHz;
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[4] = (frm1CoreClk_kHz == 0) ? ((frm0CoreClk_kHz == 0) ? mmcmUnusedClk_kHz : frm0CoreClk_kHz) : frm1CoreClk_kHz;
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[5] = fastestLaneRate_kHz / device->devStateInfo.linkLayerDataWidth; /* TDD FSM frequency */
    device->devStateInfo.tddStateMachineClk_kHz = fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[5]; 
    fpgaInit->clocks.coreMmcm.outputClkFreq_kHz[6] = mmcmUnusedClk_kHz; /* unused */

    recoveryAction = adi_fpga9010_CalculateMmcmSettings(device, refClk_kHz, &fpgaInit->clocks.coreMmcm);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* init the serializer/deserializer settings */
    /* Power down all deserializer lanes in FPGA */
    for (i = 0; i < 8; i++)
    {
        fpgaInit->datapath.deserializerCfg[i].powerDown = 3;
        fpgaInit->datapath.deserializerCfg[i].rate = 1;
    }

    recoveryAction = adi_fpga9010_CalculateQpllDivisor(device, fpgaInit->clocks.qpll.qpllVco_kHz, defrm0LaneRate_kHz, &dVal);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adrv9010LanesEnabled = fpgaCfg->deframerlink0.lanesEnabled;

    /* Power up used lanes */

    uint8_t adrv9010Framer0Lanexbar[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* Each number specifies the physical ADRV9010 serializer lane */
    /*Add flexibility to handle with different lane mappings of the tranceiver LaneXbar*/
    uint8_t adrv9010Framer0LaneFramer[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            adrv9010Framer0Lanexbar[adrv9010SerLaneIndex] = adrv9010SerLaneIndex;
            switch(adrv9010SerLaneIndex)
            {
                case 0: 
                    adrv9010Framer0LaneFramer[0] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane0FramerOutSel;
                    break;
                case 1:
                    adrv9010Framer0LaneFramer[1] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane1FramerOutSel;
                    break;
                case 2:
                    adrv9010Framer0LaneFramer[2] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane2FramerOutSel;
                    break;
                case 3:
                    adrv9010Framer0LaneFramer[3] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane3FramerOutSel;
                    break;
                case 4:
                    adrv9010Framer0LaneFramer[4] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane4FramerOutSel;
                    break;
                case 5:
                    adrv9010Framer0LaneFramer[5] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane5FramerOutSel;
                    break;
                case 6:
                    adrv9010Framer0LaneFramer[6] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane6FramerOutSel;
                    break;
                case 7:
                    adrv9010Framer0LaneFramer[7] = fpgaCfg->deframerlink0.serializerLaneCrossbar.lane7FramerOutSel;
                    break;
                default:
                    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Unsupported Serdes lane selected.");
                    ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }

    uint8_t usedLaneIndex = 0;
    uint8_t tempValue = 0;
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            if (adrv9010Framer0LaneFramer[adrv9010SerLaneIndex] != usedLaneIndex)
            {
                for (i = adrv9010SerLaneIndex; i< 8; i++)
                {
                    if (adrv9010Framer0LaneFramer[i] == usedLaneIndex)
                    {
                        tempValue = adrv9010Framer0Lanexbar[i];
                        adrv9010Framer0Lanexbar[i] = adrv9010Framer0Lanexbar[adrv9010SerLaneIndex] ;
                        adrv9010Framer0Lanexbar[adrv9010SerLaneIndex] = tempValue;
                        break;
                    }
                }
            }
            usedLaneIndex++;
        }
    }
    uint8_t defInputIndex = 0;
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            recoveryAction = fpga9010_DeserializerCfg(device, fpgaInit, adrv9010Framer0Lanexbar[adrv9010SerLaneIndex], defInputIndex++, dVal, refClk_kHz, 0);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

    }

    recoveryAction = adi_fpga9010_CalculateQpllDivisor(device, fpgaInit->clocks.qpll.qpllVco_kHz, defrm1LaneRate_kHz, &dVal);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adrv9010LanesEnabled = fpgaCfg->deframerlink1.lanesEnabled;
    /* Don't reset j from loop above, continue using its value for the next valid lane. */
    uint8_t adrv9010Framer1Lanexbar[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; /*Each number specifies the physical ADRV9010 serializer lane */
    /*Add flexibility to handle with different lane mappings of the tranceiver LaneXbar*/
    uint8_t adrv9010Framer1LaneFramer[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            adrv9010Framer1Lanexbar[adrv9010SerLaneIndex] = adrv9010SerLaneIndex;
            switch(adrv9010SerLaneIndex)
            {
                case 0: 
                    adrv9010Framer1LaneFramer[0] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane0FramerOutSel;
                    break;
                case 1:
                    adrv9010Framer1LaneFramer[1] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane1FramerOutSel;
                    break;
                case 2:
                    adrv9010Framer1LaneFramer[2] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane2FramerOutSel;
                    break;
                case 3:
                    adrv9010Framer1LaneFramer[3] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane3FramerOutSel;
                    break;
                case 4:
                    adrv9010Framer1LaneFramer[4] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane4FramerOutSel;
                    break;
                case 5:
                    adrv9010Framer1LaneFramer[5] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane5FramerOutSel;
                    break;
                case 6:
                    adrv9010Framer1LaneFramer[6] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane6FramerOutSel;
                    break;
                case 7:
                    adrv9010Framer1LaneFramer[7] = fpgaCfg->deframerlink1.serializerLaneCrossbar.lane7FramerOutSel;
                    break;
                default:
                    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Unsupported Serdes lane selected.");
                    ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }
    usedLaneIndex = 0;
    tempValue = 0;
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            if (adrv9010Framer1LaneFramer[adrv9010SerLaneIndex] != usedLaneIndex)
            {
                for (i = adrv9010SerLaneIndex; i< 8; i++)
                {
                    if (adrv9010Framer1LaneFramer[i] == usedLaneIndex)
                    {
                        tempValue = adrv9010Framer1Lanexbar[i];
                        adrv9010Framer1Lanexbar[i] = adrv9010Framer1Lanexbar[adrv9010SerLaneIndex] ;
                        adrv9010Framer1Lanexbar[adrv9010SerLaneIndex] = tempValue;
                    }
                }
            }
            usedLaneIndex++;
        }
    }
    defInputIndex = 0;
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        /* for each deserializer used by deframer 1 setup its parameters */
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            recoveryAction = fpga9010_DeserializerCfg(device, fpgaInit, adrv9010Framer1Lanexbar[adrv9010SerLaneIndex], defInputIndex++, dVal, refClk_kHz, 1);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    recoveryAction = adi_fpga9010_CalculateQpllDivisor(device, fpgaInit->clocks.qpll.qpllVco_kHz, defrm2LaneRate_kHz, &dVal);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adrv9010LanesEnabled = fpgaCfg->deframerlink2.lanesEnabled;
    uint8_t adrv9010Framer2Lanexbar[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; /* Each number specifies the physical ADRV9010 serializer lane */
    /*Add flexibility to handle with different lane mappings of the tranceiver LaneXbar*/
    uint8_t adrv9010Framer2LaneFramer[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            adrv9010Framer2Lanexbar[adrv9010SerLaneIndex] = adrv9010SerLaneIndex;
            switch(adrv9010SerLaneIndex)
            {
                case 0: 
                    adrv9010Framer2LaneFramer[0] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane0FramerOutSel;
                    break;
                case 1:
                    adrv9010Framer2LaneFramer[1] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane1FramerOutSel;
                    break;
                case 2:
                    adrv9010Framer2LaneFramer[2] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane2FramerOutSel;
                    break;
                case 3:
                    adrv9010Framer2LaneFramer[3] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane3FramerOutSel;
                    break;
                case 4:
                    adrv9010Framer2LaneFramer[4] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane4FramerOutSel;
                    break;
                case 5:
                    adrv9010Framer2LaneFramer[5] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane5FramerOutSel;
                    break;
                case 6:
                    adrv9010Framer2LaneFramer[6] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane6FramerOutSel;
                    break;
                case 7:
                    adrv9010Framer2LaneFramer[7] = fpgaCfg->deframerlink2.serializerLaneCrossbar.lane7FramerOutSel;
                    break;
                default:
                    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Unsupported Serdes lane selected.");
                    ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }
    usedLaneIndex = 0;
    tempValue = 0;
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            if (adrv9010Framer2LaneFramer[adrv9010SerLaneIndex] != usedLaneIndex)
            {
                for (i = adrv9010SerLaneIndex; i< 8; i++)
                {
                    if (adrv9010Framer2LaneFramer[i] == usedLaneIndex)
                    {
                        tempValue = adrv9010Framer2Lanexbar[i];
                        adrv9010Framer2Lanexbar[i] = adrv9010Framer2Lanexbar[adrv9010SerLaneIndex] ;
                        adrv9010Framer2Lanexbar[adrv9010SerLaneIndex] = tempValue;
                    }
                }
            }
            usedLaneIndex++;
        }
    }
    defInputIndex = 0;
    for (adrv9010SerLaneIndex = 0; adrv9010SerLaneIndex < 8; adrv9010SerLaneIndex++)
    {
        /* for each deserializer used by deframer 4 setup its parameters */
        if ((adrv9010LanesEnabled >> adrv9010SerLaneIndex) & 0x1)
        {
            recoveryAction = fpga9010_DeserializerCfg(device, fpgaInit, adrv9010Framer2Lanexbar[adrv9010SerLaneIndex], defInputIndex++, dVal, refClk_kHz, 2);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    /* Power down all FPGA serializer lanes */
    for (i = 0; i < 8; i++)
    {
        fpgaInit->datapath.serializerCfg[i].powerDown = 3;
        fpgaInit->datapath.serializerCfg[i].rate = 1;

        /* Initialize Lane Xbar to 0x1F. 0x1F is the max the lane_x_select bitfield can take before error */
        fpgaInit->datapath.framerCfg[0].laneXbar[i] = 0x1F;
        fpgaInit->datapath.framerCfg[1].laneXbar[i] = 0x1F;
    }

    recoveryAction = adi_fpga9010_CalculateQpllDivisor(device, fpgaInit->clocks.qpll.qpllVco_kHz, frm0LaneRate_kHz, &dVal);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);

    adrv9010LanesEnabled = fpgaCfg->framerlink0.lanesEnabled;
    uint8_t frmOutputIndex = 0;
    for (i = 0; i < 8; i++)
    {
        /* for each serializer used by framer 0 setup its parameters */
        if ((adrv9010LanesEnabled >> i) & 0x1)
        {
            recoveryAction = fpga9010_SerializerCfg(device, fpgaInit, i, frmOutputIndex++, dVal, refClk_kHz, 0);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    recoveryAction = adi_fpga9010_CalculateQpllDivisor(device, fpgaInit->clocks.qpll.qpllVco_kHz, frm1LaneRate_kHz, &dVal);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    adrv9010LanesEnabled = fpgaCfg->framerlink1.lanesEnabled;
    frmOutputIndex = 0;
    for (i = 0; i < 8; i++)
    {
        /* for each serializer used by framer 2 setup its parameters */
        if ((adrv9010LanesEnabled >> i) & 0x1)
        {
            recoveryAction = fpga9010_SerializerCfg(device, fpgaInit, i, frmOutputIndex++, dVal, refClk_kHz, 1);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    /* init the framer/deframer settings */

    /* set deframer 0 settings */
    if (defrm0L > 0)
    {
        jesd204F = (fpgaCfg->deframerlink0.jesd204Np * fpgaCfg->deframerlink0.jesd204M * fpgaCfg->deframerlink0.jesd204S) / (8 * defrm0L);
    }

    /* Common */
    fpgaInit->datapath.deframerCfg[0].sysRefDelay = 0;
    fpgaInit->datapath.deframerCfg[0].subclassV = 1;
    fpgaInit->datapath.deframerCfg[0].lanesInUse =  (defrm0L == 8) ? 0xFF :
                                                    (defrm0L == 4) ? 0x0F :
                                                    (defrm0L == 2) ? 0x03 :
                                                    (defrm0L == 1) ? 0x01 : 0;

    /* JESD204B */
    fpgaInit->datapath.deframerCfg[0].scramblingEn = fpgaCfg->deframerlink0.scramble;
    fpgaInit->datapath.deframerCfg[0].cfgF = (defrm0L > 0) ? jesd204F : 0;
    fpgaInit->datapath.deframerCfg[0].cfgK = (uint8_t)fpgaCfg->deframerlink0.jesd204K;
    fpgaInit->datapath.deframerCfg[0].rxBufferDly = 0;
    fpgaInit->datapath.deframerCfg[0].errReportingDisable = 0;
    fpgaInit->datapath.deframerCfg[0].ilaSupportEn = 1;
    fpgaInit->datapath.deframerCfg[0].sysRefAlways = 0; 
    fpgaInit->datapath.deframerCfg[0].sysRefRequiredOnResync = 0;

    /* JESD204C */
    fpgaInit->datapath.deframerCfg[0].enableCmdInterface = 0;
    fpgaInit->datapath.deframerCfg[0].enableDataInterface = 1;
    fpgaInit->datapath.deframerCfg[0].cfgE = fpgaCfg->deframerlink0.jesd204E;
    fpgaInit->datapath.deframerCfg[0].ctrlMetaMode = 0;
    fpgaInit->datapath.deframerCfg[0].ctrlRxBufAdv = 0;
    fpgaInit->datapath.deframerCfg[0].ctrlRxMBlockTh = 1;
    fpgaInit->datapath.deframerCfg[0].ctrlIrq = 0x3FF; /* Enable all interrupts */

    /* set deframer 0 datamover settings */
    fpgaInit->datapath.rxDmaCfg[0].enableEnhancedMode = 0;
    fpgaInit->datapath.rxDmaCfg[0].enableSg = 0;
    fpgaInit->datapath.rxDmaCfg[0].simpleStartAddr = 0 * RX_DMA_SIZE;
    fpgaInit->datapath.rxDmaCfg[0].length = RX_DMA_SIZE;
    fpgaInit->datapath.rxDmaCfg[0].validDataWidthStream = (defrm0L * device->devStateInfo.dmaDataWidth / 32) - 1;
    fpgaInit->datapath.rxDmaCfg[0].sgFirstDescriptor = 0;
    fpgaInit->datapath.rxDmaCfg[0].sgLastDescriptor = 0;
    fpgaInit->datapath.rxDmaCfg[0].runStop = 0;

    /* set deframer 1 settings */
    if (defrm1L > 0)
    {
        jesd204F = (fpgaCfg->deframerlink1.jesd204Np * fpgaCfg->deframerlink1.jesd204M * fpgaCfg->deframerlink1.jesd204S) / (8 * defrm1L);
    }

    /* Common */
    fpgaInit->datapath.deframerCfg[1].sysRefDelay = 0;
    fpgaInit->datapath.deframerCfg[1].subclassV = 1;
    fpgaInit->datapath.deframerCfg[1].lanesInUse =  (defrm1L == 8) ? 0xFF :
                                                    (defrm1L == 4) ? 0x0F :
                                                    (defrm1L == 2) ? 0x03 :
                                                    (defrm1L == 1) ? 0x01 : 0;

    /* JESD204B */
    fpgaInit->datapath.deframerCfg[1].scramblingEn = fpgaCfg->deframerlink1.scramble;
    fpgaInit->datapath.deframerCfg[1].cfgF = (defrm1L > 0) ? jesd204F : 0;
    fpgaInit->datapath.deframerCfg[1].cfgK = (uint8_t)fpgaCfg->deframerlink1.jesd204K ;
    fpgaInit->datapath.deframerCfg[1].rxBufferDly = 0;
    fpgaInit->datapath.deframerCfg[1].errReportingDisable = 0;
    fpgaInit->datapath.deframerCfg[1].ilaSupportEn = 1;
    fpgaInit->datapath.deframerCfg[1].sysRefAlways = 0;
    fpgaInit->datapath.deframerCfg[1].sysRefRequiredOnResync = 0;

    /* JESD204C */
    fpgaInit->datapath.deframerCfg[1].enableCmdInterface = 0;
    fpgaInit->datapath.deframerCfg[1].enableDataInterface = 1;
    fpgaInit->datapath.deframerCfg[1].cfgE = fpgaCfg->deframerlink1.jesd204E;
    fpgaInit->datapath.deframerCfg[1].ctrlMetaMode = 0;
    fpgaInit->datapath.deframerCfg[1].ctrlRxBufAdv = 0;
    fpgaInit->datapath.deframerCfg[1].ctrlRxMBlockTh = 1;
    fpgaInit->datapath.deframerCfg[1].ctrlIrq = 0x3FF; /* Enable all interrupts */

    /* set deframer 1 datamover settings */
    fpgaInit->datapath.rxDmaCfg[1].enableEnhancedMode = 0;
    fpgaInit->datapath.rxDmaCfg[1].enableSg = 0;
    fpgaInit->datapath.rxDmaCfg[1].simpleStartAddr = 1 * RX_DMA_SIZE;
    fpgaInit->datapath.rxDmaCfg[1].length = RX_DMA_SIZE;
    fpgaInit->datapath.rxDmaCfg[1].validDataWidthStream = (defrm1L * device->devStateInfo.dmaDataWidth / 32) - 1;
    fpgaInit->datapath.rxDmaCfg[1].sgFirstDescriptor = 0;
    fpgaInit->datapath.rxDmaCfg[1].sgLastDescriptor = 0;
    fpgaInit->datapath.rxDmaCfg[1].runStop = 0;

    /* set deframer 2 settings */
    if (defrm2L > 0)
    {
        jesd204F = (fpgaCfg->deframerlink2.jesd204Np * fpgaCfg->deframerlink2.jesd204M * fpgaCfg->deframerlink2.jesd204S) / (8 * defrm2L);
    }

    /* Common */
    fpgaInit->datapath.deframerCfg[2].sysRefDelay = 0;
    fpgaInit->datapath.deframerCfg[2].subclassV = 1;
    fpgaInit->datapath.deframerCfg[2].lanesInUse =  (defrm2L == 8) ? 0xFF :
                                                    (defrm2L == 4) ? 0x0F :
                                                    (defrm2L == 2) ? 0x03 :
                                                    (defrm2L == 1) ? 0x01 : 0;

    /* JESD204B */
    fpgaInit->datapath.deframerCfg[2].scramblingEn = fpgaCfg->deframerlink2.scramble;
    fpgaInit->datapath.deframerCfg[2].cfgF = (defrm2L > 0) ? jesd204F : 0;
    fpgaInit->datapath.deframerCfg[2].cfgK = (uint8_t)fpgaCfg->deframerlink2.jesd204K;
    fpgaInit->datapath.deframerCfg[2].rxBufferDly = 0;
    fpgaInit->datapath.deframerCfg[2].errReportingDisable = 0;
    fpgaInit->datapath.deframerCfg[2].ilaSupportEn = 1;
    fpgaInit->datapath.deframerCfg[2].sysRefAlways = 0;
    fpgaInit->datapath.deframerCfg[2].sysRefRequiredOnResync = 0;

    /* JESD204C */
    fpgaInit->datapath.deframerCfg[2].enableCmdInterface = 0;
    fpgaInit->datapath.deframerCfg[2].enableDataInterface = 1;
    fpgaInit->datapath.deframerCfg[2].cfgE = fpgaCfg->deframerlink2.jesd204E;
    fpgaInit->datapath.deframerCfg[2].ctrlMetaMode = 0;
    fpgaInit->datapath.deframerCfg[2].ctrlRxBufAdv = 0;
    fpgaInit->datapath.deframerCfg[2].ctrlRxMBlockTh = 1;
    fpgaInit->datapath.deframerCfg[2].ctrlIrq = 0x3FF; /* Enable all interrupts */

    /* set deframer 2 datamover settings */
    fpgaInit->datapath.rxDmaCfg[2].enableEnhancedMode = 0;
    fpgaInit->datapath.rxDmaCfg[2].enableSg = 0;
    fpgaInit->datapath.rxDmaCfg[2].simpleStartAddr = 2 * RX_DMA_SIZE;
    fpgaInit->datapath.rxDmaCfg[2].length = RX_DMA_SIZE;
    fpgaInit->datapath.rxDmaCfg[2].validDataWidthStream = (defrm2L * device->devStateInfo.dmaDataWidth / 32) - 1;
    fpgaInit->datapath.rxDmaCfg[2].sgFirstDescriptor = 0;
    fpgaInit->datapath.rxDmaCfg[2].sgLastDescriptor = 0;
    fpgaInit->datapath.rxDmaCfg[2].runStop = 0;


   /* set framer 0 settings */
    if (frm0L > 0)
    {
        jesd204F = (fpgaCfg->framerlink0.jesd204Np  * fpgaCfg->framerlink0.jesd204M * fpgaCfg->framerlink0.jesd204S) / (8 * frm0L);
    }

    /* Common */
    fpgaInit->datapath.framerCfg[0].deviceId = fpgaCfg->framerlink0.deviceId;
    fpgaInit->datapath.framerCfg[0].bankId = 1;
    fpgaInit->datapath.framerCfg[0].subclassV = 1;
    fpgaInit->datapath.framerCfg[0].sysRefDelay = 0;
    fpgaInit->datapath.framerCfg[0].lanesInUse =    (frm0L == 8) ? 0xFF :
                                                    (frm0L == 4) ? 0x0F :
                                                    (frm0L == 2) ? 0x03 :
                                                    (frm0L == 1) ? 0x01 : 0;

    /* JESD204B */
    fpgaInit->datapath.framerCfg[0].ilaSupportEn = 1;
    fpgaInit->datapath.framerCfg[0].scramblingEn = fpgaCfg->framerlink0.scramble;
    fpgaInit->datapath.framerCfg[0].ilaMultiFrames = 4;
    fpgaInit->datapath.framerCfg[0].cfgF = (frm0L > 0) ? jesd204F : 0;
    fpgaInit->datapath.framerCfg[0].cfgK = (uint8_t)fpgaCfg->framerlink0.jesd204K;
    fpgaInit->datapath.framerCfg[0].ilaM = fpgaCfg->framerlink0.jesd204M;
    fpgaInit->datapath.framerCfg[0].ilaN = fpgaCfg->framerlink0.jesd204Np;
    fpgaInit->datapath.framerCfg[0].ilaCs = 0;
    fpgaInit->datapath.framerCfg[0].ilaNp = fpgaCfg->framerlink0.jesd204Np;
    fpgaInit->datapath.framerCfg[0].ilaS = fpgaCfg->framerlink0.jesd204S;
    fpgaInit->datapath.framerCfg[0].ilaCf = 0;
    fpgaInit->datapath.framerCfg[0].sysRefAlways = 0;
    fpgaInit->datapath.framerCfg[0].sysRefRequiredOnResync = 0;

    /* JESD204C */
    fpgaInit->datapath.framerCfg[0].enableCmdInterface = 0;
    fpgaInit->datapath.framerCfg[0].enableDataInterface = 1;
    fpgaInit->datapath.framerCfg[0].cfgE = fpgaCfg->framerlink0.jesd204E;
    fpgaInit->datapath.framerCfg[0].ctrlMetaMode = 0;
    fpgaInit->datapath.framerCfg[0].ctrlIrq = 0x3FF; /* Enable all interrupts */

    /* Prevent divide by 0 */
    if (fpgaCfg->framerlink0.jesd204Np == 0)
    {
        fpgaInit->datapath.framerCfg[0].ilaHd = 0;
    }
    else
    {
        fpgaInit->datapath.framerCfg[0].ilaHd = ((((uint16_t)(jesd204F) * 8) % fpgaCfg->framerlink0.jesd204Np) > 0) ? 1 : 0;
    }

    /* set deframer 0 datamover */
    fpgaInit->datapath.txDmaCfg[0].enableEnhancedMode = 0;
    fpgaInit->datapath.txDmaCfg[0].enableSg = 0;
    fpgaInit->datapath.txDmaCfg[0].simpleStartAddr = 0x80000000; /* First link starts on tx RAM boundary*/
    fpgaInit->datapath.txDmaCfg[0].length = TX_DMA_SIZE - 1; /* End the first link just before the next link's memory starts */
    fpgaInit->datapath.txDmaCfg[0].validDataWidthStream = (frm0L * device->devStateInfo.dmaDataWidth / 32) - 1;
    ;
    fpgaInit->datapath.txDmaCfg[0].sgFirstDescriptor = 0;
    fpgaInit->datapath.txDmaCfg[0].sgLastDescriptor = 0;
    fpgaInit->datapath.txDmaCfg[0].runStop = 0;
    fpgaInit->datapath.txDmaCfg[0].continuous = 1;

    /* set framer 1 settings */
    if (frm1L > 0)
    {
        jesd204F = (fpgaCfg->framerlink1.jesd204Np  * fpgaCfg->framerlink1.jesd204M * fpgaCfg->framerlink1.jesd204S) / (8 * frm1L);
    }

    /* Common */
    fpgaInit->datapath.framerCfg[1].deviceId = fpgaCfg->framerlink1.deviceId;
    fpgaInit->datapath.framerCfg[1].bankId = 1;
    fpgaInit->datapath.framerCfg[1].subclassV = 1;
    fpgaInit->datapath.framerCfg[1].sysRefDelay = 0;
    fpgaInit->datapath.framerCfg[1].lanesInUse =    (frm1L == 8) ? 0xFF :
                                                    (frm1L == 4) ? 0x0F :
                                                    (frm1L == 2) ? 0x03 :
                                                    (frm1L == 1) ? 0x01 : 0;

    /* JESD204B */
    fpgaInit->datapath.framerCfg[1].ilaSupportEn = 1;
    fpgaInit->datapath.framerCfg[1].scramblingEn = fpgaCfg->framerlink1.scramble;
    fpgaInit->datapath.framerCfg[1].ilaMultiFrames = 4;
    fpgaInit->datapath.framerCfg[1].cfgF = (frm1L > 0) ? jesd204F : 0;
    fpgaInit->datapath.framerCfg[1].cfgK = (uint8_t)fpgaCfg->framerlink1.jesd204K ;
    fpgaInit->datapath.framerCfg[1].ilaM = fpgaCfg->framerlink1.jesd204M;
    fpgaInit->datapath.framerCfg[1].ilaN = fpgaCfg->framerlink1.jesd204Np;
    fpgaInit->datapath.framerCfg[1].ilaCs = 0;
    fpgaInit->datapath.framerCfg[1].ilaNp = fpgaCfg->framerlink1.jesd204Np;
    fpgaInit->datapath.framerCfg[1].ilaS = fpgaCfg->framerlink1.jesd204S;
    fpgaInit->datapath.framerCfg[1].ilaCf = 0;
    fpgaInit->datapath.framerCfg[1].sysRefAlways = 0;
    fpgaInit->datapath.framerCfg[1].sysRefRequiredOnResync = 0;

    /* JESD204C */
    fpgaInit->datapath.framerCfg[1].enableCmdInterface = 0;
    fpgaInit->datapath.framerCfg[1].enableDataInterface = 1;
    fpgaInit->datapath.framerCfg[1].cfgE = fpgaCfg->framerlink1.jesd204E;
    fpgaInit->datapath.framerCfg[1].ctrlMetaMode = 0;
    fpgaInit->datapath.framerCfg[1].ctrlIrq = 0x3FF; /* Enable all interrupts */

    /* Prevent divide by 0 */
    if (fpgaCfg->framerlink1.jesd204Np == 0)
    {
        fpgaInit->datapath.framerCfg[1].ilaHd = 0;
    }
    else
    {
        fpgaInit->datapath.framerCfg[1].ilaHd = ((((uint16_t)(jesd204F) * 8) % fpgaCfg->framerlink1.jesd204Np) > 0) ? 1 : 0;
    }

    /* set deframer 0 datamover */
    fpgaInit->datapath.txDmaCfg[1].enableEnhancedMode = 0;
    fpgaInit->datapath.txDmaCfg[1].enableSg = 0;
    fpgaInit->datapath.txDmaCfg[1].simpleStartAddr = 0x80000000 + TX_DMA_SIZE; /* First link starts on tx RAM boundary*/
    fpgaInit->datapath.txDmaCfg[1].length = TX_DMA_SIZE - 1; /* End the first link just before the next link's memory starts */
    fpgaInit->datapath.txDmaCfg[1].validDataWidthStream = (frm1L * device->devStateInfo.dmaDataWidth / 32) - 1;

    fpgaInit->datapath.txDmaCfg[1].sgFirstDescriptor = 0;
    fpgaInit->datapath.txDmaCfg[1].sgLastDescriptor = 0;
    fpgaInit->datapath.txDmaCfg[1].runStop = 0;
    fpgaInit->datapath.txDmaCfg[1].continuous = 1;

    /* tollgates */
    fpgaInit->datapath.rxTollgateCfg.tollGateEdgeOrLvl = 1;
    fpgaInit->datapath.rxTollgateCfg.tollGateHiRiseOrLoFall = 1;
    fpgaInit->datapath.rxTollgateCfg.tollgateReset = 1;
    fpgaInit->datapath.rxTollgateCfg.tollGateTrigSource = ADI_FPGA9010_IMM_TRIG;

    fpgaInit->datapath.txTollgateCfg.tollGateEdgeOrLvl = 1;
    fpgaInit->datapath.txTollgateCfg.tollGateHiRiseOrLoFall = 1;
    fpgaInit->datapath.txTollgateCfg.tollgateReset = 1;
    fpgaInit->datapath.txTollgateCfg.tollGateTrigSource = ADI_FPGA9010_TX_IMM_TRIG;

    /* Setup SYNCB crossbars in FPGA */
    for(i = 0 ; i < (ADI_FPGA9010_NUM_OF_DEFRAMERS + ADI_FPGA9010_NUM_OF_FRAMERS) ; i++)
    {
        fpgaInit->datapath.syncBSel[i] = i;
    }

    return recoveryAction;
}

int32_t adi_fpga9010_FpgaConfigurationPrint(adi_fpga9010_Device_t *device)
{
    /* Read FPGA regs to verify state */
    uint32_t fpgaReg = 0;            
    uint32_t fpgaAddr;
    uint32_t recoveryAction = 0;
    int i, j, l;

    /*Physical layer*/
    fpgaAddr = 0x43400114; /* channel 0 rx control */
    for (i = 0; i < 8; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s\n", "********************************************");
        printf("%s\n", "INFO: FPGA Rx deserializer config per lane");
        printf("%s\n", "********************************************");
        printf("%s%d%s0x%x\n", "Rx channel_", i, "_rx_dfe_lpm_en: ", ((fpgaReg >> 8) & 0x01));
        printf("%s%d%s0x%x\n", "Rx channel_", i, "_rx_rate: ", ((fpgaReg >> 4) & 0x07));
        printf("%s%d%s0x%x\n", "Rx channel_", i, "_rx_8b10b_enable: ", ((fpgaReg >> 3) & 0x01));
        printf("%s%d%s0x%x\n", "Rx channel_", i, "_rx_polarity: ", ((fpgaReg >> 2) & 0x01));
        printf("%s%d%s0x%x\n", "Rx channel_", i, "_rx_powerdown: ", ((fpgaReg >> 0) & 0x03));
        printf("\n");
        fpgaAddr += 0x100;
    }

    fpgaAddr = 0x43400118; /* channel 0 tx control */
    for (i = 0; i < 8; i++)
    {

        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s\n", "********************************************");
        printf("%s\n", "INFO: FPGA Tx serializer config per lane");
        printf("%s\n", "********************************************");
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_diff_control: ", ((fpgaReg >> 24) & 0x0F));
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_precursor: ", ((fpgaReg >> 16) & 0x1F));
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_postcursor: ", ((fpgaReg >> 8) & 0x1F));
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_rate: ", ((fpgaReg >> 4) & 0x07));
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_8b10b_enable: ", ((fpgaReg >> 3) & 0x01));
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_polarity: ", ((fpgaReg >> 2) & 0x01));
        printf("%s%d%s0x%x\n", "Tx channel_", i, "_tx_powerdown: ", ((fpgaReg >> 0) & 0x03));
        printf("\n");
        fpgaAddr += 0x100;
    }

    /* Read FPGA CLK frequency detectors */
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Clocks frequency detectors");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43404010;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "rx_core_clock_0", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "rx_core_clock_1", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "rx_core_clock_2", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "tx_core_clock_0", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "tx_core_clock_1", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "tdd_clock", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "mmcm_ref_clock", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "tx_lane_0_clock", i, ": ", fpgaReg);
    fpgaAddr += 4;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%d%s%u Hz\n", "tx_lane_1_clock", i, ": ", fpgaReg);        

    /* Read FPGA deframer 0 lane crossbars */
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Deframer 0 lane crossbars");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43405004;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "rx_lane_xbar_link_0::reset: ", fpgaReg);

    fpgaAddr = 0x43405010;
    for (i = 0; i < 8; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "rx_lane_xbar_link_0::lane_", i, "_select: ", (fpgaReg & 0x1F));
        fpgaAddr += 4;
    }

    /* Read FPGA deframer 1 lane crossbars */
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Deframer 1 lane crossbars");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43406004;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "rx_lane_xbar_link_1::reset: ", fpgaReg);

    fpgaAddr = 0x43406010;
    for (i = 0; i < 8; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "rx_lane_xbar_link_1::lane_", i, "_select: ", (fpgaReg & 0x1F));
        fpgaAddr += 4;
    }

    /* Read FPGA framer 0 lane crossbars */
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Framer 0 lane crossbars");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43407004;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "tx_lane_xbar_link_0::reset: ", fpgaReg);

    fpgaAddr = 0x43407010;
    for (i = 0; i < 8; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "tx_lane_xbar_link_0::lane_", i, "_select: ", (fpgaReg & 0x1F));
        fpgaAddr += 4;
    }

    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Framer Config");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x4340A000;
    for (i = 0; i < 1; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 4, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::reset_self_clearing: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::reset_fixd: ", (fpgaReg >> 1) & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::watchdog_timer_disable: ", (fpgaReg >> 16) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 8, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::ila_support_end: ", fpgaReg & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0xC, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::scrambling_en: ", fpgaReg & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x10, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::sysref_always: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::sysref_delay: ", (fpgaReg >> 8) & 0xF);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::sysref_required_on_resync: ", (fpgaReg >> 16) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x14, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::ila_multiframes: ", fpgaReg & 0xFF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x18, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::test_mode: ", fpgaReg & 0x7);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x1C, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        for (j = 0; j < 8; j++)
        {
            printf("%s%d%s%d%s%d\n", "jesd204b_framer_", i, "::link_error_status_lane_", j, ": ", ((fpgaReg >> i * 3) & 0x3));
        }
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::rx_buffer_ovfg_alarm: ", (fpgaReg >> 29) & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::sysref_lmfc_alarm: ", (fpgaReg >> 30) & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::lane_align_alarm: ", (fpgaReg >> 31) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x20, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::cfg_f: ", fpgaReg & 0xFF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x24, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::cfg_k: ", fpgaReg & 0x1F);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x28, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::lane_in_use: ", fpgaReg & 0xFF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x2C, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::cfg_subclassv: ", fpgaReg & 0x3);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x30, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::rx_buffer_delay: ", fpgaReg & 0x3FF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x34, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::link_err_cntrs_en: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::dis_err_on_sync: ", (fpgaReg >> 8) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x38, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::sync_status: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_framer_", i, "::sysref_captured: ", (fpgaReg >> 16) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x3C, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        for (j = 0; j < 8; j++)
        {
            printf("%s%d%s%d%s%d\n", "jesd204b_framer_", i, "::link_debug_status_lane_", j, ": ", ((fpgaReg >> i * 4) & 0xF));
        }
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x810, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_m: ", fpgaReg & 0xFF);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_n: ", (fpgaReg >> 8) & 0x1F);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_np: ", (fpgaReg >> 16) & 0x1F);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_cs: ", (fpgaReg >> 24) & 0x3);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x814, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_scr: ", fpgaReg & 0x1);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_s: ", (fpgaReg >> 8) & 0x1F);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_hd: ", (fpgaReg >> 16) & 0x1);
        printf("\t%s%d%s%d\n", "jesd204b_framer_", i, "::ila_cf: ", (fpgaReg >> 24) & 0x1F);
    }
    
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Rx DMAs & Tollgates");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43101008;
    for (i = 0; i < 2; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::run_stop: ", (fpgaReg & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::enable_sg: ", ((fpgaReg >> 2) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::enable_enhanced_mode: ", ((fpgaReg >> 3) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::valid_data_width_stream: ", ((fpgaReg >> 8) & 0xF));
        
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::active: ", (fpgaReg & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::complete: ", ((fpgaReg >> 1) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::halt_complete: ", ((fpgaReg >> 2) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::overflow: ", ((fpgaReg >> 3) & 0x1));        
        
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_dma_rx_", i, "::simple_start_addr: ", fpgaReg);
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 16), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::length: ", fpgaReg);
        
        fpgaAddr += 0x1000;
    }
    fpgaAddr = 0x43103004;
    for (i = 0; i < 2; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_tollgate_rx_", i, "::reset: ", (fpgaReg & 0x1));
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_tollgate_rx_", i, "::trigger_select: ", fpgaReg);
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_tollgate_rx_", i, "::edge_level: ", fpgaReg);
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 12), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_tollgate_rx_", i, "::high_rising_low_falling: ", fpgaReg);
        
        fpgaAddr += 0x1000;
    }

    /* Read FPGA deframer 0 config */
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Deframer Config");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43408000;
    for (i = 0; i < 2; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 4, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::reset_self_clearing: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::reset_fixd: ", (fpgaReg >> 1) & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::watchdog_timer_disable: ", (fpgaReg >> 16) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 8, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_support_end: ", fpgaReg & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0xC, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::scrambling_en: ", fpgaReg & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x10, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::sysref_always: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::sysref_delay: ", (fpgaReg >> 8) & 0xF);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::sysref_required_on_resync: ", (fpgaReg >> 16) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x14, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_multiframes: ", fpgaReg & 0xFF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x18, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::test_mode: ", fpgaReg & 0x7);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x1C, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        for (j = 0; j < 8; j++)
        {
            printf("%s%d%s%d%s%d\n", "jesd204b_deframer_", i, "::link_error_status_lane_", j, ": ", ((fpgaReg >> i * 3) & 0x3));
        }
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::rx_buffer_ovfg_alarm: ", (fpgaReg >> 29) & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::sysref_lmfc_alarm: ", (fpgaReg >> 30) & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::lane_align_alarm: ", (fpgaReg >> 31) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x20, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::cfg_f: ", fpgaReg & 0xFF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x24, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::cfg_k: ", fpgaReg & 0x1F);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x28, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::lane_in_use: ", fpgaReg & 0xFF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x2C, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::cfg_subclassv: ", fpgaReg & 0x3);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x30, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::rx_buffer_delay: ", fpgaReg & 0x3FF);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x34, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::link_err_cntrs_en: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::dis_err_on_sync: ", (fpgaReg >> 8) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x38, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::sync_status: ", fpgaReg & 0x1);
        printf("%s%d%s%d\n", "jesd204b_deframer_", i, "::sysref_captured: ", (fpgaReg >> 16) & 0x1);
    
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x3C, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        for (j = 0; j < 8; j++)
        {
            printf("%s%d%s%d%s%d\n", "jesd204b_deframer_", i, "::link_debug_status_lane_", j, ": ", ((fpgaReg >> i * 4) & 0xF));
        }
    
        /* start lane specific data captured through ila */
        for (l = 0; l < 8; l++)
        {
            printf("\t%s\n", "********************************************");
            printf("\t%s%d\n", "INFO: ILA info for lane ", l);
            printf("\t%s\n", "********************************************");
            recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x800 + (0x40 * l), &fpgaReg);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_subclass: ", fpgaReg & 0x7);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_jesdv: ", (fpgaReg >> 8) & 0x7);
    
            recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x804 + (0x40 * l), &fpgaReg);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_f: ", fpgaReg & 0xFF);
    
            recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x808 + (0x40 * l), &fpgaReg);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_k: ", fpgaReg & 0x1F);
    
            recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x810 + (0x40 * l), &fpgaReg);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_m: ", fpgaReg & 0xFF);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_n: ", (fpgaReg >> 8) & 0x1F);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_np: ", (fpgaReg >> 16) & 0x1F);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_cs: ", (fpgaReg >> 24) & 0x3);
    
            recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr + 0x814 + (0x40 * l), &fpgaReg);
            ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
            ADI_ERROR_RETURN(device->common.error.newAction);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_scr: ", fpgaReg & 0x1);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_s: ", (fpgaReg >> 8) & 0x1F);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_hd: ", (fpgaReg >> 16) & 0x1);
            printf("\t%s%d%s%d\n", "jesd204b_deframer_", i, "::ila_cf: ", (fpgaReg >> 24) & 0x1F);
        }
        fpgaAddr += 0x1000;
    }
    
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Tx DMAs & Tollgates");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43201008;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_dma_tx_0::run_stop: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::continuous: ", ((fpgaReg >> 1) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::enable_sg: ", ((fpgaReg >> 2) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::enable_enhanced_mode: ", ((fpgaReg >> 3) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::valid_data_width_stream: ", ((fpgaReg >> 8) & 0xF));
    
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_dma_tx_0::active: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::complete: ", ((fpgaReg >> 1) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::halt_complete: ", ((fpgaReg >> 2) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::underflow: ", (fpgaReg & 0x8));
    
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_dma_tx_0::simple_start_addr: ", fpgaReg);
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 16), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_dma_tx_0::length: ", fpgaReg);
        
    fpgaAddr = 0x43202004;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_tollgate_tx_0::reset: ", (fpgaReg & 0x1));
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_tollgate_tx_0::trigger_select: ", fpgaReg);
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_tollgate_tx_0::edge_level: ", fpgaReg);
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 12), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_tollgate_tx_0::high_rising_low_falling: ", fpgaReg);

    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Tx Capture Control");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43200008;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_capture_control_tx::datapath_active: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_capture_control_tx::pass_token: ", ((fpgaReg >> 1) & 0x1));

    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Rx Capture Control");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43100008;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_capture_control_rx::datapath_active: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_capture_control_rx::pass_token: ", ((fpgaReg >> 1) & 0x1));
    
    return recoveryAction;
}

int32_t adi_fpga9010_FpgaDatapathCfgPrint(adi_fpga9010_Device_t *device)
{
    /* Read FPGA regs to verify state */
    uint32_t fpgaReg = 0;            
    uint32_t fpgaAddr;
    uint32_t recoveryAction = 0;
    int i;
    
    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Rx DMAs & Tollgates");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43101008;
    for (i = 0; i < 2; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::run_stop: ", (fpgaReg & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::enable_sg: ", ((fpgaReg >> 2) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::enable_enhanced_mode: ", ((fpgaReg >> 3) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::valid_data_width_stream: ", ((fpgaReg >> 8) & 0xF));
        
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::active: ", (fpgaReg & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::complete: ", ((fpgaReg >> 1) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::halt_complete: ", ((fpgaReg >> 2) & 0x1));
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::overflow: ", ((fpgaReg >> 3) & 0x1));        
        
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_dma_rx_", i, "::simple_start_addr: ", fpgaReg);
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 16), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_dma_rx_", i, "::length: ", fpgaReg);
        
        fpgaAddr += 0x1000;
    }
    fpgaAddr = 0x43103004;
    for (i = 0; i < 2; i++)
    {
        recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s%u\n", "dp_tollgate_rx_", i, "::reset: ", (fpgaReg & 0x1));
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_tollgate_rx_", i, "::trigger_select: ", fpgaReg);
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_tollgate_rx_", i, "::edge_level: ", fpgaReg);
        recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 12), &fpgaReg);
        ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);
        printf("%s%d%s0x%x\n", "dp_tollgate_rx_", i, "::high_rising_low_falling: ", fpgaReg);
        
        fpgaAddr += 0x1000;
    }

    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Tx DMAs & Tollgates");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43201008;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_dma_tx_0::run_stop: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::continuous: ", ((fpgaReg >> 1) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::enable_sg: ", ((fpgaReg >> 2) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::enable_enhanced_mode: ", ((fpgaReg >> 3) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::valid_data_width_stream: ", ((fpgaReg >> 8) & 0xF));
    
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_dma_tx_0::active: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::complete: ", ((fpgaReg >> 1) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::halt_complete: ", ((fpgaReg >> 2) & 0x1));
    printf("%s%u\n", "dp_dma_tx_0::underflow: ", ((fpgaReg >> 3) & 0x1));
    
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_dma_tx_0::simple_start_addr: ", fpgaReg);
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 16), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_dma_tx_0::length: ", fpgaReg);
        
    fpgaAddr = 0x43202004;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_tollgate_tx_0::reset: ", (fpgaReg & 0x1));
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 4), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_tollgate_tx_0::trigger_select: ", fpgaReg);
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 8), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_tollgate_tx_0::edge_level: ", fpgaReg);
    recoveryAction = adi_fpga9010_RegisterRead(device, (fpgaAddr + 12), &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s0x%x\n", "dp_tollgate_tx_0::high_rising_low_falling: ", fpgaReg);

    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Tx Capture Control");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43200008;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_capture_control_tx::datapath_active: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_capture_control_tx::pass_token: ", ((fpgaReg >> 1) & 0x1));

    printf("%s\n", "********************************************");
    printf("%s\n", "INFO: FPGA Rx Capture Control");
    printf("%s\n", "********************************************");
    fpgaAddr = 0x43100008;
    recoveryAction = adi_fpga9010_RegisterRead(device, fpgaAddr, &fpgaReg);
    ADI_ERROR_REPORT(&device->common, device->common.error.errSource, device->common.error.errCode, recoveryAction, device->common.error.varName, device->common.error.errormessage);
    ADI_ERROR_RETURN(device->common.error.newAction);
    printf("%s%u\n", "dp_capture_control_rx::datapath_active: ", (fpgaReg & 0x1));
    printf("%s%u\n", "dp_capture_control_rx::pass_token: ", ((fpgaReg >> 1) & 0x1));
    
    return recoveryAction;
}
