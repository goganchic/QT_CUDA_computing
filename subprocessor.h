#ifndef SUBPROCESSOR_H
#define SUBPROCESSOR_H

#include <QThread>

class SubProcessor : public QThread
{
    Q_OBJECT
public:
    explicit SubProcessor(unsigned int n, unsigned int bs, QObject *parent = 0);

public slots:
    void processData(float *ptr, float *res);

private:
    unsigned int blockSize;
    unsigned int number;

protected:
    void run();

signals:
    void dataProcessed();

};

#endif // SUBPROCESSOR_H
