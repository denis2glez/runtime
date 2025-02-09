/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <memory>
#include <utility>

#include "mlir/Dialect/Math/Transforms/Passes.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "tfrt/cpu/jit/transforms/codegen_passes.h"

namespace tfrt {
namespace cpu {
namespace jit {
namespace {

#define GEN_PASS_CLASSES
#include "tfrt/cpu/jit/transforms/codegen_gen_passes.h.inc"

struct MathOptimizationPass
    : public MathOptimizationPassBase<MathOptimizationPass> {
  explicit MathOptimizationPass(bool enable_avx2) {
    enable_avx2_ = enable_avx2;
  }
  void runOnFunction() override;
};

}  // namespace

void MathOptimizationPass::runOnFunction() {
  mlir::OwningRewritePatternList patterns(&getContext());
  mlir::populateMathAlgebraicSimplificationPatterns(patterns);
  mlir::MathPolynomialApproximationOptions approx_options;
  approx_options.enableAvx2 = enable_avx2_;
  mlir::populateMathPolynomialApproximationPatterns(patterns, approx_options);
  if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(),
                                                std::move(patterns))))
    signalPassFailure();
}

std::unique_ptr<mlir::FunctionPass> CreateMathOptimizationPass(
    bool enable_avx2) {
  return std::make_unique<MathOptimizationPass>(enable_avx2);
}

}  // namespace jit
}  // namespace cpu
}  // namespace tfrt
