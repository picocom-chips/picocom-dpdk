/**
* \brief Contains BitField definitions to support ADRV9010 transceiver device.
*
*/

/**
* Disclaimer Legal Disclaimer
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/

#ifndef __ADRV9010_BF_HAL_TYPES_H__
#define __ADRV9010_BF_HAL_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif



typedef enum adrv9010_Bf_Error
{
    ADRV9010_BF_NO_ACTION = 10, /*!< BitField function successful. No error Detected */
    ADRV9010_BF_SPI_FAIL,      /*!< HAL SPI operation failure. SPI controller Down */
    ADRV9010_BF_CACHE_OVERFLOW /*!< The bitField Cache has exceeded the cache size */
} adrv9010_Bf_Error_e;


typedef enum adrv9010_Bf_WrCache_State
{
    ADRV9010_WR_CACHE_OFF = 0x0,
    ADRV9010_WR_HW_RMW_ON = 0x1,
    ADRV9010_WR_BF_CACHE_ON = 0x2,
    ADRV9010_WR_GLB_CACHE_ON = 0x4,
    ADRV9010_WR_GBL_MERGE_ON = 0x8
} adrv9010_Bf_WrCache_State_e;
 

typedef enum adrv9010_Bf_RdCache_State
{
    ADRV9010_RD_CACHE_OFF = 0x0,
    ADRV9010_RD_BF_CACHE_ON = 0x1,
    ADRV9010_RD_GLB_CACHE_ON = 0x2
} adrv9010_Bf_RdCache_State_e;

#ifdef __cplusplus
}
#endif

#endif // __ADRV9010_BF_HAL_TYPES_H__
