#ifndef EULERINPUT_H
#define EULERINPUT_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QMatrix4x4>

class EulerInput : public QWidget
{
public:
    EulerInput(QWidget *parent = nullptr);


public slots:
    // Compute transformation matrix from inputs
    QMatrix4x4 eulerPose();


private:
    QLineEdit *m_xEdit;
    QLineEdit *m_yEdit;
    QLineEdit *m_zEdit;
    QLineEdit *m_rot1Edit;
    QLineEdit *m_rot2Edit;
    QLineEdit *m_rot3Edit;
};

#endif // EULERINPUT_H
