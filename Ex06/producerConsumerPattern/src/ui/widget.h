/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <memory>
#include "dataBuffer.h"
#include "control.h"

// Forward declarations
class DataBuffer;
class Control;
class VideoVisualizer;
class QTimer;

namespace Ui {
class Widget;
}

class Widget : public QWidget, public IControl
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    // TODO: Move to interface
    virtual void displayMsg(std::string tag, std::string msg) override;
    virtual void setData(DataBufferPtr data) override;
    // ------------------------------------------------------------

private:
    void initGUI();
    void updateScanVis();

// Slots are normal C++ functions and can be called normally; their only special feature is that signals can be connected to them.
private slots:
    void updateGui();
    void updateFrameRate();
    void playDataFromFile();
    void setPlayRate();

private:
    Ui::Widget* ui;
    QString m_tag;

    std::shared_ptr<DataBuffer> m_lastData;
    std::unique_ptr<Control> m_appCtrl;
    std::unique_ptr<VideoVisualizer> m_videoVisualizer;
    std::unique_ptr<QTimer> m_guiUpdateTimer;
    std::unique_ptr<QTimer> m_frameRateTimer;

    size_t m_frameCount;
    const int GUI_RATE_MS;
    const int FPS_LABEL_RATE;

};

#endif // WIDGET_H
