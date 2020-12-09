#ifndef TIMER_H
#define TIMER_H


#include <QTimer>
#include <QObject>

class Timer : public QObject
{
public:
    Timer(QObject* target, void (*targetMemberFunction)())
    {
        QObject::connect(&m_timer, &QTimer::timeout, target, targetMemberFunction);
        m_timer.setInterval(30);
        m_timer.start();
    }

    QTimer m_timer;
};


#endif // TIMER_H
