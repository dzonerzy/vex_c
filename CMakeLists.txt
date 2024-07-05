cmake_minimum_required(VERSION 3.10)

# Set the project name
project(vex_c)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(ExternalProject)

# Define build and install directories for the vex project
set(VEX_BINARY_DIR ${CMAKE_BINARY_DIR}/vex)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add the external project for the vex project
ExternalProject_Add(
    vex
    PREFIX ${VEX_BINARY_DIR}
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/vex
    BINARY_DIR ${VEX_BINARY_DIR}/build
    BUILD_ALWAYS 1
    INSTALL_COMMAND "" # Disable install step
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/vex/pub)
include_directories(${CMAKE_SOURCE_DIR}/vex/priv)

# Define source files for vex_c
set(VEX_C_SOURCES
    src/analysis.c
    src/logging.c
    src/postprocess.c
    src/vexc.c
)

# Define headers for vex_c
set(VEX_C_HEADERS
    src/e4c_lite.h
    src/logging.h
    src/vexc.h
    src/vexc_internal.h
)

# Create the static library for vex_c
add_library(${PROJECT_NAME}_static STATIC ${VEX_C_SOURCES} ${VEX_C_HEADERS})

# Ensure that vex is built before building the vex_c library
add_dependencies(${PROJECT_NAME}_static vex)

# Link against the vex static library
target_link_libraries(${PROJECT_NAME}_static ${VEX_INSTALL_DIR}/lib/libLibVex_static.a)

# Platform-specific settings
if (WIN32)
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    target_link_libraries(${PROJECT_NAME}_static)
else()
    target_compile_options(${PROJECT_NAME}_static PRIVATE -Wall -Wextra)
    target_link_libraries(${PROJECT_NAME}_static pthread)
endif()

# Handle debug mode
option(DEBUG "Enable debug mode" OFF)
if (DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()

# Handle extra C flags
if (EXTRA_CFLAGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
endif()
