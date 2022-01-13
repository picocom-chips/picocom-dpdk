/**
 * \file: adi_fpga9010_clk.c
 *
 * \brief Contains top level fpga9010 related functions
 *
 * FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_clk.h"
#include "adi_fpga9010.h"
#include "../../private/include/fpga9010_bf_xilinx_clock_wizard.h"
#include "../../private/include/fpga9010_bf_jesd204_phy_tokelau_ads8.h"

int32_t adi_fpga9010_MmcmSet(adi_fpga9010_Device_t *device, adi_fpga9010_MmcmSel_e mmcmSel, adi_fpga9010_MmcmCfg_t *mmcm)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Set base address for the correct Clock Wizard module */
    if (mmcmSel == ADI_FPGA9010_CORE_MMCM)
    {
        baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, mmcmSel, "Invalid MMCM selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Reset the clock wizard */
    recoveryAction = fpga9010_XilinxClockWizardSoftwareResetBfSet(device, baseAddr, 0xA);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resetting clock wizard");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Write the configuration registers */
    recoveryAction = fpga9010_XilinxClockWizardClkfboutMultBfSet(device, baseAddr, mmcm->mVal);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->mVal, "Error setting clock wizard M value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardDivclkDivideBfSet(device, baseAddr, mmcm->dVal);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->dVal, "Error setting clock wizard D value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout0DivideBfSet(device, baseAddr, mmcm->outputClkDiv[0]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[0], "Error setting clock wizard channel 0 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout1DivideBfSet(device, baseAddr, mmcm->outputClkDiv[1]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[1], "Error setting clock wizard channel 1 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout2DivideBfSet(device, baseAddr, mmcm->outputClkDiv[2]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[2], "Error setting clock wizard channel 2 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout3DivideBfSet(device, baseAddr, mmcm->outputClkDiv[3]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[3], "Error setting clock wizard channel 3 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout4DivideBfSet(device, baseAddr, mmcm->outputClkDiv[4]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[4], "Error setting clock wizard channel 4 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout5DivideBfSet(device, baseAddr, mmcm->outputClkDiv[5]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[5], "Error setting clock wizard channel 5 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout6DivideBfSet(device, baseAddr, mmcm->outputClkDiv[6]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, mmcm->outputClkDiv[6], "Error setting clock wizard channel 6 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Set the saddr bitfield to indicate current configuration register values are for dynamic reconfiguration*/
    recoveryAction = fpga9010_XilinxClockWizardSaddrBfSet(device, baseAddr, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting clock wizard saddr");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Set load bitfield to start the dynamic reconfiguration process*/
    recoveryAction = fpga9010_XilinxClockWizardLoadBfSet(device, baseAddr, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error starting clock wizard dynamic reconfiguration");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_MmcmGet(adi_fpga9010_Device_t *device, adi_fpga9010_MmcmSel_e mmcmSel, adi_fpga9010_MmcmCfg_t *mmcm)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Set base address for the correct Clock Wizard module */
    if (mmcmSel == ADI_FPGA9010_CORE_MMCM)
    {
        baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, mmcmSel, "Invalid MMCM selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Read the configuration registers */
    recoveryAction = fpga9010_XilinxClockWizardClkfboutMultBfGet(device, baseAddr, &mmcm->mVal);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard M value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardDivclkDivideBfGet(device, baseAddr, &mmcm->dVal);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard D value");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout0DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[0]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 0 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout1DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[1]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 1 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout2DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[2]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 2 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout3DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[3]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 3 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout4DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[4]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 4 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout5DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[5]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 5 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_XilinxClockWizardClkout6DivideBfGet(device, baseAddr, &mmcm->outputClkDiv[6]);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard channel 6 divider");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_MmcmResetSet(adi_fpga9010_Device_t *device, adi_fpga9010_MmcmSel_e mmcmSel)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Set base address for the correct Clock Wizard module */
    if (mmcmSel == ADI_FPGA9010_CORE_MMCM)
    {
        baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, mmcmSel, "Invalid MMCM selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Reset the clock wizard */
    recoveryAction = fpga9010_XilinxClockWizardSoftwareResetBfSet(device, baseAddr, 0xA);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resetting clock wizard");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9010_MmcmLockGet(adi_fpga9010_Device_t *device, adi_fpga9010_MmcmSel_e mmcmSel, uint8_t *lockBit)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, lockBit);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Set base address for the correct Clock Wizard module */
    if (mmcmSel == ADI_FPGA9010_CORE_MMCM)
    {
        baseAddr = FPGA9010_BF_JESD204_CORE_CLOCK_WIZARD;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, mmcmSel, "Invalid MMCM selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Load bit returns to 0 after reconfiguring and locked */
    recoveryAction = fpga9010_XilinxClockWizardLockedBfGet(device, baseAddr, lockBit);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading clock wizard lock bit");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;

}

int32_t adi_fpga9010_QpllSet(adi_fpga9010_Device_t *device, uint8_t quadMask, adi_fpga9010_QpllCfg_t *qPll)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint16_t mDrpVal = 0;
    uint16_t nDrpVal = 0;
    uint8_t powerGood = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, qPll);

    switch (qPll->mVal)
    {
    case 1: 
        mDrpVal = 0x0800;
        break;
    case 2:
        mDrpVal = 0x0000;
        break;
    case 3:
        mDrpVal = 0x0080;
        break;
    case 4:
        mDrpVal = 0x0100;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, qPll->mVal, "Invalid M val");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    nDrpVal = qPll->nVal - 2;
        
    /* Range checks */
    if (qPll->band > ADI_FPGA9010_QPLLCLK0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, qPll->band, "Invalid band");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /*Quad 0*/
    if ((quadMask & 0x1) == 0x1)
    {
        /* set ref clk for qpll*/
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0RefClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, qPll->refClkSelect[0]);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting ref clk for quad 0 qppl 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1RefClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, qPll->refClkSelect[0]);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting ref clk for quad 0 qppl 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        if (qPll->band == ADI_FPGA9010_QPLLCLK0)
        {
            /* Power up this qpll*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering up quad 0 qppl 0");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* Power down the other qpll in this quad*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering down quad 0 qppl 1");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Set the reset bit of the correct qpll*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resetting quad 0 qpll 0");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lpf value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_LPF_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->lpf, ADI_FPGA9010_QPLL_LPF_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 lpf value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cfg4 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_CFG4_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->cfg4, ADI_FPGA9010_QPLL_CFG4_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 cfg4 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cp value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_CP_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->cp, ADI_FPGA9010_QPLL_CP_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 cp value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->lockCfg, ADI_FPGA9010_QPLL_LOCK_CFG_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 lock cfg value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg g3 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_G3_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->lockCfgG3, ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 lock cfg g3 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* Write n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_N_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 N value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_M_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 0 M value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Ensure power good is set for all channels*/
            recoveryAction = adi_fpga9010_LanePowerGoodGet(device, 0, &powerGood);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to read power good signals from quad 0 channels");
            ADI_ERROR_RETURN(device->common.error.newAction);

            if (powerGood != 0x0F)
            {
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_RESET_FULL, ADI_FPGA9010_ERR_CHANNEL_POWER_GOOD_FAILURE, NULL, "One of more quad 0 channels reporting invalid power good");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }

            /* Clear the reset bit of the correct qpll*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to reset qpll 0");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
        }
        else
        {
            /* Power up this qpll*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering up quad 0 qppl 1");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* Power down the other qpll in this quad*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering down quad 0 qppl 0");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Set the reset bit */
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resetting quad 0 qpll 1");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lpf value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_LPF_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->lpf, ADI_FPGA9010_QPLL_LPF_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 1 lpf value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cfg4 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_CFG4_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->cfg4, ADI_FPGA9010_QPLL_CFG4_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 1 cfg4 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cp value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_CP_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->cp, ADI_FPGA9010_QPLL_CP_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 1 cp value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_LOCK_CFG_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->lockCfg, ADI_FPGA9010_QPLL_LOCK_CFG_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 1 lock cfg value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg g3 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_LOCK_CFG_G3_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD0, qPll->lockCfgG3, ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 1 lock cfg g3 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Write n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_N_ADDRESS, ADI_FPGA9010_PHY_QUAD0, nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpp 1 N value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_M_ADDRESS, ADI_FPGA9010_PHY_QUAD0, mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 0 qpll 1 M value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Ensure power good is set for all channels*/
            recoveryAction = adi_fpga9010_LanePowerGoodGet(device, 0, &powerGood);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to read power good signals from quad 0 channels");
            ADI_ERROR_RETURN(device->common.error.newAction);

            if (powerGood != 0x0F)
            {
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_RESET_FULL, ADI_FPGA9010_ERR_CHANNEL_POWER_GOOD_FAILURE, NULL, "One of more quad 0 channels reporting invalid power good");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
            
            /* Clear the reset bit*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error taking quad 0 qpll 1 out of reset");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

    }
    /* Quad 1*/
    if ((quadMask & 0x2) == 0x2)
    {
        /* set ref clk for qpll*/
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0RefClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, qPll->refClkSelect[1]);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting ref clk for quad 1 qppl 0");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1RefClkSelBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, qPll->refClkSelect[1]);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error setting ref clk for quad 1 qppl 1");
        ADI_ERROR_RETURN(device->common.error.newAction);
        
        if (qPll->band == ADI_FPGA9010_QPLLCLK0)
        {
            /* Power up this qpll*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering up quad 1 qppl 0");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* Power down the other qpll in this quad*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering down quad 1 qppl 1");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Set the reset bit*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resetting quad 1 qpll 0");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lpf value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_LPF_ADDRESS, ADI_FPGA9010_PHY_QUAD0, qPll->lpf, ADI_FPGA9010_QPLL_LPF_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 lpf value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cfg4 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_CFG4_ADDRESS, ADI_FPGA9010_PHY_QUAD0, qPll->cfg4, ADI_FPGA9010_QPLL_CFG4_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 cfg4 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cp value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_CP_ADDRESS, ADI_FPGA9010_PHY_QUAD0, qPll->cp, ADI_FPGA9010_QPLL_CP_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 cp value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_ADDRESS, ADI_FPGA9010_PHY_QUAD0, qPll->lockCfg, ADI_FPGA9010_QPLL_LOCK_CFG_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 lock cfg value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg g3 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_G3_ADDRESS, ADI_FPGA9010_PHY_QUAD0, qPll->lockCfgG3, ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 lock cfg g3 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* Write n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_N_ADDRESS, ADI_FPGA9010_PHY_QUAD1, nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpp 0 N value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK0_M_ADDRESS, ADI_FPGA9010_PHY_QUAD1, mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 M value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Ensure power good is set for all channels*/
            recoveryAction = adi_fpga9010_LanePowerGoodGet(device, 1, &powerGood);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to read power good signals from quad 0 channels");
            ADI_ERROR_RETURN(device->common.error.newAction);

            if (powerGood != 0xF0)
            {
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_RESET_FULL, ADI_FPGA9010_ERR_CHANNEL_POWER_GOOD_FAILURE, NULL, "One of more quad 1 channels reporting invalid power good");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
            
            /* Clear reset bit */
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to reset qpll 1");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            /* Power up this qpll*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering up quad 1 qppl 1");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* Power down the other qpll in this quad*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0PdBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error powering down quad 1 qppl 0");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Set the reset bit*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 1);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error resetting quad 1 qpll 1");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            /* write lpf value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_LPF_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD1, qPll->lpf, ADI_FPGA9010_QPLL_LPF_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 1 lpf value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cfg4 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_CFG4_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD1, qPll->cfg4, ADI_FPGA9010_QPLL_CFG4_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 1 cfg4 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cp value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_CP_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD1, qPll->cp, ADI_FPGA9010_QPLL_CP_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 1 cp value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_LOCK_CFG_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD1, qPll->lockCfg, ADI_FPGA9010_QPLL_LOCK_CFG_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 0 lock cfg value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg g3 value */
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_LOCK_CFG_G3_ADDRESS, (uint8_t)ADI_FPGA9010_PHY_QUAD1, qPll->lockCfgG3, ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 1 lock cfg g3 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Write n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_N_ADDRESS, ADI_FPGA9010_PHY_QUAD1, nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpp 1 N value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpWrite(device, ADI_FPGA9010_QPLLCLK1_M_ADDRESS, ADI_FPGA9010_PHY_QUAD1, mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error writing to quad 1 qpll 1 M value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Ensure power good is set for all channels*/
            recoveryAction = adi_fpga9010_LanePowerGoodGet(device, 1, &powerGood);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to read power good signals from quad 0 channels");
            ADI_ERROR_RETURN(device->common.error.newAction);

            if (powerGood != 0xF0)
            {
                ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ACT_ERR_RESET_FULL, ADI_FPGA9010_ERR_CHANNEL_POWER_GOOD_FAILURE, NULL, "One of more quad 1 channels reporting invalid power good");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
            
            /* Clear reset bit*/
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1ResetBfSet(device, FPGA9010_BF_TOKELAU_JESD_PHY, 0);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error trying to reset qpll 1");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

//int32_t adi_fpga9010_QpllGet(adi_fpga9010_Device_t *device, adi_fpga9010_QpllSel_e qpllSel, adi_fpga9010_QpllCfg_t *qPll)
int32_t adi_fpga9010_QpllGet(adi_fpga9010_Device_t *device, adi_fpga9010_Qpll_Quad_e quadSel, adi_fpga9010_LaneClkSel_e bandSel, adi_fpga9010_QpllCfg_t *qPll)
{
    int recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint16_t mDrpVal = 0;
    uint16_t nDrpVal = 0;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);
    
    ADI_NULL_PTR_RETURN(&device->common, qPll);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    if (quadSel == ADI_FPGA9010_QPLL_QUAD0)
    {
        if (bandSel == ADI_FPGA9010_QPLLCLK0)
        {
            /* Read n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_N_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 0 qppl 0 N value");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_M_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 0 qppl 0 M value");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lpf value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_LPF_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->lpf, ADI_FPGA9010_QPLL_LPF_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 0 qpll 0 lpf value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cfg4 value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_CFG4_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->cfg4, ADI_FPGA9010_QPLL_CFG4_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 0 qpll 0 cfg4 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cp value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_CP_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->cp, ADI_FPGA9010_QPLL_CP_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 0 qpll 0 cp value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->lockCfg, ADI_FPGA9010_QPLL_LOCK_CFG_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 0 qpll 0 lock cfg value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg g3 value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_G3_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->lockCfgG3, ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 0 qpll 0 lock cfg g3 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else if (bandSel == ADI_FPGA9010_QPLLCLK1)
        {
            /* Read n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK1_N_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 0 qppl 1 N value");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK1_M_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 0 qppl 1 M value");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else 
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid qpll band selection");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    else if  (quadSel == ADI_FPGA9010_QPLL_QUAD1)
    {
        if (bandSel == ADI_FPGA9010_QPLLCLK0)
        {
            /* Read n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_N_ADDRESS, ADI_FPGA9010_PHY_QUAD1, &nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 1 qppl 0 N value");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_M_ADDRESS, ADI_FPGA9010_PHY_QUAD1, &mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 1 qppl 0 M value");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lpf value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_LPF_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->lpf, ADI_FPGA9010_QPLL_LPF_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 1 qpll 0 lpf value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cfg4 value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_CFG4_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->cfg4, ADI_FPGA9010_QPLL_CFG4_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 1 qpll 0 cfg4 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write cp value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_CP_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->cp, ADI_FPGA9010_QPLL_CP_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 1 qpll 0 cp value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->lockCfg, ADI_FPGA9010_QPLL_LOCK_CFG_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 1 qpll 0 lock cfg value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* write lock cfg g3 value */
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK0_LOCK_CFG_G3_ADDRESS, ADI_FPGA9010_PHY_QUAD0, &qPll->lockCfgG3, ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Error reading to quad 1 qpll 0 lock cfg g3 value through DRP");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else if (bandSel == ADI_FPGA9010_QPLLCLK1)
        {
            /* Read n and m values through DRP transactions*/
            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK1_N_ADDRESS, ADI_FPGA9010_PHY_QUAD1, &nDrpVal, ADI_FPGA9010_QPLL_N_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 1 qppl 1 N value");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9010_DrpRead(device, ADI_FPGA9010_QPLLCLK1_M_ADDRESS, ADI_FPGA9010_PHY_QUAD1, &mDrpVal, ADI_FPGA9010_QPLL_M_MASK);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Unable to read quad 1 qppl 1 M value");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else 
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid qpll band selection");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    else 
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "Invalid qpll Quad selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    switch (mDrpVal)
    {
    case 0x0800: 
        qPll->mVal = 1;
        break;
    case 0x0000:
        qPll->mVal = 2;
        break;
    case 0x0080:
        qPll->mVal = 3;
        break;
    case 0x0100:
        qPll->mVal = 4;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEHAL, ADI_FPGA9010_ERR_DRP_ERROR, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Invalid M val reported from DRP");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    switch (nDrpVal)
    {
    case 0x000E:
        qPll->nVal = 16;
        break;
    case 0x0012:
        nDrpVal = 20;
        break;
    case 0x001E:
        nDrpVal = 32;
        break;
    case 0x0026:
        nDrpVal = 40;
        break;
    case 0x003A:
        nDrpVal = 60;
        break;
    case 0x003E:
        nDrpVal = 64;
        break;
    case 0x0040:
        nDrpVal = 66;
        break;
    case 0x0049:
        nDrpVal = 75;
        break;
    case 0x004E:
        nDrpVal = 80;
        break;
    case 0x0052:
        nDrpVal = 84;
        break;
    case 0x005A:
        nDrpVal = 90;
        break;
    case 0x005E:
        nDrpVal = 96;
        break;
    case 0x0062:
        nDrpVal = 100;
        break;
    case 0x006E:
        nDrpVal = 112;
        break;
    case 0x0076:
        nDrpVal = 120;
        break;
    case 0x007B:
        nDrpVal = 125;
        break;
    case 0x0094:
        nDrpVal = 150;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_DEVICEHAL, ADI_FPGA9010_ERR_DRP_ERROR, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Invalid N val reported from DRP");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }
    
    return recoveryAction;
}

int32_t adi_fpga9010_QpllLockGet(adi_fpga9010_Device_t *device, uint8_t quadSel, uint8_t bandSel, uint8_t *lockBit)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, lockBit);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    if (quadSel == ADI_FPGA9010_QPLL_QUAD0)
    {
        if (bandSel == ADI_FPGA9010_QPLLCLK0)
        {
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0LockBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, lockBit);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read quad 0 qpll0 lock bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1LockBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, lockBit);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read quad 0 qpll 1 lock bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

    }
    else if (quadSel == ADI_FPGA9010_QPLL_QUAD1)
    {
        if (bandSel == ADI_FPGA9010_QPLLCLK0)
        {
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0LockBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, lockBit);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read quad 1 qpll0 lock bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        else
        {
            recoveryAction = fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1LockBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, lockBit);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read quad 1 qpll 1 lock bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    else
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, quadSel, "Invalid quad selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;

}

int32_t adi_fpga9010_LanePowerGoodGet(adi_fpga9010_Device_t *device, uint8_t quadSel, uint8_t *powerGood)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t bfReturn = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, powerGood);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif
    
    /* Range checks */    
    if (quadSel > 1)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, quadSel, "Invalid quad selection");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *powerGood = 0;

    if (quadSel == 0)
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel0GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 0 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 0;

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel1GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 1 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 1;

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel2GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 2 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 2;

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel3GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 3 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 3;
    }
    else
    {
        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel4GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 4 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 4;

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel5GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 5 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 5;

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel6GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 6 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 6;

        recoveryAction = fpga9010_Jesd204PhyTokelauAds8Channel7GtpowergoodBfGet(device, FPGA9010_BF_TOKELAU_JESD_PHY, &bfReturn);
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, recoveryAction, NULL, "Could not read channel 7 power good");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *powerGood |= (bfReturn & 0x01) << 7;
    }

    return recoveryAction;

}
