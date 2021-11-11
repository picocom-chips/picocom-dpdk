#ifndef _ADI_DAUGHTERBOARD_TRX_TYPES_H_
#define _ADI_DAUGHTERBOARD_TRX_TYPES_H_

#include <stdint.h>
#include "adi_common.h"
#include "adi_fmc_fru.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef ADI_BOARD_NAME_SIZE
#define ADI_BOARD_NAME_SIZE 64
#endif

#define  TRX_DAUGHTERBOARD_ATTRIBUTE_TYPE_EE                0x00000001
#define  TRX_DAUGHTERBOARD_ATTRIBUTE_PREALLOCATE_TRX_DEVICE 0x00000002

typedef enum adrvtrx_board_action
{
    TRX_BOARD_ACTION_NONE = 0,
    TRX_BOARD_ACTION_DEVICE_ALLOC,
    TRX_BOARD_ACTION_DEVICE_HWOPEN,
    TRX_BOARD_ACTION_DEVICE_HWCLOSE,
    TRX_BOARD_ACTION_CLOCK_CONFIG,
    TRX_BOARD_ACTION_DEVICE_JESD_BRINGUP,
    TRX_BOARD_ACTION_DEVICE_JESD_TX_BRINGUP,
    TRX_BOARD_ACTION_DEVICE_JESD_RX_BRINGUP,
    TRX_BOARD_ACTION_PHASE_1,
    TRX_BOARD_ACTION_PHASE_2,
    TRX_BOARD_ACTION_DATA_INTF_RESET,
    
    TRX_BOARD_ACTION_FPGA_INIT,
    TRX_BOARD_ACTION_DEVICE_AD9528_INIT,
    TRX_BOARD_ACTION__FPGA__INIT
} adrvtrx_board_action_e;

typedef struct adi_daughterboard_trx adi_daughterboard_trx_t;

/**
* \brief Data structure to hold SPI settings for all system device types
*/
typedef struct adi_adrvtrx_SpiSettings
{
    uint8_t  msbFirst;           /*!< 1 = MSB First, 0 = LSB First Bit order for SPI transaction */
    uint8_t  enSpiStreaming;     /*!< Not Recommended - most registers in ADRV9010 API are not consecutive */
    uint8_t  autoIncAddrUp;      /*!< For SPI Streaming, set address increment direction. 1= next addr = addr+1, 0:addr = addr-1 */
    uint8_t  fourWireMode;       /*!< 1: Use 4-wire SPI, 0: 3-wire SPI (SDIO pin is bidirectional). NOTE: ADI's FPGA platform always uses 4-wire mode */
    uint32_t cmosPadDrvStrength; /*!< Drive strength of CMOS pads when used as outputs (SDIO, SDO, GP_INTERRUPT, GPIO 1, GPIO 0) */
} adi_adrvtrx_SpiSettings_t;

/*
 * \brief This is a union structure to contain several structures. It is intended to either access the common pointer (which is the fist element of device structure) 
 *        or the device structure itself.
 */
typedef union adi_trxAbstract_union
{
    adi_common_Device_t* commonAbstractDevice;
    uintptr_t            fpgaAbstractDevice;  /*!< Abstract pointer to FPGA device */
    uintptr_t            trxAbstractDevice;   /*!< Abstract pointer to TRX device i.e. 9010, 9025 */
    uintptr_t            clockAbstractDevice; /*!< Abstract pointer to Clock device */
} adi_trxAbstract_union_t;

/*
 * \brief Saving some necessary information during initialization for later access.
 */
typedef struct adi_adrvtrx_MiscInfo
{
    uint8_t   enable204cState;
    uintptr_t spi2Device;
} adi_adrvtrx_MiscInfo_t;

