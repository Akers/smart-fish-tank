#ifndef __SFT_EVENT_RECEIVER
#define __SFT_EVENT_RECEIVER
// Check if platform define is already supplied by build system (Travis-CI defines ATMEGA for tests):
#ifndef __ATMEGA__
// Not yet defined? Make a platform define for ESP32:
#define __ESP32__
#endif
#include "EventSource.hpp"
#include <string>
#include "ustd_map.h"
#include <any>

class EventReceiver
{
private:
    /* data */
    ustd::map<std::string, long> eventMap;
public:
    EventReceiver();
    ~EventReceiver();
    void on(std::string eventName, EventSource* source, void (*cb_fun_t)(EventSource* , EventReceiver* , void *));
    void trigger(std::string eventName, EventSource* source, void* payload);
};

typedef void (*cb_fun_t)(EventSource* , EventReceiver* , void *);

EventReceiver::EventReceiver(/* args */)
{
}

void EventReceiver::on(std::string eventName, EventSource* source, cb_fun_t callback)
{
    if (eventName.empty())
    {
        eventName = EVENTS_DEFAULT;
    }
   this->eventMap[eventName] = (long)callback;

    // this->eventMap.insert(pair<std::string, void (*)(EventSource*, EventReceiver*, std::any)>(eventMap, encoder_long_press));

}

void EventReceiver::trigger(std::string eventName, EventSource* source, void* payload)
{
    int idx = this->eventMap.find(eventName);
    if (idx > 0 && idx < this->eventMap.length())
    {
        // 获取事件回调指针
        long fptr = this->eventMap[eventName];
        // 调用回调函数
        ((cb_fun_t)fptr)(source, this, payload);
    }
}

EventReceiver::~EventReceiver()
{
}

#endif