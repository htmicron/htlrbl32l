# HTLRBL32- LoRaBase on FreeRTOS 

## Application Description

This application is an example of running the LoRa stack on FreeRTOS. The example contains two tasks (created in createTasks function in main.c), one dedicated for initializing and running LoRa ticks and another which simply prints out the current FreeRTOS tick count in-between LoRa TX/RX windows at least once every 3 seconds.

Due to being a more time-sensitive task, LORATask will continuously take control of the semaphore to avoid interruption by other tasks.

The variable 'testLastTick' is used to control the last time the testTask was run, to avoid its excessive execution and ensure that LORATask is not suspended when the next TX/RX window is reached.

FreeRTOS configurations are found in FreeRTOSConfig.h.

## Test Setup

This section describes the basic test setup to running this application.

* [Git](https://git-scm.com/downloads).
* [RF-Flasher Utility](https://www.st.com/en/embedded-software/stsw-bnrgflasher.html).
* [WiSE-Studio IDE](https://www.st.com/en/embedded-software/stsw-wise-studio.html).
* RS232 terminal ([Termite](https://www.compuphase.com/software_termite.htm) is recommended).
* [ST-Link Debugger](https://www.st.com/en/development-tools/st-link-v2.html) to flash a firmware.
* HTLRBL32 device.
* Semtech SX1308 LoRa® Gateway.
* FTDI (usb-serial converter – one for each device).

## Extra Documentation

Datasheets and application notes can be found at [HTLRBL32 Repository](https://github.com/htmicron/htlrbl32l).

Application notes relevant to the [LoRaWAN-Base](../LoRaWAN-Base) example are relevant to this example as well.

## References

For additional information:

* [HTLRBL32 datasheet](https://www.st.com/resource/en/datasheet/hts221.pdf).
* [Semtech SX1308 LoRa® Gateway datasheet](https://www.mouser.com/datasheet/2/761/sx1308-1277867.pdf).
* [FreeRTOS Features documentation](https://www.freertos.org/features.html).


## Contact Information

Head Office – São Leopoldo, RS <br/>
HT Micron Semiconductors <br/>
Unisinos Avenue, 1550 <br/>
São Leopoldo - RS <br/>
ZIP 93022-750 <br/>
Brazil <br/>
Tel: +55 51 3081-8650 <br/>
E-mail (Support): support_iot@htmicron.com.br <br/>
E-mail (General Enquiries): htmicron@htmicron.com.b <br/>
