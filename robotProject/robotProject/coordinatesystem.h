#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "cylinder3d.h"

class CoordinateSystem : public Qt3DCore::QEntity
{
public:
    CoordinateSystem(Qt3DCore::QEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_xAxis(new Cylinder3d(this))
        , m_yAxis(new Cylinder3d(this))
        , m_zAxis(new Cylinder3d(this))
    {
        m_xAxis->m_material->setDiffuse(QColor("red"));
        m_yAxis->m_material->setDiffuse(QColor("green"));
        m_zAxis->m_material->setDiffuse(QColor("blue"));

        m_xAxis->m_transform->setRotationX(90);
        m_yAxis->m_transform->setRotationZ(90);
        m_xAxis->m_transform->setTranslation(QVector3D(0,0,50));
        m_yAxis->m_transform->setTranslation(QVector3D(50,0,0));
        m_zAxis->m_transform->setTranslation(QVector3D(0,50,0));

        m_xAxis->m_mesh->setLength(100);
        m_yAxis->m_mesh->setLength(100);
        m_zAxis->m_mesh->setLength(100);
        m_xAxis->m_mesh->setRadius(5);
        m_yAxis->m_mesh->setRadius(5);
        m_zAxis->m_mesh->setRadius(5);

    }

    Cylinder3d *m_xAxis;
    Cylinder3d *m_yAxis;
    Cylinder3d *m_zAxis;
};


#endif // COORDINATESYSTEM_H
