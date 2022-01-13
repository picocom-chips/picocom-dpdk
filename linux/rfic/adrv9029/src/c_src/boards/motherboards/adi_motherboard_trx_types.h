#ifndef _ADI_MOTHERBOARD_TRX_TYPES_H_
#define _ADI_MOTHERBOARD_TRX_TYPES_H_

#include <stdint.h>
#include "adi_common.h"
#include "adi_fmc_fru.h"
#include "adi_daughterboard_trx_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ADI_MAX_DAUGHTERBOARDS                    2
#define ADI_BOARD_NAME_SIZE                      64

typedef enum adrvtrx_data_save
{
    TRX_PLATFORM_DATA_SAVE_TRX_DEVICE = 1,
    TRX_PLATFORM_DATA_SAVE_TRX_SETTING_INIT,
    TRX_PLATFORM_DATA_SAVE_TRX_SETTING_POST_MCS,
    TRX_PLATFORM_DATA_SAVE_TRX_SETTING_PLATFORM_FILES,
    TRX_PLATFORM_DATA_SAVE_TRX_SETTING_PIN_MODE,
    TRX_PLATFORM_DATA_SAVE_CLOCK_SETTING_INIT,
    TRX_PLATFORM_DATA_SAVE_FPGA_SETTING_INIT,
    TRX_PLATFORM_DATA_SAVE_STREAM_SETTING_INIT
} adrvtrx_data_save_t;

typedef struct adi_daughterboard_trx adi_daughterboard_trx_t;
typedef struct adi_motherboard_trx   adi_motherboard_trx_t;

/**
* \brief Data structure to hold devices in an daughter card
*/
typedef struct adi_motherboard_trx
{
    /* Common device */
    adi_common_Device_t common; /*!< Pointer to common device */

    /* Initialization status */
    uint32_t initializedStatus; /*!< initialization status */

    uint32_t motherboardId;                        /*!< The motherboard type i.e ADS8, ADS9 etc. */
    int8_t   motherboardName[ADI_BOARD_NAME_SIZE]; /*!< Platform name string */

    /* Array of daughter boards pointers */
    adi_daughterboard_trx_t* daughterboards[ADI_MAX_DAUGHTERBOARDS];

    /* function pointers */
    /* Constructors and destructors */
    int32_t (*Create)(adi_motherboard_trx_t*);

    int32_t (*Destroy)(adi_motherboard_trx_t*);

    /* Programming functions */
    int32_t (*BoardProgram)(adi_motherboard_trx_t*);

    int32_t (*BoardJesdBringup)(adi_motherboard_trx_t*,
                                uint32_t              ,
                                uint32_t              );

    int32_t (*BoardProgramPhase1)(adi_motherboard_trx_t*);

    int32_t (*BoardProgramPhase2)(adi_motherboard_trx_t*);
}             adi_motherboard_trx_t;

#ifdef __cplusplus
}
#endif

#endif
