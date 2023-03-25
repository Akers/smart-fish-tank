#ifndef __SFT_Encoder_Event_Receiver
#define __SFT_Encoder_Event_Receiver
#include "EventReceiver.hpp"
#include "EventSource.hpp"
#include <any>

class EncoderEventReceiver : public ButtonEventReceiver
{
private:
    /* data */
public:
    EncoderEventReceiver(/* args */);
    ~EncoderEventReceiver();
    void onCw(cb_fun_t callback);
    void onCcw(cb_fun_t callback);
};
#endif

EncoderEventReceiver::EncoderEventReceiver()
{
}
EncoderEventReceiver::~EncoderEventReceiver()
{
}
void EncoderEventReceiver::onCw(cb_fun_t callback)
{
    on(EVENTS_ENCODER_CW, callback);
}

void EncoderEventReceiver::onCcw(cb_fun_t callback)
{
    on(EVENTS_ENCODER_CCW, callback);
}