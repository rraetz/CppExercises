#include <QDebug>

#include "main.h"
#include <vector>
#include "utils.h"
#include "joint.h"
#include "robot.h"

#include <QTimer>
#include <QObject>
#include <QLineEdit>
#include "coordinatesystem.h"
#include <QSlider>
#include "inversekinematics.h"
#include <QOrbitCameraController>



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

    // Text input fields
    QLineEdit *le1 = new QLineEdit();
    QLineEdit *le2 = new QLineEdit();
    QLineEdit *le3 = new QLineEdit();
    QLineEdit *le4 = new QLineEdit();
    QLineEdit *le5 = new QLineEdit();
    QLineEdit *le6 = new QLineEdit();

    // Button
    QPushButton *button = new QPushButton("Set Pose");


    // Text
    QLabel *label2 = new QLabel();
    label2->setText(QString("Enabled"));

    QLabel *label3 = new QLabel();
    label3->setText(QString("Position"));

    // Slider
    QSlider *slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setWindowIconText(QString("Slider text"));


    // Add everything to layout
    vLayout->addWidget(info);
    vLayout->addWidget(checkBox1);
    vLayout->addWidget(label);
    vLayout->addWidget(label2);
    vLayout->addWidget(label3);
    vLayout->addWidget(le1);
    vLayout->addWidget(le2);
    vLayout->addWidget(le3);
    vLayout->addWidget(le4);
    vLayout->addWidget(le5);
    vLayout->addWidget(le6);
    vLayout->addWidget(button);




    // ADD SCENE, CAMERA & LIGHT ///////////////////////////////
    // Scene root entity
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    view->setRootEntity(scene);


    // Create robot
    Robot robbie(scene);


    // Set and launch timer
    QTimer myTimer(checkBox1);
    myTimer.setInterval(30);
//    myTimer.start();

    // Connect timer to robot and checkbox and texts with lambda function
    QObject::connect(&myTimer, &QTimer::timeout, &robbie, &Robot::move);
    QObject::connect(checkBox1, &QCheckBox::toggled, &myTimer,
                [&myTimer] (bool checked) {if (checked) myTimer.start(); else myTimer.stop(); });
//    QObject::connect(checkBox1, &QCheckBox::toggled, &robbie, &Robot::disable);
    QObject::connect(checkBox1, &QCheckBox::toggled, label2,
                [label2] (bool checked) {if (checked) label2->setText(QString("Enabled"));
                else label2->setText(QString("Disabled")); });
//    QObject::connect(&myTimer, &QTimer::timeout, label3,
//                     [label3, &robbie] {label3->setText(QString::number(robbie.m_joints.at(0).m_theta));} );

    QObject::connect(button, &QPushButton::pressed,
                     [le1, le2, le3, le4, le5, le6, &robbie, &myTimer] (void) {
                        robbie.setTargetPoseFromEulerZYZ(le1->text().toDouble(),
                                                   le2->text().toDouble(),
                                                   le3->text().toDouble(),
                                                   le4->text().toDouble(),
                                                   le5->text().toDouble(),
                                                   le6->text().toDouble());
                        ik(&robbie);
                        robbie.initalizeMovement();
                        myTimer.start();} );


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
