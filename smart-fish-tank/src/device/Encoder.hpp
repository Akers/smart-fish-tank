#ifndef __SFT_ENCODER
#define __SFT_ENCODER
#include "Device.hpp"
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
    // 同向旋钮短触发次数
    uint8_t shortDirChangeTimes = 0;
    // 按钮长按阈值
    const int btnLongPressThreshold = 300;
    // 长短步间隔阈值，超过阈值的视为长步，否则为短步，毫秒
    const int shortStepThreshold = 100;

public:
    Encoder(/* args */);
    Encoder(int ecAPin, int ecBPing, int ecBtnPin)
        : ecAPin(ecAPin), ecBPin(ecBPin), ecBtnPin(ecBtnPin){};
    Encoder(int ecAPin, int ecBPing, int ecBtnPin, uint8_t btnLongPressThreshold, uint8_t shortStepThreshold)
        : ecAPin(ecAPin), ecBPin(ecBPin), ecBtnPin(ecBtnPin), ecType(ecType), btnLongPressThreshold(btnLongPressThreshold), shortStepThreshold(){};
    Encoder(int ecAPin, int ecBPing, int ecBtnPin, char ecType)
        : ecAPin(ecAPin), ecBPin(ecBPin), ecBtnPin(ecBtnPin), ecType(ecType){};
    ~Encoder();
    /**
     * 触发事件判断
     */
    vector<SimpleEvent> triggedEvents();
    /**
     * Must be called either from an interrupt handler associated with pin changes,
     * or periodically from a polling loop.
     * The current states of both pins should be passed here.
     * Note that we expect that the default state of both pins is HIGH when the encoder is at a stable point.
     */
    SimpleEvent checkPins(bool pinAState, bool pinBState, bool switchPinState = true);
};

Encoder::Encoder(/* args */)
{
}

vector<SimpleEvent> Encoder::triggedEvents()
{
    long currentMillis = millis();
    vector<SimpleEvent> events = vector<SimpleEvent>();
    // 读取按钮状态
    uint8_t btnState = digitalRead(ecBtnPin);
    if (this->ecBtnLast != btnState)
    {
        this->ecBtnLast = btnState;
        // 低-->高，按下
        if (btnState == HIGH)
        {
            events.push_back(SimpleEvent(EVENTS_PRESSED));
        }
        else
        {
            events.push_back(SimpleEvent(EVENTS_RELEASED));
            if (currentMillis - this->lastBtnChange > this->btnLongPressThreshold)
            {
                std::any payload = currentMillis - this->lastBtnChange;
                events.push_back(SimpleEvent(EVENTS_LONGPRESS, payload));
            }
            else
            {
                events.push_back(SimpleEvent(EVENTS_CLICKED));
            }
        }

        this->lastBtnChange = millis();
    }

    // 读取编码器旋转
    SimpleEvent _event = this->checkCWEvent(digitalRead(ecAPin), digitalRead(ecBPin));
    // 判断是否触发事件
    if (EVENTS_ENCODER_CW == _event.name || EVENTS_ENCODER_CCW == _event.name)
    {
        
    }
    return events;
}

/**
 * Must be called either from an interrupt handler associated with pin changes,
 * or periodically from a polling loop.
 * The current states of both pins should be passed here.
 * Note that we expect that the default state of both pins is HIGH when the encoder is at a stable point.
 */
SimpleEvent Encoder::checkCWEvent(bool pinAState, bool pinBState, bool switchPinState = true)
{
    long currentMillis = millis();
    if (ecReadFlag == 0 && digitalRead(ecAPin) == LOW)
    {
        this->cw1 = digitalRead(ecBPin);
        ecReadFlag = 1;
        // 处理上一轮读取中可能忽略掉的短步
        if (currentMillis - this->lastCwEventMills > this->shortStepThreshold)
        {
            if (this->cw1 == true && this->cw2 == true)
            {
                return SimpleEvent(EVENTS_ENCODER_CW, this->shortDirChangeTimes);
            }

            if (this->cw1 == false && this->cw2 == false)
            {
                return SimpleEvent(EVENTS_ENCODER_CCW, this->shortDirChangeTimes);
            }
        }
    }

    if (ecReadFlag == 1 && digitalRead(ecAPin) == HIGH)
    {
        this->cw2 = !digitalRead(ecBPin);
        // 判断是否和上次同向
        if (this->lastCw1 == this->cw1 && this->lastCw2 == this->cw2)
        {
            this->shortDirChangeTimes ++;

            // 判断长短步
            if (currentMillis - this->lastCwEventMills > this->shortStepThreshold)
            {
                // 长步
                _event.payload = 1;
            }
            else 
            {
                // 短步，截取时间段步数
                _event.payload = 1;
            }
            this->lastCwEventMills = millis();
            events.push_back(_event);



        } else {
            // 记录方向改变时间
            this->lastDirChange = millis();
            this->shortDirChangeTimes = 0;
        }

        ecReadFlag = 0;

        if (this->cw1 == true && this->cw2 == true)
        {
            return EVENTS_ENCODER_CW;
        }

        if (this->cw1 == false && this->cw2 == false)
        {
            return EVENTS_ENCODER_CCW;
        }
        
    }
}

Encoder::~Encoder()
{
}

#endif