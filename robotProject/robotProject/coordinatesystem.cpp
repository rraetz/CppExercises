#include "coordinatesystem.h"


CoordinateSystem::CoordinateSystem(Qt3DCore::QEntity *parent)
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
    m_yOffset.translate(50,0,0);
    m_zOffset.translate(0,50,0);
    m_xOffset.translate(0,0,50);
    m_yOffset.rotate(90, 0,0,1);
    m_xOffset.rotate(90, 1,0,0);

    // Some reasonable dimensions
    m_yAxis->m_mesh->setLength(100);
    m_zAxis->m_mesh->setLength(100);
    m_xAxis->m_mesh->setLength(100);
    m_yAxis->m_mesh->setRadius(5);
    m_zAxis->m_mesh->setRadius(5);
    m_xAxis->m_mesh->setRadius(5);

    // Initialise pose
    this->setPose(QMatrix4x4());

}


void CoordinateSystem::setPose(const QMatrix4x4 &T)
{
    m_pose.setMatrix(T);
    m_xAxis->m_transform->setMatrix(T*m_xOffset);
    m_yAxis->m_transform->setMatrix(T*m_yOffset);
    m_zAxis->m_transform->setMatrix(T*m_zOffset);
}
