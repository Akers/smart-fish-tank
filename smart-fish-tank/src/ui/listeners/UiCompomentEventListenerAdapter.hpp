#ifndef __SFT_UI_COMPOMENT_EVENT_LISTENER_ADAPTER
#define __SFT_UI_COMPOMENT_EVENT_LISTENER_ADAPTER
#include "UiCompomentEventListener.hpp"

class UiCompomentEventListenerAdapter : public UiCompomentEventListener
{
private:
    /* data */
public:
    UiCompomentEventListenerAdapter(string name, UiEvent event, void (*callback)(UiEvent e, any payload))
        : UiCompomentEventListener(event, name, callback)
    {};
    ~UiCompomentEventListenerAdapter();
};

// 处理事件分发
void UiCompomentEventListener::eventDispatched(UiEvent event, any payload) {
    if (this->event == event) {
        this->callback(event, payload);
    }
}

// 处理事件分发
void UiCompomentEventListener::eventDispatched(UiEvent event) {
    if (this->event == event) {
        any param = std::any{};
        this->callback(event, param);
    }
}

UiCompomentEventListenerAdapter::~UiCompomentEventListenerAdapter()
{
}

#endif