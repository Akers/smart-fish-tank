#include "Menu.h"
#include <GlcdRemoteClient.h>

/**
 * 绘制首页
*/
void draw_main_page(GlcdRemoteClient *u8g2, const char *timeStr, uint8_t curTemp, uint8_t targetTemp, uint8_t airTemp, uint8_t airHumidity, uint8_t tds, boolean wifiFlag, boolean pumpFlag, boolean lightFlag, boolean heaterFlag, boolean o2Flag, boolean feedFlag);

/**
 * 绘制图标菜单
*/
void draw_icon_menu(GlcdRemoteClient *u8g2, MenuItem menu);

/**
 * 绘制列表菜单
*/
void draw_list_menu(GlcdRemoteClient *u8g2, MenuItem menu);



