#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "IBaseCamera.h"
#include "VCamera.h"

#include <memory>


class CameraFactory
{
public:
    CameraFactory(){qDebug("Factory Created");}

    std::unique_ptr<IBaseCamera> CreateCamera(IVCamera* host, std::shared_ptr<DataBufferPool> dataPool, const int type)
    {
        qDebug("Create Camera from Factory");
        switch(type)
        {
            case 0:
            {
                qDebug("VCamera selected");
                return std::unique_ptr<IBaseCamera>(new VCamera(host, dataPool));
            }
            case 1:
            {
                qDebug("VRGBCamera selected");
                return nullptr;
            }

        }
        return nullptr;
    }
};

#endif // CAMERAFACTORY_H
