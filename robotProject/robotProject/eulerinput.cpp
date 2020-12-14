#include "eulerinput.h"



EulerInput::EulerInput(QWidget *parent)
    : QWidget(parent)
    , m_xEdit(new QLineEdit(this))
    , m_yEdit(new QLineEdit(this))
    , m_zEdit(new QLineEdit(this))
    , m_rot1Edit(new QLineEdit(this))
    , m_rot2Edit(new QLineEdit(this))
    , m_rot3Edit(new QLineEdit(this))
{
    // Descriptions
    auto *xLabel = new QLabel("X", this);
    auto *yLabel = new QLabel("Y", this);
    auto *zLabel = new QLabel("Z", this);
    auto *rot1Label = new QLabel("Rot Z1", this);
    auto *rot2Label = new QLabel("Rot Y", this);
    auto *rot3Label = new QLabel("Rot Z2", this);

    // Units
    auto *xUnit = new QLabel("[mm]", this);
    auto *yUnit = new QLabel("[mm]", this);
    auto *zUnit = new QLabel("[mm]", this);
    auto *rot1Unit = new QLabel("[deg]", this);
    auto *rot2Unit = new QLabel("[deg]", this);
    auto *rot3Unit = new QLabel("[deg]", this);

    // Create and fill grid
    auto *grid = new QGridLayout(this);
    grid->addWidget(xLabel, 0,0);
    grid->addWidget(yLabel, 1,0);
    grid->addWidget(zLabel, 2,0);
    grid->addWidget(rot1Label, 3,0);
    grid->addWidget(rot2Label, 4,0);
    grid->addWidget(rot3Label, 5,0);

    grid->addWidget(m_xEdit, 0, 1);
    grid->addWidget(m_yEdit, 1, 1);
    grid->addWidget(m_zEdit, 2, 1);
    grid->addWidget(m_rot1Edit, 3, 1);
    grid->addWidget(m_rot2Edit, 4, 1);
    grid->addWidget(m_rot3Edit, 5, 1);

    grid->addWidget(xUnit, 0, 2);
    grid->addWidget(yUnit, 1, 2);
    grid->addWidget(zUnit, 2, 2);
    grid->addWidget(rot1Unit, 3, 2);
    grid->addWidget(rot2Unit, 4, 2);
    grid->addWidget(rot3Unit, 5, 2);

    setLayout(grid);
}


QMatrix4x4 EulerInput:: eulerPose()
{
    QMatrix4x4 T;
    T.setToIdentity();
    T.translate(this->m_yEdit->text().toDouble(), this->m_zEdit->text().toDouble(), m_xEdit->text().toDouble());
    T.rotate(this->m_rot1Edit->text().toDouble(), 0,1,0);
    T.rotate(this->m_rot2Edit->text().toDouble(), 1,0,0);
    T.rotate(this->m_rot3Edit->text().toDouble(), 0,1,0);
    return T;
}
