// Copyright 2020 The TensorFlow Runtime Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// cuBLAS enum parsers and printers.
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/raw_ostream.h"
#include "tfrt/gpu/wrapper/cublas_wrapper.h"
#include "tfrt/support/fp16.h"
#include "wrapper_detail.h"

namespace tfrt {
namespace gpu {
namespace wrapper {

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cublasStatus_t status) {
  switch (status) {
    case CUBLAS_STATUS_SUCCESS:
      return os << "CUBLAS_STATUS_SUCCESS";
    case CUBLAS_STATUS_NOT_INITIALIZED:
      return os << "CUBLAS_STATUS_NOT_INITIALIZED";
    case CUBLAS_STATUS_ALLOC_FAILED:
      return os << "CUBLAS_STATUS_ALLOC_FAILED";
    case CUBLAS_STATUS_INVALID_VALUE:
      return os << "CUBLAS_STATUS_INVALID_VALUE";
    case CUBLAS_STATUS_ARCH_MISMATCH:
      return os << "CUBLAS_STATUS_ARCH_MISMATCH";
    case CUBLAS_STATUS_MAPPING_ERROR:
      return os << "CUBLAS_STATUS_MAPPING_ERROR";
    case CUBLAS_STATUS_EXECUTION_FAILED:
      return os << "CUBLAS_STATUS_EXECUTION_FAILED";
    case CUBLAS_STATUS_INTERNAL_ERROR:
      return os << "CUBLAS_STATUS_INTERNAL_ERROR";
    case CUBLAS_STATUS_NOT_SUPPORTED:
      return os << "CUBLAS_STATUS_NOT_SUPPORTED";
    case CUBLAS_STATUS_LICENSE_ERROR:
      return os << "CUBLAS_STATUS_LICENSE_ERROR";
    default:
      return os << llvm::formatv("cublasStatus_t({0})",
                                 static_cast<int>(status));
  }
}

template <>
Expected<cudaDataType> Parse<cudaDataType>(llvm::StringRef name) {
  if (name == "CUDA_R_16F") return CUDA_R_16F;
  if (name == "CUDA_C_16F") return CUDA_C_16F;
  if (name == "CUDA_R_32F") return CUDA_R_32F;
  if (name == "CUDA_C_32F") return CUDA_C_32F;
  if (name == "CUDA_R_64F") return CUDA_R_64F;
  if (name == "CUDA_C_64F") return CUDA_C_64F;
  if (name == "CUDA_R_8I") return CUDA_R_8I;
  if (name == "CUDA_C_8I") return CUDA_C_8I;
  if (name == "CUDA_R_8U") return CUDA_R_8U;
  if (name == "CUDA_C_8U") return CUDA_C_8U;
  if (name == "CUDA_R_32I") return CUDA_R_32I;
  if (name == "CUDA_C_32I") return CUDA_C_32I;
  if (name == "CUDA_R_32U") return CUDA_R_32U;
  if (name == "CUDA_C_32U") return CUDA_C_32U;
  return MakeStringError("Unknown cudaDataType: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cudaDataType value) {
  switch (value) {
    case CUDA_R_16F:
      return os << "CUDA_R_16F";
    case CUDA_C_16F:
      return os << "CUDA_C_16F";
    case CUDA_R_32F:
      return os << "CUDA_R_32F";
    case CUDA_C_32F:
      return os << "CUDA_C_32F";
    case CUDA_R_64F:
      return os << "CUDA_R_64F";
    case CUDA_C_64F:
      return os << "CUDA_C_64F";
    case CUDA_R_8I:
      return os << "CUDA_R_8I";
    case CUDA_C_8I:
      return os << "CUDA_C_8I";
    case CUDA_R_8U:
      return os << "CUDA_R_8U";
    case CUDA_C_8U:
      return os << "CUDA_C_8U";
    case CUDA_R_32I:
      return os << "CUDA_R_32I";
    case CUDA_C_32I:
      return os << "CUDA_C_32I";
    case CUDA_R_32U:
      return os << "CUDA_R_32U";
    case CUDA_C_32U:
      return os << "CUDA_C_32U";
    default:
      return os << llvm::formatv("cudaDataType({0})", static_cast<int>(value));
  }
}

template <>
Expected<cublasDiagType_t> Parse<cublasDiagType_t>(llvm::StringRef name) {
  if (name == "CUBLAS_DIAG_NON_UNIT") return CUBLAS_DIAG_NON_UNIT;
  if (name == "CUBLAS_DIAG_UNIT") return CUBLAS_DIAG_UNIT;
  return MakeStringError("Unknown cublasDiagType_t: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cublasDiagType_t value) {
  switch (value) {
    case CUBLAS_DIAG_NON_UNIT:
      return os << "CUBLAS_DIAG_NON_UNIT";
    case CUBLAS_DIAG_UNIT:
      return os << "CUBLAS_DIAG_UNIT";
    default:
      return os << llvm::formatv("cublasDiagType_t({0})",
                                 static_cast<int>(value));
  }
}

template <>
Expected<cublasComputeType_t> Parse<cublasComputeType_t>(llvm::StringRef name) {
  if (name == "CUBLAS_COMPUTE_16F") return CUBLAS_COMPUTE_16F;
  if (name == "CUBLAS_COMPUTE_16F_PEDANTIC") return CUBLAS_COMPUTE_16F_PEDANTIC;
  if (name == "CUBLAS_COMPUTE_32F") return CUBLAS_COMPUTE_32F;
  if (name == "CUBLAS_COMPUTE_32F_PEDANTIC") return CUBLAS_COMPUTE_32F_PEDANTIC;
  if (name == "CUBLAS_COMPUTE_32F_FAST_16F") return CUBLAS_COMPUTE_32F_FAST_16F;
  if (name == "CUBLAS_COMPUTE_32F_FAST_16BF")
    return CUBLAS_COMPUTE_32F_FAST_16BF;
  if (name == "CUBLAS_COMPUTE_32F_FAST_TF32")
    return CUBLAS_COMPUTE_32F_FAST_TF32;
  if (name == "CUBLAS_COMPUTE_64F") return CUBLAS_COMPUTE_64F;
  if (name == "CUBLAS_COMPUTE_64F_PEDANTIC") return CUBLAS_COMPUTE_64F_PEDANTIC;
  if (name == "CUBLAS_COMPUTE_32I") return CUBLAS_COMPUTE_32I;
  if (name == "CUBLAS_COMPUTE_32I_PEDANTIC") return CUBLAS_COMPUTE_32I_PEDANTIC;
  return MakeStringError("Unknown cublasComputeType_t: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os,
                              cublasComputeType_t value) {
  switch (value) {
    case CUBLAS_COMPUTE_16F:
      return os << "CUBLAS_COMPUTE_16F";
    case CUBLAS_COMPUTE_16F_PEDANTIC:
      return os << "CUBLAS_COMPUTE_16F_PEDANTIC";
    case CUBLAS_COMPUTE_32F:
      return os << "CUBLAS_COMPUTE_32F";
    case CUBLAS_COMPUTE_32F_PEDANTIC:
      return os << "CUBLAS_COMPUTE_32F_PEDANTIC";
    case CUBLAS_COMPUTE_32F_FAST_16F:
      return os << "CUBLAS_COMPUTE_32F_FAST_16F";
    case CUBLAS_COMPUTE_32F_FAST_16BF:
      return os << "CUBLAS_COMPUTE_32F_FAST_16BF";
    case CUBLAS_COMPUTE_32F_FAST_TF32:
      return os << "CUBLAS_COMPUTE_32F_FAST_TF32";
    case CUBLAS_COMPUTE_64F:
      return os << "CUBLAS_COMPUTE_64F";
    case CUBLAS_COMPUTE_64F_PEDANTIC:
      return os << "CUBLAS_COMPUTE_64F_PEDANTIC";
    case CUBLAS_COMPUTE_32I:
      return os << "CUBLAS_COMPUTE_32I";
    case CUBLAS_COMPUTE_32I_PEDANTIC:
      return os << "CUBLAS_COMPUTE_32I_PEDANTIC";
    default:
      return os << llvm::formatv("cublasComputeType_t({0})",
                                 static_cast<int>(value));
  }
}

template <>
Expected<cublasOperation_t> Parse<cublasOperation_t>(llvm::StringRef name) {
  if (name == "CUBLAS_OP_N") return CUBLAS_OP_N;
  if (name == "CUBLAS_OP_T") return CUBLAS_OP_T;
  if (name == "CUBLAS_OP_C") return CUBLAS_OP_C;
  if (name == "CUBLAS_OP_HERMITAN") return CUBLAS_OP_HERMITAN;
  if (name == "CUBLAS_OP_CONJG") return CUBLAS_OP_CONJG;
  return MakeStringError("Unknown cublasOperation_t: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cublasOperation_t value) {
  switch (value) {
    case CUBLAS_OP_N:
      return os << "CUBLAS_OP_N";
    case CUBLAS_OP_T:
      return os << "CUBLAS_OP_T";
    case CUBLAS_OP_C:
      return os << "CUBLAS_OP_C";
    case CUBLAS_OP_CONJG:
      return os << "CUBLAS_OP_CONJG";
    default:
      return os << llvm::formatv("cublasOperation_t({0})",
                                 static_cast<int>(value));
  }
}

template <>
Expected<cublasGemmAlgo_t> Parse<cublasGemmAlgo_t>(llvm::StringRef name) {
  if (name == "CUBLAS_GEMM_DFALT") return CUBLAS_GEMM_DFALT;
  if (name == "CUBLAS_GEMM_DEFAULT") return CUBLAS_GEMM_DEFAULT;
  if (name == "CUBLAS_GEMM_ALGO0") return CUBLAS_GEMM_ALGO0;
  if (name == "CUBLAS_GEMM_ALGO1") return CUBLAS_GEMM_ALGO1;
  if (name == "CUBLAS_GEMM_ALGO2") return CUBLAS_GEMM_ALGO2;
  if (name == "CUBLAS_GEMM_ALGO3") return CUBLAS_GEMM_ALGO3;
  if (name == "CUBLAS_GEMM_ALGO4") return CUBLAS_GEMM_ALGO4;
  if (name == "CUBLAS_GEMM_ALGO5") return CUBLAS_GEMM_ALGO5;
  if (name == "CUBLAS_GEMM_ALGO6") return CUBLAS_GEMM_ALGO6;
  if (name == "CUBLAS_GEMM_ALGO7") return CUBLAS_GEMM_ALGO7;
  if (name == "CUBLAS_GEMM_ALGO8") return CUBLAS_GEMM_ALGO8;
  if (name == "CUBLAS_GEMM_ALGO9") return CUBLAS_GEMM_ALGO9;
  if (name == "CUBLAS_GEMM_ALGO10") return CUBLAS_GEMM_ALGO10;
  if (name == "CUBLAS_GEMM_ALGO11") return CUBLAS_GEMM_ALGO11;
  if (name == "CUBLAS_GEMM_ALGO12") return CUBLAS_GEMM_ALGO12;
  if (name == "CUBLAS_GEMM_ALGO13") return CUBLAS_GEMM_ALGO13;
  if (name == "CUBLAS_GEMM_ALGO14") return CUBLAS_GEMM_ALGO14;
  if (name == "CUBLAS_GEMM_ALGO15") return CUBLAS_GEMM_ALGO15;
  if (name == "CUBLAS_GEMM_ALGO16") return CUBLAS_GEMM_ALGO16;
  if (name == "CUBLAS_GEMM_ALGO17") return CUBLAS_GEMM_ALGO17;
  if (name == "CUBLAS_GEMM_ALGO18") return CUBLAS_GEMM_ALGO18;
  if (name == "CUBLAS_GEMM_ALGO19") return CUBLAS_GEMM_ALGO19;
  if (name == "CUBLAS_GEMM_ALGO20") return CUBLAS_GEMM_ALGO20;
  if (name == "CUBLAS_GEMM_ALGO21") return CUBLAS_GEMM_ALGO21;
  if (name == "CUBLAS_GEMM_ALGO22") return CUBLAS_GEMM_ALGO22;
  if (name == "CUBLAS_GEMM_ALGO23") return CUBLAS_GEMM_ALGO23;
  if (name == "CUBLAS_GEMM_DEFAULT_TENSOR_OP")
    return CUBLAS_GEMM_DEFAULT_TENSOR_OP;
  if (name == "CUBLAS_GEMM_DFALT_TENSOR_OP") return CUBLAS_GEMM_DFALT_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO0_TENSOR_OP") return CUBLAS_GEMM_ALGO0_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO1_TENSOR_OP") return CUBLAS_GEMM_ALGO1_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO2_TENSOR_OP") return CUBLAS_GEMM_ALGO2_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO3_TENSOR_OP") return CUBLAS_GEMM_ALGO3_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO4_TENSOR_OP") return CUBLAS_GEMM_ALGO4_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO5_TENSOR_OP") return CUBLAS_GEMM_ALGO5_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO6_TENSOR_OP") return CUBLAS_GEMM_ALGO6_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO7_TENSOR_OP") return CUBLAS_GEMM_ALGO7_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO8_TENSOR_OP") return CUBLAS_GEMM_ALGO8_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO9_TENSOR_OP") return CUBLAS_GEMM_ALGO9_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO10_TENSOR_OP")
    return CUBLAS_GEMM_ALGO10_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO11_TENSOR_OP")
    return CUBLAS_GEMM_ALGO11_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO12_TENSOR_OP")
    return CUBLAS_GEMM_ALGO12_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO13_TENSOR_OP")
    return CUBLAS_GEMM_ALGO13_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO14_TENSOR_OP")
    return CUBLAS_GEMM_ALGO14_TENSOR_OP;
  if (name == "CUBLAS_GEMM_ALGO15_TENSOR_OP")
    return CUBLAS_GEMM_ALGO15_TENSOR_OP;
  return MakeStringError("Unknown cublasGemmAlgo_t: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cublasGemmAlgo_t value) {
  switch (value) {
    case CUBLAS_GEMM_DEFAULT:
      return os << "CUBLAS_GEMM_DEFAULT";
    case CUBLAS_GEMM_ALGO0:
      return os << "CUBLAS_GEMM_ALGO0";
    case CUBLAS_GEMM_ALGO1:
      return os << "CUBLAS_GEMM_ALGO1";
    case CUBLAS_GEMM_ALGO2:
      return os << "CUBLAS_GEMM_ALGO2";
    case CUBLAS_GEMM_ALGO3:
      return os << "CUBLAS_GEMM_ALGO3";
    case CUBLAS_GEMM_ALGO4:
      return os << "CUBLAS_GEMM_ALGO4";
    case CUBLAS_GEMM_ALGO5:
      return os << "CUBLAS_GEMM_ALGO5";
    case CUBLAS_GEMM_ALGO6:
      return os << "CUBLAS_GEMM_ALGO6";
    case CUBLAS_GEMM_ALGO7:
      return os << "CUBLAS_GEMM_ALGO7";
    case CUBLAS_GEMM_ALGO8:
      return os << "CUBLAS_GEMM_ALGO8";
    case CUBLAS_GEMM_ALGO9:
      return os << "CUBLAS_GEMM_ALGO9";
    case CUBLAS_GEMM_ALGO10:
      return os << "CUBLAS_GEMM_ALGO10";
    case CUBLAS_GEMM_ALGO11:
      return os << "CUBLAS_GEMM_ALGO11";
    case CUBLAS_GEMM_ALGO12:
      return os << "CUBLAS_GEMM_ALGO12";
    case CUBLAS_GEMM_ALGO13:
      return os << "CUBLAS_GEMM_ALGO13";
    case CUBLAS_GEMM_ALGO14:
      return os << "CUBLAS_GEMM_ALGO14";
    case CUBLAS_GEMM_ALGO15:
      return os << "CUBLAS_GEMM_ALGO15";
    case CUBLAS_GEMM_ALGO16:
      return os << "CUBLAS_GEMM_ALGO16";
    case CUBLAS_GEMM_ALGO17:
      return os << "CUBLAS_GEMM_ALGO17";
    case CUBLAS_GEMM_ALGO18:
      return os << "CUBLAS_GEMM_ALGO18";
    case CUBLAS_GEMM_ALGO19:
      return os << "CUBLAS_GEMM_ALGO19";
    case CUBLAS_GEMM_ALGO20:
      return os << "CUBLAS_GEMM_ALGO20";
    case CUBLAS_GEMM_ALGO21:
      return os << "CUBLAS_GEMM_ALGO21";
    case CUBLAS_GEMM_ALGO22:
      return os << "CUBLAS_GEMM_ALGO22";
    case CUBLAS_GEMM_ALGO23:
      return os << "CUBLAS_GEMM_ALGO23";
    case CUBLAS_GEMM_DEFAULT_TENSOR_OP:
      return os << "CUBLAS_GEMM_DEFAULT_TENSOR_OP";
    case CUBLAS_GEMM_ALGO0_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO0_TENSOR_OP";
    case CUBLAS_GEMM_ALGO1_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO1_TENSOR_OP";
    case CUBLAS_GEMM_ALGO2_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO2_TENSOR_OP";
    case CUBLAS_GEMM_ALGO3_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO3_TENSOR_OP";
    case CUBLAS_GEMM_ALGO4_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO4_TENSOR_OP";
    case CUBLAS_GEMM_ALGO5_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO5_TENSOR_OP";
    case CUBLAS_GEMM_ALGO6_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO6_TENSOR_OP";
    case CUBLAS_GEMM_ALGO7_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO7_TENSOR_OP";
    case CUBLAS_GEMM_ALGO8_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO8_TENSOR_OP";
    case CUBLAS_GEMM_ALGO9_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO9_TENSOR_OP";
    case CUBLAS_GEMM_ALGO10_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO10_TENSOR_OP";
    case CUBLAS_GEMM_ALGO11_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO11_TENSOR_OP";
    case CUBLAS_GEMM_ALGO12_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO12_TENSOR_OP";
    case CUBLAS_GEMM_ALGO13_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO13_TENSOR_OP";
    case CUBLAS_GEMM_ALGO14_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO14_TENSOR_OP";
    case CUBLAS_GEMM_ALGO15_TENSOR_OP:
      return os << "CUBLAS_GEMM_ALGO15_TENSOR_OP";
    default:
      return os << llvm::formatv("cublasGemmAlgo_t({0})",
                                 static_cast<int>(value));
  }
}

template <>
Expected<cublasFillMode_t> Parse<cublasFillMode_t>(llvm::StringRef name) {
  if (name == "CUBLAS_FILL_MODE_LOWER") return CUBLAS_FILL_MODE_LOWER;
  if (name == "CUBLAS_FILL_MODE_UPPER") return CUBLAS_FILL_MODE_UPPER;
  if (name == "CUBLAS_FILL_MODE_FULL") return CUBLAS_FILL_MODE_FULL;
  return MakeStringError("Unknown cublasFillMode_t: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cublasFillMode_t value) {
  switch (value) {
    case CUBLAS_FILL_MODE_LOWER:
      return os << "CUBLAS_FILL_MODE_LOWER";
    case CUBLAS_FILL_MODE_UPPER:
      return os << "CUBLAS_FILL_MODE_UPPER";
    case CUBLAS_FILL_MODE_FULL:
      return os << "CUBLAS_FILL_MODE_FULL";
    default:
      return os << llvm::formatv("cublasFillMode_t({0})",
                                 static_cast<int>(value));
  }
}

template <>
Expected<cublasSideMode_t> Parse<cublasSideMode_t>(llvm::StringRef name) {
  if (name == "CUBLAS_SIDE_LEFT") return CUBLAS_SIDE_LEFT;
  if (name == "CUBLAS_SIDE_RIGHT") return CUBLAS_SIDE_RIGHT;
  return MakeStringError("Unknown cublasSideMode_t: ", name);
}

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, cublasSideMode_t value) {
  switch (value) {
    case CUBLAS_SIDE_LEFT:
      return os << "CUBLAS_SIDE_LEFT";
    case CUBLAS_SIDE_RIGHT:
      return os << "CUBLAS_SIDE_RIGHT";
    default:
      return os << llvm::formatv("cublasSideMode_t({0})",
                                 static_cast<int>(value));
  }
}

mlir::TypeID GetCudaDataTypeId(cudaDataType data_type) {
  switch (data_type) {
    case CUDA_R_16F:
      return mlir::TypeID::get<fp16>();
    case CUDA_R_32F:
      return mlir::TypeID::get<float>();
    case CUDA_R_64F:
      return mlir::TypeID::get<double>();
    default:
      return {};
  }
}

mlir::TypeID GetCublasComputeTypeId(cublasComputeType_t compute_type) {
  switch (compute_type) {
    case CUBLAS_COMPUTE_16F:
    case CUBLAS_COMPUTE_16F_PEDANTIC:
      return mlir::TypeID::get<fp16>();
    case CUBLAS_COMPUTE_32F:
    case CUBLAS_COMPUTE_32F_PEDANTIC:
    case CUBLAS_COMPUTE_32F_FAST_16F:
    case CUBLAS_COMPUTE_32F_FAST_16BF:
    case CUBLAS_COMPUTE_32F_FAST_TF32:
      return mlir::TypeID::get<float>();
    case CUBLAS_COMPUTE_64F:
    case CUBLAS_COMPUTE_64F_PEDANTIC:
      return mlir::TypeID::get<double>();
    case CUBLAS_COMPUTE_32I:
    case CUBLAS_COMPUTE_32I_PEDANTIC:
      return mlir::TypeID::get<int32_t>();
    default:
      return {};
  }
}

}  // namespace wrapper
}  // namespace gpu
}  // namespace tfrt
