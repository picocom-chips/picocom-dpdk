/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PSEC_LOG_H_
#define _PSEC_LOG_H_

extern int psec_logtype;

#define PSEC_LOG(level, fmt, args...)                         \
    rte_log(RTE_LOG_##level, psec_logtype, "%s(): " fmt "\n", \
        __func__, ##args)

#endif /* _PSEC_LOG_H_ */
