/**
 * 简易事件模型
*/
#ifndef __SFT_SIMPLE_EVENTMANAGER
#define __SFT_SIMPLE_EVENTMANAGER
#include "EventReceiver.hpp"
#include "EventSource.hpp"
#include <string>
#include <vector>
#include <any>
#include "../device/Device.hpp"
 
using namespace std;

/**
 * 简易事件管理器
*/
class SimpleEventManager
{
    private:
        std::vector<Device> devices;
    public:
        /**
         * 注册设备
        */
        void registDevice(Device* device);
        /**
         * 监听事件，每次循环调用
        */
        void startListening();
        SimpleEventManager();
        ~SimpleEventManager()
        {
            devices.clear();
            devices.~vector();
        };
};
void SimpleEventManager::registDevice(Device *device)
{
}

void SimpleEventManager::startListening()
{
    
}
#endif