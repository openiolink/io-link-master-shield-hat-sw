#!/bin/bash

################################################################################
# Sets up the toolchain for the specified target (if not already done), compiles
# the Software for this target and starts the debugger.
#
# NOTE: DO NOT call this script manually. It is called by make.sh
################################################################################

## direct call prevention
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

