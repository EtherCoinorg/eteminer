#pragma once

#include <stdexcept>
#include <string>
#include <sstream>
#include <stdint.h>
#include <cuda_runtime.h>


typedef struct
{
	uint64_t uint64s[256 / sizeof(uint64_t)];
} hash256_t;


#define CU_SAFE_CALL(call)								\
do {													\
	CUresult result = call;								\
	if (result != CUDA_SUCCESS) {						\
		std::stringstream ss;							\
		const char *msg;								\
		cuGetErrorName(result, &msg);                   \
		ss << "CUDA error in func " 					\
			<< __FUNCTION__ 							\
			<< " at line "								\
			<< __LINE__									\
			<< " calling " #call " failed with error "  \
			<< msg;										\
		throw cuda_runtime_error(ss.str());				\
	}													\
} while (0)

#define NVRTC_SAFE_CALL(call)							\
do {                                                    \
    nvrtcResult result = call;                          \
    if (result != NVRTC_SUCCESS) {                      \
		std::stringstream ss;							\
		ss << "CUDA NVRTC error in func " 				\
			<< __FUNCTION__ 							\
			<< " at line "								\
			<< __LINE__									\
			<< " calling " #call " failed with error "  \
            << nvrtcGetErrorString(result) << '\n';     \
		throw cuda_runtime_error(ss.str());				\
    }                                                   \
} while(0)
