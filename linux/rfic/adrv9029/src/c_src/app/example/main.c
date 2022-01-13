/**
* \file main.c
* \brief Contains extern declarations for adrv9025 data structures initializations
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
* Copyright 2015 - 2018 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.txt" file in this zip file.
*/

#include <stdio.h>
#include "string.h"
#include "adi_platform.h"
#include "adi_adrv9025_daughter_board.h"
#include "adi_adrv9025_utilities.h"
#include "adi_adrv9025.h"
#include "adi_adrv9025_radioctrl.h"
#include "adi_adrv9025_tx.h"
#include "adi_common_error.h"
#include "adi_fpga9025.h"
#include "adi_ad9528.h"
#include "initdata.h"
#include "platform_utils/adi_fmc_fru.h"
#include "platform_utils/adi_fmc_eeprom.h"
#include "daughterboards/adi_daughterboard_trx_types.h"
#include "motherboards/adi_motherboard_trx.h"



adi_motherboard_trx_t *motherboard = NULL;

/* If Json file used for profile then set to 1
 * if structure initialization taken from "initdata.c" then set to 0*/
#define USE_JSON_FILE 0
static adi_fpga9025_Init_t fpga9025DeviceInitInst = { { { 0 } } };
static adi_ad9528_Init_t ad9528InitInst = { { 0 } };
adi_adrv9025_StreamSettings_t streamSettingsInst = { 0 };

///* Platfrom files settings */
static adi_adrv9025_PlatformFiles_t platformFiles = { {"/home/analog/adrv9025_c_example/resources/adrv9025/arm_firmware/ADRV9025_FW.bin;/home/analog/adrv9025_c_example/resources/adrv9025/arm_firmware/ADRV9025_DPDCORE_FW.bin"},
                                                      {"/home/analog/adrv9025_c_example/resources/adrv9025/arm_firmware/stream_image.bin"},
                                                      { {{"/home/analog/adrv9025_c_example/resources/adrv9025/gain_tables/RxGainTable.csv"}, 0xFF} },
                                                      1,
                                                      { {{"/home/analog/adrv9025_c_example/resources/adrv9025/gain_tables/TxAttenTable.csv"}, 0x0F} },
                                                      1};


static int32_t adi_adrv9025_EnableTxExample (adi_adrv9025_Device_t *device)
{
    int32_t recoveryAction = 0;
    
    if (device == NULL)
    {
        printf("NULL ADRV9025 device pointer\n");
        return -1;
    }
    
    /* Setup internal Tx test tone frequency */
    adi_adrv9025_TxTestToneCfg_t toneCfg = { 0 }; 
    toneCfg.txChannelMask = ADI_ADRV9025_TXALL;
    toneCfg.txToneFreq_Hz = 500000;
    toneCfg.txToneGain = ADI_ADRV9025_TX_NCO_0_DB;
    toneCfg.enable = 1;
    
    recoveryAction = adi_adrv9025_TxTestToneSet(device, &toneCfg, 1);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("Failed to setup ADRV9025 Tx Test Tone\n");
        printf("ERROR: Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               device->common.error.errCode,
               device->common.error.newAction,
               device->common.error.errFile,
               device->common.error.errFunc,
               device->common.error.errLine,
               device->common.error.varName,
               device->common.error.errormessage);
        /* Call action handler */
        return ADI_COMMON_ACT_ERR_RESET_FULL;
    }
    
    adi_adrv9025_TxAtten_t txAtten = { 0 };
    txAtten.txChannelMask = ADI_ADRV9025_TX2;
    txAtten.txAttenuation_mdB = 0; /* Back off Tx output power by 30dB */
    recoveryAction = adi_adrv9025_TxAttenSet(device, &txAtten, 1);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("Failed to set ADRV9025 Tx Attenuation\n");
        printf("ERROR: Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               device->common.error.errCode,
               device->common.error.newAction,
               device->common.error.errFile,
               device->common.error.errFunc,
               device->common.error.errLine,
               device->common.error.varName,
               device->common.error.errormessage);
        /* Call action handler */
        return ADI_COMMON_ACT_ERR_RESET_FULL;
    }
    
    /* Enable Tx1 output : NOTE, make sure transmitter outputs are 50 ohm terminated or risk
     * possible damage to Tx output
     */
    recoveryAction = adi_adrv9025_RxTxEnableSet(device, 0, ADI_ADRV9025_TXALL);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("Failed to enable ADRV9025 Tx RF output\n");
        printf("ERROR: Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               device->common.error.errCode,
               device->common.error.newAction,
               device->common.error.errFile,
               device->common.error.errFunc,
               device->common.error.errLine,
               device->common.error.varName,
               device->common.error.errormessage);
        /* Call action handler */
        return ADI_COMMON_ACT_ERR_RESET_FULL;
    }
    
    return 0;
}


