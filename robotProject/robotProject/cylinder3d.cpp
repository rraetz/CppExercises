#include "cylinder3d.h"
#include <Qt3DRender/QMesh>


Cylinder3d::Cylinder3d(Qt3DCore::QEntity *parent)
    : Qt3DCore::QEntity(parent)
    , m_mesh(new Qt3DExtras::QCylinderMesh)
    , m_material(new Qt3DExtras::QDiffuseSpecularMaterial)
    , m_transform(new Qt3DCore::QTransform)
{
    // Add pointers to mesh, material and transform as components
    this->addComponent(m_mesh);
    this->addComponent(m_material);
    this->addComponent(m_transform);

    // Some basic settings
    m_mesh->setRadius(25);
    m_mesh->setLength(50);
    m_mesh->setRings(100);
    m_mesh->setSlices(20);
    m_material->setDiffuse(QColor("cornflowerblue"));
}
