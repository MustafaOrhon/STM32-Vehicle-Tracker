# STM32 Vehicle Tracker

A vehicle tracker prototype on an STM32F413 with FreeRTOS, written during my internship at the
Teltonika IoT & B2B Academy in Kaunas (February to April 2024). It reads its position from a GNSS
receiver, sends records to a server over TCP/IP through a GSM modem, and answers SMS commands with
its location.

## What is in it

| Layer | Folder | Contents |
|---|---|---|
| Drivers | `STM32CubeIDE_Project/Source/Driver` | GPIO and UART drivers on the LL library, the UART with a ring buffer |
| APIs | `STM32CubeIDE_Project/Source/API` | UART, modem (AT commands), TCP, SMS, GNSS, a command line, debug output, memory and LEDs; the shared ones are locked for use from several tasks |
| Applications | `STM32CubeIDE_Project/Source/APP` | the network connection, record sending, SMS handling, the command line, LEDs |
| Utility | `STM32CubeIDE_Project/Source/Utility` | interrupt helpers |
| Third party | `STM32CubeIDE_Project/Source/ThirdParty` | STM32Cube and FreeRTOS sources |

## Notes

- The recipient's number in `sms_api.c` is a placeholder.
- The repository shows the code; it has no build or set-up guide.
