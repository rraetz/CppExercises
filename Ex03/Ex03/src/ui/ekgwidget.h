#ifndef EKGWIDGET_H
#define EKGWIDGET_H

#include <QWidget>
#include <unordered_map>

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


private slots:
    void on_pushButton_clicked();

private:
    Ui::EkgWidget *ui;
    const double m_peakThreshold = 1100;
    const double m_samplingRate = 1.0/360.0;
    QVector<double> readEkgData(const std::string &fileName);
    void computePeaks(const QVector<double> &ekgData, QVector<double> &key, QVector<double> &value);
    double computeAverageHeartRate(const QVector<double> &timeOfPeaks);
    void normalizeToSamplingRate(QVector<double> &xData);


};

#endif // EKGWIDGET_H
