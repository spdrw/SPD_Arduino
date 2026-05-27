#include "SPD_Arduino.h"

namespace _DDR4 {
    const uint8_t PAGE0_ADDR = 0x36;
    const uint8_t PAGE1_ADDR = 0x37;
}

SPDClass SPD;
static constexpr uint8_t SPD_PAGE_DELAY_MS = 5;
static constexpr uint8_t SPD_WRITE_DELAY_MS = 10;

static inline void i2cWriteSimple(uint8_t addr, const uint8_t* data, size_t len) {
    Wire.beginTransmission(addr);
    Wire.write(data, (size_t)len);
    (void)Wire.endTransmission();
}

static inline void i2cReadSimple(uint8_t addr, uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; ++i) data[i] = 0xFF;
    uint8_t received = Wire.requestFrom(addr, (uint8_t)len);
    for (uint8_t i = 0; i < received && i < len; ++i) {
        if (Wire.available()) data[i] = (uint8_t)Wire.read();
    }
}

static inline void i2cWriteThenReadSimple(uint8_t addr, const uint8_t* wdata, size_t wlen, uint8_t* rdata, size_t rlen) {
    Wire.beginTransmission(addr);
    Wire.write(wdata, (size_t)wlen);
    (void)Wire.endTransmission(false); // repeated start
    i2cReadSimple(addr, rdata, rlen);
}

static inline void ddr4SetPage(uint16_t address) {
    uint8_t pageAddr = (address < 256) ? _DDR4::PAGE0_ADDR : _DDR4::PAGE1_ADDR;
    uint8_t data = 0x00;
    i2cWriteSimple(pageAddr, &data, 1);
    delay(SPD_PAGE_DELAY_MS);
}

static inline void checkSPDDevice(uint8_t addr) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() != 0) {
        Serial.print("SPD device not found at address 0x");
        Serial.println(addr, HEX);
        while (true);
    }
}

void SPDClass::begin(uint8_t spdType, uint8_t addr) {
    _spdType = spdType;
    _addr = addr;
    checkSPDDevice(_addr);
}

uint16_t SPDClass::read(uint16_t address) {
    if (_spdType == 4) {
        ddr4SetPage(address);
    }
    uint8_t addrByte = (uint8_t)(address & 0xFF);
    uint8_t data = 0xFF;
    i2cWriteThenReadSimple(_addr, &addrByte, 1, &data, 1);
    return data;
}

void SPDClass::write(uint16_t address, uint8_t value) {
    if (_spdType == 4) {
        ddr4SetPage(address);
    }
    uint8_t buf[2] = {(uint8_t)(address & 0xFF), value};
    i2cWriteSimple(_addr, buf, 2);
    delay(10);
}