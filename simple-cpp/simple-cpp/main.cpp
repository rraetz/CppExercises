

#include "main.h"
#include <vector>
#include <QSharedDataPointer>


//class Sphere
//{
//public:
//    Sphere(Qt3DCore::QEntity* scene, float period, QColor color)
//        : m_scene(new Qt3DCore::QEntity(scene))
//        , m_T(new Controller)
//        , m_mesh(new Qt3DExtras::QSphereMesh)
//        , m_material(new Qt3DExtras::QDiffuseSpecularMaterial())
//    {
////        m_mesh = new(Qt3DExtras::QSphereMesh);
//        m_mesh->setRadius(10.0f);
//        m_T->m_radius = 10.0f;
//        m_T->m_period = period;
////        m_T.m_radius = 10.0f;
////        m_T.m_period = period;
//        m_scene->addComponent(m_mesh);
//        m_scene->addComponent(m_T);
//        m_scene->addComponent(m_material);
//        m_material->setDiffuse(color);
////        qDebug() << "Joint created with period = " << m_T->m_period;

//    }
//    virtual ~Sphere() {}

//    Qt3DCore::QEntity* m_scene;
//    Controller* m_T;
//    Qt3DExtras::QSphereMesh* m_mesh;
//    Qt3DExtras::QDiffuseSpecularMaterial* m_material;

//};

//class Joint
//{
//public:

    // Qt 3D stuff
//    Pose
//    mesh
//    material

    // Kinematics
//    theta, d, a, alpha
//    position limits
//    speed limits
//    acc limits
//    theta0

//};


/* class robot
 * {
 * public:
 *      std::vector<Joint> m_joints
 *
 *      setTargetPose (set for trajectory planner)
 *      void setPose(theta1, theta2, theta3,...)
 *
 *      void forwardKinematics
 *      void inverseKinematics
 *      void updateTrajectory
 *
 * }
 */

Qt3DCore::QEntity* createScene()
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
        sphereControllers.at(i)->m_period = 10+i*0.2f;

        // assign mesh, controller and material to each sphere
        spheres.at(i)->addComponent(sphereMeshes.at(i));
        spheres.at(i)->addComponent(sphereControllers.at(i));
        spheres.at(i)->addComponent(material);
    }


//    Sphere S(scene, 10, QColor("cornflowerblue"));
//    Sphere S2(scene, 30, QColor("red"));
//    qDebug() << J.m_T->m_period << J2.m_T->m_period;

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

    // Light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(scene);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(camera->position());
    lightEntity->addComponent(lightTransform);

    // Camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(scene);
    camController->setCamera(camera);

    // Show it
    view.setRootEntity(scene);
    view.show();

    return app.exec();
}
