#include "pages.h"
#include "logos.h"
#include "HarmonyOS_Sans_14.h"

/**
 * 绘制Wifi
*/
void draw_signal(U8G2 *u8g2, uint8_t x, uint8_t y, uint8_t strength) {
    for (uint8_t i = 0; i < strength; i++) {
        u8g2->drawCircle(x,y,i*3, U8G2_DRAW_UPPER_RIGHT);
    }
}

void draw_wifi(U8G2 *u8g2) {
    u8g2->drawXBMP(113, 2, 12, 12, icon_wifi);
}

/**
 * 绘制水泵启动标识
*/
void draw_pump(U8G2 *u8g2) {
    u8g2->drawXBMP(100, 2, 12, 12, icon_pump);
}

/**
 * 绘制水草灯启动标识
*/
void draw_light(U8G2 *u8g2) {
    u8g2->drawXBMP(87, 1, 12, 12, icon_light);
}

/**
 * 绘制加热棒启动标识
*/
void draw_heater(U8G2 *u8g2) {
    u8g2->drawXBMP(74, 2, 12, 12, icon_heater);
}

/**
 * 绘制增氧启动标识
*/
void draw_o2(U8G2 *u8g2) {
    u8g2->drawXBMP(61, 2, 12, 12, icon_o2);
}

/**
 * 绘制喂食器启动标识
*/
void draw_fish(U8G2 *u8g2) {
    u8g2->drawXBMP(48, 1, 12, 12, icon_fish);
}

/**
 * 绘制温度显示
*/
void draw_temperature(U8G2 *u8g2) {
    u8g2->setFont(u8g2_font_7_Seg_33x19_mn);
    int curTemp = 92;
    char tempChar[2] = {0};
    itoa(curTemp, tempChar, 10);
    if (curTemp < 10) {
        u8g2->drawStr(20, 24, tempChar);
    } else {
        u8g2->drawStr(2, 24, tempChar);
    }
    
    u8g2->setFont(u8g2_font_freedoomr10_tu);
    u8g2->drawLine(40, 45, 40, 54);
    u8g2->drawStr(43, 57, "26");
    u8g2->drawXBMP(40, 25, 18, 18, icon_temp_18);
}

/**
 * 气温
*/
void draw_air_temp(U8G2 *u8g2) {
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(65, 32);
    u8g2->print("气温:");
    u8g2->setCursor(98, 32);
    u8g2->print("14°C");
}

/**
 * 湿度
*/
void draw_air_humidity(U8G2 *u8g2) {
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(65, 46);
    u8g2->print("湿度:");
    u8g2->setCursor(98, 46);
    u8g2->print("60%");
}

/**
 * TDS
*/
void draw_TDS(U8G2 *u8g2) {
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(65, 59);
    u8g2->print("TDS:");
    u8g2->setCursor(98, 59);
    u8g2->print("300");
}

void draw_day_or_night(U8G2 *u8g2) {

}

/**
 * 绘制首页
*/
void draw_main_page(GlcdRemoteClient *u8g2) {
    u8g2->clearBuffer();
    u8g2->setFont(u8g2_font_7x14_tf);
    // 当前时间
    u8g2->drawStr(3, 13, "17:25");
    // WIFI连接图标
    // draw_signal(u8g2, 117, 8, 3);
    draw_wifi(u8g2);
    // u8g2->drawXBMP(110, 2, 16, 16, icon_wifi);
    // 水泵启动图标
    draw_pump(u8g2);
    // 水草灯启动标识
    draw_light(u8g2);
    draw_heater(u8g2);
    draw_o2(u8g2);
    draw_fish(u8g2);
    // 分割线
    u8g2->drawLine(4, 15, 123, 15);

    // 温度显示
    draw_temperature(u8g2);

    // 纵向分割
    u8g2->drawLine(61, 22, 61, 57);
    draw_air_temp(u8g2);
    draw_air_humidity(u8g2);
    draw_TDS(u8g2);
    u8g2->sendBuffer();
}