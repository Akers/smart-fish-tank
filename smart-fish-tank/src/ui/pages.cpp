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
    u8g2->drawLine(43, 45, 38, 54);
    u8g2->drawStr(45, 57, targetTempStr);
    drawIcon(u8g2, 43, 25, ICONS::TEMPUTER_18X18);
}

/**
 * 气温
 */
void draw_air_temp(U8G2 *u8g2, uint8_t airTemp)
{
    u8g2->setFont(HarmonyOS_Sans_14);
    // u8g2->setCursor(65, 32);
    // u8g2->print("temp:");
    u8g2->drawXBMP(80, 20, 12, 12, icon_airtemp_12);
    // u8g2->setCursor(91, 32);
    // u8g2->print(":");
    u8g2->setCursor(98, 32);
    // u8g2->printf("%d°C", airTemp);
    u8g2->printf("%d°C", 0);
}

/**
 * 湿度
 */
void draw_air_humidity(U8G2 *u8g2, uint8_t airHumidity)
{
    u8g2->setFont(HarmonyOS_Sans_14);
    // u8g2->setCursor(65, 46);
    // u8g2->print("wet:");
    u8g2->drawXBMP(80, 34, 12, 12, icon_humidity_12);
    u8g2->setCursor(98, 46);
    u8g2->printf("%d%s", airHumidity, "%");
}

/**
 * TDS
 */
void draw_TDS(U8G2 *u8g2, uint8_t tds)
{
    u8g2->setFont(HarmonyOS_Sans_14);
    // u8g2->setCursor(65, 59);
    // u8g2->print("TDS:");
    u8g2->drawXBMP(80, 47, 12, 12, icon_tds_12);
    u8g2->setCursor(98, 59);
    u8g2->printf("%d", tds);
}

/**
 * 绘制首页
 */
void draw_main_page(U8G2 *u8g2, const char *timeStr, uint8_t curTemp, uint8_t targetTemp, uint8_t airTemp, uint8_t airHumidity, uint8_t tds, boolean wifiFlag, boolean pumpFlag, boolean lightFlag, boolean heaterFlag, boolean o2Flag, boolean feedFlag, boolean coolerFlag)
{
    vector<StatusFlag> status;
    // put your main code here, to run repeatedly:
    if (wifiFlag)
    {
        status.push_back(StatusFlag::WIFI_CONECTED);
    }
    if (pumpFlag)
    {
        status.push_back(StatusFlag::PUMP_ON);
    }
    if (heaterFlag)
    {
        status.push_back(StatusFlag::HEATER_ON);
    }
    if (lightFlag)
    {
        status.push_back(StatusFlag::LIGHT_ON);
    }
    if (o2Flag)
    {
        status.push_back(StatusFlag::O2_ON);
    }
    if (coolerFlag)
    {
        status.push_back(StatusFlag::COOLER_ON);
    }
    if (feedFlag)
    {
        status.push_back(StatusFlag::FEEDMODE);
    }
    draw_main_page(u8g2, timeStr, curTemp, targetTemp, airTemp, airHumidity, tds, status);
}

void draw_main_page(U8G2 *u8g2, const char *timeStr, uint8_t curTemp, uint8_t targetTemp, uint8_t airTemp, uint8_t airHumidity, uint8_t tds, vector<StatusFlag> statusFlags)
{
    u8g2->clearBuffer();
    u8g2->setFont(HarmonyOS_Sans_14);
    // 当前时间
    u8g2->setCursor(3, 13);
    u8g2->print(timeStr);

    int size = statusFlags.size();
    int y_pox = 113;
    for (int i = 0; i < size; i++)
    {
        y_pox = 113 - (i * 13);
        if (y_pox < 0)
        {
            y_pox = 0;
        }
        drawIcon(u8g2, y_pox, 2, statusIconMap[statusFlags[i]]);
    }

    // 分割线
    u8g2->drawLine(4, 15, 123, 15);

    // 温度显示
    draw_temperature(u8g2, curTemp, targetTemp);

    // 纵向分割
    u8g2->drawLine(75, 20, 75, 57);
    draw_air_temp(u8g2, airTemp);
    draw_air_humidity(u8g2, airHumidity);
    draw_TDS(u8g2, tds);
    u8g2->sendBuffer();
}

/**
 * 绘制图标菜单
 */
void draw_icon_menu(U8G2 *u8g2, MenuItem menu)
{
    u8g2->clearBuffer();
    // u8g2->drawXBMP(40, 2, 48, 48, menu->icon);
    // u8g2->drawXBMP(40, 2, 48, 48, *menu->icon);
    drawIcon(u8g2, 40, 0, menu.icon);
    u8g2->setFont(YaHei_12);
    u8g2->setCursor(40, 60);
    u8g2->print(menu.name);
    u8g2->sendBuffer();
}

static const int LIST_MENU_PAGE_SIZE = 3;
static const int MENU_NAME_POS_X = 4;
static const int MENU_NAME_BOX_WIDTH = 120;

/**
 * 绘制列表菜单
 * @param menu 当前列表菜单的父级菜单对象
 * @param post 当前菜单位置
 */
void draw_list_menu(U8G2 *u8g2, MenuItem menu, int pos)
{
    u8g2->clearBuffer();
    // 计算当前选中序号所在页数
    int pageNum = pos <= LIST_MENU_PAGE_SIZE ? 1 : (int)((pos - 1) / LIST_MENU_PAGE_SIZE);
    // 计算需展示菜单区间
    int start = (pageNum - 1) * LIST_MENU_PAGE_SIZE;
    int end = start + LIST_MENU_PAGE_SIZE - 1;

    if (end > (menu.children.size() - 1))
    {
        end = menu.children.size() - 1;
    }
    int menuNameYPos = 3;
    u8g2->setFont(HarmonyOS_Sans_12);
    for (int i = start; i <= end; i++)
    {
        // 计算展示位置
        u8g2->setCursor(MENU_NAME_POS_X, menuNameYPos);

        if (pos == i)
        {
            // 菜单选中
            u8g2->setDrawColor(0);
            u8g2->drawRBox(MENU_NAME_POS_X, menuNameYPos, MENU_NAME_BOX_WIDTH, 16, 2);
        }
        else
        {
            u8g2->setDrawColor(1);
        }

        u8g2->print(menu.children[i].name);

        menuNameYPos += 20;
    }

    u8g2->sendBuffer();
}