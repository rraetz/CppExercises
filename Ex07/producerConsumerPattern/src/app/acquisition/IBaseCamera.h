#ifndef IBASECAMERA_H
#define IBASECAMERA_H

#include "dataBufferPool.h"
//#include "IVCamera.h"

class IBaseCamera
{
private:
//    IVCamera* m_host;
//    std::shared_ptr<DataBufferPool> m_dataPool;

public:
    IBaseCamera() {}
    virtual ~IBaseCamera() {}

    virtual void startPlayData() = 0;
    virtual void stop() = 0;
    virtual bool isPlaying() = 0;
    virtual void setPlayRate(int playRate) = 0;
};

#endif // IBASECAMERA_H
