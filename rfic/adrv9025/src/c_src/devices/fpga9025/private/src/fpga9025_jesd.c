/**
 * \file: fpga9025_jesd.c
 *
 * \brief Contains private jesd related functions
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025.h"
#include "adi_fpga9025_error.h"
#include "adi_fpga9025_jesd.h"
#include "../../private/include/fpga9025_jesd.h"
#include "../../private/include/fpga9025_bf_xilinx_jesd204b.h"
#include "../../private/include/fpga9025_bf_xilinx_jesd204c.h"

int32_t fpga9025_Jesd204BDeframerCfgSet(adi_fpga9025_Device_t*      device,
                                        uint32_t                    deframerSelMask,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deframerCfg);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_0) == ADI_FPGA9025_DEFRAMER_0)
    {
        /* set ILA multiframes to 4 multiframes */
        recoveryAction = fpga9025_XilinxJesd204bIlaMultiframesBfSet(device,
                                                                    FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                    3);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to set deframer ila_multiframes");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* Configure lane xbar */
        recoveryAction = adi_fpga9025_RxLaneXBarCfgSet(device,
                                                       ADI_FPGA9025_DEFRAMER_0,
                                                       deframerCfg->laneXbar);
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA support */
        recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                  deframerCfg->ilaSupportEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Deframer 0 ILA support");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure scrambling */
        recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                  deframerCfg->scramblingEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 scrambling");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure SYSREF settings */
        recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                  deframerCfg->sysRefAlways);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 SYSREF always");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfSet(device,
                                                                 FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                 deframerCfg->sysRefDelay);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 SYSREF delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfSet(device,
                                                                            FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                            deframerCfg->sysRefRequiredOnResync);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 SYSREF required on resync");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure octets per frame (F) */
        recoveryAction = fpga9025_XilinxJesd204bCfgFBfSet(device,
                                                          FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                          deframerCfg->cfgF - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 F");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure frames per multiframe (K) */
        recoveryAction = fpga9025_XilinxJesd204bCfgKBfSet(device,
                                                          FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                          deframerCfg->cfgK - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 K");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure lanes in use */
        recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                deframerCfg->lanesInUse);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 lanes in use");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure subclass */
        recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                  deframerCfg->subclassV);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 subclass");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure RX buffer delay */
        recoveryAction = fpga9025_XilinxJesd204bRxBufferDelayBfSet(device,
                                                                   FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                   deframerCfg->rxBufferDly);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 RX buffer delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure error reporting on sync disable */
        recoveryAction = fpga9025_XilinxJesd204bDisErrOnSyncBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                  deframerCfg->errReportingDisable);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 0 error reporting on sync disable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* disable watchdog timer & set the self-clearing reset bit */
        recoveryAction = fpga9025_XilinxJesd204bWatchdogTimerDisableBfSet(device,
                                                                          FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error disabling Deframer 0 watchdog timer");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_1) == ADI_FPGA9025_DEFRAMER_1)
    {
        /* set ILA multiframes to 4 multiframes */
        recoveryAction = fpga9025_XilinxJesd204bIlaMultiframesBfSet(device,
                                                                    FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                    3);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to set deframer ila_multiframes");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* Configure lane xbar */
        recoveryAction = adi_fpga9025_RxLaneXBarCfgSet(device,
                                                       ADI_FPGA9025_DEFRAMER_1,
                                                       deframerCfg->laneXbar);
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA support */
        recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                  deframerCfg->ilaSupportEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Deframer 2 ILA support");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure scrambling */
        recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                  deframerCfg->scramblingEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 scrambling");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure SYSREF settings */
        recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                  deframerCfg->sysRefAlways);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 SYSREF always");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfSet(device,
                                                                 FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                 deframerCfg->sysRefDelay);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 SYSREF delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfSet(device,
                                                                            FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                            deframerCfg->sysRefRequiredOnResync);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 SYSREF required on resync");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure octets per frame (F) */
        recoveryAction = fpga9025_XilinxJesd204bCfgFBfSet(device,
                                                          FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                          deframerCfg->cfgF - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 F");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure frames per multiframe (K) */
        recoveryAction = fpga9025_XilinxJesd204bCfgKBfSet(device,
                                                          FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                          deframerCfg->cfgK - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 K");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure lanes in use */
        recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                deframerCfg->lanesInUse);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 lanes in use");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure subclass */
        recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                  deframerCfg->subclassV);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 subclass");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure RX buffer delay */
        recoveryAction = fpga9025_XilinxJesd204bRxBufferDelayBfSet(device,
                                                                   FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                   deframerCfg->rxBufferDly);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 RX buffer delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure error reporting on sync disable */
        recoveryAction = fpga9025_XilinxJesd204bDisErrOnSyncBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                  deframerCfg->errReportingDisable);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 error reporting on sync disable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* disable watchdog timer & set the self-clearing reset bit */
        recoveryAction = fpga9025_XilinxJesd204bWatchdogTimerDisableBfSet(device,
                                                                          FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error disabling Deframer 2 watchdog timer");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_2) == ADI_FPGA9025_DEFRAMER_2)
    {
        /* set ILA multiframes to 4 multiframes */
        recoveryAction = fpga9025_XilinxJesd204bIlaMultiframesBfSet(device,
                                                                    FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                    3);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Unable to set deframer ila_multiframes");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* Configure lane xbar */
        recoveryAction = adi_fpga9025_RxLaneXBarCfgSet(device,
                                                       ADI_FPGA9025_DEFRAMER_2,
                                                       deframerCfg->laneXbar);
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA support */
        recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                  deframerCfg->ilaSupportEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Deframer 2 ILA support");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure scrambling */
        recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                  deframerCfg->scramblingEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 scrambling");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure SYSREF settings */
        recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                  deframerCfg->sysRefAlways);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 SYSREF always");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfSet(device,
                                                                 FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                 deframerCfg->sysRefDelay);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 SYSREF delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfSet(device,
                                                                            FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                            deframerCfg->sysRefRequiredOnResync);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 SYSREF required on resync");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure octets per frame (F) */
        recoveryAction = fpga9025_XilinxJesd204bCfgFBfSet(device,
                                                          FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                          deframerCfg->cfgF - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 F");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure frames per multiframe (K) */
        recoveryAction = fpga9025_XilinxJesd204bCfgKBfSet(device,
                                                          FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                          deframerCfg->cfgK - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 K");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure lanes in use */
        recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                deframerCfg->lanesInUse);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 lanes in use");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure subclass */
        recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                  deframerCfg->subclassV);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 subclass");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure RX buffer delay */
        recoveryAction = fpga9025_XilinxJesd204bRxBufferDelayBfSet(device,
                                                                   FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                   deframerCfg->rxBufferDly);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 RX buffer delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure error reporting on sync disable */
        recoveryAction = fpga9025_XilinxJesd204bDisErrOnSyncBfSet(device,
                                                                  FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                  deframerCfg->errReportingDisable);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Deframer 2 error reporting on sync disable");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* disable watchdog timer & set the self-clearing reset bit */
        recoveryAction = fpga9025_XilinxJesd204bWatchdogTimerDisableBfSet(device,
                                                                          FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error disabling Deframer 2 watchdog timer");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BDeframerCfgGet(adi_fpga9025_Device_t*      device,
                                        adi_fpga9025_DeframerSel_e  deframerSel,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg)
{
    int32_t                             recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204bChanAddr_e deframerBase   = FPGA9025_BF_JESD204B_DEFRAMER_0;
    uint8_t                             byteRead       = 0;
    int8_t                              i              = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deframerCfg);

    /* Set correct addresses for the deframer selected */
    if (deframerSel == ADI_FPGA9025_DEFRAMER_0)
    {
        deframerBase = FPGA9025_BF_JESD204B_DEFRAMER_0;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_1)
    {
        deframerBase = FPGA9025_BF_JESD204B_DEFRAMER_1;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_2)
    {
        deframerBase = FPGA9025_BF_JESD204B_DEFRAMER_2;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSel,
                         "Invalid deframer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* lane xbar */
    recoveryAction = adi_fpga9025_RxLaneXBarCfgGet(device,
                                                   deframerSel,
                                                   &deframerCfg->laneXbar[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* ILA support */
    recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfGet(device,
                                                              deframerBase,
                                                              &deframerCfg->ilaSupportEn);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting RX ILA support");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* scrambling */
    recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfGet(device,
                                                              deframerBase,
                                                              &deframerCfg->scramblingEn);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX scrambling");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* SYSREF settings */
    recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfGet(device,
                                                              deframerBase,
                                                              &deframerCfg->sysRefAlways);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX SYSREF always");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfGet(device,
                                                             deframerBase,
                                                             &deframerCfg->sysRefDelay);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX SYSREF delay");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfGet(device,
                                                                        deframerBase,
                                                                        &deframerCfg->sysRefRequiredOnResync);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX SYSREF required on resync");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* octets per frame (F) */
    recoveryAction = fpga9025_XilinxJesd204bCfgFBfGet(device,
                                                      deframerBase,
                                                      &byteRead);
    deframerCfg->cfgF = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX F");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* frames per multiframe (K) */
    recoveryAction = fpga9025_XilinxJesd204bCfgKBfGet(device,
                                                      deframerBase,
                                                      &byteRead);
    deframerCfg->cfgK = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX K");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* lanes in use */
    recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfGet(device,
                                                            deframerBase,
                                                            &deframerCfg->lanesInUse);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX lanes in use");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* subclass */
    recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfGet(device,
                                                              deframerBase,
                                                              &deframerCfg->subclassV);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX subclass");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* rxBufferDelay */
    recoveryAction = fpga9025_XilinxJesd204bRxBufferDelayBfGet(device,
                                                               deframerBase,
                                                               &deframerCfg->rxBufferDly);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX buffer delay");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* error reporting disable on sync */
    recoveryAction = fpga9025_XilinxJesd204bDisErrOnSyncBfGet(device,
                                                              deframerBase,
                                                              &deframerCfg->errReportingDisable);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading RX error reporting disable on sync");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Reading ILA data per lane*/
    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        /* bank ID */
        recoveryAction = fpga9025_XilinxJesd204bIlaBidBfGet(device,
                                                            deframerBase,
                                                            i,
                                                            &deframerCfg->bankId[i]);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX bank ID");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* lane ID */
        recoveryAction = fpga9025_XilinxJesd204bCfgLaneIdBfGet(device,
                                                               deframerBase,
                                                               i,
                                                               &deframerCfg->cfgLaneId[i]);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX lane ID");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* ilaS */
        recoveryAction = fpga9025_XilinxJesd204bIlaSBfGet(device,
                                                          deframerBase,
                                                          i,
                                                          &byteRead);
        deframerCfg->ilaS[i] = byteRead + 1;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX ilaS");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* ilaM */
        recoveryAction = fpga9025_XilinxJesd204bIlaMBfGet(device,
                                                          deframerBase,
                                                          i,
                                                          &byteRead);
        deframerCfg->ilaM[i] = byteRead + 1;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX ilaM");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* ilaN */
        recoveryAction = fpga9025_XilinxJesd204bIlaNBfGet(device,
                                                          deframerBase,
                                                          i,
                                                          &byteRead);
        deframerCfg->ilaN[i] = byteRead + 1;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX ilaM");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* ilaNp */
        recoveryAction = fpga9025_XilinxJesd204bIlaNpBfGet(device,
                                                           deframerBase,
                                                           i,
                                                           &byteRead);
        deframerCfg->ilaNp[i] = byteRead + 1;
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX ilaM");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* rxBufferAdj */
        recoveryAction = fpga9025_XilinxJesd204bRxBufAdjBfGet(device,
                                                              deframerBase,
                                                              i,
                                                              &deframerCfg->rxBufferAdj[i]);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading RX buffer adj");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BFramerCfgSet(adi_fpga9025_Device_t*    device,
                                      uint8_t                   linkSelMask,
                                      adi_fpga9025_FramerCfg_t* framerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        framerCfg);

    if ((linkSelMask < ADI_FPGA9025_FRAMER_0) || (linkSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         linkSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Configure one or both framers */
    if ((linkSelMask & ADI_FPGA9025_FRAMER_0) == ADI_FPGA9025_FRAMER_0)
    {
        /* Configure lane xbar */
        recoveryAction = adi_fpga9025_TxLaneXBarCfgSet(device,
                                                       ADI_FPGA9025_FRAMER_0,
                                                       framerCfg->laneXbar);
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA support */
        recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_0,
                                                                  framerCfg->ilaSupportEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Framer 0 ILA support");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure scrambling */
        recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_0,
                                                                  framerCfg->scramblingEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 scrambling");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure SYSREF settings */
        recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_0,
                                                                  framerCfg->sysRefAlways);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 SYSREF always");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfSet(device,
                                                                 FPGA9025_BF_JESD204B_FRAMER_0,
                                                                 framerCfg->sysRefDelay);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 SYSREF delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfSet(device,
                                                                            FPGA9025_BF_JESD204B_FRAMER_0,
                                                                            framerCfg->sysRefRequiredOnResync);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 SYSREF required on resync");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA multiframes */
        recoveryAction = fpga9025_XilinxJesd204bIlaMultiframesBfSet(device,
                                                                    FPGA9025_BF_JESD204B_FRAMER_0,
                                                                    (uint8_t)(framerCfg->ilaMultiFrames - 1));
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 ILA multiframes");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure octets per frame (F) */
        recoveryAction = fpga9025_XilinxJesd204bCfgFBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_0,
                                                          (uint8_t)(framerCfg->cfgF - 1));
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 F");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure frames per multiframe (K) */
        recoveryAction = fpga9025_XilinxJesd204bCfgKBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_0,
                                                          framerCfg->cfgK - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 K");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure lanes in use */
        recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfSet(device,
                                                                FPGA9025_BF_JESD204B_FRAMER_0,
                                                                framerCfg->lanesInUse);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 lanes in use");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure subclass */
        recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_0,
                                                                  framerCfg->subclassV);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 subclass");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* For ILA configuration registers, TX uses lane 0 register addresses for setup */
        /* configure Bank ID */
        recoveryAction = fpga9025_XilinxJesd204bIlaBidBfSet(device,
                                                            FPGA9025_BF_JESD204B_FRAMER_0,
                                                            0,
                                                            framerCfg->bankId);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 bank ID");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure Device ID */
        recoveryAction = fpga9025_XilinxJesd204bIlaDidBfSet(device,
                                                            FPGA9025_BF_JESD204B_FRAMER_0,
                                                            0,
                                                            framerCfg->deviceId);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 device ID");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure control bits per sample (CS)*/
        recoveryAction = fpga9025_XilinxJesd204bIlaCsBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_0,
                                                           0,
                                                           framerCfg->ilaCs);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 control bits per sample (CS)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure total bits per sample (Np) */
        recoveryAction = fpga9025_XilinxJesd204bIlaNpBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_0,
                                                           0,
                                                           framerCfg->ilaNp - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 total bits per sample (Np)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure converter resolution (N) */
        recoveryAction = fpga9025_XilinxJesd204bIlaNBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_0,
                                                          0,
                                                          framerCfg->ilaN - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 converter resolution (N)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure converters per device (M) */
        recoveryAction = fpga9025_XilinxJesd204bIlaMBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_0,
                                                          0,
                                                          framerCfg->ilaM - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 converters per device (M)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure control words per frame (CF) */
        recoveryAction = fpga9025_XilinxJesd204bIlaCfBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_0,
                                                           0,
                                                           framerCfg->ilaCf);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 control words per frame (CF)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure high density format (HD) */
        recoveryAction = fpga9025_XilinxJesd204bIlaHdBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_0,
                                                           0,
                                                           framerCfg->ilaHd);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 high density format (HD)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure samples per converter per frame (S) */
        recoveryAction = fpga9025_XilinxJesd204bIlaSBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_0,
                                                          0,
                                                          framerCfg->ilaS - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 0 samples per converter per frame (S) ");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* disable watchdog timer & set the self-clearing reset bit */
        recoveryAction = fpga9025_XilinxJesd204bWatchdogTimerDisableBfSet(device,
                                                                          FPGA9025_BF_JESD204B_FRAMER_0,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error disabling Framer 0 watchdog timer");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((linkSelMask & ADI_FPGA9025_FRAMER_1) == ADI_FPGA9025_FRAMER_1)
    {
        /* Configure lane xbar */
        recoveryAction = adi_fpga9025_TxLaneXBarCfgSet(device,
                                                       ADI_FPGA9025_FRAMER_1,
                                                       framerCfg->laneXbar);
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA support */
        recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_1,
                                                                  framerCfg->ilaSupportEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Framer 1 ILA support");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure scrambling */
        recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_1,
                                                                  framerCfg->scramblingEn);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 scrambling");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure SYSREF settings */
        recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_1,
                                                                  framerCfg->sysRefAlways);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 SYSREF always");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfSet(device,
                                                                 FPGA9025_BF_JESD204B_FRAMER_1,
                                                                 framerCfg->sysRefDelay);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 SYSREF delay");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfSet(device,
                                                                            FPGA9025_BF_JESD204B_FRAMER_1,
                                                                            framerCfg->sysRefRequiredOnResync);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 SYSREF required on resync");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure ILA multiframes */
        recoveryAction = fpga9025_XilinxJesd204bIlaMultiframesBfSet(device,
                                                                    FPGA9025_BF_JESD204B_FRAMER_1,
                                                                    (uint8_t)(framerCfg->ilaMultiFrames - 1));
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 ILA multiframes");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure octets per frame (F) */
        recoveryAction = fpga9025_XilinxJesd204bCfgFBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_1,
                                                          (uint8_t)(framerCfg->cfgF - 1));
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 F");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure frames per multiframe (K) */
        recoveryAction = fpga9025_XilinxJesd204bCfgKBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_1,
                                                          framerCfg->cfgK - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 K");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure lanes in use */
        recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfSet(device,
                                                                FPGA9025_BF_JESD204B_FRAMER_1,
                                                                framerCfg->lanesInUse);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 lanes in use");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure subclass */
        recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfSet(device,
                                                                  FPGA9025_BF_JESD204B_FRAMER_1,
                                                                  framerCfg->subclassV);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 subclass");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* For ILA configuration registers, TX uses lane 0 register addresses for setup */
        /* configure Bank ID */
        recoveryAction = fpga9025_XilinxJesd204bIlaBidBfSet(device,
                                                            FPGA9025_BF_JESD204B_FRAMER_1,
                                                            0,
                                                            framerCfg->bankId);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 bank ID");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure Device ID */
        recoveryAction = fpga9025_XilinxJesd204bIlaDidBfSet(device,
                                                            FPGA9025_BF_JESD204B_FRAMER_1,
                                                            0,
                                                            framerCfg->deviceId);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 device ID");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure control bits per sample (CS)*/
        recoveryAction = fpga9025_XilinxJesd204bIlaCsBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_1,
                                                           0,
                                                           framerCfg->ilaCs);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 control bits per sample (CS)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure total bits per sample (Np) */
        recoveryAction = fpga9025_XilinxJesd204bIlaNpBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_1,
                                                           0,
                                                           framerCfg->ilaNp - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 total bits per sample (Np)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure converter resolution (N) */
        recoveryAction = fpga9025_XilinxJesd204bIlaNBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_1,
                                                          0,
                                                          framerCfg->ilaN - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 converter resolution (N)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure converters per device (M) */
        recoveryAction = fpga9025_XilinxJesd204bIlaMBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_1,
                                                          0,
                                                          framerCfg->ilaM - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 converters per device (M)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure control words per frame (CF) */
        recoveryAction = fpga9025_XilinxJesd204bIlaCfBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_1,
                                                           0,
                                                           framerCfg->ilaCf);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 control words per frame (CF)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure high density format (HD) */
        recoveryAction = fpga9025_XilinxJesd204bIlaHdBfSet(device,
                                                           FPGA9025_BF_JESD204B_FRAMER_1,
                                                           0,
                                                           framerCfg->ilaHd);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 high density format (HD)");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* configure samples per converter per frame (S) */
        recoveryAction = fpga9025_XilinxJesd204bIlaSBfSet(device,
                                                          FPGA9025_BF_JESD204B_FRAMER_1,
                                                          0,
                                                          framerCfg->ilaS - 1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error configuring Framer 1 samples per converter per frame (S) ");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* disable watchdog timer & set the self-clearing reset bit */
        recoveryAction = fpga9025_XilinxJesd204bWatchdogTimerDisableBfSet(device,
                                                                          FPGA9025_BF_JESD204B_FRAMER_1,
                                                                          1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error disabling Framer 1 watchdog timer");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BFramerCfgGet(adi_fpga9025_Device_t*    device,
                                      adi_fpga9025_FramerSel_e  framerSel,
                                      adi_fpga9025_FramerCfg_t* framerCfg)
{
    int32_t                             recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204bChanAddr_e framerBase     = FPGA9025_BF_JESD204B_DEFRAMER_0;
    uint8_t                             byteRead       = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        framerCfg);

    /* Set correct addresses for the framer selected */
    if (framerSel == ADI_FPGA9025_FRAMER_0)
    {
        framerBase = FPGA9025_BF_JESD204B_FRAMER_0;
    }
    else if (framerSel == ADI_FPGA9025_FRAMER_1)
    {
        framerBase = FPGA9025_BF_JESD204B_FRAMER_1;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSel,
                         "Invalid framer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* lane xbar */
    recoveryAction = adi_fpga9025_TxLaneXBarCfgGet(device,
                                                   framerSel,
                                                   &framerCfg->laneXbar[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* ILA support */
    recoveryAction = fpga9025_XilinxJesd204bIlaSupportEnBfGet(device,
                                                              framerBase,
                                                              &framerCfg->ilaSupportEn);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading ILA support");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* scrambling */
    recoveryAction = fpga9025_XilinxJesd204bScramblingEnBfGet(device,
                                                              framerBase,
                                                              &framerCfg->scramblingEn);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading scrambling");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* SYSREF settings */
    recoveryAction = fpga9025_XilinxJesd204bSysrefAlwaysBfGet(device,
                                                              framerBase,
                                                              &framerCfg->sysRefAlways);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading SYSREF always");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204bSysrefDelayBfGet(device,
                                                             framerBase,
                                                             &framerCfg->sysRefDelay);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading SYSREF delay");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204bSysrefRequiredOnResyncBfGet(device,
                                                                        framerBase,
                                                                        &framerCfg->sysRefRequiredOnResync);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading SYSREF required on resync");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* ILA multiframes */
    recoveryAction = fpga9025_XilinxJesd204bIlaMultiframesBfGet(device,
                                                                framerBase,
                                                                &byteRead);
    framerCfg->ilaMultiFrames = (uint16_t)byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading ILA multiframes");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* octets per frame (F) */
    recoveryAction = fpga9025_XilinxJesd204bCfgFBfGet(device,
                                                      framerBase,
                                                      &byteRead);
    framerCfg->cfgF = (uint16_t)byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading F");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* frames per multiframe (K) */
    recoveryAction = fpga9025_XilinxJesd204bCfgKBfGet(device,
                                                      framerBase,
                                                      &byteRead);
    framerCfg->cfgK = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading K");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* lanes in use */
    recoveryAction = fpga9025_XilinxJesd204bLanesInUseBfGet(device,
                                                            framerBase,
                                                            &framerCfg->lanesInUse);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading lanes in use");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* subclass */
    recoveryAction = fpga9025_XilinxJesd204bCfgSubclassvBfGet(device,
                                                              framerBase,
                                                              &framerCfg->subclassV);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading subclass");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* For ILA configuration registers, TX uses lane 0 register addresses for setup */
    /* Bank ID */
    recoveryAction = fpga9025_XilinxJesd204bIlaBidBfGet(device,
                                                        framerBase,
                                                        0,
                                                        &framerCfg->bankId);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading bank ID");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Device ID */
    recoveryAction = fpga9025_XilinxJesd204bIlaDidBfGet(device,
                                                        framerBase,
                                                        0,
                                                        &framerCfg->deviceId);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading device ID");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* control bits per sample (CS)*/
    recoveryAction = fpga9025_XilinxJesd204bIlaCsBfGet(device,
                                                       framerBase,
                                                       0,
                                                       &framerCfg->ilaCs);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading control bits per sample (CS)");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* total bits per sample (Np) */
    recoveryAction = fpga9025_XilinxJesd204bIlaNpBfGet(device,
                                                       framerBase,
                                                       0,
                                                       &byteRead);
    framerCfg->ilaNp = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading total bits per sample (Np)");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* converter resolution (N) */
    recoveryAction = fpga9025_XilinxJesd204bIlaNBfGet(device,
                                                      framerBase,
                                                      0,
                                                      &byteRead);
    framerCfg->ilaN = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading converter resolution (N)");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* converters per device (M) */
    recoveryAction = fpga9025_XilinxJesd204bIlaMBfGet(device,
                                                      framerBase,
                                                      0,
                                                      &byteRead);
    framerCfg->ilaM = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading converters per device (M)");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* control words per frame (CF) */
    recoveryAction = fpga9025_XilinxJesd204bIlaCfBfGet(device,
                                                       framerBase,
                                                       0,
                                                       &framerCfg->ilaCf);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading control words per frame (CF)");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* high density format (HD) */
    recoveryAction = fpga9025_XilinxJesd204bIlaHdBfGet(device,
                                                       framerBase,
                                                       0,
                                                       &framerCfg->ilaHd);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading high density format (HD)");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* samples per converter per frame (S) */
    recoveryAction = fpga9025_XilinxJesd204bIlaSBfGet(device,
                                                      framerBase,
                                                      0,
                                                      &byteRead);
    framerCfg->ilaS = byteRead + 1;
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error reading  samples per converter per frame (S) ");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t fpga9025_Jesd204BFramerResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               framerSelMask,
                                        uint8_t*               resetBits)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t resetGet       = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        resetBits);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *resetBits = 0x00;

    if ((framerSelMask & ADI_FPGA9025_FRAMER_0) == ADI_FPGA9025_FRAMER_0)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetSelfClearingBfGet(device,
                                                                       FPGA9025_BF_JESD204B_FRAMER_0,
                                                                       &resetGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading  Framer 0 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *resetBits |= (resetGet & 0x01) << 0;
    }
    if ((framerSelMask & ADI_FPGA9025_FRAMER_1) == ADI_FPGA9025_FRAMER_1)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetSelfClearingBfGet(device,
                                                                       FPGA9025_BF_JESD204B_FRAMER_1,
                                                                       &resetGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading  Framer 1 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *resetBits |= (resetGet & 0x01) << 1;
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BFramerReset(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204bChanAddr_e instanceAddress = FPGA9025_BF_JESD204B_FRAMER_0;
    uint32_t                            i               = 0;
    uint32_t                            j               = 0;
    adi_fpga9025_FramerSel_e            framerSel       = ADI_FPGA9025_FRAMER_0;
    uint8_t                             resetBit        = 1;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_FRAMERS; i++)
    {
        framerSel = (adi_fpga9025_FramerSel_e)((uint8_t)(1 << i));

        switch (framerSel)
        {
        case ADI_FPGA9025_FRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204B_FRAMER_0;
            break;
        case ADI_FPGA9025_FRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204B_FRAMER_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)framerSel & framerSelMask) > 0)
        {
            resetBit = 1;

            recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Error clearing Framer 0 fixed reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204bResetSelfClearingBfSet(device,
                                                                           instanceAddress,
                                                                           1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Error setting Framer 0 self-clearing reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Give the framer 50ms to reset itself */
            for (j = 0; j < 5; j++)
            {
                if ((resetBit & 0x1) > 0)
                {
                    recoveryAction = fpga9025_XilinxJesd204bResetSelfClearingBfGet(device,
                                                                                   instanceAddress,
                                                                                   &resetBit);
                    ADI_ERROR_REPORT(&device->common,
                                     ADI_COMMON_ERRSRC_API,
                                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                                     recoveryAction,
                                     NULL,
                                     "Error reading Framer 0 self-clearing reset bit");
                    ADI_ERROR_RETURN(device->common.error.newAction);

                    recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                            10);
                }
                else
                {
                    break;
                }
            }

            if ((resetBit & 0x1) > 0)
            {
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_FPGA9025_ERR_LINK_LAYER_RESET_FAIL,
                                 ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                                 NULL,
                                 "Framer 0 self-clearing bit did not clear");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BFramerDisable(adi_fpga9025_Device_t* device,
                                       uint8_t                framerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((framerSelMask & ADI_FPGA9025_FRAMER_0) == ADI_FPGA9025_FRAMER_0)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_FRAMER_0,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Framer 0 fixed reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((framerSelMask & ADI_FPGA9025_FRAMER_1) == ADI_FPGA9025_FRAMER_1)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_FRAMER_1,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Framer 1 fixed reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BDeframerReset(adi_fpga9025_Device_t* device,
                                       uint8_t                deframerSelMask)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204bChanAddr_e instanceAddress = FPGA9025_BF_JESD204B_DEFRAMER_0;
    uint32_t                            i               = 0;
    uint32_t                            j               = 0;
    adi_fpga9025_DeframerSel_e          deframerSel     = ADI_FPGA9025_DEFRAMER_0;
    uint8_t                             resetBit        = 1;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_DEFRAMERS; i++)
    {
        deframerSel = (adi_fpga9025_DeframerSel_e)((uint8_t)(1 << i));

        switch (deframerSel)
        {
        case ADI_FPGA9025_DEFRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204B_DEFRAMER_0;
            break;
        case ADI_FPGA9025_DEFRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204B_DEFRAMER_1;
            break;
        case ADI_FPGA9025_DEFRAMER_2:
            instanceAddress = FPGA9025_BF_JESD204B_DEFRAMER_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)deframerSel & deframerSelMask) > 0)
        {
            recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Error clearing Deframer fixed reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204bResetSelfClearingBfSet(device,
                                                                           instanceAddress,
                                                                           1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Error setting Deframer self-clearing reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Give the deframer 50ms to reset itself */
            for (j = 0; j < 5; j++)
            {
                if ((resetBit & 0x1) > 0)
                {
                    recoveryAction = fpga9025_XilinxJesd204bResetSelfClearingBfGet(device,
                                                                                   instanceAddress,
                                                                                   &resetBit);
                    ADI_ERROR_REPORT(&device->common,
                                     ADI_COMMON_ERRSRC_API,
                                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                                     recoveryAction,
                                     NULL,
                                     "Error reading Deframer self-clearing reset bit");
                    ADI_ERROR_RETURN(device->common.error.newAction);

                    recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                            10);
                }
                else
                {
                    break;
                }
            }

            if ((resetBit & 0x1) > 0)
            {
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_FPGA9025_ERR_LINK_LAYER_RESET_FAIL,
                                 ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                                 NULL,
                                 "Deframer self-clearing bit did not clear");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BDeframerDisable(adi_fpga9025_Device_t* device,
                                         uint8_t                deframerSelMask)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_0) == ADI_FPGA9025_DEFRAMER_0)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Deframer 0 fixed reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_1) == ADI_FPGA9025_DEFRAMER_1)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Deframer 1 fixed reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_2) == ADI_FPGA9025_DEFRAMER_2)
    {
        recoveryAction = fpga9025_XilinxJesd204bResetFixedBfSet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                1);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Deframer 2 fixed reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204BDeframerStatusGet(adi_fpga9025_Device_t* device,
                                           uint8_t                deframerSelMask,
                                           uint8_t*               status)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t statusGet      = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        status);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *status = 0x00;

    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_0) == ADI_FPGA9025_DEFRAMER_0)
    {
        recoveryAction = fpga9025_XilinxJesd204bSyncStatusBfGet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_0,
                                                                &statusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading Deframer 0 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *status |= (statusGet & 0x01) << 0;
    }
    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_1) == ADI_FPGA9025_DEFRAMER_1)
    {
        recoveryAction = fpga9025_XilinxJesd204bSyncStatusBfGet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_1,
                                                                &statusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading Deframer 1 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *status |= (statusGet & 0x01) << 1;
    }
    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_2) == ADI_FPGA9025_DEFRAMER_2)
    {
        recoveryAction = fpga9025_XilinxJesd204bSyncStatusBfGet(device,
                                                                FPGA9025_BF_JESD204B_DEFRAMER_2,
                                                                &statusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error reading Deframer 2 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *status |= (statusGet & 0x01) << 2;
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CDeframerCfgSet(adi_fpga9025_Device_t*      device,
                                        uint32_t                    deframerSelMask,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg)
{
    int32_t                             recoveryAction     = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress    = FPGA9025_BF_JESD204C_DEFRAMER_0;
    uint32_t                            i                  = 0;
    adi_fpga9025_DeframerSel_e          deframerSel        = ADI_FPGA9025_DEFRAMER_0;
    uint32_t                            firstUnusedLaneNum = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deframerCfg);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* Find the first unused lane. Starting from this lane fill the remainder of the lane xbar with the 
       last good phy lane. This is a bug in the JESD204C Xilinx Rx link layer module */
    for (i = 0; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        if ((deframerCfg->lanesInUse & (1 << i)) == 0)
        {
            firstUnusedLaneNum = i;
            break;
        }
    }

    for (i = firstUnusedLaneNum; i < ADI_FPGA9025_NUM_LANES; i++)
    {
        deframerCfg->laneXbar[i] = deframerCfg->laneXbar[firstUnusedLaneNum - 1];
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_DEFRAMERS; i++)
    {
        deframerSel = (adi_fpga9025_DeframerSel_e)((uint8_t)(1 << i));

        switch (deframerSel)
        {
        case ADI_FPGA9025_DEFRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
            deframerCfg->lanesInUse = 0xF;
            break;
        case ADI_FPGA9025_DEFRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_1;
            deframerCfg->lanesInUse = 0xF;
            break;
        case ADI_FPGA9025_DEFRAMER_2:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_2;
            deframerCfg->lanesInUse = 0x3;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)deframerSel & deframerSelMask) > 0)
        {
            /* Configure lane xbar */
            recoveryAction = adi_fpga9025_RxLaneXBarCfgSet(device,
                                                           (adi_fpga9025_DeframerSel_e)deframerSel,
                                                           deframerCfg->laneXbar);
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cCfgMbInEmbBfSet(device,
                                                                    instanceAddress,
                                                                    deframerCfg->cfgE);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set cfgE.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cMetaModeBfSet(device,
                                                                  instanceAddress,
                                                                  deframerCfg->ctrlMetaMode);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set meta mode.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cRxBufferDelayBfSet(device,
                                                                       instanceAddress,
                                                                       deframerCfg->ctrlRxBufAdv);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set buffer advance bitfield.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cRxMbThBfSet(device,
                                                                instanceAddress,
                                                                deframerCfg->ctrlRxMBlockTh - 1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set MB lock threshold.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cLaneEnableBfSet(device,
                                                                    instanceAddress,
                                                                    deframerCfg->lanesInUse);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set lanes enabled.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cCfgSubclassvBfSet(device,
                                                                      instanceAddress,
                                                                      deframerCfg->subclassV);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set subclass.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            //recoveryAction = adi_fpga9025_Jesd204cLinkLayerIrqEnSet(device, (uint8_t)deframerSel, deframerCfg->ctrlIrq);
            //ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CDeframerCfgGet(adi_fpga9025_Device_t*      device,
                                        adi_fpga9025_DeframerSel_e  deframerSel,
                                        adi_fpga9025_DeframerCfg_t* deframerCfg)
{
    int32_t                             recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e deframerBase   = FPGA9025_BF_JESD204C_DEFRAMER_0;
    uint8_t                             registerValue  = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        deframerCfg);

    /* Set correct addresses for the deframer selected */
    if (deframerSel == ADI_FPGA9025_DEFRAMER_0)
    {
        deframerBase = FPGA9025_BF_JESD204C_DEFRAMER_0;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_1)
    {
        deframerBase = FPGA9025_BF_JESD204C_DEFRAMER_1;
    }
    else if (deframerSel == ADI_FPGA9025_DEFRAMER_2)
    {
        deframerBase = FPGA9025_BF_JESD204C_DEFRAMER_2;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSel,
                         "Invalid deframer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* lane xbar */
    recoveryAction = adi_fpga9025_RxLaneXBarCfgGet(device,
                                                   deframerSel,
                                                   &deframerCfg->laneXbar[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     deframerCfg->laneXbar,
                     "Error reading RX Lane XBar");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cEnableCmdInterfaceBfGet(device,
                                                                    deframerBase,
                                                                    &deframerCfg->enableCmdInterface);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get cmd interface enable.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cEnableDataInterfaceBfGet(device,
                                                                     deframerBase,
                                                                     &deframerCfg->enableDataInterface);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get data interface enable.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cCfgMbInEmbBfGet(device,
                                                            deframerBase,
                                                            &deframerCfg->cfgE);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get cfgE.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cMetaModeBfGet(device,
                                                          deframerBase,
                                                          &deframerCfg->ctrlMetaMode);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get meta mode.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cRxBufferDelayBfGet(device,
                                                               deframerBase,
                                                               &deframerCfg->ctrlRxBufAdv);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get buffer advance bitfield.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cRxMbThBfGet(device,
                                                        deframerBase,
                                                        &registerValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get MB lock threshold.");
    ADI_ERROR_RETURN(device->common.error.newAction);
    deframerCfg->ctrlRxMBlockTh = registerValue + 1;

    recoveryAction = fpga9025_XilinxJesd204cLaneEnableBfGet(device,
                                                            deframerBase,
                                                            &deframerCfg->lanesInUse);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get lanes enabled.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cCfgSubclassvBfGet(device,
                                                              deframerBase,
                                                              &deframerCfg->subclassV);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get subclass.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    //recoveryAction = adi_fpga9025_Jesd204cLinkLayerIrqEnGet(device, (uint8_t)deframerSel, &deframerCfg->ctrlIrq);
    //ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t fpga9025_Jesd204CFramerCfgSet(adi_fpga9025_Device_t*    device,
                                      uint32_t                  framerSelMask,
                                      adi_fpga9025_FramerCfg_t* framerCfg)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
    uint32_t                            i               = 0;
    adi_fpga9025_FramerSel_e            framerSel       = ADI_FPGA9025_FRAMER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        framerCfg);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_FRAMERS; i++)
    {
        framerSel = (adi_fpga9025_FramerSel_e)((uint8_t)(1 << i));

        switch (framerSel)
        {
        case ADI_FPGA9025_FRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
            break;
        case ADI_FPGA9025_FRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)framerSel & framerSelMask) > 0)
        {
            /* Configure lane xbar */
            recoveryAction = adi_fpga9025_TxLaneXBarCfgSet(device,
                                                           (adi_fpga9025_FramerSel_e)framerSel,
                                                           framerCfg->laneXbar);
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cCfgMbInEmbBfSet(device,
                                                                    instanceAddress,
                                                                    framerCfg->cfgE);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set cfgE.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cMetaModeBfSet(device,
                                                                  instanceAddress,
                                                                  framerCfg->ctrlMetaMode);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set meta mode.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cLaneEnableBfSet(device,
                                                                    instanceAddress,
                                                                    framerCfg->lanesInUse);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to get lanes enabled.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cCfgSubclassvBfSet(device,
                                                                      instanceAddress,
                                                                      framerCfg->subclassV);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set subclass.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            //recoveryAction = adi_fpga9025_Jesd204cLinkLayerIrqEnSet(device, (uint8_t)(framerSel << ADI_FPGA9025_NUM_OF_DEFRAMERS), framerCfg->ctrlIrq);
            //ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CFramerCfgGet(adi_fpga9025_Device_t*    device,
                                      adi_fpga9025_FramerSel_e  framerSel,
                                      adi_fpga9025_FramerCfg_t* framerCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    fpga9025_BfXilinxJesd204cChanAddr_e framerBase = FPGA9025_BF_JESD204C_FRAMER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        framerCfg);

    /* Set correct addresses for the framer selected */
    if (framerSel == ADI_FPGA9025_FRAMER_0)
    {
        framerBase = FPGA9025_BF_JESD204C_FRAMER_0;
    }
    else if (framerSel == ADI_FPGA9025_FRAMER_1)
    {
        framerBase = FPGA9025_BF_JESD204C_FRAMER_1;
    }
    else
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSel,
                         "Invalid framer selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    /* lane xbar */
    recoveryAction = adi_fpga9025_TxLaneXBarCfgGet(device,
                                                   framerSel,
                                                   &framerCfg->laneXbar[0]);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_COMMON_ERR_INV_PARAM,
                     recoveryAction,
                     framerCfg->laneXbar,
                     "Error reading TX Lane XBar");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cEnableCmdInterfaceBfGet(device,
                                                                    framerBase,
                                                                    &framerCfg->enableCmdInterface);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get cmd interface enable.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cEnableDataInterfaceBfGet(device,
                                                                     framerBase,
                                                                     &framerCfg->enableDataInterface);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get data interface enable.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cCfgMbInEmbBfGet(device,
                                                            framerBase,
                                                            &framerCfg->cfgE);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get cfgE.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cMetaModeBfGet(device,
                                                          framerBase,
                                                          &framerCfg->ctrlMetaMode);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get meta mode.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cLaneEnableBfGet(device,
                                                            framerBase,
                                                            &framerCfg->lanesInUse);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get lanes enabled.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_XilinxJesd204cCfgSubclassvBfGet(device,
                                                              framerBase,
                                                              &framerCfg->subclassV);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Unable to get subclass.");
    ADI_ERROR_RETURN(device->common.error.newAction);

    //recoveryAction = adi_fpga9025_Jesd204cLinkLayerIrqEnGet(device, (uint8_t)(framerSel << ADI_FPGA9025_NUM_OF_DEFRAMERS), &framerCfg->ctrlIrq);
    //ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t fpga9025_Jesd204CFramerResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               framerSelMask,
                                        uint8_t*               resetBits)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t resetGet       = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        resetBits);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *resetBits = 0x00;

    if ((framerSelMask & ADI_FPGA9025_FRAMER_0) == ADI_FPGA9025_FRAMER_0)
    {
        recoveryAction = fpga9025_XilinxJesd204cResetFixedBfGet(device,
                                                                FPGA9025_BF_JESD204C_FRAMER_0,
                                                                &resetGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Framer 0 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *resetBits |= (resetGet & 0x01) << 0;
    }
    if ((framerSelMask & ADI_FPGA9025_FRAMER_1) == ADI_FPGA9025_FRAMER_1)
    {
        recoveryAction = fpga9025_XilinxJesd204cResetFixedBfGet(device,
                                                                FPGA9025_BF_JESD204C_FRAMER_1,
                                                                &resetGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Framer 1 reset bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *resetBits |= (resetGet & 0x01) << 1;
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CFramerReset(adi_fpga9025_Device_t* device,
                                     uint8_t                framerSelMask)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
    uint32_t                            i               = 0;
    uint32_t                            j               = 0;
    adi_fpga9025_FramerSel_e            framerSel       = ADI_FPGA9025_FRAMER_0;
    uint8_t                             resetBit        = 1;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_FRAMERS; i++)
    {
        framerSel = (adi_fpga9025_FramerSel_e)((uint8_t)(1 << i));

        switch (framerSel)
        {
        case ADI_FPGA9025_FRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
            break;
        case ADI_FPGA9025_FRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)framerSel & framerSelMask) > 0)
        {
            resetBit = 1;

            recoveryAction = fpga9025_XilinxJesd204cResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error setting Framer reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error clearing Framer reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Give the framer 50ms to reset itself */
            for (j = 0; j < 5; j++)
            {
                if ((resetBit & 0x1) > 0)
                {
                    recoveryAction = fpga9025_XilinxJesd204cResetFixedBfGet(device,
                                                                            instanceAddress,
                                                                            &resetBit);
                    ADI_ERROR_REPORT(&device->common,
                                     ADI_COMMON_ERRSRC_API,
                                     ADI_COMMON_ERR_INV_PARAM,
                                     recoveryAction,
                                     NULL,
                                     "Error reading Framer reset bit");
                    ADI_ERROR_RETURN(device->common.error.newAction);

                    recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                            10);
                }
                else
                {
                    break;
                }
            }

            if ((resetBit & 0x1) > 0)
            {
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_INV_PARAM,
                                 ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                                 NULL,
                                 "Framer did not reset correctly");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CFramerDisable(adi_fpga9025_Device_t* device,
                                       uint8_t                framerSelMask)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
    uint32_t                            i               = 0;
    adi_fpga9025_FramerSel_e            framerSel       = ADI_FPGA9025_FRAMER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((framerSelMask < ADI_FPGA9025_FRAMER_0) || (framerSelMask > ADI_FPGA9025_FRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         framerSelMask,
                         "Invalid framer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_FRAMERS; i++)
    {
        framerSel = (adi_fpga9025_FramerSel_e)((uint8_t)(1 << i));

        switch (framerSel)
        {
        case ADI_FPGA9025_FRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_0;
            break;
        case ADI_FPGA9025_FRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_FRAMER_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)framerSel & framerSelMask) > 0)
        {
            /* These two bitfields are tied to the LEDs on the ADS9. Zero out to ensure the LEDs are turned off */
            recoveryAction = fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet(device,
                                                                            instanceAddress,
                                                                            0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set cmd interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cEnableDataInterfaceBfSet(device,
                                                                             instanceAddress,
                                                                             0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set data interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error setting Framer 0 reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CDeframerReset(adi_fpga9025_Device_t* device,
                                       uint8_t                deframerSelMask)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
    uint32_t                            i               = 0;
    uint32_t                            j               = 0;
    adi_fpga9025_DeframerSel_e          deframerSel     = ADI_FPGA9025_DEFRAMER_0;
    uint8_t                             resetBit        = 1;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_DEFRAMERS; i++)
    {
        deframerSel = (adi_fpga9025_DeframerSel_e)((uint8_t)(1 << i));

        switch (deframerSel)
        {
        case ADI_FPGA9025_DEFRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
            break;
        case ADI_FPGA9025_DEFRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_1;
            break;
        case ADI_FPGA9025_DEFRAMER_2:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)deframerSel & deframerSelMask) > 0)
        {
            recoveryAction = fpga9025_XilinxJesd204cResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error setting Deframer reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error clearing Deframer reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* Give the deframer 50ms to reset itself */
            for (j = 0; j < 5; j++)
            {
                if ((resetBit & 0x1) > 0)
                {
                    recoveryAction = fpga9025_XilinxJesd204cResetFixedBfGet(device,
                                                                            instanceAddress,
                                                                            &resetBit);
                    ADI_ERROR_REPORT(&device->common,
                                     ADI_COMMON_ERRSRC_API,
                                     ADI_COMMON_ERR_INV_PARAM,
                                     recoveryAction,
                                     NULL,
                                     "Error reading Deframer reset bit");
                    ADI_ERROR_RETURN(device->common.error.newAction);

                    recoveryAction = adi_common_hal_Wait_ms(&device->common,
                                                            10);
                }
                else
                {
                    break;
                }
            }

            if ((resetBit & 0x1) > 0)
            {
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_COMMON_ERR_INV_PARAM,
                                 ADI_COMMON_ACT_ERR_RESET_INTERFACE,
                                 NULL,
                                 "Deframer did not reset correctly");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CDeframerDisable(adi_fpga9025_Device_t* device,
                                         uint8_t                deframerSelMask)
{
    int32_t                             recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfXilinxJesd204cChanAddr_e instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
    uint32_t                            i               = 0;
    adi_fpga9025_DeframerSel_e          deframerSel     = ADI_FPGA9025_DEFRAMER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_DEFRAMERS; i++)
    {
        deframerSel = (adi_fpga9025_DeframerSel_e)((uint8_t)(1 << i));

        switch (deframerSel)
        {
        case ADI_FPGA9025_DEFRAMER_0:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_0;
            break;
        case ADI_FPGA9025_DEFRAMER_1:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_1;
            break;
        case ADI_FPGA9025_DEFRAMER_2:
            instanceAddress = FPGA9025_BF_JESD204C_DEFRAMER_2;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)deframerSel & deframerSelMask) > 0)
        {
            /* These two bitfields are tied to the LEDs on the ADS9. Zero out to ensure the LEDs are turned off */
            recoveryAction = fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet(device,
                                                                            instanceAddress,
                                                                            0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set cmd interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cEnableDataInterfaceBfSet(device,
                                                                             instanceAddress,
                                                                             0);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Unable to set data interface enable.");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_XilinxJesd204cResetFixedBfSet(device,
                                                                    instanceAddress,
                                                                    1);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_COMMON_ERR_INV_PARAM,
                             recoveryAction,
                             NULL,
                             "Error setting Deframer reset bit");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t fpga9025_Jesd204CDeframerStatusGet(adi_fpga9025_Device_t* device,
                                           uint8_t                deframerSelMask,
                                           uint8_t*               status)
{
    int32_t recoveryAction      = ADI_COMMON_ACT_NO_ACTION;
    uint8_t syncHeaderStatusGet = 0;
    uint8_t mbLockStatusGet     = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        status);

    if ((deframerSelMask < ADI_FPGA9025_DEFRAMER_0) || (deframerSelMask > ADI_FPGA9025_DEFRAMER_ALL))
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         deframerSelMask,
                         "Invalid deframer selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *status = 0x00;

    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_0) == ADI_FPGA9025_DEFRAMER_0)
    {
        recoveryAction = fpga9025_XilinxJesd204cMbLockBfGet(device,
                                                            FPGA9025_BF_JESD204C_DEFRAMER_0,
                                                            &mbLockStatusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Deframer 0 mb lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        recoveryAction = fpga9025_XilinxJesd204cSyncHeaderLockBfGet(device,
                                                                    FPGA9025_BF_JESD204C_DEFRAMER_0,
                                                                    &syncHeaderStatusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Deframer 0 loss sync header lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *status |= (mbLockStatusGet & syncHeaderStatusGet) << 0;
    }
    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_1) == ADI_FPGA9025_DEFRAMER_1)
    {
        recoveryAction = fpga9025_XilinxJesd204cMbLockBfGet(device,
                                                            FPGA9025_BF_JESD204C_DEFRAMER_1,
                                                            &mbLockStatusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Deframer 1 mb lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        recoveryAction = fpga9025_XilinxJesd204cSyncHeaderLockBfGet(device,
                                                                    FPGA9025_BF_JESD204C_DEFRAMER_1,
                                                                    &syncHeaderStatusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Deframer 1 loss sync header lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *status |= (mbLockStatusGet & syncHeaderStatusGet) << 1;
    }
    if ((deframerSelMask & ADI_FPGA9025_DEFRAMER_2) == ADI_FPGA9025_DEFRAMER_2)
    {
        recoveryAction = fpga9025_XilinxJesd204cMbLockBfGet(device,
                                                            FPGA9025_BF_JESD204C_DEFRAMER_2,
                                                            &mbLockStatusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Deframer 2 mb lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        recoveryAction = fpga9025_XilinxJesd204cSyncHeaderLockBfGet(device,
                                                                    FPGA9025_BF_JESD204C_DEFRAMER_2,
                                                                    &syncHeaderStatusGet);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         recoveryAction,
                         NULL,
                         "Error reading  Deframer 2 loss sync header lock bit");
        ADI_ERROR_RETURN(device->common.error.newAction);
        *status |= (mbLockStatusGet & syncHeaderStatusGet) << 2;
    }

    return recoveryAction;
}
