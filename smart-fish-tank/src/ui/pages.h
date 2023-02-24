#include <map>
#include "Menu.h"
#include <U8g2lib.h>

// 状态标志
enum StatusFlag {
    WIFI_CONECTED
    , PUMP_ON
    , LIGHT_ON
    , HEATER_ON
    , O2_ON
    , COOLER_ON
    , FEEDMODE
};

// 状态图标映射
static std::map<StatusFlag, ICONS> statusIconMap = {
    {StatusFlag::WIFI_CONECTED, ICONS::WIFI_12X12}
    , {StatusFlag::PUMP_ON, ICONS::PUMP_12X12}
    , {StatusFlag::LIGHT_ON, ICONS::LIGHT_12X12}
    , {StatusFlag::HEATER_ON, ICONS::HEATER_12X12}
    , {StatusFlag::COOLER_ON, ICONS::COOLER_12X12}
    , {StatusFlag::O2_ON, ICONS::O2_12X12}
    , {StatusFlag::FEEDMODE, ICONS::FISH_12X12}
};

/**
 * 绘制首页
*/
void draw_main_page(U8G2 *u8g2, const char *timeStr, uint8_t curTemp, uint8_t targetTemp, uint8_t airTemp, uint8_t airHumidity, uint8_t tds, boolean wifiFlag, boolean pumpFlag, boolean lightFlag, boolean heaterFlag, boolean o2Flag, boolean feedFlag, boolean coolerFlag);

/**
 * 绘制首页
 * @param u8g2 
 * @param timeStr 当前时间
 * @param curTemp 当前水温
 * @param targetTemp 目标水温
 * @param airTemp 气温
 * @param airHumidity 湿度
 * @param tds TDS数值
 * @param statusFlags 状态图标列表
*/
void draw_main_page(U8G2 *u8g2, const char *timeStr, uint8_t curTemp, uint8_t targetTemp, uint8_t airTemp, uint8_t airHumidity, uint8_t tds, vector<StatusFlag> statusFlags);

/**
 * 绘制图标菜单
*/
void draw_icon_menu(U8G2 *u8g2, MenuItem menu);

/**
 * 绘制列表菜单
 * @param menu 当前列表菜单的父级菜单对象
 * @param post 当前菜单位置
*/
void draw_list_menu(U8G2 *u8g2, MenuItem menu, int pos);



