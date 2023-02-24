#ifndef __SFT_DEVICE
#define __SFT_DEVICE
#include <string>
#include <vector>
#include <any>
#include "../events/SimpleEvent.h"

using namespace std;

class Device
{
private:
    /* data */
public:
    Device(/* args */);
    ~Device();
    /**
     * 获取触发的事件
     * @return 触发的事件名数组
    */
    virtual vector<SimpleEvent> triggedEvents()=0;
};

Device::Device(/* args */)
{
}

Device::~Device()
{
}
#endif