/**
* \file adi_ad9528_utilities.c
* \brief Contains source code for AD9528 utility functions.
*/
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#include "adi_ad9528_user.h"
#include "adi_ad9528_utilities.h"
#include "adi_common_error.h"
#include "adi_common_error_types.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int32_t adi_ad9528_ConfigFileLoad(const char *configFile, adi_ad9528_Init_t *init)
{
    FILE *fp;
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    char line[ADI_AD9528_MAX_BUFFER];
    char *id_string;
    uint8_t ad9528 = 0;
    uint8_t outSource = 0;
    uint8_t outBufferCtrl = 0;
    uint8_t outAnalogDelay = 0;
    uint8_t outDigitalDelay = 0;
    uint8_t outChannelDiv = 0;
    uint8_t outFrequency_Hz = 0;
    //void *outArrayHelper = 0;
    int32_t index = 0;
    //uint8_t outArrayFillFlag = 0;
    uint32_t int32;
    int32_t ret;

#ifdef __GNUC__
    fp = fopen(configFile, "r");
#else
    fopen_s(&fp, configFile, "r");
#endif

    if (fp == NULL)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    while (fgets(line, ADI_AD9528_MAX_BUFFER, fp))
    {

        if (!ad9528 && strstr(line, "<adi_ad9528_Device_t"))
        {
            id_string = strstr(line, "id=");
            if (id_string)
            {
#ifdef __GNUC__
                if (sscanf(id_string, "id=%u", &init->deviceId) != 1)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;

                }
#else
                if (sscanf_s(id_string, "id=%u", &init->deviceId) != 1)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;

                }
#endif
            }
            else
            {
                init->deviceId = 0;
            }
            ad9528 = 1;
            continue;
        }

        if (ad9528)
        {
            if (strstr(line, "</adi_ad9528_Device_t>"))
            {
                break;
            }

            if (!outSource && strstr(line, "<outSource>"))
            {
                outSource = 1;
                //outArrayFillFlag = 1;
                //outArrayHelper = init->outputSettings.outSource;
                continue;
            }
            if (outSource && strstr(line, "</outSource>"))
            {
                outSource = 0;
                //outArrayFillFlag = 0;
                index = 0;
                continue;
            }

            if (!outBufferCtrl && strstr(line, "<outBufferCtrl>"))
            {
                outBufferCtrl = 1;
                //outArrayFillFlag = 1;
                //outArrayHelper = init->outputSettings.outBufferCtrl;
                continue;
            }
            if (outBufferCtrl && strstr(line, "</outBufferCtrl>"))
            {
                outBufferCtrl = 0;
                //outArrayFillFlag = 0;
                index = 0;
                continue;
            }

            if (!outAnalogDelay && strstr(line, "<outAnalogDelay>"))
            {
                outAnalogDelay = 1;
                //outArrayFillFlag = 1;
                //outArrayHelper = init->outputSettings.outAnalogDelay;
                continue;
            }
            if (outAnalogDelay && strstr(line, "</outAnalogDelay>"))
            {
                outAnalogDelay = 0;
                //outArrayFillFlag = 0;
                index = 0;
                continue;
            }

            if (!outDigitalDelay && strstr(line, "<outDigitalDelay>"))
            {
                outDigitalDelay = 1;
                //outArrayFillFlag = 1;
                //outArrayHelper = init->outputSettings.outDigitalDelay;
                continue;
            }
            if (outDigitalDelay && strstr(line, "</outDigitalDelay>"))
            {
                outDigitalDelay = 0;
                //outArrayFillFlag = 0;
                index = 0;
                continue;
            }

            if (!outChannelDiv && strstr(line, "<outChannelDiv>"))
            {
                outChannelDiv = 1;
                //outArrayFillFlag = 1;
               // outArrayHelper = init->outputSettings.outChannelDiv;
                continue;
            }
            if (outChannelDiv && strstr(line, "</outChannelDiv>"))
            {
                outChannelDiv = 0;
                //outArrayFillFlag = 0;
                index = 0;
                continue;
            }

            if (!outFrequency_Hz && strstr(line, "<outFrequency_Hz>"))
            {
                outFrequency_Hz = 1;
                //outArrayFillFlag = 1;
                //outArrayHelper = init->outputSettings.outFrequency_Hz;
                continue;
            }
            if (outFrequency_Hz && strstr(line, "</outFrequency_Hz>"))
            {
                outFrequency_Hz = 0;
                //outArrayFillFlag = 0;
                index = 0;
                continue;
            }

            GET_TOKEN(init->spiSettings, msbFirst, ret, line, &int32, int32);
            //GET_TOKEN(init->spiSettings, enSpiStreaming, ret, line, &int32, int32);
            GET_TOKEN(init->spiSettings, autoIncAddrUp, ret, line, &int32, int32);
            GET_TOKEN(init->spiSettings, fourWireMode, ret, line, &int32, int32);

            GET_TOKEN(init->pll1Settings, refA_Frequency_Hz, ret, line, &int32, int32);
            GET_TOKEN(init->pll1Settings, refA_Divider, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->pll1Settings, refA_bufferCtrl, adi_ad9528_RefBuffer_e, ret, line, &int32, int32);
            GET_TOKEN(init->pll1Settings, refB_Frequency_Hz, ret, line, &int32, int32);
            GET_TOKEN(init->pll1Settings, refB_Divider, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->pll1Settings, refB_bufferCtrl, adi_ad9528_RefBuffer_e, ret, line, &int32, int32);
            GET_TOKEN(init->pll1Settings, vcxo_Frequency_Hz, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->pll1Settings, vcxoBufferCtrl, adi_ad9528_RefBuffer_e, ret, line, &int32, int32);
            GET_TOKEN(init->pll1Settings, nDividerPll1, ret, line, &int32, int32);

            GET_TOKEN_CAST(init->sysrefSettings, sysrefRequestMethod, adi_ad9528_SysrefRequestMethod_e, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->sysrefSettings, sysrefSource, adi_ad9528_SysrefSourceSelection_e, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->sysrefSettings, sysrefPinEdgeMode, adi_ad9528_SysrefPinEdgeMode_e, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->sysrefSettings, sysrefPinBufferMode, adi_ad9528_RefBuffer_e, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->sysrefSettings, sysrefPatternMode, adi_ad9528_SysrefPatternMode_e, ret, line, &int32, int32);
            GET_TOKEN_CAST(init->sysrefSettings, sysrefNshotMode, adi_ad9528_SysrefNshotMode_e, ret, line, &int32, int32);
            GET_TOKEN(init->sysrefSettings, sysrefDivide, ret, line, &int32, int32);

            GET_TOKEN(init->pll2Settings, rfDivider, ret, line, &int32, int32);
            GET_TOKEN(init->pll2Settings, n2Divider, ret, line, &int32, int32);
            GET_TOKEN(init->pll2Settings, totalNdiv, ret, line, &int32, int32);

            GET_TOKEN(init->outputSettings, outPowerDown, ret, line, &int32, int32);

            if (outSource)
            {
                if (index >= ADI_AD9528_NUM_OUTPUT_CHANNELS)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;
                }
                if (sscanf_s(line, " %d", &ret) == 1) {
                    init->outputSettings.outSource[index++] = (adi_ad9528_OutSourceSel_e)ret;
                    continue;
                }
            }

            if (outBufferCtrl)
            {
                if (index >= ADI_AD9528_NUM_OUTPUT_CHANNELS)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;
                }
                if (sscanf_s(line, " %d", &ret) == 1) {
                    init->outputSettings.outBufferCtrl[index++] = (adi_ad9528_OutBufferControl_e)ret;
                    continue;
                }
            }

            if (outAnalogDelay)
            {
                if (index >= ADI_AD9528_NUM_OUTPUT_CHANNELS)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;
                }
                if (sscanf_s(line, " %d", &ret) == 1) {
                    init->outputSettings.outAnalogDelay[index++] = ret;
                    continue;
                }
            }

            if (outDigitalDelay)
            {
                if (index >= ADI_AD9528_NUM_OUTPUT_CHANNELS)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;
                }
                if (sscanf_s(line, " %d", &ret) == 1) {
                    init->outputSettings.outDigitalDelay[index++] = ret;
                    continue;
                }
            }

            if (outChannelDiv)
            {
                if (index >= ADI_AD9528_NUM_OUTPUT_CHANNELS)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;
                }
                if (sscanf_s(line, " %d", &ret) == 1) {
                    init->outputSettings.outChannelDiv[index++] = ret;
                    continue;
                }
            }

            if (outFrequency_Hz)
            {
                if (index >= ADI_AD9528_NUM_OUTPUT_CHANNELS)
                {
                    (void)fclose(fp);
                    return ADI_COMMON_ACT_ERR_CHECK_PARAM;
                }
                if (sscanf_s(line, " %d", &ret) == 1) {
                    init->outputSettings.outFrequency_Hz[index++] = ret;
                    continue;
                }
            }
        }
    }

    (void)fclose(fp);
    return recoveryAction;
}

