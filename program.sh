#!/bin/bash

################################################################################
# Sets up the toolchain for the specified target (if not already done), compiles
# the Software for this target and programs it (if specified).
#
# NOTE: DO NOT call this script manually. It is called by make.sh
################################################################################

# TODO: make programming the target board optional, only when -p is provided
# TODO: clean when changing target board

## direct call prevention ------------------------------------------------------
# With this, it's not neccessary to check all arguments again
CODE=123
if [ $3 -ne $CODE ]
then 
    echo "DO NOT call program.sh directly. It is used by make.sh."
    exit 1
fi

## functions -------------------------------------------------------------------
clean() {
    echo "rm -rf *"
    rm -rf *
}

checkLastTarget() {
    # make sure the check file exists
    checkFile=$2
    touch $checkFile

    # check if the target changed (i.e. the current target is (not) equal to the last target
    currentTarget=$1
    lastTarget=$(<$checkFile)
    if [ "$currentTarget" != "$lastTarget" ]
    then
        echo "The target changed, cleaning the debug directory..."
        clean
    fi

    # update the check file with the current target
    printf "$currentTarget" > "$checkFile"
}

## script ----------------------------------------------------------------------
# make sure the working directory for this script is the root of the software repository
cd ~/git/io-link-master-shield-hat-sw/

# Create build directory if not present, and enter it
if [ ! -d build ]
then
    mkdir build
fi
cd build

# make sure there is no wrong toolchain (i.e. form an other target board) set up
checkFileName="lastTarget.txt"
checkLastTarget $1 $checkFileName

## Make sure that (at least) one command (argument) was provided
#if [ $# -eq 0 ]
#then
#    echo "please specify 'raspi', 'arduino' or 'clean'"

# Delete everything inside "build"
#elif [ $1 = "clean" ]
if [ $1 = "clean" ]
then
    clean

else # compilation is requested
    # make sure there is no wrong toolchain (i.e. form an other target board) set up
    checkFileName="lastTarget.txt"
    checkLastTarget $1 $checkFileName

    # Compile for Raspberry Pi and copy the executable to it. If not already done, 
    # the build system is initialized first
    #elif [ $1 = "raspi" ]
    if [ $1 = "raspi" ]
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
        echo "Copied software test_board to Raspberry Pi"
        echo "You can now start it by issuing \"./test_board\" in the home directory of the Raspberry Pi."

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

    # Compile for the WSL to run unit tests with Catch2
    elif [ $1 = "test" ]
    then
        # Initialize build system
        if [ ! -d CMakeFiles ]  # CMakeFiles directory not present --> cmake not ready
        then
            cmake ..
            echo ""
            echo "Initialized the build system for Unit Testing"
        fi
        # Compile
        echo "Building for Unit Testing..."
        cmake --build . -j
        # Inform the user where to find the executable
        echo "You can now search your executable... ;)"

    fi
fi
exit 0

# return to calling directory
#cd ..
