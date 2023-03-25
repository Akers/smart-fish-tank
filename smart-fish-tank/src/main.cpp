// Check if platform define is already supplied by build system (Travis-CI defines ATMEGA for tests):
#ifndef __ATMEGA__
#ifndef __ESP32__
// Not yet defined? Make a platform define for ESP32:
#define __ESP32__
#endif
#endif
#include <Arduino.h>
#include <U8g2lib.h>
#include <map>
#include <SmartFishTankConfig.h>
#include "ui/pages.h"
#include "ui/customer_font.h"
#include "sencers/DS18e20_util.hpp"
#include "events/SimpleEventManager.hpp"

// U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL, I2C_SDA);

DS18e20Sencer dS18e20Sencer(TEMP_PIN);

SimpleEventManager simpleEventManager = SimpleEventManager();

EncoderEventReceiver encoderEventReceiver = EncoderEventReceiver();

Encoder encoder;

int count = 0;

static boolean wifiConnected = true;
static boolean pumpOn = true;
static boolean heaterOn = false;
static boolean lightOn = false;
static boolean o2On = false;
static boolean coolerOn = false;
static boolean feedMode = false;

// 数值变量
static int curTemp = 23;     // 当前水温
static int targetTemp = 26;  // 目标水温
static int airTemp = 28;     // 气温
static int airHumidity = 70; // 湿度
static int tds = 0;          // TDS数值

// 编码器标志
int flag = 0; // 标志位
boolean CW_1 = 0;
boolean CW_2 = 0;
long encoder_btn_press_time = 0;

// 编码器事件
// 编码器顺时针转动回调
void (*encoder_cw)(int variation);
// 编码器逆时针转动回调
void (*encoder_ccw)(int variation);
// 编码器按下回调
void (*encoder_press)(void);
// 编码器长按回调
void (*encoder_long_press)(int interval);

void main_page_encoder_cw(int variation)
{
  Serial.printf("\nmain_page_encoder_cw: %d\n", variation);
}

void main_page_encoder_ccw(int variation)
{
  Serial.printf("\nmain_page_encoder_ccw: %d\n", variation);
}

void main_page_encoder_press(void)
{
  Serial.printf("\nmain_page_encoder_pressed \n");
}

void main_page_encoder_long_press(int interval)
{
  Serial.printf("\nmain_page_encoder_long_pressed: %d \n", interval);
}

/**
 * 旋转编码器中断
 */
IRAM_ATTR void encoder_a_inter()
{
  // 只要处理一个脚的外部中断--上升沿&下降沿
  int alv = digitalRead(ENCODER_PIN_A);
  int blv = digitalRead(ENCODER_PIN_B);
  if (flag == 0 && alv == LOW)
  {
    CW_1 = blv;
    flag = 1;
  }
  if (flag && alv)
  {
    CW_2 = !blv; // 取反是因为 alv,blv必然异步，一高一低。
    // Serial.printf("CW_1: %d, CW_2: %d\n",CW_1, CW_2);
    if (CW_1 && CW_2)
    {
      encoder_cw(1);
    }
    if (CW_1 == false && CW_2 == false)
    {
      encoder_ccw(1);
    }

    flag = 0;
  }
}

IRAM_ATTR void encoder_btn_inter()
{
  int btn = digitalRead(ENCODER_PIN_BTN);
  Serial.printf("\nencoder btn state: %d\n", btn);
  if (btn == LOW)
  {
    long spand = millis() - encoder_btn_press_time;
    // 长按大于3s
    if (spand > 1000)
    {
      // 长按
      encoder_long_press(spand);
      Serial.printf("\nencoder btn long press, interval: %d\n", spand);
    }
    else
    {
      // 短按
      encoder_press();
      Serial.printf("\nencoder btn press, interval: %d\n", spand);
    }
  }
  else
  {
    encoder_btn_press_time = millis();
  }
}

void main_page_encoder_cw(EventSource *sources, EventReceiver *receiver, std::any payload)
{
  Serial.printf("\main_page_encoder_cw\n");
}

void main_page_encoder_ccw(EventSource *sources, EventReceiver *receiver, std::any payload)
{
  Serial.printf("\main_page_encoder_ccw\n");
}

void main_page_encoder_click(EventSource *sources, EventReceiver *receiver, std::any payload)
{
  Serial.printf("\nmain_page_encoder_click\n");
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // u8g2.begin();
  // u8g2.enableUTF8Print();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  dS18e20Sencer.begin();

  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);
  pinMode(ENCODER_PIN_BTN, INPUT);
  // 编码器旋转中断
  //  attachInterrupt(ENCODER_PIN_A, encoder_a_inter, CHANGE);
  //  attachInterrupt(ENCODER_PIN_BTN, encoder_btn_inter, CHANGE);

  // 定义编码器设备
  encoder = Encoder("MainEncoder", ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_BTN);

  // 注册设备
  simpleEventManager.registDevice(encoder);

  // encoder_cw = main_page_encoder_cw;
  // encoder_ccw = main_page_encoder_ccw;
  // encoder_press = main_page_encoder_press;
  // encoder_long_press = main_page_encoder_long_press;
}

void loop()
{
  // Serial.println("Running...");
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
  if (heaterOn)
  {
    status.push_back(StatusFlag::HEATER_ON);
  }
  if (lightOn)
  {
    status.push_back(StatusFlag::LIGHT_ON);
  }
  if (o2On)
  {
    status.push_back(StatusFlag::O2_ON);
  }
  if (coolerOn)
  {
    status.push_back(StatusFlag::COOLER_ON);
  }
  if (feedMode)
  {
    status.push_back(StatusFlag::FEEDMODE);
  }
  curTemp = dS18e20Sencer.read();
  // draw_main_page(&u8g2, "17:30", curTemp, targetTemp, airTemp, airHumidity, tds, status);

  delay(100);
}
