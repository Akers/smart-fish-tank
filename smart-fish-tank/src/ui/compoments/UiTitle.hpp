#ifndef __SFT_UI_TITLE
#define __SFT_UI_TITLE
#include <U8g2lib.h>
#include "UiContainer.hpp"
class UiTitle : public UiContainer
{
public:
    vector<StatusFlag> status;
    string timeStr = "00:00";

private:
    /* data */
    UiLabel *labelTimeDisplay;
    UiContainer *containerStatusBar;

protected:
    void drawCompoment();

public:
    UiTitle(string id) : UiTitle("UI_COMPOMENT_TITLE1", nullptr, 0, 0, 0, 0){};
    UiTitle(string id, U8G2 *u8g2_t) : UiTitle(id, u8g2_t, 119, 15){};
    UiTitle(string id, int width, int height) : UiTitle(id, nullptr, width, height, 0, 0){};
    UiTitle(string id, int width, int height, int x, int y) : UiTitle(id, nullptr, width, height, x, y){};
    UiTitle(string id, U8G2 *u8g2_t, int width, int height) : UiTitle(id, nullptr, width, height, 0, 0){};
    UiTitle(string id, U8G2 *u8g2_t, int width, int height, int x, int y);

    /**
     * 刷新状态栏
     */
    void refreshStatusBar();
    ~UiTitle();
};

UiTitle::UiTitle(string id, U8G2 *u8g2_t, int width, int height, int x, int y) : UiContainer(id, u8g2_t, width, height, x, y)
{
    // 添加时间label
    this->labelTimeDisplay = new UiLabel("UI_COMPOMENT_TIME_DISPLAY1", this->u8g2_t);
    this->labelTimeDisplay->setFont(HarmonyOS_Sans_14);
    this->labelTimeDisplay->setTextAlign(TextAlign::LEFT);
    this->labelTimeDisplay->setText(this->timeStr.empty() ? "00:00" : this->timeStr);
    this->labelTimeDisplay->x = 0;
    this->labelTimeDisplay->y = 0;
    this->addChild(this->labelTimeDisplay);
    // 初始化状态图标容器
    this->containerStatusBar = new UiContainer("UI_COMPOMENT_STATUS_BAR1", this->u8g2_t, this->width - labelTimeDisplay->width, height);
    this->containerStatusBar->x = 0;
    this->containerStatusBar->y = 0;
    this->addChild(this->containerStatusBar);
    this->refreshStatusBar();
}

void UiTitle::refreshStatusBar()
{
    this->containerStatusBar->removeChildren();

    int maxIcons = this->containerStatusBar->width / 12;
    int iconX = 0;
    int iconY = 1;
    UiIcon *icon;
    for (int i = 0; i < this->status.size(); i++)
    {
        // 计算图标位置
        if (i <= maxIcons)
        {
            // 计算图标位置
            iconX = this->containerStatusBar->width - 12 * i;
            icon = new UiIcon("UI_STATUSBAR_ICON" + (i + 1), this->u8g2_t, 12, 12, iconX, iconY);
            icon->iconName = statusIconMap[this->status[i]];
            this->containerStatusBar->addChild(icon);
        }
    }
}

void UiTitle::drawCompoment()
{
    // 底边
    this->u8g2_t->drawLine(this->calculatedX(), this->margin_top + this->padding_bottom + this->height, this->width, this->height);
}

UiTitle::~UiTitle()
{
}

#endif