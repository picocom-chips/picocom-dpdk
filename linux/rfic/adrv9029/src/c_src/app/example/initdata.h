/**
* \file initdata.h
* \brief Contains extern declarations for adrv9025 data structures initializations
*
* ADRV9025 API Version: 6.0.0.41
*
*/

/**
* Copyright 2015 - 2018 Analog Devices Inc.
* Released under the adrv9025 API license, for more information
* see the "LICENSE.txt" file in this zip file.
*/
#ifndef INITDATA_H_
#define INITDATA_H_

#include "adi_adrv9025.h"
#include "adi_adrv9025_utilities.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern adi_adrv9025_ApiVersion_t    initStructApiVersion;
    extern adi_adrv9025_ArmVersion_t    initStructArmVersion;
    extern adi_adrv9025_StreamVersion_t initStructStreamVersion;
    extern adi_adrv9025_Init_t          deviceInitStruct;
    extern adi_adrv9025_PostMcsInit_t   adrv9025PostMcsInitInst;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef INITDATA_H_ */