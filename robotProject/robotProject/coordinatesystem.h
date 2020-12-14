#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "cylinder3d.h"

// Inherits from QEntity --> get some nice features, e.g. enable/disable
class CoordinateSystem : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CoordinateSystem(Qt3DCore::QEntity *parent);
    virtual ~CoordinateSystem(){};

    Cylinder3d *m_xAxis;
    Cylinder3d *m_yAxis;
    Cylinder3d *m_zAxis;
    Qt3DCore::QTransform m_pose;
    QMatrix4x4 m_xOffset;
    QMatrix4x4 m_yOffset;
    QMatrix4x4 m_zOffset;

    void setPose(const QMatrix4x4 &T);

};


#endif // COORDINATESYSTEM_H
