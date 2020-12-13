#include <QDebug>
#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <Qt3DCore/QEntity>
#include <QtWidgets/QWidget>
#include <QObject>
#include <QtWidgets/QHBoxLayout>
#include <QTimer>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <Qt3DRender/QCamera>
#include <QOrbitCameraController>

#include "main.h"
#include <vector>
#include "utils.h"
#include "joint.h"
#include "robot.h"
#include "coordinatesystem.h"
#include "inversekinematics.h"
#include "eulerinput.h"
#include "jointdisplay.h"




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
    widget->setWindowTitle(QStringLiteral("Robot Demo"));

    // Layouts and side bar
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QWidget *sideBar = new QWidget;
    QVBoxLayout *vLayout = new QVBoxLayout(sideBar);
    vLayout->setAlignment(Qt::AlignTop);
    sideBar->setMaximumWidth(250);
    hLayout->addWidget(container, 1);
    hLayout->addWidget(sideBar);



    // INFOS & BUTTONS ////////////////////////////////////////
    QLabel *info = new QLabel();
    info->setText(QString("Please enter a 3D pose according to the Euler ZYZ convention "
                          "and press the button below. An optimization-based inverse kinematics solver "
                          "will find the corresponding joint angles and the robot will move to the indicated pose."));
    info->setWordWrap(true);

    // Button
    QPushButton *button = new QPushButton("Compute Joint Angles");

//    // Text
//    QLabel *label2 = new QLabel();
//    label2->setText(QString("Enabled"));
//    QLabel *label3 = new QLabel();
//    label3->setText(QString("Position"));
    // Slider
//    QSlider *slider = new QSlider(Qt::Orientation::Horizontal);
//    slider->setWindowIconText(QString("Slider text"));

    // Euler angles input and joint angle display
    EulerInput *eulerInputs = new EulerInput();
    JointDisplay *jointAngles = new JointDisplay(6);


    // Add everything to vertical layout
    vLayout->addWidget(info);
    vLayout->addWidget(eulerInputs);
    vLayout->addWidget(button);
    vLayout->addWidget(jointAngles);



    // ADD SCENE, CAMERA & LIGHT ///////////////////////////////
    // Scene root entity
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    view->setRootEntity(scene);

    // Create robot
    Robot robbie(scene);

    // Setup of timer
    QTimer myTimer;
    myTimer.setInterval(30);

    // Connect timer to robot
    QObject::connect(button, &QPushButton::pressed,
                     [&eulerInputs, &robbie, &myTimer] (void) {
                        robbie.m_targetPose = eulerInputs->eulerPose();
                        robbie.initalizeMovement(ik(&robbie));
                        myTimer.start();} );

    QObject::connect(&myTimer, &QTimer::timeout, &robbie, &Robot::move);

    QObject::connect(&myTimer, &QTimer::timeout,
                     [&jointAngles, &robbie] (void) {jointAngles->update(robbie.jointAngles()); });



    // Camera & Camera controls
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 100.0f, 2000.0f);
    camera->setPosition(QVector3D(1000.0f, 500.0f, 500.0f));
    camera->setViewCenter(QVector3D(0, 200, 0));
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

    return app.exec();
}
