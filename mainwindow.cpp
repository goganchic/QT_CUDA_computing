#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timeCurve("Processing time"),
    prevTime(QTime::currentTime())
{
    ui->setupUi(this);
    timeCurve.setPen(QPen(Qt::red));
    timeCurve.setRenderHint(QwtPlotItem::RenderAntialiased);
    timeCurve.attach(ui->plot);

    ui->plot->setAxisTitle(QwtPlot::yLeft, "processing time -->");
    ui->plot->insertLegend(new QwtLegend(), QwtPlot::TopLegend);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startCPUButton_clicked()
{
    unsigned int dataSize = ui->dataSizeEdit->text().toInt();
    unsigned int threadsCount = ui->threadsCountEdit->text().toInt();
    unsigned int dataPerThread = dataSize / threadsCount;

    ui->dataPerThread->setText(QString::number(dataPerThread));
    xs.clear();
    ys.clear();
    processor = new CPUProcessor(dataPerThread, threadsCount);
    connect(processor, SIGNAL(dataProcessed()), this, SLOT(updateStats()));
    connect(this, SIGNAL(startBlockProcessing()), processor, SLOT(blockProcessed()));
    processor->start();
}

void MainWindow::updateStats()
{
    QTime curTime = QTime::currentTime();
    double diff = curTime.msec() - prevTime.msec();

    if (diff > 0)
    {
        xs.push_back(xs.size());

        if (xs.size() < 2)
        {
            ys.push_back(0);
        }
        else
        {
            ys.push_back(curTime.msec() - prevTime.msec());
        }


        timeCurve.setData(&xs[0], &ys[0], xs.size());

        ui->plot->replot();
    }

    prevTime = curTime;
}

void MainWindow::on_stopButton_clicked()
{
    if (processor)
    {
        processor->quit();
        processor->wait();
        delete processor;
    }
}
