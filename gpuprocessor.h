#ifndef GPUPROCESSOR_H
#define GPUPROCESSOR_H

#include <QThread>

class GPUProcessor : public QThread
{
    Q_OBJECT
public:
    explicit GPUProcessor(unsigned int bs, unsigned int bc, QObject *parent = 0);
    ~GPUProcessor();

signals:
    void dataProcessed();

private:
    unsigned int blockSize;
    unsigned int blocksCount;
    unsigned int blocksCountToProcess;
    float *blocks;
    float *results;

protected:
    void run();
};

#endif // GPUPROCESSOR_H
