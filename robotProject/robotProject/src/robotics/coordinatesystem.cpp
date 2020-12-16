#include "coordinatesystem.h"


//===================================
// CONSTRUCTOR & DESTRUCTOR
//===================================
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
    m_yOffset.translate(m_CYLINDER_LENGTH/2,0,0);
    m_zOffset.translate(0,m_CYLINDER_LENGTH/2,0);
    m_xOffset.translate(0,0,m_CYLINDER_LENGTH/2);
    m_yOffset.rotate(90, 0,0,1);
    m_xOffset.rotate(90, 1,0,0);

    // Some reasonable dimensions
    m_yAxis->m_mesh->setLength(m_CYLINDER_LENGTH);
    m_zAxis->m_mesh->setLength(m_CYLINDER_LENGTH);
    m_xAxis->m_mesh->setLength(m_CYLINDER_LENGTH);
    m_yAxis->m_mesh->setRadius(m_CYLINDER_RADIUS);
    m_zAxis->m_mesh->setRadius(m_CYLINDER_RADIUS);
    m_xAxis->m_mesh->setRadius(m_CYLINDER_RADIUS);

    // Initialise pose
    this->setPose(QMatrix4x4());

}



//===================================
// METHODS
//===================================

// Define pose for all cylinder3d members of the coordinate system
void CoordinateSystem::setPose(const QMatrix4x4 &T)
{
    m_pose.setMatrix(T);
    m_xAxis->m_transform->setMatrix(T*m_xOffset);
    m_yAxis->m_transform->setMatrix(T*m_yOffset);
    m_zAxis->m_transform->setMatrix(T*m_zOffset);
}
