#include <Arduino.h>
#include <Wire.h>
#include "SPD_Arduino.h"

const uint16_t SPD_SIZE = 512; // Total SPD Data Size

void read() {
    Serial.println("Read all SPD data and print");
    for (uint16_t i = 0; i < SPD_SIZE; i++) {
        uint8_t value = SPD.read(i);
        
        if (value < 0x10) Serial.print("0");
        Serial.print(value, HEX);
        Serial.print(" ");
        
        if ((i + 1) % 16 == 0) {
            Serial.println();
        }
    }
}

void setup() {
    Serial.begin(115200);
    Wire.begin();
    SPD.begin(4, 0x50); // Initialized as DDR4 type, address 0x50
    delay(1000);
    
    read();
    delay(2000);
    
    Serial.println("Write all bytes as 0xDF");
    for (uint16_t i = 0; i < SPD_SIZE; i++) {
        SPD.write(i, 0xDF);
    }
    
    delay(2000);
    read();
}

void loop() {
}