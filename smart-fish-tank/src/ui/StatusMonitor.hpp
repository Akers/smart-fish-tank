#ifndef __SFT_STATUSMONITOR
#define __SFT_STATUSMONITOR
#include "compoments/UiContainer.hpp"

class StatusMonitor : public UiContainer
{
private:
    /* data */
public:
    StatusMonitor(string id) : StatusMonitor(id, nullptr){};
    StatusMonitor(string id, U8G2 *u8g2_t) : StatusMonitor(id, u8g2_t, 0, 0, 0, 0){};
    StatusMonitor(string id, int width, int height) : StatusMonitor(id, nullptr, width, height, 0, 0){};
    StatusMonitor(string id, int width, int height, int x, int y) : StatusMonitor(id, nullptr, width, height, x, y){};
    StatusMonitor(string id, U8G2 *u8g2_t, int width, int height) : StatusMonitor(id, nullptr, width, height, 0, 0){};
    StatusMonitor(string id, U8G2 *u8g2_t, int width, int height, int x, int y);
    ~StatusMonitor();
};

StatusMonitor::StatusMonitor(string id, U8G2 *u8g2_t, int width, int height, int x, int y) : UiContainer(id, u8g2_t, width, height, x, y)
{
}

StatusMonitor::~StatusMonitor()
{
}

#endif