# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2018-2020 Picocom Corporation

include $(RTE_SDK)/mk/rte.vars.mk

#
# library name
#
LIB = librte_pmd_pc802.a

CFLAGS += -O3
CFLAGS += $(WERROR_FLAGS)
CFLAGS += -DALLOW_EXPERIMENTAL_API
LDLIBS += -lrte_eal -lrte_mbuf -lrte_mempool -lrte_ring
LDLIBS += -lrte_ethdev -lrte_net -lrte_kvargs
LDLIBS += -lrte_bus_pci

EXPORT_MAP := rte_pmd_pc802_version.map

LIBABIVER := 1

ifeq ($(CONFIG_RTE_TOOLCHAIN_ICC),y)
#
# CFLAGS for icc
#
CFLAGS_BASE_DRIVER  = -diag-disable 177 -diag-disable 181
CFLAGS_BASE_DRIVER += -diag-disable 869 -diag-disable 2259
else
#
# CFLAGS for gcc/clang
#
CFLAGS_BASE_DRIVER = -Wno-uninitialized -Wno-unused-parameter
CFLAGS_BASE_DRIVER += -Wno-unused-variable
ifeq ($(CONFIG_RTE_TOOLCHAIN_GCC),y)
ifeq ($(shell test $(GCC_VERSION) -ge 60 && echo 1), 1)
CFLAGS_BASE_DRIVER += -Wno-misleading-indentation
ifeq ($(shell test $(GCC_VERSION) -ge 70 && echo 1), 1)
CFLAGS_BASE_DRIVER += -Wno-implicit-fallthrough
endif
endif
endif
endif

#
# Add extra flags for base driver files (also known as shared code)
# to disable warnings in them
#
#BASE_DRIVER_OBJS=$(sort $(patsubst %.c,%.o,$(notdir $(wildcard $(SRCDIR)/base/*.c))))
#$(foreach obj, $(BASE_DRIVER_OBJS), $(eval CFLAGS_$(obj)+=$(CFLAGS_BASE_DRIVER)))

#VPATH += $(SRCDIR)/base

#
# all source are stored in SRCS-y
#
SRCS-$(CONFIG_RTE_LIBRTE_PC802_PMD) += pc802_logs.c
SRCS-$(CONFIG_RTE_LIBRTE_PC802_PMD) += pc802_ethdev.c
SRCS-$(CONFIG_RTE_LIBRTE_PC802_PMD) += pc802_atl.c

# install this header file
SYMLINK-$(CONFIG_RTE_LIBRTE_PC802_PMD)-include += pc802_common.h
SYMLINK-$(CONFIG_RTE_LIBRTE_PC802_PMD)-include += pc802_ethdev.h
SYMLINK-$(CONFIG_RTE_LIBRTE_PC802_PMD)-include += pc802_atl.h

include $(RTE_SDK)/mk/rte.lib.mk
