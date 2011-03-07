#include "gpuprocessor.h"

extern void processWithGPU(float *blocks, float *results, unsigned int blockSize, unsigned int blocksCount);

GPUProcessor::GPUProcessor(unsigned int bs, unsigned int bc, QObject *parent) :
    QThread(parent), blockSize(bs), blocksCount(bc), blocksCountToProcess(0)
{
    this->moveToThread(this);
    blocks = new float[blocksCount * blockSize];
    results = new float[blocksCount];
}

GPUProcessor::~GPUProcessor()
{
    delete[] blocks;
    delete[] results;
}

void GPUProcessor::run()
{
    while (true)
    {
        processWithGPU(blocks, results, blockSize, blocksCount);
        emit dataProcessed();
    }
}
