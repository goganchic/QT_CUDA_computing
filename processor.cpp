#include "processor.h"

Processor::Processor(unsigned int bs, unsigned int bc, QObject *parent) :
    QThread(parent), blockSize(bs), blocksCount(bc), blocksCountToProcess(0)
{
    this->moveToThread(this);
    subProcessors = new SubProcessor*[blocksCount];
    for (unsigned int i = 0; i < blocksCount; i++)
    {
        subProcessors[i] = new SubProcessor(i, blockSize);
        connect(subProcessors[i], SIGNAL(dataProcessed()), this, SLOT(blockProcessed()));
        connect(this, SIGNAL(processBlock(float*,float*)), subProcessors[i], SLOT(processData(float*, float*)));
        subProcessors[i]->start();
    }

    blocks = new float[blocksCount * blockSize];
    results = new float[blocksCount];
}

Processor::~Processor()
{
    for (unsigned int i = 0; i < blocksCount; i++)
    {
        subProcessors[i]->quit();
        subProcessors[i]->wait();
        delete subProcessors[i];
    }

    delete[] subProcessors;
    delete[] results;
}

void Processor::run()
{
    blockProcessed();
    exec();
}

void Processor::blockProcessed()
{
    if (blocksCountToProcess > 0)
        blocksCountToProcess--;

    if (blocksCountToProcess == 0)
    {
        emit dataProcessed();
        delete[] blocks;
        blocks = new float[blocksCount * blockSize];
        blocksCountToProcess = blocksCount;
        emit processBlock(blocks, results);
    }
}
