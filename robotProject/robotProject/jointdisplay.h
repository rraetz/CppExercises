#ifndef JOINTDISPLAY_H
#define JOINTDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class JointDisplay : public QWidget
{
public:
    JointDisplay(size_t nJoints);

public slots:
    void update(const std::vector<double> &jointAngles);

private:
    std::vector<QLabel*> m_descriptionLabel;
    std::vector<QLabel*> m_angleLabel;
    std::vector<QLabel*> m_unitLabel;

};



#endif // JOINTDISPLAY_H
