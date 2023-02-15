#include <Arduino.h>
#include <U8g2lib.h>
#include <SmartFishTankConfig.h>
#include "ui/pages.h"

// U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL, I2C_SDA);
// U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL, I2C_SDA);

int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // u8g2.begin();
  // u8g2.enableUTF8Print();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);
}