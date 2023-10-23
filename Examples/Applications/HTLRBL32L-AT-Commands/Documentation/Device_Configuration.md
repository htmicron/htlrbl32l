# Device Configuration

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

### Region

Sets the region of operation of the device, avaiable regions in this version are 1 (AU915),5 (EU868) and 8 (US915). Check the full documentation to find details.

| **Command**         | **Parameter**             | **Description**        |
| ------------------- | ------------------------- | ---------------------- |
| AT+REGION=<param>   | 1, or 5 or 8              | Sets the LoRaWAN Region|
| AT+REGION?          |              | Returns to current Region|

### ADR
Sets the ADR bit. Adaptive Data Rate (ADR) is a mechanism for optimizing data rates, airtime and energy consumption in the network.
The ADR mechanism controls the following transmission parameters of an end device.

     Spreading factor
     Bandwidth
     Transmission power

>[!NOTE]
>Default TX Datarate is ignored when the ADR bit is active

| **Command**    | **Parameter** | **Description**            |
| -------------- | ------------- | -------------------------- |
| AT+ADR=<param> | Off=0 On=1    | Sets the ADR bit           |
| AT+ADR?        |               | Returns current ADR config |

### Default TX Datarate

| **Command**   | **Parameter** | **Description**           |
| ------------- | ------------- | ------------------------- |
| AT+DR=<param> | 0-7           | Sets the default datarate |
| AT+DR?        |               | Returns default datarate  |

>[!NOTE]
>Default Datarate is not used when the ADR bit is activated

### Data rate configurations

| **DR** | **AU915** | **US915** | **EU868** |
| ------ | --------- | --------- | --------- |
| 0      | SF12BW125 | SF10BW125 | SF12BW125 |
| 1      | SF11BW125 | SF9BW125  | SF11BW125 |
| 2      | SF10BW125 | SF8BW125  | SF10BW125 |
| 3      | SF9BW125  | SF7BW125  | SF9BW125  |
| 4      | SF8BW125  | SF8BW500  | SF8BW125  |
| 5      | SF7BW125  | Invalid   | SF7BW125  |
| 6      | SF8BW500  | Invalid   | SF7BW250  |
| 7      | Invalid   | Invalid   | FSK       |

### Join Delay
Delay between Tx and opening the Rx1 and Rx2 windows during activation (used by OTAA activation mode)

| **Command**             | **Parameter**        | **Description**                   |
| ----------------------- | -------------------- | --------------------------------- |
| AT+JOINDELAYRX1=<param> | Time in microssecond | Sets the join delay on the RX1    |
| AT+JOINDELAYRX1?        |                      | Returns the join delay on the RX1 |
| AT+JOINDELAYRX2=<param> | Time in microssecond | Sets the join delay on the RX2    |
| AT+JOINDELAYRX2?        |                      | Returns the join delay on the RX2 |


### RX Window delay

Delay between Tx and opening the Rx1 and Rx2 windows during regular execution

| **Command**         | **Parameter**        | **Description**              |
| ------------------- | -------------------- | ---------------------------- |
| AT+DELAYRX1=<param> | Time in microssecond | Sets the delay on the RX1    |
| AT+DELAYRX1?        |                      | Returns the delay on the RX1 |
| AT+DELAYRX2=<param> | Time in microssecond | Sets the delay on the RX2    |
| AT+DELAYRX2?        |                      | Returns the delay on the RX2 |

### RX Window Duration

Sets the duration in which the Rx windows stay open (regular and join procedure RX windows). This rule must be respected when setting Rx window delays: (Rx2Delay-Rx1Delay) >= (RxDuration +100).

| **Command**           | **Parameter**        | **Description**                 |
| --------------------- | -------------------- | ------------------------------- |
| AT+RXDURATION=<param> | Time in microssecond | Sets the duration RX stays open |
| AT+RXDURATION?        |                      | Returns the set duration        |

### TX Power

Tx power can be limited by regional specification, please refer to RP002-1.0.2 LoRaWAN Regional Parameters Document for more information

| **Command**      | **Parameter** | **Description**          |
| ---------------- | ------------- | ------------------------ |
| AT+POWER=<param> | 0-15          | Sets the TX power level  |
| AT+POWER?        |               | Returns current TX power |

### Add Channels

Command compatible with US915 and AU915 regions only.

>[!NOTE]
>Maximum of 8 channels per command (e.g: AT+CHMASK=1:2:3:4:5:10:25:8)

| **Command**       | **Parameter**             | **Description**                   |
| ----------------- | ------------------------- | --------------------------------- |
| AT+CHMASK=<param> | param1:param2:param3...\* | Adds channels to the channel mask |
| AT+CHMASK?        |                           | Returns current channel mask      |

The frequency each channel represents in the device is on [Channel Config](Documentation/Channel_config.md)


### Remove Channels

>[!NOTE]
>Command compatible with US915 and AU915 regions only.
>Maximum of 8 channels per command (e.g: AT+RMVCHMASK=1:2:3:4:5:10:25:8)
>Sending a “AT+RMVCHMASK=0” command revert the channel mask to its default state.

| **Command**          | **Parameter**             | **Description**                        |
| -------------------- | ------------------------- | -------------------------------------- |
| AT+RMVCHMASK=<param> | param1:param2:param3...\* | Removes channels from the channel mask |
| AT+CHMASK?           |                           | Returns current channel mask           |

### Network Mode

| **Command**        | **Parameter**                   | **Description**              |
| ------------------ | ------------------------------- | ---------------------------- |
| AT+NWKMODE=<param> | 0: private mode, 1: public mode | Sets network mode            |
| AT+NWKMODE?        |                                 | Returns current network mode |



