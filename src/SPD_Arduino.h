#ifndef SPD_ARDUINO_H
#define SPD_ARDUINO_H

#include <Arduino.h>
#include <Wire.h>

class SPDClass {
private:
    uint8_t spdType;  // 3, 4, or 5
    uint8_t spdaddr;  // I2C address

public:
    void begin(uint8_t type, uint8_t addr);
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
};

extern SPDClass SPD;

#endif