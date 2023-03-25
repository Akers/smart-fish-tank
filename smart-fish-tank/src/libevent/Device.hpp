#ifndef __SFT_DEVICE
#define __SFT_DEVICE
#include <string>
#include <vector>
#include <any>
#include "EventObject.hpp"

using namespace std;

class Device : EventSource
{
private:
    /* data */
public:
    string name = "UnNamedDevice";
    Device(/* args */);
    Device(string name) : name(name){};
    ~Device();
    /**
     * 获取触发的事件
     * @return 触发的事件名数组
    */
    virtual vector<EventObject*> triggedEvents()=0;
};

Device::Device(/* args */)
{
}

Device::~Device()
{
}
#endif