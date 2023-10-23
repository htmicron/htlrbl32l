# AT Commands Specification

This application has the objective of making the first contact with the HTLRBL32L’s LoRaWAN® capabilities quick and easy using AT commands through a UART interface. The LoRaWAN version used on this application is LoRaWAN 1.0.2rb and has all the features required to run on any LoRaWAN® network.

### Serial Terminal Setup

To use the UART interface you can choose between 
- connect the pins TX(PA9) and RX(PA8) to a USB-Serial converter and connecting it to a computer
- connect to another microcontroller with a UART interface

The parameters values to configure the serial communication are shown bellow

| Parameter    | Value      |
| ---------------- | ---------- |
| Baud rate        | 115200     |
| Data bits        | 8          |
| Stop bits        | 1          |
| Parity           |  none      |
| Flow Control     |  none      |
| Transmitted text |  Append LF |

## AT Command Syntax

In the table bellow, you can see how the syntax is interpreted by the hardware

| **Command**         | **Description**                    |
| ------------------- | ---------------------------------- |
| AT+CMD=?            | Read the parameter value           |
| AT+CMD              | Executes a command                 |
| AT+CMD=<parameters> | Executes a command with parameters |

## General Commands

To send commands, the used syntax is the one shown bellow

| **Command**      | **Parameter**    | **Description**             |
| ---------------- | ---------------- | --------------------------- |
| AT+ECHO =<param> | Any string value | Returns the input parameter |


## Device configuration

> [!IMPORTANT]
> The [Device Configuration](https://github.com/htmicron/htlrbl32l/blob/SDK/Examples/Applications/HTLRBL32L-AT-Commands/Documentation/Device_Configuration.md) section has all the commands necessary to configure the device. If you need to understand what these parameters means, access this [Link](https://www.thethingsindustries.com/docs/devices/abp-vs-otaa/)

| **Command**       | **Parameter**             | **Description**        |
| ----------------- | ------------------------- | ---------------------- |
| AT+DEVEUI=<param> | 16 charactere hexadecimal | Sets the DevEUI        |
| AT+DEVEUI?        |                           | Returns current DevEUI |

To see the full device configuration, go to [Device Configuration](Documentation/Device_Configuration.md)

## Sending or Receving a message
There are different types of messages used to transport MAC commands and application data. To see how to configure these messages on HTLRBL32L SiP, check [Packet send/receive](Documentation/Packet_send_receive.md).

## Max payload
Maximum payload displays the maximum payload allowed for each datarate of each region, to check the table with the values for each region, go to [Max payload](Documentation/Max_payload.md).

## Default parameter state
When the system is initialized/reset all parameters go to their default state, to check them go to [Default parameter state](Documentation/Default_parameter_state.md).

## Error codes
After every command and during special events the system will return a hexadecimal 4-byte error code referring to possible errors during the execution, to check the codes go to [Error codes](Documentation/Error_codes.md).
