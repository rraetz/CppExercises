#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H

#include <QWidget>
#include <QLabel>



class StatusMessage : public QWidget
{
public:
    // Constructor
    StatusMessage(QWidget *parent = nullptr);

public slots:
    void update(QString message);


private:
    // Private member variables
    QLabel *m_label;
    QLabel *m_status;

};

#endif // STATUSMESSAGE_H
