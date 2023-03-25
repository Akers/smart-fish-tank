#ifndef __SFT_ENCODER_EVENT
#define __SFT_ENCODER_EVENT
#include "UiEvent.hpp"

class EncoderEvent : public UiEvent
{
private:
    /* data */
public:
    EncoderEvent(/* args */);
    EncoderEvent(EventTypes eventType);
    EncoderEvent(EventTypes eventType, any payload);
    ~EncoderEvent();
    static EncoderEvent newCwEvent();
    static EncoderEvent newCcwEvent();
};

EncoderEvent::EncoderEvent(/* args */)
{
}

EncoderEvent::EncoderEvent(EventTypes eventType) {
    EncoderEvent(eventType, any{});
}

EncoderEvent::EncoderEvent(EventTypes eventType, any payload) {
    switch (eventType)
    {
    case ENCODER_CW:
    case ENCODER_CCW:
        this->id = eventType;
        break;
    default:
        break;
    }
    this->payLoad = payload;
}

EncoderEvent EncoderEvent::newCwEvent() {
    return EncoderEvent(EventTypes::ENCODER_CW);
}
EncoderEvent EncoderEvent::newCcwEvent() {
    return EncoderEvent(EventTypes::ENCODER_CCW);
}

EncoderEvent::~EncoderEvent()
{
}

#endif