#include "SPD_Arduino.h"

namespace DDR4 {
    const uint8_t PAGE0_ADDR = 0x36;
    const uint8_t PAGE1_ADDR = 0x37;
}

static inline void i2cWrite(uint8_t addr, uint8_t address, uint8_t data) {
    Wire.beginTransmission(addr);
    Wire.write(address);
    Wire.write(data);
    Wire.endTransmission();
    delay(10);
}

static inline uint8_t i2cRead(uint8_t addr, uint8_t address) {
    Wire.beginTransmission(addr);
    Wire.write(address);
    Wire.endTransmission(false);
    Wire.requestFrom(addr, 1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0xFF;
}

void SPDClass::begin(uint8_t type, uint8_t addr) {
    spdType = type;
    spdaddr = addr;
}

uint8_t SPDClass::read(uint16_t address) {
    if (spdType == 4) {
        uint8_t pageAddr = (address < 256) ? DDR4::PAGE0_ADDR : DDR4::PAGE1_ADDR;
        i2cWrite(pageAddr, 0x00, 0x00);
    }
    return i2cRead(spdaddr, address & 0xFF);
}

void SPDClass::write(uint16_t address, uint8_t value) {
    if (spdType == 4) {
        uint8_t pageAddr = (address < 256) ? DDR4::PAGE0_ADDR : DDR4::PAGE1_ADDR;
        i2cWrite(pageAddr, 0x00, 0x00);
    }
    i2cWrite(spdaddr, address & 0xFF, value);
}

SPDClass SPD;