#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTime>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include "cpuprocessor.h"

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
    CPUProcessor *processor;
    QwtPlotCurve timeCurve;
    QVector<double> xs;
    QVector<double> ys;
    QTime prevTime;

private slots:
    void on_stopButton_clicked();
    void on_startCPUButton_clicked();
    void updateStats();

signals:
    void startBlockProcessing();
};

#endif // MAINWINDOW_H
