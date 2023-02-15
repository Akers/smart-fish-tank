#include <Arduino.h>
#include <U8g2lib.h>
#include <SmartFishTankConfig.h>
#include "ui/pages.h"

// U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL, I2C_SDA);

int count = 0;

static boolean wifiConnected = false;
static boolean pumpOn = false;
static boolean heaterOn = false;
static boolean lightOn = false;
static boolean o2On = false;
static boolean coolerOn = false;
static boolean feedMode = false;

static int curTemp = 23; //当前水温
static int targetTemp = 26; //目标水温
static int airTemp = 28; //气温
static int airHumidity = 70; //湿度
static int tds = 0; //TDS数值

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // u8g2.begin();
  // u8g2.enableUTF8Print();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  vector<StatusFlag> status;
  // put your main code here, to run repeatedly:
  if (wifiConnected)
  {
    status.push_back(StatusFlag::WIFI_CONECTED);
  }
  if (pumpOn)
  {
    status.push_back(StatusFlag::PUMP_ON);
  }
  if (heaterOn = false)
  {
    status.push_back(StatusFlag::HEATER_ON);
  }
  if (lightOn = false)
  {
    status.push_back(StatusFlag::LIGHT_ON);
  }
  if (o2On = false)
  {
    status.push_back(StatusFlag::O2_ON);
  }
  if (coolerOn = false)
  {
    status.push_back(StatusFlag::COOLER_ON);
  }
  if (feedMode = false)
  {
    status.push_back(StatusFlag::FEEDMODE);
  }
  
  draw_main_page(&u8g2, "17:30", curTemp, targetTemp, airTemp, airHumidity, tds, status);

  delay(2000);
}