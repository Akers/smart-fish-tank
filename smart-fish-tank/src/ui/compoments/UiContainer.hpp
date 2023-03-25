#ifndef __SFT_UI_CONTAINER
#define __SFT_UI_CONTAINER
#include "UiCompoment.hpp"

/**
 * 基础容器
 */
class UiContainer : public UiCompoment
{
protected:
private:
    /* data */
public:
    // 宽
    int width;
    // 高
    int height;
    // 背景
    int background = 0;
    // padding和margin
    int padding_top = 0;
    int padding_left = 0;
    int padding_right = 0;
    int padding_bottom = 0;
    int margin_top = 0;
    int margin_left = 0;
    int margin_right = 0;
    int margin_bottom = 0;

public:
    UiContainer(string id) : UiContainer(id, nullptr, 0, 0, 0, 0){};
    UiContainer(string id, U8G2 *u8g2_t) : UiContainer(id, u8g2_t, 0, 0, 0, 0){};
    UiContainer(string id, int width, int height) : UiContainer(id, nullptr, width, height, 0, 0){};
    UiContainer(string id, int width, int height, int x, int y) : UiContainer(id, nullptr, width, height, x, y){};
    UiContainer(string id, U8G2 *u8g2_t, int width, int height) : UiContainer(id, nullptr, width, height, 0, 0){};
    UiContainer(string id, U8G2 *u8g2_t, int width, int height, int x, int y) : UiCompoment(id, u8g2_t), width(width), height(height){};
    void setBackground(int background);
    int calculatedX();
    int calculatedY();
    void setPosition(int x, int y);
    void setPadding(int padding_top, int padding_right, int padding_bottom, int padding_left);
    void setMargin(int margin_top, int margin_right, int margin_bottom, int margin_left);
    void setPadding(int padding_top_bottom, int padding_left_right);
    void setMargin(int margin_top_bottom, int margin_left_right);
    void setPadding(int padding_all);
    void setMargin(int margin_all);
    ~UiContainer();
};

void UiContainer::setBackground(int background)
{
    this->background = background;
}

int UiContainer::calculatedX()
{

    switch (this->position)
    {
    case RELATIVE:
        int parentX = 0;
        if (this->parent != nullptr)
        {
            parentX = this->parent->calculatedX();
            if (typeid(UiContainer) == typeid(this->parent))
            {
                parentX += ((UiContainer *)this->parent)->margin_left + ((UiContainer *)this->parent)->padding_left;
            }
        }
        return parentX + this->margin_left + this->x;
    case ABSOLUTE:

    default:
        return this->x;
    }
}

int UiContainer::calculatedY()
{
    switch (this->position)
    {
    case RELATIVE:
        int parentY = 0;
        if (this->parent != nullptr)
        {
            parentY = this->parent->calculatedX();
            if (typeid(UiContainer) == typeid(this->parent))
            {
                parentY += ((UiContainer *)this->parent)->margin_top + ((UiContainer *)this->parent)->padding_top;
            }
        }
        return parentY + this->margin_top + this->y;
    case ABSOLUTE:

    default:
        return this->y;
    }
}

void UiContainer::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
void UiContainer::setPadding(int padding_top, int padding_right, int padding_bottom, int padding_left)
{
    this->padding_top = padding_top;
    this->padding_right = padding_right;
    this->padding_bottom = padding_bottom;
    this->padding_left = padding_left;
}
void UiContainer::setMargin(int margin_top, int margin_right, int margin_bottom, int margin_left)
{
    this->margin_top = margin_top;
    this->margin_right = margin_right;
    this->margin_bottom = margin_bottom;
    this->margin_left = margin_left;
}
void UiContainer::setPadding(int padding_top_bottom, int padding_left_right)
{
    this->padding_top = padding_top_bottom;
    this->padding_bottom = padding_top_bottom;
    this->padding_left = padding_left_right;
    this->padding_right = padding_left_right;
}
void UiContainer::setMargin(int margin_top_bottom, int margin_left_right)
{
    this->margin_top = margin_top_bottom;
    this->margin_bottom = margin_top_bottom;
    this->margin_left = margin_left_right;
    this->margin_right = margin_left_right;
}
void UiContainer::setPadding(int padding_all)
{
    this->padding_top = padding_all;
    this->padding_bottom = padding_all;
    this->padding_left = padding_all;
    this->padding_right = padding_all;
}
void UiContainer::setMargin(int margin_all)
{
    this->margin_top = margin_all;
    this->margin_bottom = margin_all;
    this->margin_left = margin_all;
    this->margin_right = margin_all;
}

UiContainer::~UiContainer()
{
}

#endif