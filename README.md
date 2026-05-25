# SPD_Arduino

English description [README.md](README.md)
简体中文版 [README_cn.md](README_cn.md)

## Project Overview

`SPD_Arduino` is an Arduino library for reading/writing EEPROM / Serial Presence Detect (SPD) chips, lightly wrapped for the ESP32 / Arduino platform. The library communicates with SPD devices over I2C and provides simple initialization, read and write interfaces, making it easy to retrieve memory module information or operate small I2C EEPROMs in firmware.

## Key Features

- Initialization: `begin(spdType, addr)`
- Read: `read(address)`
- Write: `write(address, value)`

## Compatibility

- ESP32
- Arduino (uses Wire / I2C)

## Installation

1. Install this repository as an Arduino library in your `libraries/` folder, or use the Arduino IDE "Add .ZIP Library" feature.
2. Include `Wire.h` in your sketch (the library implementation uses Wire).

## Pins & Wiring

Connect the target SPD/EEPROM SDA to your board's SDA, SCL to SCL, and wire power and ground. Common ESP32 I2C pins are GPIO21 (SDA) and GPIO22 (SCL), but check your board.

Typical wiring (ESP32):

- SPD SDA -> GPIO21
- SPD SCL -> GPIO22
- VCC -> 3.3V (or device's required voltage)
- GND -> GND

## Usage Example

The examples/examples.ino file contains a demo. Minimal example:

```cpp
#include <Wire.h>
#include <SPD_Arduino.h>

void setup() {
	Serial.begin(115200);
	Wire.begin(); // For ESP32 you can pass SDA/SCL pins, e.g. Wire.begin(21, 22);

	SPD.begin(3, 0x50);  // Initialize with spdType = DDR3, SPD I2C address = 0x50

	uint16_t val = SPD.read(0);  // Read byte at address 0
	Serial.print("Read value: ");
	Serial.println(val);

	SPD.write(10, 0x42);  // Write 0x42 to byte address 10
}

void loop() {
	// empty
}
```

## API Reference

- `void begin(uint8_t spdType, uint8_t addr)`
	- Initialize the library. `spdType` distinguishes device types internally, `addr` is the I2C address (e.g. 0x50).
- `uint16_t read(uint16_t address)`
	- Read a value from the specified byte address and return it.
- `void write(uint16_t address, uint8_t value)`
	- Write a value to the specified byte address.

(See source: [src/SPD_Arduino.h](src/SPD_Arduino.h) and [src/SPD_Arduino.cpp](src/SPD_Arduino.cpp))

## Tips & Debugging

- Use `Serial` prints to confirm I2C communication.
- If you experience issues, check device power, pull-up resistors on I2C, and the device address.

## License

This project is licensed as described in LICENSE.txt in this repository.


