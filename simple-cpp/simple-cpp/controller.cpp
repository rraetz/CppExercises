#include "controller.h"
#include <Qt3DCore/qtransform.h>

Controller::Controller()
    : m_radius(0.3f)
    , m_period(1.0f)
    , m_angle(0.0f)
    , m_counter(0.0f)
{
    m_timer.setInterval(10);
    connect(&m_timer, &QTimer::timeout, this, &Controller::updatePosition);
    m_timer.start();
}


void Controller::updateMatrix()
{
    QMatrix4x4 T;
    T.setToIdentity();
    T.rotate(m_angle, QVector3D(0.0f, 5.0f, 0.0f));
    T.translate(m_radius, 0.0f, 0.0f);
    this->setMatrix(T);
}


void Controller::updatePosition()
{
    m_counter++;
    float angle = sin(m_counter/1000*m_period)*90;
    m_angle = angle;
    updateMatrix();
    qDebug() << "Position updated, m_counter =" << m_counter;

}

