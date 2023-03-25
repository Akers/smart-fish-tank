#ifndef __SFT_UI_LABEL
#define __SFT_UI_LABEL
#include <string>
#include "UiContainer.hpp"

enum TextAlign
{
    LEFT,
    CENTER,
    RIGHT
};

class UiLabel : public UiContainer
{
private:
    /* data */
    string text;
    const uint8_t *font;
    uint8_t fontSize;
    TextAlign textAlign = LEFT;

protected:
    void drawCompoment();

public:
    UiLabel(/* args */) : UiLabel("UI_LABEL1", nullptr){};
    UiLabel(string id) : UiLabel(id, nullptr){};
    UiLabel(string id, U8G2 *u8g2_t) : UiLabel(id, u8g2_t, 0, 0, 0, 0){};
    UiLabel(string id, int width, int height) : UiLabel(id, nullptr, width, height, 0, 0){};
    UiLabel(string id, int width, int height, int x, int y) : UiLabel(id, nullptr, width, height, x, y){};
    UiLabel(string id, U8G2 *u8g2_t, int width, int height) : UiLabel(id, nullptr, width, height, 0, 0){};
    UiLabel(string id, U8G2 *u8g2_t, int width, int height, int x, int y);
    void setText(const string text);
    string getText();
    void setFont(const uint8_t *font);
    void setFontSize(const uint8_t fontSize);
    uint8_t getFontSize();
    TextAlign getTextAlign();
    void setTextAlign(TextAlign textAlign);
    ~UiLabel();
};

void UiLabel::drawCompoment()
{
    this->u8g2_t->setFont(font);
    // 当前时间
    this->u8g2_t->setCursor(this->x, this->fontSize);
    // 取字符高度
    uint8_t maxCharHeigh = this->u8g2_t->getMaxCharHeight();
    // 计算字符串长度
    uint8_t textUtf8Width = this->u8g2_t->getUTF8Width(this->text.c_str());
    int calcY = this->calculatedY() + this->padding_bottom + maxCharHeigh;

    // 根据字符对齐计算字符绘制坐标
    switch (this->textAlign)
    {
    case LEFT:
        this->u8g2_t->drawUTF8(this->calculatedX() + this->padding_left, calcY, this->text.c_str());
        break;
    case CENTER:
        this->u8g2_t->drawUTF8((this->calculatedX() + this->padding_left) - textUtf8Width / 2, calcY, this->text.c_str());
        break;
    case RIGHT:
        this->u8g2_t->drawUTF8((this->calculatedX() + this->padding_left) - textUtf8Width, this->y, this->text.c_str());
        break;
    default:
        break;
    }
    // u8g2->print(timeStr);
}

void UiLabel::setFontSize(const uint8_t fontSize)
{
    this->fontSize = fontSize;
}

uint8_t UiLabel::getFontSize()
{
    return this->fontSize;
}

void UiLabel::setText(const string text)
{
    this->text = text;
    this->u8g2_t->setFont(font);
    this->width = this->u8g2_t->getUTF8Width(text.c_str());
}

string UiLabel::getText()
{
    return this->text;
}

void UiLabel::setFont(const uint8_t *font)
{
    this->font = font;
}

TextAlign UiLabel::getTextAlign()
{
    return this->textAlign;
}

void UiLabel::setTextAlign(TextAlign textAlign)
{
    this->textAlign = textAlign;
}

UiLabel::~UiLabel()
{
}

#endif