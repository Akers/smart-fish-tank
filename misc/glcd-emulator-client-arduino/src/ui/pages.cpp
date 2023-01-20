#include "pages.h"
#include "icons.h"
#include "customer_font.h"


/**
 * 绘制Wifi
 */
void draw_signal(U8G2 *u8g2, uint8_t x, uint8_t y, uint8_t strength)
{
    for (uint8_t i = 0; i < strength; i++)
    {
        u8g2->drawCircle(x, y, i * 3, U8G2_DRAW_UPPER_RIGHT);
    }
}

void draw_wifi(U8G2 *u8g2)
{
    u8g2->drawXBMP(113, 2, 12, 12, icon_wifi);
}

/**
 * 绘制水泵启动标识
 */
void draw_pump(U8G2 *u8g2)
{
    u8g2->drawXBMP(100, 2, 12, 12, icon_pump);
}

/**
 * 绘制水草灯启动标识
 */
void draw_light(U8G2 *u8g2)
{
    u8g2->drawXBMP(87, 1, 12, 12, icon_light);
}

/**
 * 绘制加热棒启动标识
 */
void draw_heater(U8G2 *u8g2)
{
    u8g2->drawXBMP(74, 2, 12, 12, icon_heater);
}

/**
 * 绘制增氧启动标识
 */
void draw_o2(U8G2 *u8g2)
{
    u8g2->drawXBMP(61, 2, 12, 12, icon_o2);
}

/**
 * 绘制喂食器启动标识
 */
void draw_fish(U8G2 *u8g2)
{
    u8g2->drawXBMP(48, 1, 12, 12, icon_fish);
}

/**
 * 绘制温度显示
 */
void draw_temperature(U8G2 *u8g2, uint8_t curTemp, uint8_t targetTemp)
{
    u8g2->setFont(u8g2_font_7_Seg_33x19_mn);
    char tempChar[2] = {0};
    itoa(curTemp, tempChar, 10);
    if (curTemp < 10)
    {
        u8g2->drawStr(20, 24, tempChar);
    }
    else
    {
        u8g2->drawStr(2, 24, tempChar);
    }
    char targetTempStr[2] = {0};
    itoa(targetTemp, targetTempStr, 10);
    u8g2->setFont(u8g2_font_freedoomr10_tu);
    u8g2->drawLine(40, 45, 40, 54);
    u8g2->drawStr(43, 57, targetTempStr);
    drawIcon(u8g2, 40, 25, ICONS::TEMPUTER_18X18);
}

/**
 * 气温
 */
void draw_air_temp(U8G2 *u8g2, uint8_t airTemp)
{
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(65, 32);
    u8g2->print("气温:");
    u8g2->setCursor(98, 32);
    u8g2->printf("%d°C", airTemp);
}

/**
 * 湿度
 */
void draw_air_humidity(U8G2 *u8g2, uint8_t airHumidity)
{
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(65, 46);
    u8g2->print("湿度:");
    u8g2->setCursor(98, 46);
    u8g2->printf("%d%s", airHumidity, "%");
}

/**
 * TDS
 */
void draw_TDS(U8G2 *u8g2, uint8_t tds)
{
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(65, 59);
    u8g2->print("TDS:");
    u8g2->setCursor(98, 59);
    u8g2->printf("%d", tds);
}

/**
 * 绘制首页
 */
void draw_main_page(GlcdRemoteClient *u8g2, const char *timeStr, uint8_t curTemp, uint8_t targetTemp, uint8_t airTemp, uint8_t airHumidity, uint8_t tds, boolean wifiFlag, boolean pumpFlag, boolean lightFlag, boolean heaterFlag, boolean o2Flag, boolean feedFlag)
{
    u8g2->clearBuffer();
    u8g2->setFont(HarmonyOS_Sans_14);
    // 当前时间
    u8g2->setCursor(3, 13);
    u8g2->print(timeStr);

    // WIFI连接图标
    if (wifiFlag)
    {
        // draw_wifi(u8g2);
        drawIcon(u8g2, 113, 2, ICONS::WIFI_12X12);
    }
    // 水泵启动图标
    if (pumpFlag)
    {
        // draw_pump(u8g2);
        drawIcon(u8g2, 100, 2, ICONS::PUMP_12X12);
    }
    // 水草灯启动标识
    if (lightFlag)
    {
        // draw_light(u8g2);
        drawIcon(u8g2, 87, 1, ICONS::LIGHT_12X12);
    }
    // 加热棒启动标识
    if (heaterFlag)
    {
        // draw_heater(u8g2);
        drawIcon(u8g2, 74, 2, ICONS::HEATER_12X12);
    }
    // 加氧启动标识
    if (o2Flag)
    {
        // draw_o2(u8g2);
        drawIcon(u8g2, 61, 2, ICONS::O2_12X12);
    }
    // 喂食器启动标识
    if (feedFlag)
    {
        // draw_fish(u8g2);
        drawIcon(u8g2, 48, 1, ICONS::FISH_12X12);
    }

    // 分割线
    u8g2->drawLine(4, 15, 123, 15);

    // 温度显示
    draw_temperature(u8g2, curTemp, targetTemp);

    // 纵向分割
    u8g2->drawLine(61, 22, 61, 57);
    draw_air_temp(u8g2, airTemp);
    draw_air_humidity(u8g2, airHumidity);
    draw_TDS(u8g2, tds);
    u8g2->sendBuffer();
}

/**
 * 绘制图标菜单
*/
void draw_icon_menu(GlcdRemoteClient *u8g2, MenuItem menu)
{
    u8g2->clearBuffer();
    // u8g2->drawXBMP(40, 2, 48, 48, menu->icon);
    // u8g2->drawXBMP(40, 2, 48, 48, *menu->icon);
    drawIconDebug(u8g2, 40, 0, menu.icon);
    u8g2->setFont(YaHei_12);
    u8g2->setCursor(40, 60);
    u8g2->print(menu.name);
    u8g2->sendBuffer();
}

/**
 * 绘制列表菜单
*/
void draw_list_menu(GlcdRemoteClient *u8g2, MenuItem menu)
{

}