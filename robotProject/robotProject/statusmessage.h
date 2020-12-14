#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class StatusMessage : public QWidget
{
public:
    StatusMessage(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_label(new QLabel)
        , m_status(new QLabel)
    {
        auto *grid = new QGridLayout(this);
        m_label->setText("STATUS: ");
        m_status->setText("Ready");
        grid->addWidget(m_label, 0, 0);
        grid->addWidget(m_status, 0, 1);
        setLayout(grid);
    }

public slots:
    void update(QString message)
    {
        m_status->setText(message);
    }


private:
    QLabel *m_label;
    QLabel *m_status;

};

#endif // STATUSMESSAGE_H
