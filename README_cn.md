# SPD_Arduino

English description [README.md](README.md)

简体中文版 [README_cn.md](README_cn.md)

## 项目简介

`SPD_Arduino` 是一个用于读取/写入 EEPROM/Serial Presence Detect (SPD) 芯片的 Arduino 库，针对 ESP32 / Arduino 平台进行了轻量封装。库通过 I2C 与 SPD 器件通信，提供简单的初始化、读写接口，方便在固件中获取内存条信息或操作小型 I2C EEPROM，目前仅支持DDR4及以下。

## 主要特性

- 初始化：`begin(spdType, addr)`
- 读取：`read(address)`
- 写入：`write(address, value)`

## 兼容性

- ESP32
- Arduino（使用 Wire / I2C 总线）

## 引脚与接线

将目标 SPD/EEPROM 器件的 SDA 接到开发板的 SDA，SCL 接到 SCL，并接好电源与地。ESP32 常见的 I2C 引脚为 GPIO21 (SDA) 和 GPIO22 (SCL)，但以你的板子为准。

示例接线（ESP32 常见）：

- SPD SDA -> GPIO21
- SPD SCL -> GPIO22
- VCC -> 3.3V（或器件要求电压）
- GND -> GND

## 使用示例

examples/examples.ino 中包含演示。下面是一个最小示例：

```cpp
#include <Wire.h>
#include <SPD_Arduino.h>

void setup() {
	Serial.begin(115200);
	Wire.begin(); // 对于 ESP32 可传入 SDA/SCL 引脚，例如 Wire.begin(21, 22);

	SPD.begin(3, 0x50);  // 初始化DDR类型为DDR3,SPD地址为0x50

	uint16_t val = SPD.read(0);  // 读取字节地址 0 的值
	Serial.print("Read value: ");
	Serial.println(val);

	SPD.write(10, 0x42);  // 将值 0x42 写入字节地址 10
}

void loop() {
	// 空循环
}
```

## API 参考

- `void begin(uint8_t spdType, uint8_t addr)`
	- 初始化库，`spdType` 为器件类型（库实现使用该参数做内部区分），`addr` 为 I2C 地址（例如 0x50）。
- `uint16_t read(uint16_t address)`
	- 从指定字节地址读取值并返回。
- `void write(uint16_t address, uint8_t value)`
	- 向指定字节地址写入值。

（更多细节参见源代码：[src/SPD_Arduino.h](src/SPD_Arduino.h) 和 [src/SPD_Arduino.cpp](src/SPD_Arduino.cpp)）

## 示例与调试建议

- 使用 `Serial` 打印调试信息以确认 I2C 是否正常。
- 如果遇到通信问题，检查器件电源电压、I2C 拉高电阻以及地址是否正确。

## 许可证

本项目遵循本仓库中的 LICENSE.txt 许可。

---


