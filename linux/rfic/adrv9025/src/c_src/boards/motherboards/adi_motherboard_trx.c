/**
 * \file adi_board_trx.c
 *
 * ADRV9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the ADRV9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_platform.h"
#include "adi_fmc_eeprom.h"
#include "adi_fmc_fru.h"
#include "adi_platform_identify.h"

#include "adi_motherboard_trx.h"
#include "adi_daughterboard_trx_dev.h"

#include <stdlib.h>
#include <string.h>

#ifdef _ADI_STS_PLATFORM
#define strncasecmp(_x,_y,_z) _strnicmp((_x),(_y),(_z))
#endif

/**
 * Platform and board discovery functions
 * This functions are called while in board discovery in order to assignate the correct HAL layer and FPGA drivers
 */

/****************************************************************************
* Local functions
****************************************************************************/

static int32_t adi_motherboard_Compare(adi_motherboard_trx_t* trxMotherboard1,
                                       adi_motherboard_trx_t* trxMotherboard2)
{
    int32_t i = 0;

    if ((trxMotherboard1 == NULL) || (trxMotherboard2 == NULL))
    {
        return ADI_FALSE;
    }

    for (i = 0; i < ADI_MAX_DAUGHTERBOARDS; i++)
    {
        if ((trxMotherboard1->daughterboards[i] != NULL) && (trxMotherboard2->daughterboards[i] != NULL))
        {
            if (trxMotherboard1->daughterboards[i]->daughterCardId != trxMotherboard2->daughterboards[i]->daughterCardId)
            {
                return ADI_FALSE;
            }
        }
        else if ((trxMotherboard1->daughterboards[i] == NULL) && (trxMotherboard2->daughterboards[i] == NULL))
        {
            continue;
        }
        else
        {
            return ADI_FALSE;
        }
    }

    return ADI_TRUE;
}

/*
 * This function is to read the EEPROM of the daughter card to learn its identity (i.e. 9010 or 9025 etc.) and fill up the FRU structure.
 */
#if 0
static FRU_DATA_t* trx_BoardReadFru(void* devHalCfg)
{
    struct FRU_DATA* fru            = NULL;
    adi_hal_Cfg_t*   halCfg         = NULL;
    uint8_t*         raw_input_data = NULL;

    if (devHalCfg == NULL)
    {
        return (0);
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS9 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->i2cCfg.drvName[0] == '\0')
    {
        return 0;
    }

    /* trx_read_file will allocate a chunk of memory to hold the FRU information */
    if ((raw_input_data = read_file(halCfg->i2cCfg.drvName)) != NULL)
    {
        fru = parse_FRU(raw_input_data);
        /* free memory allocated by trx_read_file() */
        free(raw_input_data);

        /* The parse_FRU() will return a null pointer for fru if an error occurred during reading the EEPROM, so verify a non-NULL pointer */
        if (fru == NULL)
        {
            return 0;
        }

        return fru;
    } /* if EEPROM file was readable, will still read even if daughter is not plugged on. */
    else
    {
        printf_err("ERROR: Board daughter card EEPROM not found or blank.\n");
        return (NULL);
    }

    return (0);
}

/*
 * Read the FRU data, parse the FRU data to identify the daughter card.
 */
