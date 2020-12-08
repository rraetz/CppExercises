

#include "main.h"
#include <vector>


Qt3DCore::QEntity *createScene()
{
    // Root entity
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity;

    // Material (independend of sphere)
    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial();
    material->setDiffuse(QColor("cornflowerblue"));

    // Spheres
    std::vector<Qt3DCore::QEntity*> spheres;
    std::vector<Qt3DExtras::QSphereMesh*> sphereMeshes;
    std::vector<Controller*> sphereControllers;

    for (int i=0; i < 10; ++i)
    {
        // Create sphere entities
        spheres.push_back(new Qt3DCore::QEntity(scene));

        // One mesh for each sphere
        sphereMeshes.push_back(new Qt3DExtras::QSphereMesh);
        sphereMeshes.at(i)->setRadius(i);

        // One controller for each sphere
        sphereControllers.push_back(new Controller);
        sphereControllers.at(i)->m_radius = i*10.0f;
        sphereControllers.at(i)->m_period = i*1.0f;

        // assign mesh, controller and material to each sphere
        spheres.at(i)->addComponent(sphereMeshes.at(i));
        spheres.at(i)->addComponent(sphereControllers.at(i));
        spheres.at(i)->addComponent(material);
    }

    return scene;
}


int main(int argc, char* argv[])
{
    // App, window and scene
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity *scene = createScene();

    // Camera
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(-100.0f, 100.0f, 200.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(scene);
    camController->setCamera(camera);

    // Show it
    view.setRootEntity(scene);
    view.show();

    return app.exec();
}
