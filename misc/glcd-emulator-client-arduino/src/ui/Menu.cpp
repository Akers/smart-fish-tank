#include "Menu.h"
#include "customer_font.h"

Menu::Menu(/* args */)
{
    // 菜单0: 首页
    MenuItem home(ICONS::HOME_48X48);
    home.id = 1;
    strcpy(home.name, "返回主屏");
    strcpy(home.code, "Home");
    home.type = MenuType::ICON_SWITCH;
    this->menus.push_back(home);


    // 菜单1: 开启喂食模式
    MenuItem feedModeSwitch(ICONS::FEEDING_48X48);
    feedModeSwitch.id = 2;
    strcpy(feedModeSwitch.name, "喂食模式");
    strcpy(feedModeSwitch.code, "FeedMode");
    feedModeSwitch.type = MenuType::ICON_SWITCH;
    this->menus.push_back(feedModeSwitch);

    // 菜单2: 水泵开关
    MenuItem pumpSwitch(ICONS::PUMP_48X48);
    pumpSwitch.id = 3;
    strcpy(pumpSwitch.name, "开启水泵");
    strcpy(pumpSwitch.code, "PumpSwitch");
    pumpSwitch.type = MenuType::ICON_SWITCH;
    this->menus.push_back(pumpSwitch);

    // 菜单3: 灯光开关
    MenuItem lightSwitch(ICONS::LIGHT_48X48);
    lightSwitch.id = 4;
    strcpy(lightSwitch.name, "开启灯光");
    strcpy(lightSwitch.code, "LightSwitch");
    lightSwitch.type = MenuType::ICON_SWITCH;
    this->menus.push_back(lightSwitch);


    // 菜单4: 加热开关
    MenuItem heaterSwitch(ICONS::HEATER_48X48);
    heaterSwitch.id = 5;
    strcpy(heaterSwitch.name, "开启加热");
    strcpy(heaterSwitch.code, "HeaterSwitch");
    heaterSwitch.type = MenuType::ICON_SWITCH;
    this->menus.push_back(heaterSwitch);


    // 菜单5: 设置页面
    MenuItem settings(ICONS::SETTING_48X48);
    settings.id = 5;
    strcpy(settings.name, "设置菜单");
    strcpy(settings.code, "settings");
    settings.type = MenuType::ICON_SWITCH;
    this->menus.push_back(settings);


    // 默认选中菜单1（喂食模式）
    this->selectedMenuIdx = 1;
}

void Menu::show(U8G2 *u8g2)
{
    this->refresh(u8g2);
}

void Menu::refresh(U8G2 *u8g2) 
{
    u8g2->clearBuffer();
    drawIcon(u8g2, 40, 10, this->getSelectedMenu().icon);
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(20, 48);
    u8g2->print(this->curMenu->name);
    u8g2->sendBuffer();
}

MenuItem *Menu::getCurMenu()
{
    return this->curMenu;
}

MenuItem Menu::getSelectedMenu()
{
    return this->menus[this->selectedMenuIdx];
}

void Menu::next()
{
    if (++this->selectedMenuIdx >= this->menus.size())
    {
        this->selectedMenuIdx = 0;
        this->curMenu = &(this->menus[this->selectedMenuIdx]);
    } else {
        this->curMenu = &(this->menus[this->selectedMenuIdx]);
    }
}

void Menu::prev()
{
    if (--this->selectedMenuIdx <= 0 )
    {
        this->selectedMenuIdx = this->menus.size() - 1;
        this->curMenu = &(this->menus[this->selectedMenuIdx]);
    } else {
        this->curMenu = &(this->menus[this->selectedMenuIdx]);
    }
}

void Menu::back()
{
    if (this->curMenu->parent) {
        this->curMenu = this->curMenu->parent;
    }
}

Menu::~Menu()
{
}