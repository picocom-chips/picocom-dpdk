# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2010-2015 Intel Corporation

include $(RTE_SDK)/mk/rte.vars.mk

ifeq ($(CONFIG_RTE_TEST_PC802),y)

#
# library name
#
APP = testpc802

CFLAGS += -DALLOW_EXPERIMENTAL_API
CFLAGS += -O3
CFLAGS += $(WERROR_FLAGS)
CFLAGS += -Wno-deprecated-declarations
#CFLAGS += -I$(RTE_SDK)/drivers/net/pc802

#
# all source are stored in SRCS-y
#
SRCS-y := testpc802.c cmdline.c

LDLIBS += -lrte_pmd_pc802

include $(RTE_SDK)/mk/rte.app.mk

endif
