#include <QDebug>
#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
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
#include <Qt3DRender/qpointlight.h>
#include <Qt3DExtras/QForwardRenderer>
#include <QFirstPersonCameraController>

#include "joint.h"
#include "robot.h"
#include "coordinatesystem.h"
#include "eulerinput.h"
#include "jointdisplay.h"
#include "statusmessage.h"



int main(int argc, char* argv[])
{
    //===================================
    // BASIC SETUP
    //===================================
    // App, window
    QApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor("gainsboro"));

    // Main widgets
    QWidget *container = QWidget::createWindowContainer(view);
    QWidget *widget = new QWidget;
    widget->setWindowTitle(QStringLiteral("Robot Demo"));

    // Layouts and side panel
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QWidget *sideBar = new QWidget;
    QVBoxLayout *vLayout = new QVBoxLayout(sideBar);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setSpacing(20);
    sideBar->setMaximumWidth(250);
    hLayout->addWidget(container, 1);
    hLayout->addWidget(sideBar);

    // Scene root entity
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    view->setRootEntity(scene);

    // Create robot
    Robot robbie(scene);



    //===================================
    // SIDE PANEL
    //===================================
    QLabel *info = new QLabel();
    info->setText(QString("Please enter a 3D pose according to the Euler ZYZ convention "
                          "and press the button below. An optimization-based gradient-free inverse kinematics solver "
                          "will find the corresponding joint angles and the robot will move to the indicated pose."));
    info->setWordWrap(true);
    QLabel *axes = new QLabel();
    axes->setText(QString("X-axis: Red \nY-axis: Green \nZ-axis: Blue"));
    QLabel *hint = new QLabel();
    hint->setText("Hint: If you press the button multiple times, the solver might find different configurations.");
    hint->setWordWrap(true);

    // Euler angles input and joint angle display
    EulerInput *eulerInputs = new EulerInput();
    JointDisplay *jointAngles = new JointDisplay(robbie.jointAngles().size());

    // Button
    QPushButton *button = new QPushButton("Compute Joint Angles");

    // Status message
    StatusMessage *status = new StatusMessage();

    // Add everything to vertical layout
    vLayout->addWidget(info);
    vLayout->addWidget(axes);
    vLayout->addWidget(eulerInputs);
    vLayout->addWidget(button);
    vLayout->addWidget(hint);
    vLayout->addWidget(jointAngles);
    vLayout->addWidget(status);



    //===================================
    // CONNECT SIGNALS & SLOTS
    //===================================
    // Setup of timer
    QTimer myTimer;
    myTimer.setInterval(30);

    // Connect timer and button to robot
    QObject::connect(button, &QPushButton::pressed,
                     [&eulerInputs, &robbie, &myTimer] (void)
                        {robbie.initalizeMovement(eulerInputs->eulerPose()); myTimer.start();} );

    // Connect trajectory planner to timer
    QObject::connect(&myTimer, &QTimer::timeout, &robbie, &Robot::move);

    // Update joint angles display while moving
    QObject::connect(&myTimer, &QTimer::timeout,
                     [&jointAngles, &robbie] (void) {jointAngles->update(robbie.jointAngles()); });

    // Update status message
    QObject::connect(&robbie, &Robot::statusMessage, status, &StatusMessage::update);




    //===================================
    // CAMERA & LIGHT
    //===================================
    // Camera & Camera controls
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 100.0f, 2000.0f);
    camera->setPosition(QVector3D(1000.0f, 1000.0f, 500.0f));
    camera->setViewCenter(QVector3D(0, 200, 0));
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(scene);
    camController->setCamera(camera);
    camController->setLinearSpeed(300);

    // Light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(scene);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(camera->position());
    lightEntity->addComponent(lightTransform);



    //===================================
    // DISPLAY EVERYTHING
    //===================================
    widget->show();
    widget->resize(1200, 800);
    return app.exec();
}