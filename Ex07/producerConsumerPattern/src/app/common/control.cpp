/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "control.h"
#include "dataBufferPool.h"

Control::Control(IControl *parent) :
    m_IControl(parent),
    m_cameraType(0),
    m_height(256),
    m_widht(256),
    m_player(nullptr)
{
    // init control handels
    init();
}

Control::~Control()
{

}

// reset main handels
void Control::init()
{
    // init data pool
    m_dataPool.reset(new DataBufferPool(m_height, m_widht));

    // Message
    m_IControl->displayMsg("Control", "Constructed");
}

// -----------------------------------------------------------------
// Functions called by Player (tight coupling)
// -----------------------------------------------------------------
void Control::displayMsg(const std::string &tag, const std::string &msg)
{    
    m_IControl->displayMsg(tag, msg);
}

void Control::setData(DataBufferPtr dataJunk)
{
    m_IControl->setData(dataJunk);
}

void Control::startPlaying()
{
    init(); // reinit handlers

    // Create factory and generate player
    std::unique_ptr<CameraFactory> cameraFactory = std::unique_ptr<CameraFactory>(new CameraFactory());
    m_player = std::unique_ptr<IBaseCamera>(cameraFactory->CreateCamera(this, m_dataPool, m_cameraType));

    if (m_player) m_player->startPlayData();
}

void Control::stopPlaying()
{
    if (m_player) m_player->stop();
}

bool Control::isPlaying() const
{   
    bool isPlaying = (m_player) ?  m_player->isPlaying() : false;
    return isPlaying;
}

void Control::setPlayRate(int playRate)
{
    if (m_player) m_player->setPlayRate(playRate);
}
