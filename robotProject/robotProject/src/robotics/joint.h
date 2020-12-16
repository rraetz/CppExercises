#ifndef JOINT_H
#define JOINT_H


#include "cylinder3d.h"
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>



class Joint : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    // Constructor
    Joint(Qt3DCore::QEntity *parent, double theta0, double a, double d, double alpha);

    // Public member variables
    double m_theta;


    // Methods
    void setTheta(double angle);
    void setPose(QMatrix4x4 T);
    QMatrix4x4 computeTransform(double theta);


private:
    // Private member variables
    Cylinder3d *m_joint;
    Cylinder3d *m_linkD;
    Cylinder3d *m_linkA;
    double m_theta0;
    double m_d;
    double m_a;
    double m_alpha;

    // Private constants
    const double m_LINK_RADIUS = 10;
    const QColor m_LINK_COLOR = QColor("grey");
};


#endif // JOINT_H
