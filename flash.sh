#!/bin/bash

FIRMWARE_HEX=build/blinky.hex
FIRMWARE_ZIP=build/firmware.zip
DEVICE=/dev/serial/by-id/usb-Seeed_XIAO_nRF52840_Sense_F4CC67C7574B3127-if00

adafruit-nrfutil dfu genpkg --dev-type 0x0052 --sd-req 0x0123 --application $FIRMWARE_HEX $FIRMWARE_ZIP
adafruit-nrfutil dfu serial -p $DEVICE -b 115200 --singlebank -pkg $FIRMWARE_ZIP
