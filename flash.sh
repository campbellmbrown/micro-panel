#!/bin/bash

FIRMWARE_HEX=_build/nrf52840_xxaa.hex
FIRMWARE_ZIP=_build/firmware.zip

adafruit-nrfutil dfu genpkg --dev-type 0x0052 --sd-req 0x0123 --application $FIRMWARE_HEX $FIRMWARE_ZIP
adafruit-nrfutil dfu serial -p /dev/ttyACM0 -b 115200 --singlebank -pkg $FIRMWARE_ZIP
