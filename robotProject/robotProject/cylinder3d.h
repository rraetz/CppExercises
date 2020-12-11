#ifndef CYLINDER3D_H
#define CYLINDER3D_H


#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <QMatrix4x4>

#include <Qt3DRender/QMesh>


class Cylinder3d : public Qt3DCore::QEntity
{
public:
    // Constructor
    Cylinder3d(Qt3DCore::QEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_mesh(new Qt3DExtras::QCylinderMesh)
//        , m_mesh(new Qt3DRender::QMesh)
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
        m_transform->setMatrix(QMatrix4x4());

//        qDebug() << "Cylinder3d constructed";
    }


    // Destructor
    virtual ~Cylinder3d()
    {
//        qDebug() << "Cylinder3d destructed";
    }


    // Member variables
//    Qt3DRender::QMesh *m_mesh;
    Qt3DExtras::QCylinderMesh *m_mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *m_material;
    Qt3DCore::QTransform *m_transform;
};


#endif // CYLINDER3D_H
