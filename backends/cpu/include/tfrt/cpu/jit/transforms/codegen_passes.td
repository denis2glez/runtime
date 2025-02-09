// Copyright 2021 The TensorFlow Runtime Authors
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

#ifndef CODEGEN_PASSES
#define CODEGEN_PASSES

include "mlir/Pass/PassBase.td"

def AlignedAllocationsPass : FunctionPass<"codegen-aligned-allocations"> {
  let summary = "Add alignment attribute to all `alloc` operations.";
  let description = [{
    This pass adds an alignment attribute to all `alloc` operations which don't
    have such an attribute yet, or which have a smaller alignment than the one
    configured for this pass.
  }];
  let constructor = "::tfrt::cpu::jit::CreateAlignedAllocationsPass()";
  let options = [
   Option<"alignment_", "alignment", "int64_t", "64",
          "Byte alignment for allocated memrefs.">
  ];
}

def MathOptimizationPass : FunctionPass<"codegen-math-optimization"> {
  let summary = "Optimize operations from the `math` dialect.";
  let description = [{
    This pass performs algebraic simplification and polynomial approximation for
    ops from the Math dialect.
  }];
  let constructor = "::tfrt::cpu::jit::CreateMathOptimizationPass()";
  let dependentDialects = [
    "mlir::vector::VectorDialect",
    "mlir::x86vector::X86VectorDialect"
  ];
  let options = [
   Option<"enable_avx2_", "enable-avx2", "bool", "false",
          "Enable math approximations that emit AVX2 intrinsics.">
  ];
}

def RewriteVectorMultiReductionPass :
    FunctionPass<"codegen-rewrite-vector-multi-reduction"> {
  let summary = "Convert `vector.multi_reduction` into `vector.reduction` ops.";
  let description = [{
    This pass converts `vector.multi_reduction` ops into a a sequence of
    `vector.reduction` ops.
  }];
  let constructor = "::tfrt::cpu::jit::CreateRewriteVectorMultiReductionPass()";
  let dependentDialects = [
    "mlir::memref::MemRefDialect",
  ];
}

#endif  // CODEGEN_PASSES
