#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTime>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include "cpuprocessor.h"
#include "gpuprocessor.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CPUProcessor *cpuProcessor;
    GPUProcessor *gpuProcessor;
    QwtPlotCurve timeCurve;
    QVector<double> xs;
    QVector<double> ys;
    QTime prevTime;

private slots:
    void on_startGPUButton_clicked();
    void on_stopButton_clicked();
    void on_startCPUButton_clicked();
    void updateStats();
};

#endif // MAINWINDOW_H
