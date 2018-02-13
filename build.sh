#!/bin/bash

USB=`lsusb | grep Clay`
BUS=`echo $USB | cut -f2 -d" "`
DEV=`echo $USB | cut -f4 -d" " | sed 's/.$//'`

make clean

make jj40:$1 || exit 1

sudo usb_detach /dev/bus/usb/${BUS}/${DEV}

sudo ./util/atmega32a_program.py .build/jj40_$1.hex
