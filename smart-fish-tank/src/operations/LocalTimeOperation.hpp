#ifndef __SFT_LOCAL_TIME_OPERATION
#define __SFT_LOCAL_TIME_OPERATION
#include <Arduino.h>
#include <string>
#include <stdio.h>

using namespace std;

class LocalTimeOperation
{
private:
    /* data */
    struct tm timeinfo;
    // cn.pool.ntp.org
    const char *ntpServer;
    const long gmtOffset_sec;
    const int daylightOffset_sec;

public:
    LocalTimeOperation(char *ntpServer, long gmtOffsetSec, int daylightOffsetSec) : ntpServer(ntpServer), gmtOffset_sec(gmtOffsetSec), daylightOffset_sec(daylightOffsetSec){};
    /**
     * 获取时间字符串
     * 格式：hh:mm
     */
    string getHourMinuteTimeStr();
    ~LocalTimeOperation();
};

string LocalTimeOperation::getHourMinuteTimeStr()
{
    if (!getLocalTime(&timeinfo))
    {
        return "00:00";
    }

    // 格式化，并获取最终需要的字符串
    char buf[6];
    int realLen = snprintf(buf, sizeof(buf), "%R", &timeinfo);
    return string(buf, realLen);
}

LocalTimeOperation::~LocalTimeOperation()
{
}

#endif