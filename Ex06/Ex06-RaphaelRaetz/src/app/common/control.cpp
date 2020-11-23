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
    m_height(256),
    m_widht(256)
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

    // create file reader
    m_player.reset( new VCamera( this, m_dataPool) );

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
    m_player->startPlayData();
}

void Control::stopPlaying()
{
    m_player->stop();
}

bool Control::isPlaying() const
{
    bool isPlaying = (m_player->isPlaying());
    return isPlaying;
}

void Control::setPlayRate(int playRate)
{
    m_player->setPlayRate(playRate);
}