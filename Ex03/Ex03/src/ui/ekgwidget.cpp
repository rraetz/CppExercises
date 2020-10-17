#include "ekgwidget.h"
#include "ui_ekgwidget.h"

EkgWidget::EkgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EkgWidget)
{
    ui->setupUi(this);
    plotEkg();
}

EkgWidget::~EkgWidget()
{
    delete ui;
}


void EkgWidget::plotEkg()
{

    // Set userinteraction: zoom and drag
    ui->ekgwidget->setInteraction(QCP::iRangeDrag, true);
    ui->ekgwidget->setInteraction(QCP::iRangeZoom, true);
    connect(ui->ekgwidget, SIGNAL(mouseDoubleClick(QMouseEvent*)), ui->ekgwidget, SLOT(rescaleAxes()));

    // Add Graph and set some properties
    ui->ekgwidget->addGraph();
    ui->ekgwidget->xAxis->setLabel("X");
    ui->ekgwidget->yAxis->setLabel("Y");
    ui->ekgwidget->xAxis->grid()->setSubGridVisible(true);
    ui->ekgwidget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->ekgwidget->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->ekgwidget->graph(0)->setPen(QPen{QColor{Qt::red}});

    // Create data: f(x) = x^2
    std::vector<double> X(101);
    std::iota(X.begin(),X.end(), -50);
    std::vector<double> Y(101);
    std::transform(X.begin(),X.end(), Y.begin(), [](double x){return x*x*x; });

    // Plot data
    ui->ekgwidget->graph(0)->setData(QVector<double>(X.begin(), X.end()), QVector<double>(Y.begin(), Y.end()));

    // Rescale axes and plot
    ui->ekgwidget->rescaleAxes();
    ui->ekgwidget->replot();
}
