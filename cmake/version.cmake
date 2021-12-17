# PICOCOM PROPRIETARY INFORMATION
#
# This software is supplied under the terms of a license agreement or
# nondisclosure agreement with PICOCOM and may not be copied
# or disclosed except in accordance with the terms of that agreement.
#
# Copyright PICOCOM.

# SPDX-License-Identifier: Apache-2.0

#.rst:
# version.cmake
# -------------
#
# Inputs:
#
#   ``*VERSION*`` and other constants set by
#   maintainers in ``${PICOOS_BASE}/VERSION``
#
# Outputs with examples::
#
#   PICOOS_VERSION           1.14.99.07

file(READ ${PICOOS_BASE}/VERSION ver)

string(REGEX MATCH "VERSION_MAJOR = ([0-9]*)" _ ${ver})
set(PICOOS_VERSION_MAJOR ${CMAKE_MATCH_1})

string(REGEX MATCH "VERSION_MINOR = ([0-9]*)" _ ${ver})
set(PICOOS_VERSION_MINOR ${CMAKE_MATCH_1})

string(REGEX MATCH "PATCHLEVEL = ([0-9]*)" _ ${ver})
set(PICOOS_VERSION_PATCH ${CMAKE_MATCH_1})

string(REGEX MATCH "VERSION_TWEAK = ([0-9]*)" _ ${ver})
set(PICOOS_VERSION_TWEAK ${CMAKE_MATCH_1})

string(REGEX MATCH "EXTRAVERSION = ([a-z0-9]*)" _ ${ver})
set(PICOOS_VERSION_EXTRA ${CMAKE_MATCH_1})

# Temporary convenience variable
set(PICOOS_VERSION_WITHOUT_TWEAK ${PICOOS_VERSION_MAJOR}.${PICOOS_VERSION_MINOR}.${PICOOS_VERSION_PATCH})


if(PICOOS_VERSION_EXTRA)
  set(PICOOS_VERSION_EXTRA_STR "-${PICOOS_VERSION_EXTRA}")
endif()

if(PICOOS_VERSION_TWEAK)
  set(PICOOS_VERSION ${PICOOS_VERSION_WITHOUT_TWEAK}.${PICOOS_VERSION_TWEAK})
else()
  set(PICOOS_VERSION ${PICOOS_VERSION_WITHOUT_TWEAK})
endif()

set(PICOOS_VERSION_STR ${PICOOS_VERSION}${PICOOS_VERSION_EXTRA_STR})

if (NOT NO_PRINT_VERSION)
  message(STATUS "PicoOS version: ${PICOOS_VERSION_STR} (${PICOOS_BASE})")
endif()

# Cleanup convenience variables
unset(MAJOR)
unset(MINOR)
unset(PATCH)
unset(PICOOS_VERSION_WITHOUT_TWEAK)
