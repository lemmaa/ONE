/*
 * Copyright (c) 2025 Samsung Electronics Co., Ltd. All Rights Reserved
 * Copyright 2019 The TensorFlow Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// from tensorflow/compiler/mlir/lite/ir/tfl_ops.cc

#ifndef __CIRCLE_MLIR_DIALECT_OPS_RSQRT_OP_H__
#define __CIRCLE_MLIR_DIALECT_OPS_RSQRT_OP_H__

#include "circle-mlir/dialect/CircleDialect.h"

namespace mlir
{
namespace Circle
{

//===----------------------------------------------------------------------===//
// RsqrtOp
//===----------------------------------------------------------------------===//

OpFoldResult RsqrtOp::fold(FoldAdaptor adaptor)
{
  auto operands = adaptor.getOperands();
  Type result_type = getType();
  // Only constant fold for tensor of f32 is implemented.
  if (!IsF32ShapedType(result_type))
    return nullptr;

  auto compute = [](APFloat value) -> APFloat {
    bool loseInfo;
    const llvm::fltSemantics &original_float_semantics = value.getSemantics();
    value.convert(APFloat::IEEEsingle(), APFloat::rmNearestTiesToEven, &loseInfo);
    float f = value.convertToFloat();
    APFloat result(1.f / std::sqrt(f));
    result.convert(original_float_semantics, APFloat::rmNearestTiesToEven, &loseInfo);
    return result;
  };
  return ConstFoldUnaryOp(result_type, operands[0], compute);
}

} // namespace Circle
} // namespace mlir

#endif // __CIRCLE_MLIR_DIALECT_OPS_RSQRT_OP_H__
