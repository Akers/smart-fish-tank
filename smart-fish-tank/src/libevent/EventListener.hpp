#ifndef __SFT_EVENTLISTENER
#define __SFT_EVENTLISTENER
#include <string>
using namespace std;

class EventListener
{
private:
    /* data */
    // 监听器名字
    string name;
public:
    EventListener(/* args */);
    EventListener(string name) : name(name){};
    ~EventListener();
    string getName();
    //重载运算符 == 
    bool operator == (const EventListener &x) //查找数值x是否与val相等
    {
        return (this->name == x.getName());
    }
};

EventListener::EventListener(/* args */)
{
    this->name = 'UnNamedEventListener';
}

EventListener::~EventListener()
{
}

string EventListener::getName() {
    return this->name;
}

#endif