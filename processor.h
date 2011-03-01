#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QThread>
#include <QMutex>
#include "subprocessor.h"

class Processor : public QThread
{
    Q_OBJECT
public:
    explicit Processor(unsigned int bs, unsigned int bc, QObject *parent = 0);
    ~Processor();

signals:
    void dataProcessed();
    void processBlock(float *ptr, float *res);

public slots:
    void blockProcessed();

private:
    unsigned int blockSize;
    unsigned int blocksCount;
    unsigned int blocksCountToProcess;
    QMutex mutex;
    SubProcessor **subProcessors;
    float *blocks;
    float *results;

protected:
    void run();
};

#endif // PROCESSOR_H
