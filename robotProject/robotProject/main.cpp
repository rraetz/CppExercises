#include <QDebug>
#include <Geometry>

#include "main.h"
#include <vector>
#include "spaceTransformations.h"
#include "utils.h"
#include "controller.h"



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
//    material->setDiffuse(QColor("red"));

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


    return scene;
}


int main(int argc, char* argv[])
{
    // BASIC SETUP ////////////////////////////////////////
    // App, window
    QApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor("grey"));

    // Main widgets
    QWidget *container = QWidget::createWindowContainer(view);
    QWidget *widget = new QWidget;
    widget->setWindowTitle(QStringLiteral("My robot"));

    // Box Layouts
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);



    // INFOS & BUTTONS ////////////////////////////////////////
    // Info Panel
    QCommandLinkButton *info = new QCommandLinkButton();
    info->setIconSize(QSize(0,0));
    info->setText(QStringLiteral("Qt3D ready-made meshes"));
    info->setDescription(QString::fromLatin1("Qt3D provides several ready-made meshes, like torus, cylinder, cone, "
                                             "cube, plane and sphere."));
    QLabel *label = new QLabel();
    label->setText(QString("Hello there \nThis is a test"));

    // Checkbox
    QCheckBox *checkBox1 = new QCheckBox(widget);
    checkBox1->setChecked(true);
    checkBox1->setText(QStringLiteral("This is a checkbox"));
    checkBox1->setChecked(true);

    // Add everything to layout
    vLayout->addWidget(info);
    vLayout->addWidget(checkBox1);
    vLayout->addWidget(label);



    // ADD SCENE, CAMERA & LIGHT ///////////////////////////////
    // Scene root entity
    Qt3DCore::QEntity *scene = createScene();
    view->setRootEntity(scene);

    // Camera & Camera controls
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(-100.0f, 100.0f, 200.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(scene);
    camController->setCamera(camera);

    // Light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(scene);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(camera->position());
    lightEntity->addComponent(lightTransform);


    // Show window
    widget->show();
    widget->resize(1200, 800);


    SE3 T(1,2,3,4);
    printTransformation(T);

    return app.exec();
}
