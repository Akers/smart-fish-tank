#include <Arduino.h>
#include "icons.h"
#include <U8G2Lib.h>
#include <vector> 
using namespace std;

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

class MenuItem
{
public:
    uint8_t id;
    char name[20];
    char code[40];
    ICONS icon;
    MenuType type;
    MenuItem *children[5];
    MenuItem *parent;
    MenuItem(ICONS i) : icon(i) {};
};

class Menu
{
private:
    /* data */
    // 菜单列表
    vector<MenuItem> menus;
    // 当前选中菜单序号
    int selectedMenuIdx = 0;
    // 当前菜单指针，根菜单时为空
    MenuItem *curMenu;
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
    void show(U8G2 *u8g2);
    // 刷新菜单
    void refresh(U8G2 *u8g2);
    // 获取当前菜单
    MenuItem *getCurMenu();
    MenuItem getSelectedMenu();
};

#endif