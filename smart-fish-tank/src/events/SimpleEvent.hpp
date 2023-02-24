/**
 * 简易事件模型
*/
#ifndef __SFT_SIMPLE_EVENT
#define __SFT_SIMPLE_EVENT
#include "EventReceiver.hpp"
#include "EventSource.hpp"
#include <string>
#include <vector>
#include <any>
 
using namespace std;
// 默认事件
static const std::string EVENTS_DEFAULT = "DEFAULT";
// 点击事件（一次按下+一次释放视为一次点击）
static const std::string EVENTS_CLICKED = "CLICK";
// 按下事件
static const std::string EVENTS_PRESSED = "PRESSED";
// 释放事件
static const std::string EVENTS_RELEASED = "RELEASED";
// 长按（按下，超过btnLongPressThreshold阈值后释放视为一次LONGPRESS事件）
static const std::string EVENTS_LONGPRESS = "LONGPRESS";
// EC11 旋转编码器顺时针旋转
static const std::string EVENTS_ENCODER_CW = "ENCODER_CW";
// EC11 旋转编码器逆时针旋转
static const std::string EVENTS_ENCODER_CCW = "ENCODER_CCW";

/**
 * 简易事件
*/
class SimpleEvent
{
    public:
        // 事件名称
        std::string name;
        // 负载部分，注意类型转换
        std::any payload;
        SimpleEvent(){};
        SimpleEvent(std::string name) : name(name) {};
        SimpleEvent(std::string name, std::any payload) : name(name), payload(payload) {};
        ~SimpleEvent()
        {
            payload.~any();
        };
};
#endif