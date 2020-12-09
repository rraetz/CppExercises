#include <QDebug>
#include <Geometry>

#include "main.h"
#include <vector>
#include "spaceTransformations.h"
#include "utils.h"
#include "controller.h"
#include "joint.h"
#include "robot.h"

#include <QTimer>
#include <QObject>

#include "timer.h"


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
//    Qt3DCore::QEntity *scene = createScene();
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    view->setRootEntity(scene);


    // Create robot
    Robot robbie(scene);

    // Set and launch timer
    QTimer myTimer;
    QObject::connect(&myTimer, &QTimer::timeout, &robbie, &Robot::updatePosition);
    myTimer.setInterval(30);
    myTimer.start();


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
