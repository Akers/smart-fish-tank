#ifndef __SFT_Encoder_Event_Receiver
#define __SFT_Encoder_Event_Receiver
#include "EventReceiver.hpp"
#include "EventSource.hpp"
#include <any>

class EncoderEventReceiver:EventReceiver
{
private:
    /* data */
public:
    EncoderEventReceiver(/* args */);
    ~EncoderEventReceiver();
};


EncoderEventReceiver::EncoderEventReceiver()
{
}
EncoderEventReceiver::~EncoderEventReceiver()
{
}
#endif