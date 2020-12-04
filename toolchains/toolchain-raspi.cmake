# https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-linux

if(NOT DEFINED CMAKE_SYSROOT)
    if(EXISTS $ENV{HOME}/sysroot_raspi_local/)
        set(CMAKE_SYSROOT $ENV{HOME}/sysroot_raspi_local) #set the sysroot of your Raspberry Pi here
    elseif(EXISTS $ENV{HOME}/sysroot_raspi/)
        set(CMAKE_SYSROOT $ENV{HOME}/sysroot_raspi) #set the sysroot of your Raspberry Pi here
    else()
        message( FATAL_ERROR "You have to set the sysroot of the Raspberry Pi with the command -DCMAKE_SYSROOT=PATH_TO_SYSROOT" )
    endif()
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_BIN_PATH /usr/bin)

set(CMAKE_C_COMPILER   ${TOOLCHAIN_BIN_PATH}/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_PATH}/arm-linux-gnueabihf-g++)

# Use our definitions for compiler tools
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers in the target directories only
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
