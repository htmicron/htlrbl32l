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
> The [Device Configuration](Documentation/Device_Configuration.md) section has all the commands necessary to configure the device. If you need to understand what these parameters means, access this [Link](https://www.thethingsindustries.com/docs/devices/abp-vs-otaa/)

| **Command**       | **Parameter**             | **Description**        |
| ----------------- | ------------------------- | ---------------------- |
| AT+DEVEUI=<param> | 16 charactere hexadecimal | Sets the DevEUI        |
| AT+DEVEUI?        |                           | Returns current DevEUI |


## Packet send/receive

[Packet send/receive](Documentation/Packet_send_receive.md)

## Max payload

[Max payload](Documentation/Max_payload.md)

## Default parameter state

[Default parameter state](Documentation/Default_parameter_state.md)

## Error codes

[Error codes](Documentation/Error_codes.md)
