#include "subprocessor.h"

SubProcessor::SubProcessor(unsigned int n, unsigned int bs, QObject *parent) :
    QThread(parent), blockSize(bs), number(n)
{
    this->moveToThread(this);
}

void SubProcessor::run()
{
    exec();
}

void SubProcessor::processData(float *ptr, float *res)
{
    float result = 0;

    for (unsigned int i = 0; i < blockSize; i++)
    {
       result += *(ptr + blockSize * number + i);
    }

    res[number] = result / blockSize;

    emit dataProcessed();
}
