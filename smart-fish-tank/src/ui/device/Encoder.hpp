#ifndef __SFT_ENCODER
#define __SFT_ENCODER
#include "libevent/Device.hpp"
#include "../events/ButtonEvent.hpp"
#include "../events/EncoderEvent.hpp"

#include <Arduino.h>

class Encoder : public Device
{
private:
    /* data */
    // EC11的A引脚，视为时钟线
    int ecAPin;
    // EC11的B引脚，视为信号线
    int ecBPin;
    // EC11的按键
    int ecBtnPin;
    //----------------局部文件内变量列表----------------//
    // 转向判据1
    boolean cw1;
    // 转向判据2
    boolean cw2;
    // 上一次转向判据1
    boolean lastCw1;
    // 上一次转向判据2
    boolean lastCw2;
    // 防抖读取标志
    int ecReadFlag = 0;
    // 上次旋转时间触发时间
    long lastCwEventMills = 0;
    // 首步开始时间
    long firstStepStarted = 0;
    // EC11的按键上一次的状态
    int ecBtnLast = 0;
    // 定义变量暂存EC11的类型---->>>>----  0：一定位对应一脉冲；  1：两定位对应一脉冲
    // 所谓一定位对应一脉冲，是指EC11旋转编码器每转动一格，A和B都会输出一个完整的方波。
    // 而  两定位对应一脉冲，是指EC11旋转编码器每转动两格，A和B才会输出一个完整的方波，只转动一格只输出A和B的上升沿或下降沿
    char ecType = 1;
    // 上次按钮状态改变时间
    long lastBtnChange;
    // 上次旋扭方向改变时间
    long lastDirChange;
    // 按下时长
    long pressTime = 0;
    // 同向旋钮短触发次数
    uint8_t shortDirChangeTimes = 0;
    // 按钮长按阈值
    const int btnLongPressThreshold = 300;
    // 长短步间隔阈值，超过阈值的视为长步，否则为短步，毫秒
    const int shortStepThreshold = 100;

private:
    EncoderEvent checkCWEvent(bool pinAState, bool pinBState, bool switchPinState = true);
    // 读取旋转方向
    EventTypes readDirection();

public:
    Encoder(/* args */);
    Encoder(std::string name, int ecAPin, int ecBPing, int ecBtnPin)
        : Device(name), ecAPin(ecAPin), ecBPin(ecBPin), ecBtnPin(ecBtnPin){};
    Encoder(std::string name, int ecAPin, int ecBPing, int ecBtnPin, uint8_t btnLongPressThreshold, uint8_t shortStepThreshold)
        : Device(name), ecAPin(ecAPin), ecBPin(ecBPin), ecBtnPin(ecBtnPin), ecType(ecType), btnLongPressThreshold(btnLongPressThreshold), shortStepThreshold(){};
    Encoder(std::string name, int ecAPin, int ecBPing, int ecBtnPin, char ecType)
        : Device(name), ecAPin(ecAPin), ecBPin(ecBPin), ecBtnPin(ecBtnPin), ecType(ecType){};
    ~Encoder();
    /**
     * 触发事件判断
     */
    vector<EventObject *> triggedEvents();
};

Encoder::Encoder(/* args */)
{
}

vector<EventObject *> Encoder::triggedEvents()
{
    long currentMillis = millis();
    vector<EventObject *> events = vector<EventObject *>();
    // 读取按钮状态
    uint8_t btnState = digitalRead(ecBtnPin);
    if (this->ecBtnLast != btnState)
    {
        this->ecBtnLast = btnState;
        // 低-->高，按下
        if (btnState == HIGH)
        {
            events.push_back(&ButtonEvent::newPressedEvent());
        }
        else
        {
            events.push_back(&ButtonEvent::newReleasedEvent());
            this->pressTime = currentMillis - this->lastBtnChange;
            if (this->pressTime > this->btnLongPressThreshold)
            {
                ButtonEvent _e = ButtonEvent(EventTypes::LONGPRESS, this->pressTime);

                events.push_back(&_e);
            }
            else
            {
                events.push_back(&ButtonEvent::newClickedEvent());
            }
        }

        this->lastBtnChange = millis();
    }

    // 读取编码器旋转
    EncoderEvent *_event = &this->checkCWEvent(digitalRead(ecAPin), digitalRead(ecBPin));
    if (_event != NULL)
    {
        events.push_back(_event);
    }

    return events;
}

/**
 * Must be called either from an interrupt handler associated with pin changes,
 * or periodically from a polling loop.
 * The current states of both pins should be passed here.
 * Note that we expect that the default state of both pins is HIGH when the encoder is at a stable point.
 */
EncoderEvent Encoder::checkCWEvent(bool pinAState, bool pinBState, bool switchPinState = true)
{
    long currentMillis = millis();
    if (ecReadFlag == 0 && digitalRead(ecAPin) == LOW)
    {
        this->cw1 = digitalRead(ecBPin);
        ecReadFlag = 1;
        // 处理上一轮读取中可能忽略掉的短步
        if (currentMillis - this->lastCwEventMills > this->shortStepThreshold)
        {
            return EncoderEvent(this->readDirection(), this->shortDirChangeTimes);
        }
    }

    if (ecReadFlag == 1 && digitalRead(ecAPin) == HIGH)
    {
        this->cw2 = !digitalRead(ecBPin);
        // 判断是否和上次同向
        if (this->lastCw1 == this->cw1 && this->lastCw2 == this->cw2)
        {
            this->shortDirChangeTimes++;
            this->lastCwEventMills = millis();
        }
        else
        {
            // 记录方向改变时间
            this->lastDirChange = millis();
            this->shortDirChangeTimes = 0;
        }

        // 判断长短步
        return EncoderEvent(this->readDirection(), this->shortDirChangeTimes);
        ecReadFlag = 0;
    }

    return;
}

EventTypes Encoder::readDirection()
{
    if (this->cw1 == true && this->cw2 == true)
    {
        return EventTypes::ENCODER_CW;
    }

    if (this->cw1 == false && this->cw2 == false)
    {
        return EventTypes::ENCODER_CCW;
    }
}

Encoder::~Encoder()
{
}

#endif