static int32_t trx_BoardIdentify(adi_daughterboard_trx_t* trxdaughterboard)
{
    int32_t     halError                         = (int32_t)ADI_HAL_OK;
    char        productName[ADI_BOARD_NAME_SIZE] = {0};
    char*       strPtr                           = NULL;
    int         i                                = 0;
    FRU_DATA_t* fru                              = NULL;

    if (trxdaughterboard == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (ADI_HAL_NULL_PTR);
    }

#ifdef _ADI_STS_PLATFORM
    // 9025 is the default daughter board? add daughtercard name?
    trxdaughterboard->daughterCardId = ADI_BOARD_9025STSHAL;
    strncpy((char *) trxdaughterboard->daughterCardName, "Product Name:9025STSHAL; ; ; ; ; ", ADI_BOARD_NAME_SIZE);
#else

    /* Read the FRU information from EEPROM */
    fru = trx_BoardReadFru(trxdaughterboard->common.devHalInfo);
    if (fru == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (ADI_HAL_NULL_PTR);
    }

    /* Copy board name from FRU */
    if (!strncasecmp((const char *)&fru->Board_Area->manufacturer[1],
                     ADI_MANUFACTURER,
                     strlen(ADI_MANUFACTURER)))
    {
        for (i = 0; i < CUSTOM_FIELDS; i++)
        {
            /* These are ADI custom fields */
            if (fru->Board_Area->custom[i] && (fru->Board_Area->custom[i][0] & 0x3F))
            {
                switch (fru->Board_Area->custom[i][1])
                {
                case 1:
                    snprintf(productName,
                             ADI_BOARD_NAME_SIZE,
                             "%s",
                             (fru->Board_Area->custom[i] + 2));
                    break;

                    //                case 2:
                    //                    sprintf(tmp_str, "%s", fru->Board_Area->custom[i]);
                    //                    strncat(bomStr, ";BOM REV:", (infoStrSize - 1));
                    //                    strncat(infoStr, &tmp_str1[2], (infoStrSize - 1));
                    //                    break;

                default:
                    break;
                }
            }
        }
    }

    /* Save the product name string */
    if ((strPtr = strstr(productName,
                         "9010CE01")) != NULL)
    {
        trxdaughterboard->daughterCardId     = ADI_BOARD_9010CE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9010CE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9010",
                6);
    }
    else if ((strPtr = strstr(productName,
                              "9010EE01")) != NULL)
    {
        trxdaughterboard->boardAttribute |= TRX_DAUGHTERBOARD_ATTRIBUTE_TYPE_EE;
        trxdaughterboard->daughterCardId     = ADI_BOARD_9010EE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9010EE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9010",
                6);
    }
    else if ((strPtr = strstr(productName,
                              "9025CE01")) != NULL)
    {
        trxdaughterboard->daughterCardId     = ADI_BOARD_9025CE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9025CE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9025",
                6);
    }
    else if ((strPtr = strstr(productName,
             "9025EE01")) != NULL)
    {
        trxdaughterboard->boardAttribute |= TRX_DAUGHTERBOARD_ATTRIBUTE_TYPE_EE;
        trxdaughterboard->daughterCardId = ADI_BOARD_9025EE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9025EE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9025",
                6);
    }
    else if ((strPtr = strstr(productName,
             "9026CE01")) != NULL)
    {
        trxdaughterboard->daughterCardId = ADI_BOARD_9026CE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9026CE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9026",
                6);
    }    
    else if ((strPtr = strstr(productName,
              "9024CE01")) != NULL)
    {
        trxdaughterboard->daughterCardId = ADI_BOARD_9024CE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9024CE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9024",
                6);
    }
    else if ((strPtr = strstr(productName,
                              "9029CE01")) != NULL)
    {
        trxdaughterboard->daughterCardId = ADI_BOARD_9029CE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9029CE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9029",
                6);
    }
    else if ((strPtr = strstr(productName,
                              "9020CE01")) != NULL)
    {
        trxdaughterboard->daughterCardId = ADI_BOARD_9020CE01;
        trxdaughterboard->daughterCardRev[0] = *(strPtr + 8);
        sprintf((char *)trxdaughterboard->daughterCardName,
                "Product Name:9020CE01%c; : ; : ; : ; : ; ",
                trxdaughterboard->daughterCardRev[0]);
        strncpy((char *)trxdaughterboard->daughterCardStrId,
                "9020",
                6);
    }
    else
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        trxdaughterboard->daughterCardId = ADI_BOARD_UNKNOWN;
        strncpy((char *)trxdaughterboard->daughterCardName,
                "Product Name:UNKNOWN; : ; : ; : ; : ; ",
                ADI_BOARD_NAME_SIZE);
        halError = ADI_HAL_I2C_FAIL;
    }

    free(fru);
