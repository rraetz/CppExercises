#ifndef JOINT_H
#define JOINT_H

#include "spaceTransformations.h"
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <QtMath>



class Joint
{
public:
    Joint(double theta0, double d, double a, double alpha)
        : m_parent(nullptr)
        , m_mesh(new Qt3DExtras::QCylinderMesh)
        , m_material(new Qt3DExtras::QDiffuseSpecularMaterial)
        , m_transform(new Qt3DCore::QTransform)
        , m_theta0(theta0)
        , m_d(d)
        , m_a(a)
        , m_alpha(alpha)
    {
        // Pose
        this->setAngle(m_theta0);

        // MeshcylinderTransform
        m_mesh->setRadius(10);
        m_mesh->setLength(30);
        m_mesh->setRings(100);
        m_mesh->setSlices(20);

        // Material
        m_material->setDiffuse(QColor("cornflowerblue"));
        qDebug() << " Joint construced";

    }

    ~Joint()
    {
        qDebug() << " Joint destruced";
    }


    Qt3DCore::QEntity *m_parent;
    Qt3DExtras::QCylinderMesh *m_mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *m_material;
    Qt3DCore::QTransform *m_transform;
    SE3 m_T;

    double m_theta0;
    double m_d;
    double m_a;
    double m_alpha;

    void setParent(Qt3DCore::QEntity *parent)
    {
        m_parent = new Qt3DCore::QEntity(parent);

        // Set as child of m_qEntity
        m_parent->addComponent(m_mesh);
        m_parent->addComponent(m_material);
        m_parent->addComponent(m_transform);
    }

    void setAngle(double theta)
    {
        // Eigen matrix
        m_T = SE3(theta, m_d, m_a, m_alpha);

        // QTransform
        QMatrix4x4 T;
        T.setToIdentity();
        T.rotate(qRadiansToDegrees(theta), QVector3D(0.0f, 0.0f, 1.0f));
        T.translate(0.0, 0.0f, m_d);
        T.translate(m_a, 0.0, 0.0f);
        T.rotate(qRadiansToDegrees(m_alpha), QVector3D(1.0f, 0.0f, 0.0f));
        m_transform->setMatrix(T);
    }

};


#endif // JOINT_H
