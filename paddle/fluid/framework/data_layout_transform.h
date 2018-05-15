//   Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <vector>
#include "paddle/fluid/framework/op_kernel_type.h"
#include "paddle/fluid/framework/tensor.h"
#include "paddle/fluid/framework/variable.h"

namespace paddle {
namespace framework {

#ifdef PADDLE_WITH_MKLDNN
using MkldnnFormat = mkldnn::memory::format;
using MkldnnDataType = mkldnn::memory::data_type;

inline MkldnnFormat to_mkldnn_format(const DataLayout& layout) {
  switch (layout) {
  case DataLayout::kNHWC:
    return MkldnnFormat::nhwc;
  case DataLayout::kNCHW:
    return MkldnnFormat::nchw;
  default:
    PADDLE_THROW("Fail to convert layout %s to MKLDNN format",
                 DataLayoutToString(layout));
  }
}

inline DataLayout to_paddle_layout(const MkldnnFormat& format) {
  switch (format) {
  case MkldnnFormat::nhwc:
    return DataLayout::kNHWC;
  case MkldnnFormat::nchw:
    return DataLayout::kNCHW;
  default:
    PADDLE_THROW("Fail to convert MKLDNN format to paddle layout");
  }
}

inline MkldnnDataType to_mkldnn_data_type(const std::type_index type) {
  // Fix me: to be implemented
  return MkldnnDataType::f32;
}

void TransDataLayoutMkldnn(const OpKernelType& kernel_type_for_var,
                     const OpKernelType& expected_kernel_type, const Tensor& in,
                     Tensor* out);
#endif

std::vector<int> GetAxis(const DataLayout& from, const DataLayout& to);

void TransDataLayout(const OpKernelType& kernel_type_for_var,
                     const OpKernelType& expected_kernel_type, const Tensor& in,
                     Tensor* out);

}  // namespace framework
}  // namespace paddle
