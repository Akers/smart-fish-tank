/**
 * 事件对象
*/
#ifndef __SFT_EVENTOBJECT
#define __SFT_EVENTOBJECT
#include <any>
#include "EventSource.hpp"

using namespace std;

class EventObject
{
protected:
    /* data */
    EventSource* source;
    any payLoad;
public:
    EventObject(/* args */);
    EventObject(EventSource* source):source(source) {};
    EventObject(EventSource* source, any payLoad):source(source), payLoad(payLoad) {};
    EventSource* getSource() {
        return source;
    }
    any getPayLoad() {
        return payLoad;
    }
    void setSource(EventSource* source);
    void setPayload(any payload);
    ~EventObject();
};

EventObject::EventObject(/* args */)
{
}

void EventObject::setSource(EventSource* source) 
{
    this->source = source;
}

void EventObject::setPayload(any payload) 
{
    this->payLoad = payload;
}

EventObject::~EventObject()
{
}

#endif