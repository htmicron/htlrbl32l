# Error Codes

After every command and during special events the system will return a hexadecimal 4-byte error code referring to possible errors during the execution, using this format: 

![Error Codes](https://github.com/KKerne/htlrbl32l/blob/SDK/Examples/Applications/HTLRBL32L-AT-Commands/Documentation/LoRa_error_codes.png)

| **Code** | **Description**            |
| -------- | -------------------------- |
| 0x00     | No errors                  |
| 0x01     | Invalid command            |
| 0x02     | Parameter missing          |
| 0x03     | Parameter overflow         |
| 0x04     | Invalid command header     |
| 0x05     | Expected hexadecimal value |

## Uart Error Codes

The second byte is related to possible UART errors.

| **Code** | **Description**           |
| -------- | ------------------------- |
| 0x00     | No errors                 |
| 0x01     | Command max size violated |
| 0x02     | Empty command             |

## LoRa Error Codes

The third byte refers to LoRa errors.

| **Code** | **Description**                  |
| -------- | -------------------------------- |
| 0x00     | No errors                        |
| 0x01     | Invalid region                   |
| 0x02     | Invalid Rx Window configuration¹ |
| 0x03     | Network already joined           |
| 0x04     | Invalid payload size             |
| 0x05     | Invalid payload+FOPTS size²      |
| 0x06     | No new Rx Data                   |
| 0x07     | LoRaWAN stack error³             |
| 0x08     | Tx Timeout                       |

¹ - (Rx2 Window Delay - Rx1 Window Delay) must be greater than (Rx Window size + 100). 
Eg: 
Rx2Delay = 1000.
Rx1Delay = 2000.
RxDuration = 850.

(Rx2Delay-Rx1Delay) >= (RxDuration +100) OK

Eg: 
Rx2Delay = 1000.
Rx1Delay = 2000.
RxDuration = 1500.

(Rx2Delay-Rx1Delay) >= (RxDuration +100) ERROR

² - Application Payload plus LoRaWAN configuration commands exceeds max payload size. This error can be reported dynamically during execution. When this error happens, the packet is sent without the application payload.

³ - Internal LoRaWAN stack error. After this error the stack is reset (user configuration is maintained)
