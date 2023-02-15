#include "icons.h"

void drawIcon(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y, ICONS iconName)
{
    switch (iconName)
    {
    case O2_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_o2);
        break;
    case WIFI_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_wifi);
        break;
    case PUMP_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_pump);
        break;
    case LIGHT_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_light);
        break;
    case HEATER_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_heater);
        break;
    case FISH_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_fish);
        break;
    case COOLER_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_cooler);
        break;
    case TEMPUTER_18X18:
        u8g2->drawXBMP(x, y, 18, 18, icon_temp_18);
        break;
    case FEEDING_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_feeding_48);
        break;
    case O2_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_o2_48);
        break;
    case WIFI_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_wifi_48);
        break;
    case PUMP_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_pump_48);
        break;
    case LIGHT_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_light_48);
        break;
    case HEATER_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_heater_48);
        break;
    case HOME_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_home_48);
        break;
    case SETTING_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_settings_48);
        break;
    default:
        break;
    }
}

void drawIconDebug(GlcdRemoteClient* u8g2, u8g2_uint_t x, u8g2_uint_t y, ICONS iconName)
{
    switch (iconName)
    {
    case O2_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_o2);
        break;
    case WIFI_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_wifi);
        break;
    case PUMP_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_pump);
        break;
    case LIGHT_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_light);
        break;
    case HEATER_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_heater);
        break;
    case COOLER_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_cooler);
        break;
    case FISH_12X12:
        u8g2->drawXBMP(x, y, 12, 12, icon_fish);
        break;
    case TEMPUTER_18X18:
        u8g2->drawXBMP(x, y, 18, 18, icon_temp_18);
        break;
    case FEEDING_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_feeding_48);
        break;
    case O2_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_o2_48);
        break;
    case WIFI_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_wifi_48);
        break;
    case PUMP_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_pump_48);
        break;
    case LIGHT_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_light_48);
        break;
    case HEATER_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_heater_48);
        break;
    case HOME_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_home_48);
        break;
    case SETTING_48X48:
        u8g2->drawXBMP(x, y, 48, 48, icon_settings_48);
        break;
    default:
        break;
    }
}