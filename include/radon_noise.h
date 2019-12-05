#include <cuda.h>
#include <cuda_runtime.h>
#include <curand.h>
#include <curand_kernel.h>
#include "utils.h"

class RadonNoiseGenerator{
    curandState *states = nullptr;

public:
    RadonNoiseGenerator(const uint seed);

    void set_seed(const uint seed);

    void add_noise(float* sinogram, const float signal, const float density_normalization, const bool approximate, const uint width, const uint height);

    void free();
};

//class RandomStates{
//    curandState *states = nullptr;
//    uint batch_size = 0;
//    uint width = 0;
//    uint height = 0;
//
//    public:
//    cudaTextureObject_t texObj;
//
//    RandomStates(const uint seed){
//        checkCudaErrors(cudaMalloc((void **)&states, 4096 * sizeof(curandState)));
//    }
//
//    void free(){
//        if(this->array != nullptr){
//            checkCudaErrors(cudaFreeArray(this->array));
//            checkCudaErrors(cudaDestroyTextureObject(this->texObj));
//        }
//    }
//
//    void allocate(uint b, uint w, uint h){
//        // free previously allocated array
//        this->free();
//
//        this->batch_size = b;
//        this->width = w;
//        this->height = h;
//
//        // Allocate a layered CUDA array
//        cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(32, 0, 0, 0, cudaChannelFormatKindFloat);
//        const cudaExtent extent = make_cudaExtent(width, height, batch_size);
//        checkCudaErrors(cudaMalloc3DArray(&array, &channelDesc, extent, cudaArrayLayered));
//
//        cudaResourceDesc resDesc;
//        memset(&resDesc, 0, sizeof(resDesc));
//        resDesc.resType = cudaResourceTypeArray;
//        resDesc.res.array.array = array;
//
//        // Specify texture object parameters
//        cudaTextureDesc texDesc;
//        memset(&texDesc, 0, sizeof(texDesc));
//        texDesc.addressMode[0] = cudaAddressModeBorder;
//        texDesc.addressMode[1] = cudaAddressModeBorder;
//        texDesc.filterMode = cudaFilterModeLinear;
//        texDesc.readMode = cudaReadModeElementType;
//        texDesc.normalizedCoords = 0;
//
//        // Create texture object
//        checkCudaErrors(cudaCreateTextureObject(&texObj, &resDesc, &texDesc, NULL));
//    }
//
//    void put(const float *data, uint b, uint w, uint h, uint pitch){
//        // only reallocate when required
//        if(this->batch_size != b || this->width != w ||  this->height != h){
//            this->allocate(b, w, h);
//        }
//
//        // copy data into array
//        cudaMemcpy3DParms myparms = {0};
//        myparms.srcPos = make_cudaPos(0, 0, 0);
//        myparms.dstPos = make_cudaPos(0, 0, 0);
//        myparms.srcPtr = make_cudaPitchedPtr((void *) data, pitch * sizeof(float), width, height);
//        myparms.dstArray = this->array;
//        myparms.extent = make_cudaExtent(width, height, batch_size);
//        myparms.kind = cudaMemcpyDeviceToDevice;
//        checkCudaErrors(cudaMemcpy3D(&myparms));
//    }
//
//    void python_free(){
//        this->free();
//    }
//};