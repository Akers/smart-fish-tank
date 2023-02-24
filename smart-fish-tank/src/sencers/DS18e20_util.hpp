#include <OneWire.h>
#include <DallasTemperature.h>

#ifndef __SFT_DS18E20_UTIL
#define __SFT_DS18E20_UTIL

class DS18e20Sencer
{
    private:
        OneWire oneWire;// 声明连接在单总线上的单总线设备
        DallasTemperature sensors;// 声明一个传感器对象
    public:
        DS18e20Sencer(int pin);
        void begin();
        float read();
};
DS18e20Sencer::DS18e20Sencer(int pin)
{
    oneWire = OneWire(pin);
    sensors = DallasTemperature(&oneWire);
}

void DS18e20Sencer::begin()
{
    sensors.begin();
}

float DS18e20Sencer::read()
{
    // 向总线上的设备发送温度转换请求，默认情况下该方法会阻塞
    sensors.requestTemperatures();
	return sensors.getTempCByIndex(0);
}
#endif