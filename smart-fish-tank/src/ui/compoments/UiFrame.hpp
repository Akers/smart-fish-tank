#ifndef __SFT_UI_FRAME
#define __SFT_UI_FRAME
#include "UiContainer.hpp"

/**
 * 顶级容器
 */
class UiFrame : public UiContainer
{
private:
    /* data */
protected:
    void drawCompoment();

public:
    UiFrame(/* args */) : UiFrame(nullptr){};
    UiFrame(U8G2 *u8g2_t) : UiFrame(u8g2_t, NULL, NULL){};
    UiFrame(int width, int height) : UiFrame(nullptr, width, height, NULL, NULL){};
    UiFrame(int width, int height, int x, int y) : UiFrame(nullptr, width, height, x, y){};
    UiFrame(U8G2 *u8g2_t, int width, int height) : UiFrame(nullptr, width, height, NULL, NULL){};
    UiFrame(U8G2 *u8g2_t, int width, int height, int x, int y) : UiContainer("UI_MAIN_FRAME", u8g2_t, width, height, x, y){};
    ~UiFrame();
};

void UiFrame::drawCompoment()
{
}

UiFrame::~UiFrame()
{
}

#endif