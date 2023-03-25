/**
 * UI事件封装
*/
#ifndef __SFT_UIEVENTS
#define __SFT_UIEVENTS
#include <any>
#include <string>
#include "../../libevent/EventObject.hpp"

using namespace std;

const enum EventTypes {
    // 点击事件（一次按下+一次释放视为一次点击）
    CLICKED,
    // 按下事件，电平改变触发
    PRESSED,
    // 释放事件，电平改变后恢复原电平触发
    RELEASED,
    // 长按（按下，超过btnLongPressThreshold阈值后释放视为一次LONGPRESS事件）
    LONGPRESS,
    // EC11 旋转编码器顺时针旋转
    ENCODER_CW,
    // EC11 旋转编码器逆时针旋转
    ENCODER_CCW
};

class UiEvent : public EventObject
{
protected:
    // 事件ID
    EventTypes id;
private:
    /* data */
    
    // 是否已消费标志
    bool consumed = false;
public:
    UiEvent(/* args */);
    UiEvent(EventTypes id) : id(id) {};
    ~UiEvent();
    EventTypes getId();
    string getName();
    //重载运算符 == 
    bool operator == (const UiEvent &x) //查找数值x是否与val相等
    {
        return (this->id == x.id);
    }
protected:
    void consume();
};

UiEvent::UiEvent(/* args */)
{
}

EventTypes UiEvent::getId() {
    return this->id;
}

string UiEvent::getName() {
    switch (id)
    {
        // 可消费事件
        case CLICKED:
            return "CLICKED";
        case PRESSED:
            return "PRESSED";
        case RELEASED:
            return "RELEASED";
        case LONGPRESS:
            return "LONGPRESS";
        case ENCODER_CW:
            return "ENCODER_CW";
        case ENCODER_CCW:
            return "ENCODER_CCW";
        default:
            // 不可消费事件
            return "UNKNOW";
    }
}

UiEvent::~UiEvent()
{
}

void UiEvent::consume() {
    switch (id)
    {
        // 可消费事件
        case CLICKED:
        case PRESSED:
        case RELEASED:
        case LONGPRESS:
        case ENCODER_CW:
        case ENCODER_CCW:
            this->consumed = true;
            break;
        default:
            // 不可消费事件
            this->consumed = false;
            break;
    }
}
#endif