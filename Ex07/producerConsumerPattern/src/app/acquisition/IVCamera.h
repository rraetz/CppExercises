#ifndef IVCAMERA_H
#define IVCAMERA_H

#include <string>
#include "dataBuffer.h"


class IVCamera
{
public:
    IVCamera(){};
    virtual ~IVCamera(){};

    virtual void displayMsg(const std::string &tag, const std::string &msg) = 0;
    virtual void setData(DataBufferPtr dataJunk) = 0;

};


#endif // IVCAMERA_H
