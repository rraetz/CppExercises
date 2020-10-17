#include "ekgwidget.h"
#include "ui_ekgwidget.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <QDebug>

EkgWidget::EkgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EkgWidget)
{
    ui->setupUi(this);
}

EkgWidget::~EkgWidget()
{
    delete ui;
}


QVector<double> EkgWidget::readEkgData(const std::string &fileName)
{
    // Instance of stream ifstream object
    std::ifstream stream(fileName);
    if (!stream) {qDebug() << "WARNING: File not found!";}

    // Copy data to double vector
    QVector<double> data;
    copy(std::istream_iterator<double>(stream),
         std::istream_iterator<double>(),
         std::back_inserter(data));

//    for (const auto &e:data) {qDebug() << e;}

    return data;
}



void EkgWidget::computePeaks(const QVector<double> &ekgData, QVector<double> &key, QVector<double> &value)
{
    for (auto it = ekgData.begin()+1; it != ekgData.end()-1; ++it)
    {
        // Check some conditions for peaks
        bool isLargerThanPrev (*it > *(it-1));
        bool isLargerThanNext (*it > *(it+1));
        bool isLargeEnough (*it > m_peakThreshold);

        // Store key (x-value) and value (y-value) in QVectors (they are needed anyway for the setData() function
        if ( isLargerThanNext && isLargerThanPrev && isLargeEnough)
        {
            key.push_back( static_cast<double>(std::distance(ekgData.begin(), it)) );
            value.push_back(*it);
        }
    }
}


double EkgWidget::computeAverageHeartRate(const QVector<double> &timeOfPeaks)
{
    return (timeOfPeaks.size()-1) / (timeOfPeaks.last() - timeOfPeaks.first()) * 60;
}


void EkgWidget::normalizeToSamplingRate(QVector<double> &xData)
{
    std::transform(xData.begin(), xData.end(), xData.begin(), [this](double x){return x*m_samplingRate; });
}


void EkgWidget::plotEkg()
{
    // Import data and compute peaks
    QVector<double> xPeaks;
    QVector<double> yPeaks;
    auto yData = readEkgData("ekg.txt");
    computePeaks(yData, xPeaks, yPeaks);

    // Set userinteraction: zoom and drag, zoom only in horizontal axis
    ui->ekgwidget->setInteraction(QCP::iRangeDrag, true);
    ui->ekgwidget->setInteraction(QCP::iRangeZoom, true);
    ui->ekgwidget->axisRect()->setRangeZoom(Qt::Horizontal);
    connect(ui->ekgwidget, SIGNAL(mouseDoubleClick(QMouseEvent*)), ui->ekgwidget, SLOT(rescaleAxes()));


    // Add Graph and set some properties
    ui->ekgwidget->addGraph();
    ui->ekgwidget->addGraph();
    ui->ekgwidget->xAxis->setLabel("Time [ms]");
    ui->ekgwidget->yAxis->setLabel("Signal [au]");
    ui->ekgwidget->xAxis->grid()->setSubGridVisible(true);
    ui->ekgwidget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->ekgwidget->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->ekgwidget->graph(1)->setPen(QPen{QColor{Qt::red}});

    // Create x vector for data
    QVector<double> xData(yData.size());
    std::iota(xData.begin(), xData.end(), 0);

    // Normalize to sampling rate
    normalizeToSamplingRate(xData);
    normalizeToSamplingRate(xPeaks);

    // Plot data
    ui->ekgwidget->graph(0)->setData(xData, yData);
    ui->ekgwidget->graph(1)->setData(xPeaks, yPeaks);

    // Compute and display average heart rate
    ui->label->setText(QString::number(computeAverageHeartRate(xPeaks)));

    // Rescale axes and plot
    ui->ekgwidget->rescaleAxes();
    ui->ekgwidget->replot();
}

void EkgWidget::on_pushButton_clicked()
{
    plotEkg();
}
