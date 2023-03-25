#ifndef __SFT_UI_MAINPAGE
#define __SFT_UI_MAINPAGE
#include <map>
#include "./customer_font.h"
#include "compoments/UiPage.hpp"
#include "compoments/UiTitle.hpp"
#include "compoments/UiIcon.hpp"
#include "compoments/UiLabel.hpp"
#include "../operations/LocalTimeOperation.hpp"

using namespace std;

// 状态标志
enum StatusFlag
{
    WIFI_CONECTED,
    PUMP_ON,
    LIGHT_ON,
    HEATER_ON,
    O2_ON,
    COOLER_ON,
    FEEDMODE,
    CO2_ON
};

// 状态图标映射
static std::map<StatusFlag, ICONS> statusIconMap = {
    {StatusFlag::WIFI_CONECTED, ICONS::WIFI_12X12}, {StatusFlag::PUMP_ON, ICONS::PUMP_12X12}, {StatusFlag::LIGHT_ON, ICONS::LIGHT_12X12}, {StatusFlag::HEATER_ON, ICONS::HEATER_12X12}, {StatusFlag::COOLER_ON, ICONS::COOLER_12X12}, {StatusFlag::O2_ON, ICONS::O2_12X12}, {StatusFlag::FEEDMODE, ICONS::FISH_12X12}};

class MainPage : public UiPage
{
public:
    // 开关变量
    boolean wifiConnected = true;
    boolean pumpOn = true;
    boolean heaterOn = false;
    boolean lightOn = false;
    boolean o2On = false;
    boolean coolerOn = false;
    boolean feedMode = false;
    boolean co2On = false;
    // 数值变量
    int curTemp = 23;     // 当前水温
    int targetTemp = 26;  // 目标水温
    int airTemp = 28;     // 气温
    int airHumidity = 70; // 湿度
    int tds = 0;          // TDS数值
    LocalTimeOperation *localTimeOperation;

private:
    /* data */
    // 时间显示
    UiLabel *labelTimeDisplay;
    // 状态图标
    UiTitle *statusBar;
    // 主显示区
    UiContainer *mainContainer;

public:
    MainPage(int width, int height) : MainPage("UI_COMPOMENT_MAIN_PAGE1", nullptr, width, height){};
    MainPage(string id, int width, int height) : MainPage(id, nullptr, width, height){};
    MainPage(LocalTimeOperation *localTimeOperation, int width, int height) : MainPage("UI_COMPOMENT_MAIN_PAGE1", localTimeOperation, width, height){};
    MainPage(string id, LocalTimeOperation *localTimeOperation, int width, int height);

    /**
     * 刷新状态栏
     */
    void refreshStatusBar();
    /**
     * 获取互联网时间
     */
    string internetTime();
    ~MainPage();
};

MainPage::MainPage(string id, LocalTimeOperation *localTimeOperation, int width, int height) : UiPage(id, width, height, 0, 0), localTimeOperation(localTimeOperation)
{
    // 初始化标题栏
    statusBar = new UiTitle("UI_COMPOMENT_STATUS_BAR1", this->u8g2_t, 122, 15, 3, 0);
    // 初始化主显示区
}

void MainPage::refreshStatusBar()
{
    // 获取时间
    this->statusBar->timeStr = this->localTimeOperation->getHourMinuteTimeStr();

    this->statusBar->status.clear();
    // put your main code here, to run repeatedly:
    if (this->wifiConnected)
    {
        this->statusBar->status.push_back(StatusFlag::WIFI_CONECTED);
    }
    if (this->pumpOn)
    {
        this->statusBar->status.push_back(StatusFlag::PUMP_ON);
    }
    if (this->heaterOn)
    {
        this->statusBar->status.push_back(StatusFlag::HEATER_ON);
    }
    if (this->lightOn)
    {
        this->statusBar->status.push_back(StatusFlag::LIGHT_ON);
    }
    if (this->o2On)
    {
        this->statusBar->status.push_back(StatusFlag::O2_ON);
    }
    if (this->coolerOn)
    {
        this->statusBar->status.push_back(StatusFlag::COOLER_ON);
    }
    if (this->feedMode)
    {
        this->statusBar->status.push_back(StatusFlag::FEEDMODE);
    }
    if (this->co2On)
    {
        this->statusBar->status.push_back(StatusFlag::CO2_ON);
    }
}

string MainPage::internetTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
}

MainPage::~MainPage()
{
}

#endif