/* 
* \file ads9_logging.c
*/

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <time.h>
#include "ads9_logging.h"

/**
* \brief Opens a logFile. If the file is already open it will be closed and reopened.
*
* This function opens the file for writing and saves the resulting file 
* descriptor to the devHalCfg structure.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param filename The user provided name of the file to open.
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
* \retval ADI_HAL_LOGGING_FAIL If the function failed to open or write to the specified filename
*/
int32_t ads9_LogFileOpen(void*       devHalCfg,
                         const char* filename)
{
    (void)(filename);
    int32_t        halError = ADI_HAL_OK;
    int32_t        result   = 0;
    adi_hal_Cfg_t* halCfg   = NULL;
    FILE*          logfd    = NULL;
    struct tm      tm       = {0};
    time_t         t        = {0};

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    logfd = (FILE*)halCfg->logCfg.logfd;

    //if logfile already open, close it
    if (logfd != 0)
    {
        halError = ads9_LogFileClose(devHalCfg);
    }

    /* open a new log file */
    logfd = fopen(halCfg->logCfg.logFileName,
                  "w+");
    if (logfd == NULL)
    {
        return (int32_t)ADI_HAL_LOGGING_FAIL;
    }

    halCfg->logCfg.logfd = (uintptr_t)logfd;

    t = time(NULL);

    tm = *localtime(&t);

    result = fprintf(logfd,
                     "API log file \nStart date %04d-%02d-%02d %02d:%02d:%02d \nLogging level %d\n\n\n",
                     tm.tm_year + 1900,
                     tm.tm_mon + 1,
                     tm.tm_mday,
                     tm.tm_hour,
                     tm.tm_min,
                     tm.tm_sec,
                     halCfg->logCfg.logLevel);
    if (result < 0)
    {
        return ADI_HAL_LOGGING_FAIL;
    }

    result = fflush(logfd);
    if (result < ADI_HAL_OK)
    {
        halError = ADI_HAL_LOGGING_FAIL;
    }

    return halError;
}

/**
* \brief Flushes the logFile buffer to the currently open log file.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
*/
int32_t ads9_LogFileFlush(void* devHalCfg)
{
    int32_t        halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t* halCfg   = NULL;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->logCfg.logfd != 0)
    {
        halError = fflush((FILE*)halCfg->logCfg.logfd);
    }
    else
    {
        /* File not open, can not flush, No Error */
        halError = (int32_t)ADI_HAL_OK;
    }

    return halError;
}

/**
* \brief Gracefully closes the log file(s).
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
* \retval ADI_HAL_LOGGING_FAIL Error while flushing or closing the log file.
*/
int32_t ads9_LogFileClose(void* devHalCfg)
{
    int32_t        halError = (int32_t)ADI_HAL_OK;
    int32_t        result   = 0;
    adi_hal_Cfg_t* halCfg   = NULL;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->logCfg.logfd != 0)
    {
        result = fflush((FILE*)halCfg->logCfg.logfd);
        if (result < 0)
        {
            halError = ADI_HAL_LOGGING_FAIL;
        }

        result = fclose((FILE*)halCfg->logCfg.logfd);
        if (result < 0)
        {
            halError = ADI_HAL_LOGGING_FAIL;
        }

        halCfg->logCfg.logfd = 0;
        /* Log level reset was causing issues with the log files, logging was disabled */
        /* halCfg->logCfg.logLevel = 0; */
    }
    else
    {
        /* Log file is not open, can not close the file - no error */
        halError = ADI_HAL_OK;
    }

    return halError;
}

/**
* \brief Sets the log level, allowing the end user to select the granularity of
*        what events get logged.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param logLevel A mask of valid log levels to allow to be written to the log file.
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
*/
int32_t ads9_LogLevelSet(void*   devHalCfg,
                         int32_t logLevel)
{
    int32_t        halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t* halCfg   = NULL;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    halCfg->logCfg.logLevel = (logLevel & (int32_t)ADI_HAL_LOG_ALL);

    return halError;
}

/**
 * \brief Gets the currently set log level: the mask of different types of log
 *         events that are currently enabled to be logged.
 *
 * \param devHalCfg Pointer to device instance specific platform settings
 * \param logLevel Returns the current log level mask.
 *
 * \retval ADI_HAL_OK Function completed successfully, no action required
 * \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
 */
int32_t ads9_LogLevelGet(void*    devHalCfg,
                         int32_t* logLevel)
{
    int32_t        halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t* halCfg   = NULL;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    *logLevel = halCfg->logCfg.logLevel;

    return halError;
}

