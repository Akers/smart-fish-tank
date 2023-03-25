/**
 * 简易事件模型
 */
#ifndef __SFT_SIMPLE_EVENTMANAGER
#define __SFT_SIMPLE_EVENTMANAGER
#include <string>
#include <vector>
#include <any>
#include <U8g2lib.h>
#include "../compoments/UiCompoment.hpp"
#include "../device/Encoder.hpp"
#include "UiEvent.hpp"

using namespace std;

/**
 * 简易事件管理器
 */
class EventManager
{
private:
    std::vector<Device *> devices;
    std::vector<UiCompoment *> compoments;

public:
    /**
     * 注册设备
     */
    void registDevice(Device *device);
    /**
     * 注册UI组件
     */
    void registUiCompoment(UiCompoment *compoment);
    /**
     * 清除UI组件
     */
    void clearUiCompoment();
    /**
     * 监听事件，每次循环调用
     */
    void startListening();

    EventManager();
    ~EventManager();
};
EventManager::EventManager()
{
}

EventManager::~EventManager()
{
    devices.clear();
    devices.~vector();
    compoments.clear();
    compoments.~vector();
}

void EventManager::registDevice(Device *device)
{
    bool exists = false;
    for (int i = 0; i < devices.size(); i++)
    {
        if (device->name == devices[i]->name)
        {
            exists = true;
            break;
        }
    }
    if (!exists)
    {
        devices.push_back(device);
    }
}

void EventManager::registUiCompoment(UiCompoment *compoment)
{
    this->compoments.push_back(compoment);
}

void EventManager::startListening()
{
    vector<UiEvent *> triggeredEvents;
    // 获取设备
    for (int i = 0; i < devices.size(); i++)
    {
        vector<EventObject *> triggeredEvents = devices[i]->triggedEvents();
        EventObject *base;
        for (int j = 0; j < triggeredEvents.size(); j++)
        {
            // 判断需要触发的事件
            for (int k = 0; k < this->compoments.size(); k++)
            {
                UiEvent *uievent_p = static_cast<UiEvent *>(triggeredEvents[j]);
                this->compoments[k]->emit(*uievent_p, uievent_p->getPayLoad());
            }
        }
    }
}

void EventManager::clearUiCompoment()
{
    this->compoments.clear();
}
#endif