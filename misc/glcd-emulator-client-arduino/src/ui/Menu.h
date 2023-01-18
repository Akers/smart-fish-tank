#include <Arduino.h>

#ifndef _MenuStruct
#define _MenuStruct
struct MenuStruct
{
    uint8_t id;
    char name[20];
    char code[40];
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
};
#endif