/**
* \brief Writes a message to the currently open logFile specified in the 
*        adi_hal_LogCfg_t of the devHalCfg structure passed
* 
* Uses the vfprintf functionality to allow the user to supply the format and
* the number of arguments that will be logged.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param logLevel the log level to be written into
* \param comment the string to include in the line added to the log.
* \param argp variable argument list to be printed
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
* \retval ADI_HAL_LOGGING_FAIL If the function failed to flush to write 
*/
int32_t ads9_LogWrite(void*       devHalCfg,
                      int32_t     logLevel,
                      const char* comment,
                      va_list     argp)
{
    int32_t        halError                         = (int32_t)ADI_HAL_OK;
    int32_t        result                           = 0;
    adi_hal_Cfg_t* halCfg                           = NULL;
    time_t         t                                = time(NULL);
    struct tm      tm                               = {0};
    FILE*          logfd                            = NULL;
    char           logMessage[ADI_HAL_MAX_LOG_LINE] = {0};
    const char*    logLevelChar                     = NULL;
    logMessage[0]                                   = 0;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if ((halCfg->logCfg.interfaceEnabled == 0) || (halCfg->logCfg.logLevel == (int32_t)ADI_HAL_LOG_NONE))
    {
        /* If logging disabled, exit gracefully */
        halError = (int32_t)ADI_HAL_OK;
        return halError;
    }

    if (logLevel > (int32_t)ADI_HAL_LOG_ALL)
    {
        halError = (int32_t)ADI_HAL_LOGGGING_LEVEL_FAIL;
        return halError;
    }

    /* Auto Open of log file is currently disabled */
    if (halCfg->logCfg.logfd == 0)
    {
        /* Log file is not open */
        halError = (int32_t)ADI_HAL_LOGGING_FAIL;
        return halError;
    }
    else
    {
        logfd = (FILE *)halCfg->logCfg.logfd;

        if (halCfg->logCfg.currentLineNumber >= ADS9_LOG_MAX_NUM_LINES)
        {
            /* seek back to beginning of file */
            /* fseek(logfd, 2, SEEK_SET); */
            rewind(logfd);
            halCfg->logCfg.currentLineNumber = 0;
        }

        /* Print Log type */
        if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_MSG) && (logLevel == (int32_t)ADI_HAL_LOG_MSG))
        {
            logLevelChar = "MESSAGE:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_WARN) && (logLevel == (int32_t)ADI_HAL_LOG_WARN))
        {
            logLevelChar = "WARNING:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_ERR) && (logLevel == (int32_t)ADI_HAL_LOG_ERR))
        {
            logLevelChar = "ERROR:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_API) && (logLevel == (int32_t)ADI_HAL_LOG_API))
        {
            logLevelChar = "API_LOG:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_BF) && (logLevel == (int32_t)ADI_HAL_LOG_BF))
        {
            logLevelChar = "BF_LOG:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_HAL) && (logLevel == (int32_t)ADI_HAL_LOG_HAL))
        {
            logLevelChar = "ADI_HAL_LOG:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_SPI) && (logLevel == (int32_t)ADI_HAL_LOG_SPI))
        {
            logLevelChar = "SPI_LOG:";
        }
        else if ((halCfg->logCfg.logLevel & ADI_HAL_LOG_API_PRIV) && (logLevel == (int32_t)ADI_HAL_LOG_API_PRIV))
        {
            logLevelChar = "API_PRIV_LOG:";
        }
        else
        {
            /* Nothing to log - exit cleanly */
            return (int32_t)ADI_HAL_OK;
        }

        tm = *localtime(&t);
        /* Print timestamp */
        result = snprintf(logMessage,
                          ADI_HAL_MAX_LOG_LINE,
                          "%04d-%02d-%02d %02d:%02d:%02d: %s",
                          tm.tm_year + 1900,
                          tm.tm_mon + 1,
                          tm.tm_mday,
                          tm.tm_hour,
                          tm.tm_min,
                          tm.tm_sec,
                          logLevelChar);
        if (result < 0)
        {
            halError = (int32_t)ADI_HAL_LOGGING_FAIL;
            return halError;
        }

        result = vsnprintf(logMessage + strlen(logMessage),
                           ADI_HAL_MAX_LOG_LINE,
                           comment,
                           argp);
        if (result < 0)
        {
            halError = (int32_t)ADI_HAL_LOGGING_FAIL;
            return halError;
        }

        result = fprintf(logfd,
                         "%s\n",
                         logMessage);
        if (result < 0)
        {
            halError = (int32_t)ADI_HAL_LOGGING_FAIL;
            return halError;
        }

        result = fflush(logfd);
        if (result < 0)
        {
            halError = (int32_t)ADI_HAL_LOGGING_FAIL;
            return halError;
        }

        halCfg->logCfg.currentLineNumber += 1;
    }

    return halError;
}

/**
* \brief Disables the LogWrite functionality by returning ADI_HAL_OK
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param logLevel the log level to be written into
* \param comment the string to include in the line added to the log.
* \param argp variable argument list to be printed
*
* \retval ADI_HAL_OK Function completed successfully, no action required
*/
int32_t ads9_LogWrite_NoAction(void*       devHalCfg,
                               int32_t     logLevel,
                               const char* comment,
                               va_list     argp)
{
    (void)devHalCfg;
    (void)logLevel;
    (void)comment;
    (void)argp;

    return ADI_HAL_OK;
}