#endif
    return (halError);
}
#endif
/**
* \brief This function is a helper function to fill out the members of the 
*         devHalCfg structure with driver names for common platform.
*
* This function allows keeping the platform specific knowledge of driver names
* in this layer of code.  Higher layers of code can call this to fill out the
* devHalCfg structure correctly for the common platform.
*
* Each device gets a unique instance of the devHalCfg structure describing the
* device resources for that device, such as the SPI chip select, etc.
*
* \param interfaceMask A mask that represents which platform interfaces are required by a particular device (SPI, Logging, etc)
* \param spiChipSelect The chip select index describing the particular device 
* \param logFilename The filename of the logfile for this device.
*/
void* hal_DevHalCfgCreate(uint32_t    interfaceMask,
                          uint8_t     spiChipSelect,
                          const char* logFilename)
{
    adi_hal_Cfg_t* halCfg = (adi_hal_Cfg_t*)calloc(1,
                                                   sizeof(adi_hal_Cfg_t));

    if (halCfg == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return NULL;
    }

    /* Disable all interfaces, and enable only if they are needed by the specific device */
    halCfg->spiCfg.interfaceEnabled  = 0;
    halCfg->logCfg.interfaceEnabled  = 0;
    halCfg->bbicCfg.interfaceEnabled = 0;

    /* If device requires SPI interface */
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_SPI) > 0)
    {
        halCfg->spiCfg.interfaceEnabled = 1;
        halCfg->spiCfg.chipSelectIndex  = spiChipSelect;

        switch (spiChipSelect)
        {
        case SPI_CHIP_SELECT_0:
        {
            strncpy(halCfg->spiCfg.spidevName,
                    SPI_CHIP_DEV_PATH_0,
                    ADI_HAL_STRING_LENGTH);
            break;
        }
        case SPI_CHIP_SELECT_1:
        {
            strncpy(halCfg->spiCfg.spidevName,
                    SPI_CHIP_DEV_PATH_1,
                    ADI_HAL_STRING_LENGTH);
            break;
        }
        case SPI_CHIP_SELECT_2:
        {
            strncpy(halCfg->spiCfg.spidevName,
                    SPI_CHIP_DEV_PATH_2,
                    ADI_HAL_STRING_LENGTH);
            break;
        }
        default:
        {
            free(halCfg);
            return NULL;
        }
        }

        /* Default SPI settings */
        halCfg->spiCfg.autoIncAddrUp    = 1;
        halCfg->spiCfg.CPHA             = 0;
        halCfg->spiCfg.CPOL             = 0;
        halCfg->spiCfg.enSpiStreaming   = 0;
        halCfg->spiCfg.fourWireMode     = 1;
        halCfg->spiCfg.spiActionDisable = 0;
        halCfg->spiCfg.spiClkFreq_Hz    = 25000000;
    }

    /* If device requires Logging interface */
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_LOG) > 0)
    {
        halCfg->logCfg.interfaceEnabled = 1;
        halCfg->logCfg.logLevel         = ADI_HAL_LOG_ALL;
        strncpy(halCfg->logCfg.logFileName,
                logFilename,
                ADI_HAL_STRING_LENGTH);
        /* ensure null termination */
        halCfg->logCfg.logFileName[sizeof(halCfg->logCfg.logFileName) - 1] = '\0';
    }

    /* If device requires FPGA register interface */
    if (((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_BBICCTRL) > 0) ||
        ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_HWRESET) > 0)) /* ADS9 HWRESET interface requires BBICCTRL interface */
    {
        halCfg->bbicCfg.interfaceEnabled = 1;
        strncpy(halCfg->bbicCfg.coreRegsCfg.drvName,
                BBIC_CORE_REG_PATH,
                ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.coreRegsCfg.mapSize = MEM_SIZE_512MB; /* 512MB */
        strncpy(halCfg->bbicCfg.ramCfg.drvName,
                BBIC_RAM_PATH,
                ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.ramCfg.mapSize = MEM_SIZE_1GB; /* 1GB */
        strncpy(halCfg->bbicCfg.spiAdvRegsCfg.drvName,
                BBIC_SPI_ADV_REG_PATH,
                ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.spiAdvRegsCfg.mapSize = MEM_SIZE_16M; /* 16MB */
    }

    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_HWRESET) > 0)
    {
        halCfg->hwResetCfg.interfaceEnabled = 1;

        switch (spiChipSelect)
        {
        case SPI_CHIP_SELECT_0:
        {
            halCfg->hwResetCfg.resetPinIndex = 1; /* ADRV9025 reset pin bit position in FPGA register */
            break;
        }
        case SPI_CHIP_SELECT_1:
        {
            halCfg->hwResetCfg.resetPinIndex = 2; /* AD9528 reset pin bit position in FPGA register */
            break;
        }

        default:
            printf("ERROR: %s:%u has failed.\n",
                   __func__,
                   __LINE__);
            free(halCfg);
            return NULL;
        }
    }

    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_I2C) > 0)
    {
        halCfg->i2cCfg.interfaceEnabled = 1;
        strncpy(halCfg->i2cCfg.drvName,
        //        I2C_EEPROM_PATH,
                "/dev/i2c-2",
                ADI_HAL_STRING_LENGTH);
    }

    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_TIMER) > 0)
    {
        halCfg->timerCfg.interfaceEnabled = 1;
    }

    return halCfg;
}

