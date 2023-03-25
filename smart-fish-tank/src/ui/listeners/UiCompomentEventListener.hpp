#ifndef __SFT_UI_COMPOMENT_EVENT_LISTENER
#define __SFT_UI_COMPOMENT_EVENT_LISTENER
#include "../../libevent/EventListener.hpp"
#include "../events/UiEvent.hpp"

class UiCompomentEventListener : public EventListener
{
public:
    // 回掉函数
    void (*callback)(UiEvent e, any payload);
    // 监听器监听的事件
    UiEvent event;
private:
    /* data */
    
public:
    UiCompomentEventListener(/* args */) : EventListener(){};
    UiCompomentEventListener(string name) : EventListener(name) {};
    UiCompomentEventListener(string name, void (*callback)(UiEvent e, any payload)) : EventListener(name), callback(callback) {};
    UiCompomentEventListener(UiEvent event, string name, void (*callback)(UiEvent e, any payload)) : EventListener(name), event(event), callback(callback) {};
    ~UiCompomentEventListener();
    // 事件处理函数
    virtual void eventDispatched(UiEvent event, any payload);
    virtual void eventDispatched(UiEvent event);
};

UiCompomentEventListener::~UiCompomentEventListener()
{
}

#endif