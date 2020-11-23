/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <chrono>
#include "VRgbCamera.h"
#include "dataBufferPool.h"
#include <QtDebug>

// TODO: Remove compile time dependency
// ------------------------------------------------------------
VRgbCamera::VRgbCamera(IVCamera* host, std::shared_ptr<DataBufferPool> dataPool) :
    m_tag("Player"),
    m_play(false),
    m_IVCamera(host),
    m_playRate(33),
    m_dataPool(dataPool),
    m_color(0),
    offset(0)
{
    m_IVCamera->displayMsg(m_tag, "Player constructed");
}

VRgbCamera::~VRgbCamera()
{
    // Thread stopping
    m_play = false;

    if(m_acquireThread.joinable())
    {
        m_acquireThread.join();
    }
}

void VRgbCamera::startPlayData()
{
    m_play = true;
    m_acquireThread = std::thread(&VRgbCamera::run, this);
    m_IVCamera->displayMsg(m_tag, "Start Playing");
}

void VRgbCamera::stop()
{
    m_play = false;
    m_IVCamera->displayMsg(m_tag, "Stop playing");
}

bool VRgbCamera::isPlaying()
{
    return m_play;
}

void VRgbCamera::setPlayRate(int playRate)
{
    m_playRate = playRate;
}

//******* Below runs in own thread **********//
void VRgbCamera::run()
{
    while( m_play )
    {
        DataBufferPtr nextPtr = m_dataPool->getBuffer();
        if( readImage(nextPtr) )
        {
            m_IVCamera->setData(nextPtr);
        }
        // Control frame rate
        int sleeptime = static_cast<int>( 1000.0f/m_playRate ) ;
        std::this_thread::sleep_for( std::chrono::milliseconds( sleeptime ));
    }
}

bool VRgbCamera::readImage(DataBufferPtr data)
{
    int width = data->m_image.width();
    int height = data->m_image.height();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int val = x + offset;
            switch (m_color)
            {
                case 0: data->m_image.setPixel(x, y, qRgb(val, 0 ,0)); break;
                case 1: data->m_image.setPixel(x, y, qRgb(0, val ,0)); break;
                case 2: data->m_image.setPixel(x, y, qRgb(0, 0 ,val)); break;
            }
        }
    }
    offset+= 25;
    if (offset >= width)
    {
        offset = 0;
        m_color = (++m_color) % 3;
    }
    return true;
}
