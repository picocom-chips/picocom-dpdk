#ifndef _ADI_MOTHERBOARD_TRX_H_
#define _ADI_MOTHERBOARD_TRX_H_

#include "adi_motherboard_trx_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
* Runtime functions
****************************************************************************
*/
/**
* \brief This function is a helper function to fill out the members of the 
*        devHalCfg structure with driver names for common platform.
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
                          const char* logFilename);

/**
* \brief This function creates a structure to hold all the necessary information for daughter card
*
* \dep_begin
* \dep_end
* 
* \param trxMotherboard Pointer to the generic structure
*
* \retval a pointer to the generic structure, null pointer if error occurs
*/
int32_t adi_daughterboard_Discover(adi_motherboard_trx_t* trxMotherboard);

/**
* \brief This function creates a generic structure to hold all the necessary information
*
* \dep_begin
* \dep_end
*
* \param trxMotherboard Pointer to the generic structure
*
* \retval ADI_HAL_GEN_SW Function could not completed
* \retval ADI_HAL_OK Function completed successfully, no action required
*/
int32_t adi_motherboard_Discover(adi_motherboard_trx_t** trxMotherboard);

/**
* \brief This function creates a generic structure to hold all the necessary information
*
* \dep_begin
* \dep_end
*
* \param trxMotherboard Pointer to the generic structure
*
* \retval ADI_HAL_GEN_SW Function could not completed
* \retval ADI_HAL_OK Function completed successfully, no action required
*/
int32_t adi_motherboard_Discover(adi_motherboard_trx_t** trxMotherboard);

/**
* \brief This function creates a generic structure to hold all the necessary information
*
* \dep_begin
* \dep_end
*
* \param trxMotherboard Pointer to the generic structure
* \param saveData Pointer to data to be save
* \param saveType initcates the type of data
*
* \retval ADI_HAL_GEN_SW Function could not completed
* \retval ADI_HAL_OK Function completed successfully, no action required
*/
int32_t adi_motherboard_SaveInfo(adi_motherboard_trx_t* trxMotherboard,
                                 uintptr_t              saveData,
                                 adrvtrx_data_save_t    saveType);

/**
* \brief This function destroy and clean up the motherboard structure
*
* \dep_begin
* \dep_end
*
* \param trxMotherboard Pointer to the generic structure
*
* \retval ADI_HAL_GEN_SW Function could not completed
* \retval ADI_HAL_OK Function completed successfully, no action required
*/
int32_t adi_motherboard_Destroy(adi_motherboard_trx_t* trxMotherboard);

#ifdef __cplusplus
}
#endif

#endif
