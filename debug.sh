#!/bin/bash

################################################################################
# Sets up the toolchain for the specified target (if not already done), compiles
# the Software for this target and starts the debugger.
#
# NOTE: DO NOT call this script manually. It is called by make.sh
################################################################################

# TODO: clean when changing target board

## direct call prevention
# With this, it's not neccessary to check all arguments again
CODE=123
if [ $2 -ne $CODE ]
then 
    echo "DO NOT call debug.sh directly. It is used by make.sh."
    exit 1
fi

# make sure the working directory for this script is the root of the software repository
cd ~/git/io-link-master-shield-hat-sw/

# Create debug directory if not present, and enter it
if [ ! -d debug ]
then
    mkdir debug
fi
cd debug

# Compile for Debugging on the Raspberry Pi
if [ $1 = "raspi" ]
then
    # Initialize build system
    if [ ! -d CMakeFiles ]  # CMakeFiles directory not present --> cmake not ready
    then
        cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../toolchains/toolchain-raspi.cmake 
    fi
    # Compile
    echo "Building for Debugging on Raspberry Pi..."
    cmake --build . -j
    # Copy to mounted remote filesystem 
    # ~/sysroot_raspi must be mounted and ~/pi is assumed to point to sysroot_raspi/home/pi/
    cp test/board/test_board ~/pi/ 
    echo "Copied test_board"
    echo ""
    echo "Please start the GDB server on the Raspberry Pi with the following command:"
    echo "gdbserver :9080 ./test_board"
fi
