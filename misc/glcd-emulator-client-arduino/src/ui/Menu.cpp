#include "Menu.h"
#include "HarmonyOS_Sans_14.h"

Menu::Menu(/* args */)
{
    // 菜单0: 首页
    MenuStruct home;
    home.id = 1;
    strcpy(home.name, "返回主屏");
    strcpy(home.code, "Home");
    home.type = MenuType::ICON_SWITCH;
    home.icon = icon_home_48;
    this->menus[0] = home;


    // 菜单1: 开启喂食模式
    MenuStruct feedModeSwitch;
    feedModeSwitch.id = 2;
    strcpy(feedModeSwitch.name, "喂食模式");
    strcpy(feedModeSwitch.code, "FeedMode");
    feedModeSwitch.type = MenuType::ICON_SWITCH;
    feedModeSwitch.icon = icon_feeding_48;
    this->menus[1] = feedModeSwitch;

    // 菜单2: 水泵开关
    MenuStruct pumpSwitch;
    pumpSwitch.id = 3;
    strcpy(pumpSwitch.name, "开启水泵");
    strcpy(pumpSwitch.code, "PumpSwitch");
    pumpSwitch.type = MenuType::ICON_SWITCH;
    pumpSwitch.icon = icon_pump_48;
    this->menus[2] = pumpSwitch;

    // 菜单3: 灯光开关
    MenuStruct lightSwitch;
    lightSwitch.id = 4;
    strcpy(lightSwitch.name, "打开灯光");
    strcpy(lightSwitch.code, "LightSwitch");
    lightSwitch.type = MenuType::ICON_SWITCH;
    lightSwitch.icon = icon_light_48;
    this->menus[3] = lightSwitch;

    // 菜单4: 加热开关
    MenuStruct heaterSwitch;
    heaterSwitch.id = 5;
    strcpy(heaterSwitch.name, "开启加热");
    strcpy(heaterSwitch.code, "HeaterSwitch");
    heaterSwitch.type = MenuType::ICON_SWITCH;
    heaterSwitch.icon = icon_heater_48;
    this->menus[4] = heaterSwitch;

    // 菜单5: 设置页面
    MenuStruct settings;
    settings.id = 5;
    strcpy(settings.name, "进入设置");
    strcpy(settings.code, "settings");
    settings.type = MenuType::ICON_SWITCH;
    settings.icon = icon_settings_48;
    this->menus[5] = settings;

    // 默认选中菜单1（喂食模式）
    this->curMenu = &feedModeSwitch;
}

void Menu::show(GlcdRemoteClient *u8g2)
{
    this->refresh(u8g2);
}

void Menu::refresh(GlcdRemoteClient *u8g2) 
{
    u8g2->clearBuffer();
    u8g2->drawXBMP(40, 10, 48, 48, this->curMenu->icon);
    u8g2->setFont(HarmonyOS_Sans_14);
    u8g2->setCursor(20, 48);
    u8g2->print(this->curMenu->name);
    u8g2->sendBuffer();
}

MenuStruct *Menu::getCurMenu()
{
    return this->curMenu;
}

Menu::~Menu()
{
}