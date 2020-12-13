#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "cylinder3d.h"

// Inherits from QEntity --> get some nice features, e.g. enable/disable
class CoordinateSystem : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CoordinateSystem(Qt3DCore::QEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_xAxis(new Cylinder3d(this))
        , m_yAxis(new Cylinder3d(this))
        , m_zAxis(new Cylinder3d(this))
    {
        // Set colors
        m_xAxis->m_material->setDiffuse(QColor("red"));
        m_yAxis->m_material->setDiffuse(QColor("green"));
        m_zAxis->m_material->setDiffuse(QColor("blue"));

        // Set position and orientation
        m_xOffset.translate(50,0,0);
        m_yOffset.translate(0,50,0);
        m_zOffset.translate(0,0,50);
        m_xOffset.rotate(90, 0,0,1);
        m_zOffset.rotate(90, 1,0,0);

        // Some reasonable dimensions
        m_xAxis->m_mesh->setLength(100);
        m_yAxis->m_mesh->setLength(100);
        m_zAxis->m_mesh->setLength(100);
        m_xAxis->m_mesh->setRadius(5);
        m_yAxis->m_mesh->setRadius(5);
        m_zAxis->m_mesh->setRadius(5);

        // Initialise pose
        this->setPose(0,0,0,0,0,0);

    }

    virtual ~CoordinateSystem(){};

    Cylinder3d *m_xAxis;
    Cylinder3d *m_yAxis;
    Cylinder3d *m_zAxis;
    Qt3DCore::QTransform m_pose;
    QMatrix4x4 m_xOffset;
    QMatrix4x4 m_yOffset;
    QMatrix4x4 m_zOffset;



    void setPose(double x, double y, double z, double rotZ1, double rotY, double rotZ2)
    {
        QMatrix4x4 T;
        T.setToIdentity();
        T.translate(y,z,x);
        T.rotate(rotZ1, QVector3D(0,1,0));
        T.rotate(rotY, QVector3D(1,0,0));
        T.rotate(rotZ2, QVector3D(0,1,0));
        m_pose.setMatrix(T);
        m_xAxis->m_transform->setMatrix(T*m_xOffset);
        m_yAxis->m_transform->setMatrix(T*m_yOffset);
        m_zAxis->m_transform->setMatrix(T*m_zOffset);
    }


    void setPose(QMatrix4x4 T)
    {
        m_pose.setMatrix(T);
        m_xAxis->m_transform->setMatrix(T*m_xOffset);
        m_yAxis->m_transform->setMatrix(T*m_yOffset);
        m_zAxis->m_transform->setMatrix(T*m_zOffset);
    }

};


#endif // COORDINATESYSTEM_H
