/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef VCAMERA_H
#define VCAMERA_H

#include <thread>
#include "dataBuffer.h"
#include "IVCamera.h"
#include "IBaseCamera.h"

// Forward declarations
class DataBufferPool;

/**
 * @brief The VCamera class
 *
 * Note: Inheritating is not allowed since starting a thread in the constructor can be problematic for derived classes
 */
class VCamera final : public IBaseCamera
{

public:
     VCamera(IVCamera* host, std::shared_ptr<DataBufferPool> dataPool);
     ~VCamera();

     virtual void startPlayData() override;
     virtual void stop() override;
     virtual bool isPlaying() override;
     virtual void setPlayRate(int playRate) override;

private:
     void run() ;
     bool readImage(DataBufferPtr data);

     std::string m_tag;
     std::thread m_acquireThread;
     bool m_play;

     // TODO: Remove compile time dependency
     IVCamera* m_IVCamera;
     // ------------------------------------------------------------

     int m_playRate;
     std::shared_ptr<DataBufferPool> m_dataPool;
     int offset;
};

#endif // VCAMERA_H
