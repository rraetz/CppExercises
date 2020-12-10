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

#include <QLineEdit>

#include "coordinatesystem.h"



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
    checkBox1->setChecked(false);
    checkBox1->setText(QStringLiteral("Pause on/off"));

    // Text
//    QLineEdit *le = new QLineEdit();
    QLabel *label2 = new QLabel();
    label2->setText(QString("Enabled"));

    QLabel *label3 = new QLabel();
    label3->setText(QString("Position"));


    // Add everything to layout
    vLayout->addWidget(info);
    vLayout->addWidget(checkBox1);
    vLayout->addWidget(label);
    vLayout->addWidget(label2);
    vLayout->addWidget(label3);



    // ADD SCENE, CAMERA & LIGHT ///////////////////////////////
    // Scene root entity
//    Qt3DCore::QEntity *scene = createScene();
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    view->setRootEntity(scene);


    // Create robot
    Robot robbie(scene);
    CoordinateSystem cordSys(scene);

    // Set and launch timer
    QTimer myTimer(checkBox1);
    myTimer.setInterval(30);
    myTimer.start();

    // Connect timer to robot and checkbox and texts with lambda function
    QObject::connect(&myTimer, &QTimer::timeout, &robbie, &Robot::updatePosition);
    QObject::connect(checkBox1, &QCheckBox::toggled, &myTimer,
                [&myTimer] (bool checked) {if (checked) myTimer.start(); else myTimer.stop(); });
//    QObject::connect(checkBox1, &QCheckBox::toggled, &robbie, &Robot::disable);
    QObject::connect(checkBox1, &QCheckBox::toggled, label2,
                [label2] (bool checked) {if (checked) label2->setText(QString("Enabled"));
                else label2->setText(QString("Disabled")); });
//    QObject::connect(&myTimer, &QTimer::timeout, label3,
//                     [label3, &robbie] {label3->setText(QString::number(robbie.m_joints.at(0).m_theta));} );



    // Camera & Camera controls
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 100.0f, 2000.0f);
//    camera->setPosition(QVector3D(30.0f, 50.0f, 50.0f));
    camera->setPosition(QVector3D(300.0f, 500.0f, 500.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));
//    camera->setUpVector(QVector3D(0,0,1));
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(scene);
    camController->setCamera(camera);
    camController->setLinearSpeed(100);

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


//    SE3 T0(0,0,0,0);
//    SE3 T1(0,0,151.9,PI/2);
//    SE3 T2(0,-243.0,0,0);
//    SE3 T3(0,-213.25,0,0);
//    SE3 T4(0,0,112.35,PI/2);
//    SE3 T5(0,0,85.35,-PI/2);
//    SE3 T6(0,0,81.9,0);

//    printTransformation(T0);
//    printTransformation(T0*T1);
//    printTransformation(T0*T1*T2);
//    printTransformation(T0*T1*T2*T3);
//    printTransformation(T0*T1*T2*T3*T4);
//    printTransformation(T0*T1*T2*T3*T4*T5);
//    printTransformation(T0*T1*T2*T3*T4*T5*T6);




    return app.exec();
}