/**
* \brief Data structure to hold devices in an daughter card
*/
typedef struct adi_daughterboard_trx
{
    /* Common device */
    adi_common_Device_t common; /*!< Pointer to common device */

    /* Initialization status */
    uint32_t initializedStatus; /*!< initialization status */
    uint32_t boardAttribute;    /*!< Board attributes */

    /* Place holder for extra parameters */
    uint32_t  parameterBucket[12];   /*!< place holder for extra scalar parameters */
    uintptr_t parameterPointers[12]; /*!< place holder for extra pointer parameters */

    /* Platform and board information */
    uint32_t               daughterCardId;                        /*!< Board (daughter card) ID */
    uint8_t                daughterCardRev[4];                    /*!< Board Revision */
    int8_t                 daughterCardStrId[6];                  /*!< Board ID string i.e. "9010", "9025" */
    int8_t                 daughterCardName[ADI_BOARD_NAME_SIZE]; /*!< Board name string */
    uint32_t               motherboardId;                         /*!< The motherboard type i.e ADS8, ADS9 etc. */
    int8_t                 motherboardName[ADI_BOARD_NAME_SIZE];  /*!< Platform name string */
    adi_adrvtrx_MiscInfo_t savedInfo;                             /*!< Saving some necessary information */

    /* Device pointers */
    uintptr_t trxDevice;   /*!< Pointer to transceiver device on board */
    uintptr_t fpgaDevice;  /*!< Pointer to FPGA device on board */
    uintptr_t clockDevice; /*!< Pointer to clock device on board */

    adi_trxAbstract_union_t trxAbstractDev;   /*!< Abstract TRX device on board */
    adi_trxAbstract_union_t fpgaAbstractDev;  /*!< Abstract FPGA device on board */
    adi_trxAbstract_union_t clockAbstractDev; /*!< Abstract CLOCK device on board */

    uintptr_t motherboardDevice; /*!< Pointer back to the motherboard which contains this daughterboard */

    /* Initialization pointers */
    uintptr_t daughterCardInit;  /*!< Init data structure configured with the profile data*/
    uintptr_t postMcsInit;       /*<! Post MCS Init structure */
    uintptr_t clockInit;         /*<! AD9528 clock device init structure */
    uintptr_t fpgaInit;          /*<! FPGA Init structure */
    uintptr_t platformFilesInit; /*<! platform files on sd card(Arm and Stream bins, Rx Gain table, Tx Atten Table) */
    uintptr_t streamSettings;    /*<! Stream settings structure */
    uintptr_t pinModeSettings;   /*<! Saved settings from profile for use in pin mode data captures */

    /* function pointers */
    /* Constructors and destructors */
    int32_t (*DeviceCreate)(adi_daughterboard_trx_t*);

    int32_t (*DeviceDestroy)(adi_daughterboard_trx_t*);

    /* Board and device initialization functions */
    int32_t (*DeviceInit)(adi_daughterboard_trx_t*);

    /* int32_t(*FpgaConfigure) (adi_daughterboard_trx_t*, uintptr_t, uintptr_t); */
    int32_t (*ClockConfigure)(adi_daughterboard_trx_t*,
                              uintptr_t               ,
                              uint32_t                ,
                              uint32_t                ,
                              uint32_t                ,
                              uint32_t                );

    /* Programming functions */
    /*int32_t (*BoardProgram)(adi_daughterboard_trx_t*, uintptr_t, uintptr_t, uintptr_t, uintptr_t); */
    int32_t (*BoardProgram)(adi_daughterboard_trx_t*);

    int32_t (*BoardJesdBringup)(adi_daughterboard_trx_t*,
                                uint32_t                ,
                                uint32_t                );

    int32_t (*BoardProgramPhase1)(adi_daughterboard_trx_t*);

    int32_t (*BoardProgramPhase2)(adi_daughterboard_trx_t*);

    int32_t (*BoardDataInterfaceReset)(adi_daughterboard_trx_t*);

    int32_t (*BoardDispatch)(adi_daughterboard_trx_t*,
                             adrvtrx_board_action_e  );

    int32_t (*FpgaDispatch)(adi_daughterboard_trx_t*,
                            adrvtrx_board_action_e  );

    int32_t (*ClockDispatch)(adi_daughterboard_trx_t*,
                             adrvtrx_board_action_e  );
} adi_daughterboard_trx_t;

#ifdef __cplusplus
}
#endif

#endif
