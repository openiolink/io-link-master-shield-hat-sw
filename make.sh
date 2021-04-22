#!/bin/bash

################################################################################
# HELP                                                                          
# usage:                                                                        
#   make.sh             display this help and exit                              
#   make.sh $1          compile SW for platform ($1)                            
#   make.sh $1 [-p]     compile and program                                     
#   make.sh $1 [-d]     compile and debug                                       
#                                                                               
# command line argument $1:                                                     
#   raspi       target Raspberry Pi                                             
#   arduino     target Arduino Due                                              
#   clean       clean up "build" and "debug" directory                          
################################################################################

## (constant) variable declaration
# Flags
PROGRAM_FLAG="-p"
DEBUG_FLAG="-d"
# code names for different tasks
STRING_RASPI="raspi"
STRING_ARDUINO="arduino"
STRING_CLEAN="clean"
# tasks
COMPILE=""
PROGRAM=""
DEBUG=""
CLEAN=""
# direct call prevention for sub-scripts
CODE=123

## argument checking
# No argument specified --> display help and exit
if [ $# -eq 0 ]
then 
    echo ""
    echo " HELP                                                "
    echo " usage:                                              "
    echo "   make.sh             display this help and exit    "
    echo "   make.sh \$1          compile SW for platform (\$1)  "
    echo "   make.sh \$1 [-p]     compile and program           "
    echo "   make.sh \$1 [-d]     compile and debug             "
    echo "                                                     "
    echo " command line argument \$1:                           "
    echo "   raspi       target Raspberry Pi                   "
    echo "   arduino     target Arduino Due                    "
    echo "   clean       clean up 'build' and 'debug' directory"
    echo ""
    echo ""
    exit 0
fi

# check the first argument
if [ $1 != $STRING_RASPI ] && [ $1 != $STRING_ARDUINO ] && [ $1 != $STRING_CLEAN ]
then
    echo "invalid argument"
    echo "please specify \"$STRING_RASPI\", \"$STRING_ARDUINO\" or \"$STRING_CLEAN\""
    exit 1
elif [ $1 = $STRING_CLEAN ]
then
    CLEAN="yes"
    echo "CLEAN=yes"
else
    COMPILE="yes"
    echo "COMPILE=yes"
fi

# process second argument
# A) Programming after Compilation
if [ "$2" = "$PROGRAM_FLAG" ]
then
    PROGRAM="yes"

# B) Compile for Debugging (Raspberry Pi only)
elif [ "$2" = "$DEBUG_FLAG" ]
then
    if [ "$1" == "$STRING_RASPI" ]
    then
        DEBUG="yes"
    else
        echo "Error: Debugging is supported on Raspberry Pi only"
        exit 1
    fi
fi

## call apropriate sub-script 
# make sure the working directory for this script is the root of the software repository
cd ~/git/io-link-master-shield-hat-sw/

if [ $COMPILE ]
then 
    if [ $DEBUG ]
    then
        echo "calling debug.sh"
        ./debug.sh $1 $CODE

    elif [ $PROGRAM ]
    then
        echo "calling program.sh"
        ./program.sh $1 -p $CODE

    else
        echo "calling program.sh"
        ./program.sh $1 -- $CODE
    fi

elif [ $CLEAN ]
then
    echo "calling program.sh"
    ./program.sh clean --  $CODE
fi
