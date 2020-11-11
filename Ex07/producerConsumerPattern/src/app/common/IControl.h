#ifndef ICONTROL_H
#define ICONTROL_H

#include <string>
#include "dataBuffer.h"


class IControl
{
public:
    IControl() {}
    virtual ~IControl(){}

    virtual void displayMsg(std::string tag, std::string msg) = 0;
    virtual void setData(DataBufferPtr data) = 0;

};

#endif // ICONTROL_H
