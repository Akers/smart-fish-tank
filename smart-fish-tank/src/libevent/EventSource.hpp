#ifndef __SFT_EVENTSOURCE
#define __SFT_EVENTSOURCE
#include <vector>
#include "EventListener.hpp"

using namespace std;

/**
 * 事件源接口
*/
class EventSource
{
private:

public:
    EventSource(/* args */);
    ~EventSource();
};

EventSource::EventSource(/* args */)
{
}

EventSource::~EventSource()
{
}

#endif