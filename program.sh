#!/bin/bash

################################################################################
# Sets up the toolchain for the specified target (if not already done), compiles
# the Software for this target and programs it (if specified).
#
# NOTE: DO NOT call this script manually. It is called by make.sh
################################################################################

## direct call prevention
CODE=123
if [ $3 -ne $CODE ]
then 
    echo "DO NOT call program.sh directly. It is used by make.sh."
    exit 1
fi

# make sure the working directory for this script is the root of the software repository
cd ~/git/io-link-master-shield-hat-sw/

# Create build directory if not present, and enter it
if [ ! -d build ]
then
    mkdir build
fi
cd build

# Make sure that (at least) one command (argument) was provided
if [ $# -eq 0 ]
then 
    echo "please specify 'raspi', 'arduino' or 'clean'"

# Delete everything inside "build"
elif [ $1 = "clean" ]
then
    echo "rm -rf *"
    rm -rf *

# Compile for Raspberry Pi and copy the executable to it. If not already done, 
# the build system is initialized first
elif [ $1 = "raspi" ]
then
    # Initialize build system
    if [ ! -d CMakeFiles ]  # CMakeFiles directory not present --> cmake not ready
    then
        cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/toolchain-raspi.cmake
        echo ""
        echo "Initialized the build system for Raspberry Pi"
    fi
    # Compile
    echo "Building for Raspberry Pi..."
    cmake --build . -j
    # Copy to mounted remote filesystem 
    # ~/sysroot_raspi must be mounted and ~/pi is assumed to point to sysroot_raspi/home/pi/
    cp test/board/test_board ~/pi/ 
    echo "Copied test_board"

# Compile for Arduino and program it. If not already done, the build system is 
# initialized first
elif [ $1 = "arduino" ]
then
    # Initialize build system
    if [ ! -d CMakeFiles ]  # CMakeFiles directory not present --> cmake not ready
    then
        cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/Arduino-CMake-Toolchain/Arduino-toolchain.cmake -DARDUINO_INSTALL_PATH=/mnt/c/Program\ Files\ \(x86\)/Arduino/ -DARDUINO_BOARD="Arduino Due (Programming Port) [sam.arduino_due_x_dbg]"
        echo ""
        echo "Initialized the build system for Arduino Due"
    fi
    # Compile
    echo "Building for Arduino Due..."
    cmake --build . -j
    # Programm
    # NOTE: The command to program the Arduino Due uses "~/bossac.exe". This 
    #       must be a symbolic link to bossac.exe on the Windows host. We first 
    #       test if it's present.
    if [ ! -s ~/bossac.exe ]
    then 
        echo "Warning: bossac.exe is not reachable for programming"
        exit 1  # exit script with status 1
    fi
    echo ""
    echo "To program your Arduino Due, "
    echo "- plug the USB cable to the PROGRAMMING PORT and connect power to the Shield"
    echo "- press and hold the Erase button, then press the Reset button"
    echo "- release both buttons"
    echo "- confirm here with <enter>"
    echo "Cancel with <CTRL + C>"
    read    # wait for enter
    # NOTE: Meaning of the arguments:
    #  -i   show information about the Controller to be programmed
    #  -e   erase chip before programming
    #  -w   write file
    #  -v   verify 
    #  -R   Reset CPU
    #  -b   startup from Flash 
    # --port=COM3 -U    set the Arduino Due Programming Port
    ~/bossac.exe -i --port=COM3 -U true -e -w -v -R -b test/board/test_board.bin

fi 
exit 0

# return to calling directory
#cd ..
