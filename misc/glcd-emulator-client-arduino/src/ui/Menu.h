#include <Arduino.h>
#include "logos.h"
#include <GlcdRemoteClient.h>

#ifndef _MenuStruct
#define _MenuStruct

enum MenuType {
    // 带图标的快捷开关
    ICON_SWITCH,
    // 列表快捷开关
    LIST_SWITCH,
    // 列表目录
    LIST_DIR,
    // 列表项目
    LIST_ITEM
};

struct MenuStruct
{
    uint8_t id;
    char name[20];
    char code[40];
    const uint8_t *icon;
    MenuType type;
    MenuStruct *children[5];
    MenuStruct *parent;
};
class Menu
{
private:
    /* data */
    // 菜单列表
    MenuStruct menus[10];
    // 当前选中菜单序号
    int selectedMenuIdx = 0;
    // 当前菜单指针，根菜单时为空
    MenuStruct *curMenu;
public:
    Menu(/* args */);
    ~Menu();
    // 上一项菜单
    void prev();
    // 下一项菜单
    void next();
    // 返回上一层菜单
    void back();
    // 绘制菜单
    void show(GlcdRemoteClient *u8g2);
    // 刷新菜单
    void refresh(GlcdRemoteClient *u8g2);
    // 获取当前菜单
    MenuStruct *getCurMenu();
};

#endif