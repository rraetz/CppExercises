#ifndef CYLINDER3D_H
#define CYLINDER3D_H

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DCore/QTransform>


class Cylinder3d : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    // Constructor
    Cylinder3d(Qt3DCore::QEntity *parent = nullptr);

    // Public member variables
    Qt3DExtras::QCylinderMesh *m_mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *m_material;
    Qt3DCore::QTransform *m_transform;

private:
    // Private constants
    const double m_LENGTH = 50;
    const double m_RADIUS = 25;
    const double m_RINGS = 100;
    const double m_SLICES = 20;
    const QColor m_COLOR = QColor("cornflowerblue");
};


#endif // CYLINDER3D_H
