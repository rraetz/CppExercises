#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    plotData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::plotData()
{
    // Set userinteraction: zoom and drag
    ui->qcpwidget->setInteraction(QCP::iRangeDrag, true);
    ui->qcpwidget->setInteraction(QCP::iRangeZoom, true);
    connect(ui->qcpwidget, SIGNAL(mouseDoubleClick(QMouseEvent*)), ui->qcpwidget, SLOT(rescaleAxes()));

    // Add Graph and set some properties
    ui->qcpwidget->addGraph();
    ui->qcpwidget->addGraph();
    ui->qcpwidget->xAxis->setLabel("X");
    ui->qcpwidget->yAxis->setLabel("Y");
    ui->qcpwidget->xAxis->grid()->setSubGridVisible(true);
    ui->qcpwidget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->qcpwidget->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->qcpwidget->graph(1)->setPen(QPen{QColor{Qt::red}});

    // Create data: f(x) = x^2
    std::vector<double> X(101);
    std::iota(X.begin(),X.end(), -50);
    std::vector<double> Y(101);
    std::transform(X.begin(),X.end(), Y.begin(), [](double x){return x*x; });


    // Create second data: f(x) = 1/x
    std::vector<double> X2(X);
    std::vector<double> Y2(X2.size());
    std::transform(X2.begin(), X2.end(), Y2.begin(), [](double x){return 1/x; });

    // Plot data
    ui->qcpwidget->graph(0)->setData(QVector<double>(X.begin(), X.end()), QVector<double>(Y.begin(), Y.end()));
    ui->qcpwidget->graph(1)->setData(QVector<double>(X2.begin(), X2.end()), QVector<double>(Y2.begin(), Y2.end()));

    // Rescale axes and plot
    ui->qcpwidget->rescaleAxes();
    ui->qcpwidget->replot();
}

