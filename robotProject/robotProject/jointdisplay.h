#ifndef JOINTDISPLAY_H
#define JOINTDISPLAY_H

#include <algorithm>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class JointDisplay : public QWidget
{
public:
    JointDisplay(size_t nJoints)
        : QWidget(nullptr)
    {
        auto *grid = new QGridLayout(this);
        for (size_t i=0; i<nJoints; ++i)
        {
            // Populate label vectors
            m_descriptionLabel.push_back(new QLabel);
            m_angleLabel.push_back(new QLabel);
            m_unitLabel.push_back(new QLabel);

            // Set text
            m_descriptionLabel.back()->setText("Joint " + QString::number(i+1) + ": ");
            m_unitLabel.back()->setText("[deg]");

            // Add to grid
            grid->addWidget(m_descriptionLabel.back(), i, 0);
            grid->addWidget(m_angleLabel.back(), i, 1);
            grid->addWidget(m_unitLabel.back(), i, 2);

        }
        setLayout(grid);
    }

public slots:
    void update(const std::vector<double> &jointAngles)
    {
        auto it = jointAngles.begin();
        std::for_each(m_angleLabel.begin(), m_angleLabel.end(),
                      [&it] (QLabel *l) {l->setText(QString::number(*it)); ++it;});
    }

private:
    std::vector<QLabel*> m_descriptionLabel;
    std::vector<QLabel*> m_angleLabel;
    std::vector<QLabel*> m_unitLabel;

};



#endif // JOINTDISPLAY_H
