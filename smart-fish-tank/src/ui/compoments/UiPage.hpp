#ifndef __SFT_UI_PAGE
#define __SFT_UI_PAGE
#include "UiContainer.hpp"

/**
 * 页面组件
 */
class UiPage : public UiContainer
{
private:
    /* data */
protected:
    void drawCompoment();

public:
    UiPage(string id) : UiContainer(id){};
    UiPage(string id, U8G2 *u8g2_t) : UiContainer(id, u8g2_t){};
    UiPage(string id, int width, int height) : UiContainer(id, nullptr, width, height, NULL, NULL){};
    UiPage(string id, int width, int height, int x, int y) : UiContainer(id, nullptr, width, height, x, y){};
    UiPage(string id, U8G2 *u8g2_t, int width, int height) : UiContainer(id, nullptr, width, height, NULL, NULL){};
    UiPage(string id, U8G2 *u8g2_t, int width, int height, int x, int y) : UiContainer(id, u8g2_t, width, height, x, y){};
    ~UiPage();
};

void UiPage::drawCompoment()
{
}

UiPage::~UiPage()
{
}

#endif