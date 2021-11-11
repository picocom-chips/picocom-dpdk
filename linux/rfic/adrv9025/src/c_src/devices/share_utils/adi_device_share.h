#ifndef _ADI_DEVICE_SHARE_H_
#define _ADI_DEVICE_SHARE_H_

#include <stdint.h>
#include "adi_common.h"
#include "adi_ad9528_types.h"
#include "adi_adrv9025_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* Runtime functions
****************************************************************************
*/


/**
 * \brief This function uses a combination of adrv9025 device and ad9528 clock chip
 *        to test and see if sysref's are meeting timing requirements in a given clock chip state
 *
 *
 * This function iterates over 32 coarse adjustments for the ad9528 clock chip and reads back the setup and hold time 
 * for this given setting. 
 * Optionally you can enable fine measurement which sets the ad9528 fine adjustment
 * For coarse the expected output would be two arrays of size 32 i.e. 32 setup and 32 corresponding hold values
 * for fine option, you would expect 512 results, a setup and hold value (corresponding to a coarse adjustment) and the results for 
 * 16 fine clock adjustments.
 * 
 * Results can be interpreted as follows:
 * -----------------------------------------------------------------------------------
 * | Sysref Timing          | Setup Value          | Hold Value      | Meeting Timing |
 * |----------------------- |----------------------|------------     |----------------|
 * | Sysref Leading DEVCLK  | 0x0000               | 0x0000          | Yes            |
 * |                        | 0x8000 - 0xFE00      | 0x0000          | Marginally     |
 * |                        | 0xFF00 - 0xFFFF      | 0x0000          | No             |
 * |----------------------- |----------------------|-----------------|----------------|
 * | Sysref Lagging DEVCLK  | 0xFFFF               | 0x0000 - 0x00FF | No             |
 * |                        | 0xFFFF               | 0x00FF- 0xFFFF  | Marginally     |
 * |                        | 0xFFFF               | 0xFFFF          | Yes            |
 * |------------------------|----------------------|-----------------|----------------|
 * | Sysref Aligned with    | 0x7FFF - 0x0001      | 0xFFFF          | Yes            |
 * | Falling Edge of DevCLK |                      |                 |                |
 * |                        |  0x0000              | 0xFFFF - 0x8000 | Yes            |
 * |------------------------|----------------------|-----------------|----------------|
 * 
 *
 * \pre This function can be called at any time.
 *
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 *
 * \param device Pointer to the ADRV9025 device data structure containing settings
 * \param clock pointer to ad9528 device clock
 * \param fine paramter to enable fine measurement either (1 to enable fine and 0 to disable)
 * \param setupWordArr array to hold setup word results (when fine =0 array size required is 32 and when fine is enabled array size 512 is required)
 * \param holdWordArr array to capture hold word results (when fine =0 array size required is 32 and when fine is enabled array size 512 is required)
 *
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required 
 */
    

int32_t adi_device_share_setupHoldMonitorTimingBlock(adi_adrv9025_Device_t *device,
                                                     adi_ad9528_Device_t   *clock,
                                                     uint8_t               fine,
                                                     uint16_t              *setupWordArr,
                                                     uint16_t              *holdWordArr);
#ifdef __cplusplus
}
#endif

#endif
