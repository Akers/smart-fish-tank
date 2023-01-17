#include "Menu.h"

Menu::Menu(/* args */)
{
    MenuStruct feedModeMenu;
    feedModeMenu.id = 1;
    strcpy(feedModeMenu.name, "喂食模式");
    strcpy(feedModeMenu.code, "FeedMode");
    this->menus[0] = feedModeMenu;

    MenuStruct tempConfigMenu;
    tempConfigMenu.id = 2;
    strcpy(tempConfigMenu.name, "温度设置");
    strcpy(tempConfigMenu.code, "TempConf");
    this->menus[1] = tempConfigMenu;

    MenuStruct lightConfigMenu;
    lightConfigMenu.id = 3;
    strcpy(lightConfigMenu.name, "灯光设置");
    strcpy(lightConfigMenu.code, "LightConf");
    this->menus[2] = lightConfigMenu;

    MenuStruct pumpConfigMenu;
    pumpConfigMenu.id = 4;
    strcpy(pumpConfigMenu.name, "水泵设置");
    strcpy(pumpConfigMenu.code, "PumpConfig");
    
    MenuStruct PumpEnableMenu;
    PumpEnableMenu.id = 41;
    strcpy(PumpEnableMenu.name, "水泵常开");
    strcpy(PumpEnableMenu.code, "PumpEnable");
    pumpConfigMenu.children[0] = &PumpEnableMenu;

    MenuStruct PumpFeedModeMenu;
    PumpFeedModeMenu.id = 42;
    strcpy(PumpFeedModeMenu.name, "喂食模式配置");
    strcpy(PumpFeedModeMenu.code, "PumpFeedModeConfig");
    pumpConfigMenu.children[1] = &PumpFeedModeMenu;

    this->menus[3] = pumpConfigMenu;
}

Menu::~Menu()
{
}