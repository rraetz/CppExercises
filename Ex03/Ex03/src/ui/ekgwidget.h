#ifndef EKGWIDGET_H
#define EKGWIDGET_H

#include <QWidget>

namespace Ui {
class EkgWidget;
}

class EkgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EkgWidget(QWidget *parent = nullptr);
    ~EkgWidget();
    void plotEkg();

private:
    Ui::EkgWidget *ui;
};

#endif // EKGWIDGET_H
