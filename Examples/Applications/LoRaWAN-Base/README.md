# LoRaWAN Base

This application is meant to be a simple and easy to use LoRaWAN showcase and also a template from which you can derive your custom firmware. This document will show you how to test and customize this firmware to your own needs. 

The firmware works by basically transmitting a LoRaWAN packet with custom payload periodically. It is based on the LoRaWAN 1.0.2 rb specification. Can operate on AU915, EU868, and US915 regions with class A and works on ABP/OTAA activation modes. 

## Device Configuration

There are some important parameters that must be configured before you can compile and flash the firmware in the device, such as: LoRaWAN keys, activation type (ABP/OTAA), region of operation, and other configurations that need to match your specific case.
This section will go through the most important configs and how you can change them.

### Before compiling the code

#### Preprocessors

There are three configuration options that need to be addressed in the preprocessor directives of the compiler: activation mode, region, and HT crypto. They’re accessible through Wise-Studio’s IDE, as follows:

> Right click on the project -> Properties -> C/C++ Build -> Settings -> GCC C Compiler -> Preprocessor

![Preprocessor](https://github.com/KKerne/htlrbl32l/blob/SDK/Examples/Applications/LoRaWAN-Base/preprocessor.png)

#### Modes of operation

 -	OVER_THE_AIR_ACTIVATION: 1 for OTAA (Over the Air Activation) and 0 for ABP (Activation by Personalization)
 -	HT_CRYPTO: Its definition enables/disables the use of the HT Crypto library and secure element (if your hardware version supports it)  
 -	DEFAULT_REGION: Region specification based on the document RP002-1.0.2 LoRaWAN® Regional Parameters. The pre-certified available options are on the table bellow.

| **Value** | **Region** |
| --------- | ---------- |
| 1         | AU915      |
| 5         | EU868      |
| 8         | US915      |


## HT Crypto

If you have the hardware version that has the Hardware Secure Element embedded, you can enable the HT Crypto library within this project. 
The HT Crypto library is a cryptographic solution that also has an interface with the Hardware Secure Element (HSM), where it stores your LoRaWAN root keys, greatly increasing the security of your device against attacks that aim to clone your 
device or intercept messages. If you enable the HT Crypto solution, be sure to check the Key Provisioner Firmware Manual before running this firmware. There you will learn how to store your root keys inside the HSM.

## LoRaWAN Keys

For the cases that doesn’t use the HT Crypto solution the LoRaWAN root keys must be set directly on code. To do that you must edit the file “Inc/lorawandefines.h”, where addresses and keys for each activation mode (ABP or OTAA) are set up.

## Default Transmission Channels

Each region has around 64 different transmission channels available that can be used to send uplinks, but on most cases your gateway only supports 8 of those channels. So, you must configure your device to match those channels. 
Each region has a specific file on the project that must be edited to configure which channels are going to be used.

Follow the project path and open the file according to your region: 

> HTLRBL32L-SDK->LoRaWAN->lorawan_specifics->Mac->region->RegionAU915.c
> HTLRBL32L-SDK->LoRaWAN->lorawan_specifics->Mac->region->RegionUS915.c

The function RegionUS915InitDefaults or RegionAU915InitDefaults, depending on your region, has a channel mask, that must be configured accordingly:

![Channel Mask](https://github.com/KKerne/htlrbl32l/blob/SDK/Examples/Applications/LoRaWAN-Base/Default_channel_mask.png)

Each bit of the mask corresponds as an enabled channel and each array index holds 16 channels, on Figure 1 you can see that only channels 0 to 7 are enabled (0x00FF= 0000 0000 1111 1111). 

The same rule applies for array indexes 1 to 5. FIGURE 2 has enabled channels 24 to 31 (0xFF00= 1111 1111 0000 0000).  while disabled all others. 

![Channel Config](https://github.com/KKerne/htlrbl32l/blob/SDK/Examples/Applications/LoRaWAN-Base/Channel_config_example.png)

Through this method you can set any combination of channels you require.

The channel number and frequency are available on [Channel Configuration](https://github.com/KKerne/htlrbl32l/blob/SDK/Examples/Applications/HTLRBL32L-AT-Commands/Documentation/Channel_config.md) file.

## Custom Payload Transmission

On this application, an uplink with a generic message is sent every 15 seconds. To send your own uplink message all you need to do is call the function “lorawan_send” with your custom payload. 
The function is located on the “lorawan_setup.c” file. 
After you call this function the LoRaWAN state machine is set in motion which will that care of the TX and RX processes.


## Max Payload

Every region and datarate has its own maximum payload size, you need to keep it in mind when customizing your own payload. The Table bellow contains the maximum available payload sizes for each configuration. 
Note that the maximum value might be a little smaller depending on if some additional configuration bits are added automatically to the packet by the LoRaWAN stack.

| **Datarate** | **AU915** | **EU868** | **US915** |
| ------------ | --------- | --------- | --------- |
| 0            | 51        | 51        | 11        |
| 1            | 51        | 51        | 53        |
| 2            | 51        | 51        | 125       |
| 3            | 115       | 115       | 242       |
| 4            | 242       | 242       | 242       |
| 5            | 242       | 242       | Invalid   |
| 6            | 242       | 242       | Invalid   |
| 7            | Invalid   | 242       | Invalid   |


## Serial Terminal Setup

The UART interface can be used by connecting the pins TX(PA9) and RX(PA8) to a USB-Serial converter and connecting to a computer or simply connecting it to another microcontroller with a UART interface.

UART configuration required to connect:
-	Baud rate: 115200
-	Data bits: 8
-	Stop bits: 1
-	Parity: none
-	Flow Control: none
-	Transmitted text: Append LF

### Termite Setup

One of the most widely used software for UART communication using a computer is Termite.
The required configurations to use it are shown bellow.

![Termite Setup](https://github.com/KKerne/htlrbl32l/blob/SDK/Examples/Applications/LoRaWAN-Base/Termite_Setup.png)



