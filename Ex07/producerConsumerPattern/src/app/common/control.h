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
#include "VCamera.h"
#include "Icontrol.h"
#include "IBaseCamera.h"
#include "cameraFactory.h"


// TODO: Remove compile time dependency with observer pattern
// control should compile without including widget.h
// ------------------------------------------------------------

// Forward declarations
//class VCamera;
class DataBufferPool;


class Control :  public QWidget, public IVCamera
{

public:
    Control(IControl *parent);
    ~Control();

    // TODO: Move to interface
    // --> Pure virtual functions implemented
    virtual void displayMsg(const std::string &tag, const std::string &msg) override;
    virtual void setData(DataBufferPtr dataJunk) override;
    // ------------------------------------------------------------

    void init();
    void startPlaying();
    void stopPlaying();
    bool isPlaying() const;
    void setPlayRate(int playRate);

private:
    IControl* m_IControl;
    uint m_height;
    uint m_widht;
    cameraType m_cameraType;

    std::unique_ptr<IBaseCamera> m_player;
    std::shared_ptr<DataBufferPool> m_dataPool;
};
#endif // CONTROL_H
