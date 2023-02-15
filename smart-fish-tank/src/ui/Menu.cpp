#include "Menu.h"
#include "customer_font.h"

MenuItem::MenuItem()
{}

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
    // 设置列表菜单
    MenuItem setBackMenu;
    setBackMenu.id = 50;
    strcpy(setBackMenu.name, "返回");
    strcpy(setBackMenu.code, "settings_back");
    setBackMenu.type = MenuType::LIST_ITEM;
    settings.children.push_back(setBackMenu);

    MenuItem setTemperatureMenu;
    setTemperatureMenu.id = 51;
    strcpy(setTemperatureMenu.name, "水温设定");
    strcpy(setTemperatureMenu.code, "settings_temp");
    setTemperatureMenu.type = MenuType::LIST_ITEM;
    settings.children.push_back(setTemperatureMenu);

    MenuItem setFeedTimeMenu;
    setFeedTimeMenu.id = 52;
    strcpy(setFeedTimeMenu.name, "喂食时长设置");
    strcpy(setFeedTimeMenu.code, "settings_feed_time");
    setFeedTimeMenu.type = MenuType::LIST_ITEM;
    settings.children.push_back(setFeedTimeMenu);

    MenuItem setLightTimerMenu;
    setLightTimerMenu.id = 53;
    strcpy(setLightTimerMenu.name, "定时灯光");
    strcpy(setLightTimerMenu.code, "settings_light_timer");
    setLightTimerMenu.type = MenuType::LIST_ITEM;
    settings.children.push_back(setLightTimerMenu);

    MenuItem setFeedTimerMenu;
    setFeedTimerMenu.id = 54;
    strcpy(setFeedTimerMenu.name, "定时喂食");
    strcpy(setFeedTimerMenu.code, "settings_feed_timer");
    setFeedTimerMenu.type = MenuType::LIST_ITEM;
    settings.children.push_back(setFeedTimerMenu);

    MenuItem setO2TimerMenu;
    setO2TimerMenu.id = 55;
    strcpy(setO2TimerMenu.name, "定时增氧");
    strcpy(setO2TimerMenu.code, "settings_o2_timer");
    setO2TimerMenu.type = MenuType::LIST_ITEM;
    settings.children.push_back(setO2TimerMenu);
    
    this->menus.push_back(settings);

    // 默认选中菜单1（喂食模式）
    this->selectedMenuIdx = 1;
}

// 设置当前菜单
void Menu::setMenuById(int menuId)
{
    MenuItem *r = this->findMenuById(this->menus, menuId);
    if (r != nullptr)
    {
        
    }
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

void Menu::selectMenuByIdx(int idx)
{
    if (idx < this->menus.size())
    {
        this->selectedMenuIdx = idx;
        this->curMenu = &(menus[idx]);
    }
}

MenuItem *Menu::getCurMenu()
{
    return this->curMenu;
}

MenuItem Menu::getSelectedMenu()
{
    return this->menus[this->selectedMenuIdx];
}

MenuItem *Menu::findMenuById(vector<MenuItem> menus, int menuId)
{
    MenuItem *result = nullptr;

    for (vector<MenuItem>::iterator iter = menus.begin(); iter != menus.end(); iter++)
	{
		if (menuId == (*iter).id) 
        {
            result = &(*iter);
            break;
        }

        if (!(*iter).children.empty()) 
        {
            result = findMenuById((*iter).children, menuId);
            if (result != nullptr)
            {
                return result;
            }
        }
	}

    return result;
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