#ifndef __SFT_UICOMPOMENTS
#define __SFT_UICOMPOMENTS
#include <vector>
#include <algorithm>
#include <any>
#include <string>
#include <U8g2lib.h>
#include "../listeners/UiCompomentEventListener.hpp"
#include "../../libevent/EventSource.hpp"
#include "../listeners/UiCompomentEventListenerAdapter.hpp"

using namespace std;

enum ComponentPosition
{
    RELATIVE,
    ABSOLUTE,
};

/**
 * 基础UI组件
 */
class UiCompoment : public EventSource
{
protected:
    // 组件id
    string id;
    // u8g2lib
    U8G2 *u8g2_t;
    /* data */
    vector<UiCompomentEventListener *> listeners;
    // 子组件
    vector<UiCompoment *> children;
    // 父级组件
    UiCompoment *parent;

public:
    // x坐标
    int x;
    // y坐标
    int y;
    // 定位方式
    ComponentPosition position = RELATIVE;

protected:
    /**
     * 组件绘制，需各组件实现
     */
    void virtual drawCompoment();
    /**
     * 子组件绘制
     */
    void drawChildren();

public:
    UiCompoment(string id) : id(id)
    {
        // 默认最多10个监听
        this->listeners = vector<UiCompomentEventListener *>(10);
    };
    UiCompoment(string id, U8G2 *u8g2_t) : id(id), u8g2_t(u8g2_t)
    {
        // 默认最多10个监听
        this->listeners = vector<UiCompomentEventListener *>(10);
    };
    ~UiCompoment();
    // 注册监听器
    void on(UiEvent event, void (*callback)(UiEvent e, any payload));
    void addEventListener(UiCompomentEventListener *listener);
    // 注销监听器
    void off(UiEvent event);
    // 触发事件
    void emit(UiEvent event);
    void emit(UiEvent event, any payload);
    void setU8g2(U8G2 *u8g2);
    /**
     * 添加子组件
     */
    void addChild(UiCompoment *child);
    void setParent(UiCompoment *parent);
    UiCompoment *findChild(string name);
    /**
     * 删除所有子组件
     */
    void removeChildren();
    /**
     * 绘制
     */
    void draw();

    vector<UiCompomentEventListener *> getListeners();

    void setListeners(vector<UiCompomentEventListener *> listeners);
    int calculatedX();
    int calculatedY();
};

void UiCompoment::setU8g2(U8G2 *u8g2)
{
    this->u8g2_t = u8g2;
}

void UiCompoment::draw()
{
    this->u8g2_t->clearBuffer();
    drawCompoment();
    drawChildren();
    this->u8g2_t->sendBuffer();
}

void UiCompoment::drawChildren()
{
    // 绘制所有子元素
    vector<UiCompoment *>::iterator iter = this->children.begin();
    while (iter != this->children.end())
    {
        (*iter)->drawCompoment();
        iter++;
    }
}

void UiCompoment::on(UiEvent event, void (*callback)(UiEvent e, any payload))
{
    int count = 0;
    for (auto it = this->listeners.begin(); it != this->listeners.end(); it++)
    {
        if ((*it)->event == event)
        {
            count++;
        }
    }
    string listenerName = event.getName() + "_UiCompomentEventListener";
    if (count > 0)
    {
        listenerName += (count + 1);
    }
    UiCompomentEventListener *listener = &UiCompomentEventListenerAdapter(
        listenerName, event, callback);

    this->listeners.push_back(listener);
}

void UiCompoment::off(UiEvent event)
{
    vector<UiCompomentEventListener *>::iterator iter = this->listeners.begin();
    while (this->listeners.size() > 0 && iter != this->listeners.end())
    {
        if ((*iter)->event == event)
        {
            iter = this->listeners.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void UiCompoment::addEventListener(UiCompomentEventListener *listener)
{
    // 防重
    int counts = 0;
    vector<UiCompomentEventListener *>::iterator iter = this->listeners.begin();
    while (this->listeners.size() > 0 && iter != this->listeners.end())
    {
        if ((*iter)->event == listener->event && (*iter)->callback == listener->callback)
        {
            counts++;
        }
    }
    if (counts <= 0)
    {
        this->listeners.push_back(listener);
    }
}

void UiCompoment::addChild(UiCompoment *compent)
{
    compent->parent = this;
    this->children.push_back(compent);
}

void UiCompoment::removeChildren()
{
    vector<UiCompoment *>::iterator iter = this->children.begin();
    while (this->children.size() > 0 && iter != this->children.end())
    {
        this->children.erase(iter);
        delete *iter;
    }
}

// 触发事件
void UiCompoment::emit(UiEvent event)
{
    for (vector<UiCompomentEventListener *>::iterator iter = this->listeners.begin(); iter != this->listeners.end(); iter++)
    {
        event.setSource(this);
        (*iter)->eventDispatched(event);
    }
}

// 触发事件
void UiCompoment::emit(UiEvent event, any payload)
{
    for (vector<UiCompomentEventListener *>::iterator iter = this->listeners.begin(); iter != this->listeners.end(); iter++)
    {
        event.setSource(this);
        event.setPayload(payload);
        (*iter)->eventDispatched(event, payload);
    }
}

UiCompoment *UiCompoment::findChild(string name)
{
    for (vector<UiCompoment *>::iterator iter = this->children.begin(); iter != this->children.end(); iter++)
    {
        if ((*iter)->id == name)
        {
            return *iter;
        }
    }
    return NULL;
}

void UiCompoment::setParent(UiCompoment *parent)
{
    this->parent = parent;
}

vector<UiCompomentEventListener *> UiCompoment::getListeners()
{
    return this->listeners;
}

void UiCompoment::setListeners(vector<UiCompomentEventListener *> listeners)
{
    this->listeners = listeners;
}

int UiCompoment::calculatedX()
{
    switch (this->position)
    {
    case ABSOLUTE:
        return this->x;
    case RELATIVE:
        int parentX = 0;
        if (this->parent != nullptr)
        {
            parentX = this->parent->calculatedX();
        }
        return this->x + parentX;
    }
}

int UiCompoment::calculatedY()
{
    switch (this->position)
    {
    case ABSOLUTE:
        return this->x;
    case RELATIVE:
        int parentY = 0;
        if (this->parent != nullptr)
        {
            parentY = this->parent->calculatedY();
        }
        return this->y + parentY;
    }
}

UiCompoment::~UiCompoment()
{
}
#endif