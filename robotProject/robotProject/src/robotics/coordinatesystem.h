#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "cylinder3d.h"

// Inherits from QEntity --> get some nice features, e.g. enable/disable
class CoordinateSystem : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    // Constructor
    CoordinateSystem(Qt3DCore::QEntity *parent = nullptr);
    virtual ~CoordinateSystem(){};

    // Public methods
    void setPose(const QMatrix4x4 &T);

private:
    // Private member variables
    Cylinder3d *m_xAxis;
    Cylinder3d *m_yAxis;
    Cylinder3d *m_zAxis;
    Qt3DCore::QTransform m_pose;
    QMatrix4x4 m_xOffset;
    QMatrix4x4 m_yOffset;
    QMatrix4x4 m_zOffset;

    // Private constants
    const double m_CYLINDER_LENGTH = 100;
    const double m_CYLINDER_RADIUS = 5;

};


#endif // COORDINATESYSTEM_H
