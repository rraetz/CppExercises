#ifndef CYLINDER3D_H
#define CYLINDER3D_H


#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>


class Cylinder3d : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    // Constructor
    Cylinder3d(Qt3DCore::QEntity *parent);

    // Member variables
    Qt3DExtras::QCylinderMesh *m_mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *m_material;
    Qt3DCore::QTransform *m_transform;
};


#endif // CYLINDER3D_H
