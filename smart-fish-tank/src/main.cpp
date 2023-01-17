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
  Serial.printf("loop: %d\r\n", count);
  if (++count % 2 == 0  ) {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }
  // draw_main_page(u8g2);
  // u8g2.firstPage();
  // do {
  //   u8g2.setFont(u8g2_font_ncenB14_tr);
  //   u8g2.drawStr(0,24,"Hello World!");
  // } while ( u8g2.nextPage() );
  delay(2000);
}