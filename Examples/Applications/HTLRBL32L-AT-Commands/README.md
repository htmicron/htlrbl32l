# AT Commands Specification

This application has the objective of making the first contact with the HTLRBL32L’s LoRaWAN® capabilities quick and easy using AT commands through a UART interface. The LoRaWAN version used on this application is LoRaWAN 1.0.2rb and has all the features required to run on any LoRaWAN® network.

### Serial Terminal Setup

**** put a pic of pins TX(PA9) and RX(PA8) to a USB-Serial converter and connecting to a computer or simply connecting it to another microcontroller with a UART interface

| Parameter    | Value      |
| ---------------- | ---------- |
| Baud rate        | 115200     |
| Data bits        | 8          |
| Stop bits        | 1          |
| Parity           |  none      |
| Flow Control     |  none      |
| Transmitted text |  Append LF |

## AT Command Syntax

| **Command**         | **Description**                    |
| ------------------- | ---------------------------------- |
| AT+CMD=?            | Read the parameter value           |
| AT+CMD              | Executes a command                 |
| AT+CMD=<parameters> | Executes a command with parameters |

## General Commands

| **Command**      | **Parameter**    | **Description**             |
| ---------------- | ---------------- | --------------------------- |
| AT+ECHO =<param> | Any string value | Returns the input parameter |


## Device configuration

> [!IMPORTANT]
> This section has all the commands necessary to configure the device. If you need to understand what these parameters means, access this [Link](https://www.thethingsindustries.com/docs/devices/abp-vs-otaa/)

| **Command**       | **Parameter**             | **Description**        |
| ----------------- | ------------------------- | ---------------------- |
| AT+DEVEUI=<param> | 16 charactere hexadecimal | Sets the DevEUI        |
| AT+DEVEUI?        |                           | Returns current DevEUI |

### Activation Mode

| **Command**        | **Parameter**   | **Description**                         |
| ------------------ | --------------- | --------------------------------------- |
| AT+JOINCFG=<param> | ABP=0<br>OTAA=1 | Sets the join procedure type            |
| AT+JOINCFG?        |                 | Returns the current join procedure type |

### Keys Commands
#### ABP

>[!NOTE]
> ABP keys configuration is not required when using OTAA (Over-The-Air-Activation).

| **Command**        | **Parameter**             | **Description**         |
| ------------------ | ------------------------- | ----------------------- |
| AT+DEVADDR=<param> | 8 charactere hexadecimal  | Sets the DevAddr        |
| AT+DEVADDR?        |                           | Returns current DevAddr |
| AT+APPSKEY=<param> | 32 charactere hexadecimal | Sets the AppSKey        |
| AT+APPSKEY?        |                           | Returns current AppSKey |
| AT+NWKSKEY=<param> | 32 charactere hexadecimal | Sets the NwkSKey        |
| AT+NWKSKEY?        |                           | Returns current NwkSKey |

#### OTAA
>[!NOTE]
>OTAA keys configuration is not required when using ABP (Activation by Personalization).

| **Command**         | **Parameter**             | **Description**        |
| ------------------- | ------------------------- | ---------------------- |
| AT+APPEUI=<param>   | 16 charactere hexadecimal | Sets the AppEUI        |
| AT+APPEUI?          |                           | Returns current AppEUI |
| AT+ APPKEY =<param> | 32 charactere hexadecimal | Sets the AppKey        |
| AT+APPKEY?          |                           | Returns current AppKey |

#### Region

Sets the region of operation of the device, avaiable regions in this version are 1 (AU915),5 (EU868) and 8 (US915). Check the full documentation to find details.

| **Command**         | **Parameter**             | **Description**        |
| ------------------- | ------------------------- | ---------------------- |
| AT+REGION=<param>   | 1, or 5 or 8              | Sets the LoRaWAN Region|
| AT+REGION?          |              | Returns to current Region|

#### ADR
>[!NOTE]
>Default TX Datarate is ignored when the ADR bit is active

| **Command**    | **Parameter** | **Description**            |
| -------------- | ------------- | -------------------------- |
| AT+ADR=<param> | Off=0 On=1    | Sets the ADR bit           |
| AT+ADR?        |               | Returns current ADR config |



## Packet send/receive

## Max payload

## Default parameter state

## Error codes