int main()
{
    int32_t recoveryAction = 0;
    adi_adrv9025_Device_t *device = NULL;
    //adi_fpga9025_Device_t *fpga9025Device = NULL;
    //adi_ad9528_Device_t *ad9528Device = NULL;
    
    // Discover board and platform.
    recoveryAction = adi_motherboard_Discover(&motherboard);
    if ((recoveryAction != ADI_COMMON_HAL_OK) || (motherboard == NULL))
    {
        printf("ERROR: adi_Motherboard_Discover has failed.\n");
        return ADI_COMMON_ACT_ERR_RESET_FULL;
    }

    // Discover daughterboard.
    recoveryAction = adi_daughterboard_Discover(motherboard);
    if ((recoveryAction != ADI_COMMON_HAL_OK) || (motherboard == NULL))
    {
        printf("ERROR: ERPC-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }

    recoveryAction = adi_motherboard_SaveInfo(motherboard, (uintptr_t)&deviceInitStruct, TRX_PLATFORM_DATA_SAVE_TRX_SETTING_INIT);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: CMD-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }

    recoveryAction = adi_motherboard_SaveInfo(motherboard, (uintptr_t)&adrv9025PostMcsInitInst, TRX_PLATFORM_DATA_SAVE_TRX_SETTING_POST_MCS);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: CMD-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }

    recoveryAction = adi_motherboard_SaveInfo(motherboard, (uintptr_t)&ad9528InitInst, TRX_PLATFORM_DATA_SAVE_CLOCK_SETTING_INIT);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: CMD-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }

    recoveryAction = adi_motherboard_SaveInfo(motherboard, (uintptr_t)&fpga9025DeviceInitInst, TRX_PLATFORM_DATA_SAVE_FPGA_SETTING_INIT);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: CMD-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }

    recoveryAction = adi_motherboard_SaveInfo(motherboard, (uintptr_t)&platformFiles, TRX_PLATFORM_DATA_SAVE_TRX_SETTING_PLATFORM_FILES);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: CMD-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }

    recoveryAction = adi_motherboard_SaveInfo(motherboard, (uintptr_t)&streamSettingsInst, TRX_PLATFORM_DATA_SAVE_STREAM_SETTING_INIT);
    if (recoveryAction != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: CMD-SERVER: %s:%u has failed.\n", __func__, __LINE__);
        return (-1);
    }
    device = (adi_adrv9025_Device_t *) motherboard->daughterboards[0]->trxDevice;
    //fpga9025Device = (adi_fpga9025_Device_t*) motherboard->daughterboards[0]->fpgaDevice;
    //ad9528Device = (adi_ad9528_Device_t *) motherboard->daughterboards[0]->clockDevice;
    
    device->common.error.logEnable = 1;
    //fpga9025Device->memoryPageSize = 0x10000000;

    
    if (USE_JSON_FILE)
    {
        if ((recoveryAction = adi_adrv9025_ConfigFileLoad(device, "/home/analog/adrv9025_c_example/resources/adrv9025/profiles/public/ADRV9025Init_StdUseCase90_nonLinkSharing.profile", &deviceInitStruct)) != ADI_COMMON_ACT_NO_ACTION)
        {
            printf("Error loading the requested profile to ADRV9025 init");
            printf("ERROR: Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
                   device->common.error.errCode,
                   device->common.error.newAction,
                   device->common.error.errFile,
                   device->common.error.errFunc,
                   device->common.error.errLine,
                   device->common.error.varName,
                   device->common.error.errormessage);
            /* Call action handler */
            return ADI_COMMON_ACT_ERR_RESET_FULL;
        }
    }
    else
    {
        /* ADRV9025 settings are used from initdata.c 
         * they are already loaded in deviceInitStruct.
         * Verify that the structure was generated for the same API */
        printf("%s %d \n",__func__,__LINE__);
        adi_adrv9025_ApiVersion_t apiVersion;
        recoveryAction = adi_adrv9025_ApiVersionGet(device, &apiVersion);
        if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
        {
            printf("ERROR: adi_adrv9025_ApiVersionGet has failed.\n");
            return ADI_COMMON_ACT_ERR_RESET_FULL;
        }

        if (initStructApiVersion.majorVer != apiVersion.majorVer || initStructApiVersion.minorVer != apiVersion.minorVer || initStructApiVersion.maintenanceVer != apiVersion.maintenanceVer || initStructApiVersion.buildVer != apiVersion.buildVer)
        {
            printf("ERROR: Device initialization structure in \"initdata.c\" was generated for API version %d.%d.%d.%d, but the detected version on the device is %d.%d.%d.%d.\n\n",
                initStructApiVersion.majorVer, initStructApiVersion.minorVer, initStructApiVersion.maintenanceVer, initStructApiVersion.buildVer,
                apiVersion.majorVer, apiVersion.minorVer, apiVersion.maintenanceVer, apiVersion.buildVer);
            return ADI_COMMON_ACT_ERR_RESET_FULL;
        }
    }
