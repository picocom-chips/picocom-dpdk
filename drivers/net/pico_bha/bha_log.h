/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _BHA_LOG_H_
#define _BHA_LOG_H_

extern int bha_logtype;

#define BHA_LOG(level, fmt, args...)                         \
    rte_log(RTE_LOG_##level, bha_logtype, "%s(): " fmt "\n", \
        __func__, ##args)

#endif /* _BHA_LOG_H_ */
