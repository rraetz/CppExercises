#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "IBaseCamera.h"
#include "VCamera.h"

#include <memory>

enum cameraType{VCAMERA, VRGBCAMERA};


class CameraFactory
{
public:
    CameraFactory(){qDebug("Factory Created");}

    std::unique_ptr<VCamera> CreateCamera(IVCamera* host, std::shared_ptr<DataBufferPool> dataPool, const cameraType& type)
    {
        qDebug("Create Camera from Factory");
        switch(type)
        {
            case VCAMERA: return std::unique_ptr<VCamera>(new VCamera(host, dataPool));
            case VRGBCAMERA: return nullptr;
        }
        return nullptr;
    }
};

#endif // CAMERAFACTORY_H
