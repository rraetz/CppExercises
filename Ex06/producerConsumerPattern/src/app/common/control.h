/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <memory>

// TODO: Remove compile time dependency with observer pattern
// control should compile without including widget.h
#include "widget.h"
// ------------------------------------------------------------

// Forward declarations
class VCamera;
class DataBufferPool;

class Control :  public QWidget
{

public:
    Control(Widget *parent);
    ~Control();

    // TODO: Move to interface
    void displayMsg(const std::string &tag, const std::string &msg);
    void setData(DataBufferPtr dataJunk);
    // ------------------------------------------------------------

    void init();
    void startPlaying();
    void stopPlaying();
    bool isPlaying() const;
    void setPlayRate(int playRate);

private:
    Widget* m_widget;
    uint m_height;
    uint m_widht;

    std::unique_ptr<VCamera> m_player;
    std::shared_ptr<DataBufferPool> m_dataPool;
};
#endif // CONTROL_H