int32_t adi_daughterboard_Discover(adi_motherboard_trx_t* trxMotherboard)
{
    int32_t error = ADI_COMMON_HAL_OK;

    /* Daughterboard Level */

    if (trxMotherboard == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (ADI_COMMON_HAL_GEN_SW);
    }

    /* create hal layer for this daughterboard */
    trxMotherboard->daughterboards[0]->common.devHalInfo = hal_DevHalCfgCreate((ADI_HAL_INTERFACE_LOG | ADI_HAL_INTERFACE_TIMER), SPI_CHIP_SELECT_0, "daughterBoard.txt"); 
    if (trxMotherboard->daughterboards[0]->common.devHalInfo == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (ADI_COMMON_HAL_GEN_SW);
    }

    trxMotherboard->daughterboards[0]->motherboardId = trxMotherboard->motherboardId;
#if 0
    /* Identify the daughterboard */
    error = trx_BoardIdentify(trxMotherboard->daughterboards[0]);
    if (error != ADI_HAL_OK)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (ADI_COMMON_HAL_GEN_SW);
    }	
#endif
    trxMotherboard->daughterboards[0]->daughterCardId     = ADI_BOARD_9025CE01;

    /* Initializing structure operation pointers */
    trxMotherboard->daughterboards[0]->DeviceCreate  = adi_daughterboard_Create;  /* Create devices for daughter card, clock, and fpga */
    trxMotherboard->daughterboards[0]->DeviceInit    = adi_daughterboard_Init;    /* Initialize the HAL layer and bring up devices */
    trxMotherboard->daughterboards[0]->DeviceDestroy = adi_daughterboard_Destroy; /* Bring down, Close devices and free memory */
    trxMotherboard->daughterboards[0]->BoardProgram  = adi_daughterboard_Program;
    /* Start programming multiple devices on daughtercard and motherboard */
    trxMotherboard->daughterboards[0]->ClockConfigure     = adi_daughterboard_ClockConfig; /* Configuring and initialize the clock device */
    trxMotherboard->daughterboards[0]->BoardJesdBringup   = NULL;                          /* Configuring and initialize the FPGA device */
    trxMotherboard->daughterboards[0]->BoardProgramPhase1 = adi_daughterboard_ProgramPhase1;
    /* Programming phase 1 for multiple devices on daughtercard and motherboard */
    trxMotherboard->daughterboards[0]->BoardProgramPhase2 = adi_daughterboard_ProgramPhase2;
    /* Programming phase 2 for multiple devices on daughtercard and motherboard */
    trxMotherboard->daughterboards[0]->BoardDataInterfaceReset = adi_daughterboard_DataInterfaceReset; /* Resetting the data interface  */

    /* Saving motherboard pointer */
    trxMotherboard->daughterboards[0]->motherboardDevice = (uintptr_t) trxMotherboard;

    /* Create log file for daughterboard */
    if (adi_hal_HwOpen(trxMotherboard->daughterboards[0]->common.devHalInfo) != ADI_HAL_OK)
    {
        printf("Warning: %s:%u file open has failed.\n", __func__, __LINE__);
    }
    trxMotherboard->daughterboards[0]->common.error.logEnable = 1;

    /* Create board and platform */
    error = trxMotherboard->daughterboards[0]->DeviceCreate(trxMotherboard->daughterboards[0]);
    if (error != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: BoardCreate has failed.\n");
        return (error);
    }

    /* Initializing board and platforms */
    error = trxMotherboard->daughterboards[0]->DeviceInit(trxMotherboard->daughterboards[0]);
    if (error != ADI_COMMON_HAL_OK)
    {
        printf("ERROR: BoardInit has failed.\n");
        return (error);
    }

    return (ADI_HAL_OK);
}

