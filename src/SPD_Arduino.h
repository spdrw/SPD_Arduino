#ifndef SPD_Arduino_H
#define SPD_Arduino_H

#include <Arduino.h>
#include <Wire.h>

class SPDClass {
public:
	void begin(uint8_t spdType, uint8_t addr);
	uint16_t read(uint16_t address);
	void write(uint16_t address, uint8_t value);
private:
	uint8_t _addr = 0x50;
	uint8_t _spdType = 3;
};

extern SPDClass SPD;

#endif
