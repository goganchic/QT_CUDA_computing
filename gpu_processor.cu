#define DATA_SIZE 10000000
#define BLOCKS_COUNT 1
#define THREADS_COUNT 64

__global__ void findMean(unsigned int dataForBlock, float *inputData, float *results)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    float result = 0;

    for (int i = 0; i < dataForBlock; i++)
    {
        result += inputData[index * dataForBlock + i];
    }

    result /= dataForBlock;
    results[index] = result;
}

void processWithGPU(float *blocks, float *results, unsigned int blockSize, unsigned int blocksCount)
{
    unsigned int realDataCount = blockSize * blocksCount;
    cudaSetDevice(0);
    float *deviceInputData, *deviceResults;

    cudaMalloc((void **)&deviceInputData, realDataCount * sizeof(float));
    cudaMalloc((void **)&deviceResults, realDataCount * sizeof(float));
    cudaMemcpy(deviceInputData, blocks, realDataCount * sizeof(float), cudaMemcpyHostToDevice);

    findMean<<<1, blocksCount>>>(blockSize, deviceInputData, deviceResults);

    cudaMemcpy((void *)results, deviceResults, blocksCount * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(deviceInputData);
    cudaFree(deviceResults);
}