adi_motherboard_trx_t* adi_platform_Discover(void)
{
    int32_t error = ADI_COMMON_HAL_OK;
    /* Board Level */

    /* Generic board dummy */
    adi_motherboard_trx_t* trxMotherboard = (adi_motherboard_trx_t*)calloc(1,
                                                                           sizeof(adi_motherboard_trx_t));

    if (trxMotherboard == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (NULL);
    }
    trxMotherboard->initializedStatus = 0;

    /* Allocate daughterboard structure */
    trxMotherboard->daughterboards[0] = (adi_daughterboard_trx_t*)calloc(1,
                                                                         sizeof(adi_daughterboard_trx_t));

    if (trxMotherboard->daughterboards[0] == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        free(trxMotherboard);
        return (NULL);
    }

    /* create hal layer for this motherboard */
    trxMotherboard->common.devHalInfo = hal_DevHalCfgCreate((ADI_HAL_INTERFACE_LOG | ADI_HAL_INTERFACE_TIMER), SPI_CHIP_SELECT_0, "platformLog.txt"); 
    if (trxMotherboard->common.devHalInfo == NULL)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        free(trxMotherboard->daughterboards[0]);
        free(trxMotherboard);
        return (NULL);
    }

    trxMotherboard->initializedStatus |= ADI_DEV_CFG_CREATED;

    /* Identify the platform (motherboard) */
    error = adi_platform_Identify(&trxMotherboard->motherboardId);
    if (error != ADI_HAL_OK)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        free(trxMotherboard->common.devHalInfo);
        free(trxMotherboard->daughterboards[0]);
        free(trxMotherboard);
        return (NULL);
    }

    /* Copy motherboard name */
    if (trxMotherboard->motherboardId == ADI_ADS9_PLATFORM)
    {
        strcpy((char *)trxMotherboard->motherboardName,
               SYM2STR(ADI_ADS9_PLATFORM));
    }
    else if (trxMotherboard->motherboardId == ADI_ADS8_PLATFORM)
    {
        strcpy((char *)trxMotherboard->motherboardName,
               SYM2STR(ADI_ADS8_PLATFORM));
    }
        
    else
    {
        strcpy((char *)trxMotherboard->motherboardName,
               SYM2STR(ADI_UNKNOWN_PLATFORM));
    }

    /* Motherboard is now known, set up the platform */

    
    error = adi_hal_PlatformSetup(trxMotherboard->common.devHalInfo,
                                  (adi_hal_Platforms_e)trxMotherboard->motherboardId);
    if (error != ADI_HAL_OK)
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        free(trxMotherboard->common.devHalInfo);
        free(trxMotherboard->daughterboards[0]);
        free(trxMotherboard);
        return (NULL);
    }
    trxMotherboard->initializedStatus |= ADI_PLATFORM_CREATED;
    

    /*Creating log file for the platform*/
    if (adi_hal_HwOpen(trxMotherboard->common.devHalInfo) != ADI_HAL_OK)
    {
        printf("Warning: %s:%u file open has failed.\n", __func__, __LINE__);
    }

    trxMotherboard->common.error.logEnable = 1;

    return trxMotherboard;
}

