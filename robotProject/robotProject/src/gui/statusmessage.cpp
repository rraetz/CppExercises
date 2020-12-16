#include "statusmessage.h"
#include <QGridLayout>



//===================================
// CONSTRUCTOR & DESTRUCTOR
//===================================
StatusMessage::StatusMessage(QWidget *parent)
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




//===================================
// METHODS
//===================================
void StatusMessage::update(QString message)
{
    m_status->setText(message);
}
