![Ghostkey](https://github.com/raf181/Ghostkey/blob/main/wiki/source/Untitled.webp)
---
# Ghostkey
Ghostykey is a fake HID inputdevice that can be used to simulate keyboard input. It was inspired by the [Rubber Ducky](https://shop.hak5.org/products/usb-rubber-ducky-deluxe) and the [Bash Bunny](https://shop.hak5.org/products/bash-bunny). For hardware, it uses the XIAO SAMD21 board to do the HID through USB, and the [XIAO ESP32C6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html) board to do the WiFi connection and deploy selected payloads.

## Hardware
### XIAO SAMD21:
The [XIAO SAMD21](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html) powered by Microchip SAMD21G18 chip is an ultra-small, high-performance universal development board, the pioneering product of the XIAO series made by Seeed Studio. 

It was chosen for its small size, low cost, and the ability to act as a USB HID device. The [XIAO SAMD21](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html) is the main board that will be used to simulate the keyboard input.

### XIAO ESP32C6:
The [XIAO ESP32C6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html) is a small development board that is powered by the ESP32-C6 chip. It is designed for IoT applications and is capable of several methods of communication (Zigbee, thread, wifi, BLE). These board is used as the brain.

> [!note]
> Im aware that the [XIAO NRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html) is capable of doing HID through USB, and has integrated BLE, but at the time of writing this, I don't have one to test.
>
> And using the XIAO SAMD21 and the XIAO [ESP32C6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html) allows the posible use of longer range methods of communication (Zigbee, thread, wifi, BLE) at the beggining I will only focuse on wifi since it allows the use of the [ESP32C6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html) as a AP or using it to conect to a wifi and get the payloads from a C2 server.

# Install and Configuration