int32_t adi_motherboard_SaveInfo(adi_motherboard_trx_t* trxMotherboard,
                                 uintptr_t              saveData,
                                 adrvtrx_data_save_t    saveType)
{
    int32_t error = ADI_COMMON_HAL_OK;

    if ((trxMotherboard == NULL) || (trxMotherboard->daughterboards[0] == NULL))
    {
        printf("ERROR: Motherboard pointer is NULL. %s:%u\n",
               __func__,
               __LINE__);
        return (ADI_HAL_GEN_SW);
    }

    /* Save the data in the structure */
    switch (saveType)
    {
    case TRX_PLATFORM_DATA_SAVE_TRX_DEVICE:
        trxMotherboard->daughterboards[0]->trxDevice = saveData;
        trxMotherboard->daughterboards[0]->boardAttribute |= TRX_DAUGHTERBOARD_ATTRIBUTE_PREALLOCATE_TRX_DEVICE;
        break;

    case TRX_PLATFORM_DATA_SAVE_TRX_SETTING_INIT:
        trxMotherboard->daughterboards[0]->daughterCardInit = saveData;
        break;

    case TRX_PLATFORM_DATA_SAVE_TRX_SETTING_POST_MCS:
        trxMotherboard->daughterboards[0]->postMcsInit = saveData;
        break;

    case TRX_PLATFORM_DATA_SAVE_TRX_SETTING_PLATFORM_FILES:
        trxMotherboard->daughterboards[0]->platformFilesInit = saveData;
        break;

    case TRX_PLATFORM_DATA_SAVE_TRX_SETTING_PIN_MODE:
        trxMotherboard->daughterboards[0]->pinModeSettings = saveData;
        break;

    case TRX_PLATFORM_DATA_SAVE_CLOCK_SETTING_INIT:
        trxMotherboard->daughterboards[0]->clockInit = saveData;
        break;

    case TRX_PLATFORM_DATA_SAVE_FPGA_SETTING_INIT:
        trxMotherboard->daughterboards[0]->fpgaInit = saveData;
        break;

    case TRX_PLATFORM_DATA_SAVE_STREAM_SETTING_INIT:
        trxMotherboard->daughterboards[0]->streamSettings = saveData;
        break;

    default:
        printf("ERROR: Unknown saving data type. %s:%u  \n",
               __func__,
               __LINE__);
        return (ADI_HAL_GEN_SW);
    }

    return (error);
}

int32_t adi_motherboard_Discover(adi_motherboard_trx_t** genericBoard)
{
    int32_t                error          = ADI_COMMON_HAL_OK;
    adi_motherboard_trx_t* trxMotherboard = NULL;
    int32_t                compareFlag    = 0;

    /* Create a device board */
    trxMotherboard = adi_platform_Discover();
    if (trxMotherboard == NULL)
    {
        error = ADI_HAL_GEN_SW;
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (error);
    }

    compareFlag = adi_motherboard_Compare(*genericBoard,
                                          trxMotherboard);
    if (*genericBoard != NULL && compareFlag == ADI_TRUE)
    {
        /* The genericBoard parameter is the same as the existing configuration. 
         * Delete the local board and return. */
        error = adi_motherboard_Destroy(trxMotherboard);
        return (error);
    }
    else if (*genericBoard != NULL && compareFlag == ADI_FALSE)
    {
        /* The genericBoard parameter was initialized for a different configuration.
         * Delete the previous configuration and proceed with initializing the current. */
        adi_motherboard_Destroy(*genericBoard);
    }
    /* The last remaining case when genericBoard == NULL signifies the first initialization and
     * should proceed with initializing normally. */

    *genericBoard = trxMotherboard;

    /* Function pointer */
    trxMotherboard->Destroy = adi_motherboard_Destroy;

    return (ADI_COMMON_HAL_OK);
}

int32_t adi_motherboard_Destroy(adi_motherboard_trx_t* trxMotherboard)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    if (trxMotherboard == NULL)
    {
        return ADI_COMMON_ACT_ERR_CHECK_PARAM;
    }

    /* bring down and free daughterboard */
    if (trxMotherboard->daughterboards[0] != NULL)
    {
        /* Bring down and free devices associated with duaghterboard */
        recoveryAction = trxMotherboard->daughterboards[0]->DeviceDestroy(trxMotherboard->daughterboards[0]);
        if (recoveryAction != ADI_COMMON_ACT_NO_ACTION)
        {
            return ADI_COMMON_ACT_ERR_CHECK_PARAM;
        }
        /* Free the daughterboard */
        free(trxMotherboard->daughterboards[0]);
        trxMotherboard->daughterboards[0] = NULL;
    }

    /* Now free the motherboard common device and structure */
    adi_hal_DevHalCfgFree((void *)trxMotherboard->common.devHalInfo);
    free((void *)trxMotherboard);
    trxMotherboard = NULL;

    return recoveryAction;
}