int32_t adi_ad9528_InitStructConfig(adi_ad9528_Device_t *device, adi_ad9528_ClockFrequencySettings_t *clockFrequencies, adi_ad9528_Init_t *init)
{

    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t i = 0;
    uint8_t j = 0;
    uint32_t pll1PfdFreq_Hz = 0;
    uint8_t pll1Ndiv = 0;
    uint8_t validPll1DivSetting = 0;
    uint16_t refAdiv = 1;
    uint8_t pll2RfDiv = 3; /* Valid values 3,4,5 */
    uint16_t pll2Ndiv = 1; /* Valid values 1-256 */
    uint16_t totalPll2NDiv = 0;
    uint8_t pll2R1Div = 1; /* Valid values 1-31  */
    uint32_t pll2InputFreq_Hz = 0;
    uint64_t pll2VcoFreq_Hz = 0;
    uint64_t pll2VcoDivRFFreq_Hz = 0;
    uint16_t pll2NdivStart = 0;
    uint8_t validPll2DivSetting = 0;
    uint8_t validPll2ChannelDivSetting = 0;
    uint64_t chDivU64 = 0;
    uint64_t sysrefRetimingClock_Hz = 0;

    static const uint64_t PLL2_MIN_VCO_FREQ_HZ = 3450000000ULL;
    static const uint64_t PLL2_MAX_VCO_FREQ_HZ = 4025000000ULL;
    static const uint64_t SYSREF_MAX_RETIMING_CLOCK_FREQ_HZ = 1000000000ULL;
    
    init->outputSettings.outPowerDown = 0;
    /*******************************************************************
    * PLL1 Settings
    *******************************************************************
    */


    if (clockFrequencies->refAFrequency_Hz == 0)
    {
        /* Bypass PLL1, routing VCXO out of PLL1 */
        init->pll1Settings.nDividerPll1 = 0; //This init function always runs PLL1 at 30.72MHz Pfd rate
        init->pll1Settings.refA_bufferCtrl = ADI_AD9528_DISABLED;        //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
        init->pll1Settings.refA_Divider = 1;
        init->pll1Settings.refA_Frequency_Hz = 0;
        init->pll1Settings.refB_bufferCtrl = ADI_AD9528_DISABLED;            //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
        init->pll1Settings.refB_Divider = 1;
        init->pll1Settings.refB_Frequency_Hz = 0;
        init->pll1Settings.vcxoBufferCtrl = ADI_AD9528_DIFFERENTIAL;    //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
        init->pll1Settings.vcxo_Frequency_Hz = clockFrequencies->vcxoFrequency_Hz;
    }
    else
    {
        /* find valid PLL1 Ndiv and REFA div */
        for (pll1Ndiv = 1; pll1Ndiv < 20; pll1Ndiv++)
        {
            pll1PfdFreq_Hz = clockFrequencies->vcxoFrequency_Hz / pll1Ndiv;

            if ((pll1PfdFreq_Hz <= 110000000) && (pll1PfdFreq_Hz >= 1000000) &&
                (pll1PfdFreq_Hz <= clockFrequencies->refAFrequency_Hz) &&
                (clockFrequencies->refAFrequency_Hz % pll1PfdFreq_Hz == 0))
            {
                validPll1DivSetting = 1;
                refAdiv = clockFrequencies->refAFrequency_Hz / pll1PfdFreq_Hz;
                break;
            }
        }

        if (validPll1DivSetting == 0)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_CHECK_PARAM, ADI_COMMON_ERR_INV_PARAM, NULL, "Cannot find valid settings for PLL1");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        
        init->pll1Settings.nDividerPll1 = pll1Ndiv; //This init function always runs PLL1 at 30.72MHz Pfd rate
        init->pll1Settings.refA_bufferCtrl = ADI_AD9528_DIFFERENTIAL;        //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
        init->pll1Settings.refA_Divider = refAdiv;
        init->pll1Settings.refA_Frequency_Hz = clockFrequencies->refAFrequency_Hz;
        init->pll1Settings.refB_bufferCtrl = ADI_AD9528_DISABLED;            //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
        init->pll1Settings.refB_Divider = 1;
        init->pll1Settings.refB_Frequency_Hz = 0;
        init->pll1Settings.vcxoBufferCtrl = ADI_AD9528_NEG_SINGLE_ENDED;    //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
        init->pll1Settings.vcxo_Frequency_Hz = clockFrequencies->vcxoFrequency_Hz;
    }
    
    
    

    /*******************************************************************
    * PLL2 Settings
    *******************************************************************
    */

    /*******************************************************************
    * Output Distribution Settings
    * 9369CE02A uses the following clock outputs
    * OUT 1: FPGA REFCLK
    * OUT 3: FPGA SYSREF
    * OUT 12: DUT SYSREF
    * OUT 13: DUT REFCLK
    *******************************************************************
    */

    /* PLL 2 input clock can be several different things.  Currently hard coded by this init function to use
    * PLL 1 output (VCXO Frequency) with no scaling
    */
    validPll2DivSetting = 0;

    if ((init->pll1Settings.vcxo_Frequency_Hz == 0) ||
        (init->pll1Settings.vcxo_Frequency_Hz > 400000000))
    {
        /* TODO: VCXO max is 1200MHz if VCXO is in buffer mode */
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_CHECK_PARAM,
            ADI_COMMON_ERR_INV_PARAM, init->pll1Settings.vcxo_Frequency_Hz,
            "Invalid VCXO Frequency");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    for (pll2R1Div = 1; pll2R1Div <= 31; pll2R1Div++)
    {
        pll2InputFreq_Hz = init->pll1Settings.vcxo_Frequency_Hz / pll2R1Div;

        /* Sweep PLL2 Divider settings to find something that has a valid integer divide (3,4,5)*/
        for (pll2RfDiv = 3; pll2RfDiv <= 5; pll2RfDiv++)
        {
            pll2NdivStart = (uint16_t)(PLL2_MIN_VCO_FREQ_HZ / pll2RfDiv / pll2InputFreq_Hz);
            /* find valid PLL2 Ndiv (1-256) */
            for (pll2Ndiv = pll2NdivStart; pll2Ndiv <= 256; pll2Ndiv++)
            {
                totalPll2NDiv = pll2RfDiv * pll2Ndiv;
                if (totalPll2NDiv < 16)
                {
                    /* Continue to next PLL2 N div */
                    continue;
                }
                
                pll2VcoFreq_Hz = (uint64_t)pll2InputFreq_Hz * totalPll2NDiv;

                if (pll2VcoFreq_Hz < PLL2_MIN_VCO_FREQ_HZ)
                {
                    /* Continue to next PLL2 N div */
                    continue;
                }
                else if (pll2VcoFreq_Hz > PLL2_MAX_VCO_FREQ_HZ)
                {
                    /* Break to next PLL2 RF div */
                    break;
                }
                
                /* Loop through all desired output settings to make sure
                *  this PLL2 setting makes them all possible
                */
                validPll2ChannelDivSetting = 0;
                pll2VcoDivRFFreq_Hz = pll2VcoFreq_Hz / pll2RfDiv;
                for (i = 0; i < 14; i++)
                {
                    if ((clockFrequencies->outputClock_Hz[i] != 0) && 
                        ((clockFrequencies->outSource[i] == ADI_AD9528_CHANNEL_DIV) || (clockFrequencies->outSource[i] == ADI_AD9528_SYSREF)) &&
                        ((pll2VcoDivRFFreq_Hz % clockFrequencies->outputClock_Hz[i]) != 0))
                    {
                        validPll2ChannelDivSetting = 1;
                        break;
                    }
                }
                    
                if (validPll2ChannelDivSetting == 0)
                {

                    for (i = 0; i < 14; i++)
                    {
                        if (clockFrequencies->outputClock_Hz[i] != 0)
                        {
                            init->outputSettings.outPowerDown |= (1 << i);

                            if (clockFrequencies->outSource[i] == ADI_AD9528_CHANNEL_DIV) 
                            {
                                chDivU64 = (pll2VcoDivRFFreq_Hz / clockFrequencies->outputClock_Hz[i]);

                                if ((chDivU64 < 1) || (chDivU64 > 256))
                                {
                                    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_CHECK_PARAM, ADI_COMMON_ERR_INV_PARAM, NULL, "Cannot find valid settings for Channel divider");
                                    ADI_ERROR_RETURN(device->common.error.newAction);
                                }
                                else
                                {
                                    init->outputSettings.outChannelDiv[i] = (uint16_t)(chDivU64);
                                }
                            }
                            else if (clockFrequencies->outSource[i] == ADI_AD9528_SYSREF)
                            {
                                /* At this point we already guaranteed that pll2VcoDivRFFreq_Hz is multiple of clockFrequencies->outputClock_Hz[i] */
                                /* Iterate over all possible divider values, try to find minimum possible divider(i.e.maximize retiming clk freq)*/
                                for(j = 1; j <= 255; j++)
                                {
                                    if((pll2VcoDivRFFreq_Hz % j) == 0)
                                    {
                                        sysrefRetimingClock_Hz = pll2VcoDivRFFreq_Hz / j;
                                        if((sysrefRetimingClock_Hz < SYSREF_MAX_RETIMING_CLOCK_FREQ_HZ) && ((sysrefRetimingClock_Hz % clockFrequencies->outputClock_Hz[i]) == 0))
                                        {
                                            init->outputSettings.outChannelDiv[i] = j;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        
                        if (init->outputSettings.outChannelDiv[i] == 0)
                        {
                            init->outputSettings.outChannelDiv[i] = 20; /* Unused channel output divider, set to a valid value */
                        }
                        
                        init->outputSettings.outSource[i] = clockFrequencies->outSource[i];
                        init->outputSettings.outFrequency_Hz[i] = clockFrequencies->outputClock_Hz[i];
                        
                        /* currently hardcoded to default values */
                        init->outputSettings.outBufferCtrl[i] = ADI_AD9528_LVDS; /* LVDS, LVDS_BOOST, HSTL */
                        init->outputSettings.outAnalogDelay[i] = 0;
                        init->outputSettings.outDigitalDelay[i] = 0;
                    }


                    
                    /* Only set this to valid after checking the output clock dividers above */
                    init->pll2Settings.rfDivider = pll2RfDiv;
                    init->pll2Settings.totalNdiv = pll2RfDiv * pll2Ndiv;
                    init->pll2Settings.n2Divider = pll2Ndiv;
                    init->pll2Settings.r1Divider = pll2R1Div;
                    validPll2DivSetting = 1;
                    break;
                }
            }

            if (validPll2DivSetting == 1)
            {
                break;
            }
        }

        if (validPll2DivSetting == 1)
        {
            break;
        }
    }

    if (validPll2DivSetting == 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_CHECK_PARAM, ADI_COMMON_ERR_INV_PARAM, NULL, "Cannot find valid settings for PLL2");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* loop above asserted those bits for used output channels but powerdown bits should be negated */
    init->outputSettings.outPowerDown = (uint16_t)(~init->outputSettings.outPowerDown);
    init->sysrefSettings.sysrefDivide = 512; //SYSREF frequency = VCXO / 2 / sysrefDivde
    init->sysrefSettings.sysrefNshotMode = ADI_AD9528_ONE_PULSE;        //ONE_PULSE=0, TWO_PULSES=2, FOUR_PULSES=3, SIX_PULSES=4, EIGHT_PULSES=5
    init->sysrefSettings.sysrefPatternMode = ADI_AD9528_NSHOT;            //NSHOT=0, CONTINUOUS=1, PRBS=2, STOP=3
    init->sysrefSettings.sysrefPinBufferMode = ADI_AD9528_DISABLED;        //DISABLED = 0, SINGLE_ENDED, NEG_SINGLE_ENDED, DIFFERENTIAL
    init->sysrefSettings.sysrefPinEdgeMode = ADI_AD9528_LEVEL_ACTIVE_HIGH;    //LEVEL_ACTIVE_HIGH=0, LEVEL_ACTIVE_LOW=1, RISING_EDGE=2, FALLING_EDGE=3
    init->sysrefSettings.sysrefRequestMethod = ADI_AD9528_SPI;            //SPI=0,PIN=1
    init->sysrefSettings.sysrefSource = ADI_AD9528_INTERNAL;            //EXTERNAL=0, EXT_RESAMPLED=1, INTERNAL=2

    /* Default timeout set to 1sec */
    init->pllLockTimeout_ms = 1000;

    /* Default SPI settings */
    init->spiSettings.autoIncAddrUp = 1;
    init->spiSettings.fourWireMode = 1;
    init->spiSettings.msbFirst = 1;

    return recoveryAction;
}
