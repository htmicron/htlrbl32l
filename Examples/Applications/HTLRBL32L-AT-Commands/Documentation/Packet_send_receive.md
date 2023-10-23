## Join Procedure
Performs the join procedure, exchanging keys required to communicate with the network server. Command is required to be used once before sending a payload if Network Join Type is OTAA.

| **Command**     | **Parameter** | **Description**      |
| --------------- | ------------- | -------------------- |
| AT+JOIN=<param> |               | Sends a join request |
| AT+JOIN?        |               | Return join status   |

## Send Payload (string)

Sends an uplink to the network server containing a user payload. Automatically opens both RX windows to expect a downlink.

| **Command**     | **Parameter**         | **Description** |
| --------------- | --------------------- | --------------- |
| AT+SEND=<param> | 1-242 bytes payload\* | Sends a packet  |

> [!IMPORTANT]
> Payload size is dependent on current Datarate, refer to item 7 (Max Payload) for the appropriate values.

## Send Payload (Hexadecimal)

Sends an uplink to the network server containing a hexadecimal user payload. Automatically opens both RX windows to expect a downlink.

| **Command**        | **Parameter**         | **Description** |
| ------------------ | --------------------- | --------------- |
| AT+SENDHEX=<param> | 1-242 bytes payload\* | Sends a packet  |

> [!IMPORTANT]
> Payload size is dependent on current Datarate, refer to item 7 (Max Payload) for the appropriate values.

## Receive Payload

Returns the last application payload received by downlink. If there is no payload received or it has already been read an error is reported. Only payload addressed to LoRaWAN port 2 are returned.

| **Command** | **Parameter** | **Description**                   |
| ----------- | ------------- | --------------------------------- |
| AT+RCV      |               | Returns the last received payload |

## Rx Stats

Returns the last received packet stats (RSSI/SNR) on this format: <RSSI> <SNR>.

| **Command** | **Parameter** | **Description**                                  |
| ----------- | ------------- | ------------------------------------------------ |
| AT+STATS?   |               | Returns RSSI and SNR of the last packet received |