#if 0
    /* Init Ad9528 */
    recoveryAction = motherboard->daughterboards[0]->ClockConfigure(
//ToDo:        motherboard->daughterboards[0], (uintptr_t)&ad9528InitInst, adrv9010InitInst.clocks.deviceClock_kHz, 122880, 122880, adrv9010InitInst.clocks.deviceClock_kHz);
                                                        motherboard->daughterboards[0], 
                                                        (uintptr_t) &ad9528InitInst,  
                                                        245760,
                                                        122880,
                                                        122880,
                                                        245760);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        return recoveryAction;
    }
#endif
    /*
    * Function will Program the devices
    */
    printf("%s %d \n",__func__,__LINE__);
    recoveryAction = motherboard->daughterboards[0]->BoardProgram(motherboard->daughterboards[0]);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("Failed to initialize ADRV9025 Board\n");
        printf("ERROR: ADRV9025 Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               device->common.error.errCode,
               device->common.error.newAction,
               device->common.error.errFile,
               device->common.error.errFunc,
               device->common.error.errLine,
               device->common.error.varName,
               device->common.error.errormessage);
	#if 0
        printf("ERROR: fpga9025Device Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               fpga9025Device->common.error.errCode,
               fpga9025Device->common.error.newAction,
               fpga9025Device->common.error.errFile,
               fpga9025Device->common.error.errFunc,
               fpga9025Device->common.error.errLine,
               fpga9025Device->common.error.varName,
               fpga9025Device->common.error.errormessage);
        printf("ERROR: ad9528Device Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               ad9528Device->common.error.errCode,
               ad9528Device->common.error.newAction,
               ad9528Device->common.error.errFile,
               ad9528Device->common.error.errFunc,
               ad9528Device->common.error.errLine,
               ad9528Device->common.error.varName,
               ad9528Device->common.error.errormessage);
	#endif
        /* Call action handler */
        return recoveryAction;
    }
    printf("%s %d \n",__func__,__LINE__);
    recoveryAction = adi_adrv9025_EnableTxExample(device);
    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("Failed to enable ADRV9025 Transmitter\n");
        printf("ERROR: Error number %d, Recovery action %d. In file %s, in function %s, in line %d, variable name %s. Error message %s.\n",
               device->common.error.errCode,
               device->common.error.newAction,
               device->common.error.errFile,
               device->common.error.errFunc,
               device->common.error.errLine,
               device->common.error.varName,
               device->common.error.errormessage);
        /* Call action handler */
        return recoveryAction;
    }

    recoveryAction = motherboard->Destroy(motherboard);
    motherboard = NULL;

    if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
    {
        printf("Failed to destroy motherboard and daughterboard\n");
        /* Call action handler */
    }

    return recoveryAction;
}

