#ifndef GRAPHIC3DOBJECT_H
#define GRAPHIC3DOBJECT_H

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

class Graphic3dObject : public Qt3DCore::QEntity
{
public:
    Graphic3dObject(Qt3DCore::QEntity *parent)
        : m_parent(parent)
        , m_mesh(nullptr)
        , m_material(nullptr)
        , m_transform(new Qt3DCore::QTransform)
    {
        qDebug() << "Graphic3dObject constructed";
    }

    virtual ~Graphic3dObject()
    {
        qDebug() << "Graphic3dObject destructed";
    }

    Qt3DCore::QEntity *m_parent;
    Qt3DRender::QGeometryRenderer *m_mesh;
    Qt3DRender::QMaterial *m_material;
    Qt3DCore::QTransform *m_transform;

};

#endif // GRAPHIC3DOBJECT_H
