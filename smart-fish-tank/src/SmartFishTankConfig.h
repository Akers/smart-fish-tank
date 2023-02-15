/**
 * 配置文件
*/
#ifndef _SMART_FISH_TANK_CONFIG_
#define _SMART_FISH_TANK_CONFIG_

// 引脚定义配置 START

// I2C引脚定义
#define I2C_SDA 4
#define I2C_SCL 5

// 旋转编码器引脚定义
#define ENCODER_PIN_A 10
#define ENCODER_PIN_B 6
#define ENCODER_PIN_BTN 7

// WS2812B灯带控制引脚
#define WS2812B_CTL_PIN 3

// 温度传感器数据引脚
#define TEMP_PIN 2

// 外围设备控制引脚
#define DEVIC_PUMP_PIN 0 // 循环泵继电器控制脚
#define DEVIC_HEAT_PIN 1 // 加热棒继电器控制脚
#define DEVIC_LIGHT_PIN 18 // 灯具继电器控制脚
#define DEVIC_O2_PIN 19 // 增氧泵继电器控制脚
#define DEVIC_COOLER 11 // 24V制冷片控制脚


// 温湿度传感器I2C定义
#define SHTC3_I2C_SDA_PIN 8
#define SHTC3_I2C_SCL_PIN 9

// 引脚定义配置 END
#endif