#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "IBaseCamera.h"
#include "VCamera.h"
#include "VRgbCamera.h"

#include <memory>



class CameraFactory
{
public:
    CameraFactory(){}

    std::unique_ptr<IBaseCamera> CreateCamera(IVCamera* host, std::shared_ptr<DataBufferPool> dataPool, const int type)
    {
        switch(type)
        {
            case 0:
            {
                return nullptr;
            }
            case 1:
            {
                return std::unique_ptr<IBaseCamera>(new VCamera(host, dataPool));
            }
            case 2:
            {
                return std::unique_ptr<IBaseCamera>(new VRgbCamera(host, dataPool));
            }

        }
        return nullptr;
    }
};

#endif // CAMERAFACTORY_H
