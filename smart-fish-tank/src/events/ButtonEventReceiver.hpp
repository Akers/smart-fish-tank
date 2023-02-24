#ifndef __SFT_Button_Event_Receiver
#define __SFT_Button_Event_Receiver
#include <any>
#include "SimpleEvent.hpp"


class ButtonEventReceiver:EventReceiver
{
private:
    /* data */
public:
    ButtonEventReceiver(/* args */);
    ~ButtonEventReceiver();
    void onClick(EventSource* source, cb_fun_t callback);
};

ButtonEventReceiver::ButtonEventReceiver()
{
}

void ButtonEventReceiver::onClick(EventSource* source, cb_fun_t callback)
{
   on(EVENTS_CLICKED, source, callback);
}



ButtonEventReceiver::~ButtonEventReceiver()
{

}
#endif