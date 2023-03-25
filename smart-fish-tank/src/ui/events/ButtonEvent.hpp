#ifndef __SFT_BUTTON_EVENT
#define __SFT_BUTTON_EVENT
#include "UiEvent.hpp"

class ButtonEvent : public UiEvent
{
private:
    /* data */
public:
    ButtonEvent(/* args */);
    ButtonEvent(EventTypes eventType);
    ButtonEvent(EventTypes eventType, any payload);
    static ButtonEvent newClickedEvent();
    static ButtonEvent newPressedEvent();
    static ButtonEvent newReleasedEvent();
    static ButtonEvent newLongPressEvent();

    ~ButtonEvent();
};

ButtonEvent::ButtonEvent(/* args */)
{
}

ButtonEvent::ButtonEvent(EventTypes eventType) {
    ButtonEvent(eventType, any{});
}

ButtonEvent::ButtonEvent(EventTypes eventType, any payload) {
    switch (eventType)
    {
    case CLICKED:
    case PRESSED:
    case RELEASED:
    case LONGPRESS:
        this->id = eventType;
        break;
    default:
        break;
    }

    this->payLoad = payload;
}

ButtonEvent ButtonEvent::newClickedEvent() {
    return ButtonEvent(EventTypes::CLICKED);
}
ButtonEvent ButtonEvent::newPressedEvent() {
    return ButtonEvent(EventTypes::PRESSED);
}

ButtonEvent ButtonEvent::newReleasedEvent() {
    return ButtonEvent(EventTypes::RELEASED);
}

ButtonEvent ButtonEvent::newLongPressEvent() {
    return ButtonEvent(EventTypes::LONGPRESS);
}

ButtonEvent::~ButtonEvent()
{
}

#endif