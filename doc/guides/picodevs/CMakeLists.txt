# PICOCOM PROPRIETARY INFORMATION
#
# This software is supplied under the terms of a license agreement or
# nondisclosure agreement with PICOCOM and may not be copied
# or disclosed except in accordance with the terms of that agreement.
#
# Copyright PICOCOM.

cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

set(PICO_DOCBUILD TRUE)

#find_package(PicoOS REQUIRED HINTS $ENV{PICOOS_BASE})

project(picoos-doc LANGUAGES)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

set(DOXYGEN_SKIP_DOT True)
find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)
find_package(LATEX)

# Note that this won't force fatal error if latexmk is not found.
# Not having LaTeX tools should not prevent people from generating HTML docs.
find_program(
  LATEXMK
  latexmk
  )
if(${LATEXMK} STREQUAL LATEXMK-NOTFOUND)
  message(WARNING "The 'latexmk' command was not found. Targets to build PDF will not be available.")
endif()

set(SOURCE_REPO ${CMAKE_SOURCE_DIR}/../../../)
set(DOXYFILE_IN ${CMAKE_CURRENT_LIST_DIR}/picoos.doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/picoos.doxyfile)
set(DOXY_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(RST_OUT ${CMAKE_CURRENT_BINARY_DIR}/rst)
set(DOC_LOG ${CMAKE_CURRENT_BINARY_DIR}/doc.log)
set(DOXY_LOG ${CMAKE_CURRENT_BINARY_DIR}/doxy.log)
set(DOC_WARN ${CMAKE_CURRENT_BINARY_DIR}/doc.warnings)
set(CONTENT_OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/extracted-content.txt)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

add_custom_target(doxy ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

set(CONF_PY_IN ${CMAKE_CURRENT_LIST_DIR}/source/conf.py.in)
set(CONF_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/conf.py)

configure_file(${CONF_PY_IN} ${CONF_PY_OUT} @ONLY)

add_custom_target(sphinxhtml ALL
        COMMAND ${SPHINX_EXECUTABLE} -b html -c ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/sphinxhtml
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS doxy
        COMMENT "Generating html documentation with Sphinx"
        VERBATIM)

add_custom_target(sphinxlatex ALL
        COMMAND ${SPHINX_EXECUTABLE} -b latex  -c ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/sphinxlatex
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS doxy
        COMMENT "Generating latex documentation with Sphinx"
        VERBATIM)
