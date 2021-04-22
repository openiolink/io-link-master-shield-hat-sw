#!/bin/bash

################################################################################
# Sets up the SSH remote filesystem from the Raspberry Pi. This is needed to 
# compile software for the Raspberry.
#
################################################################################

sshfs pi@raspberrypi:/ ~/sysroot_raspi/

#echo "default password is raspberry"
