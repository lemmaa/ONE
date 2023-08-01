/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef LUCI_INTERPRETER_TEST_MODELS_FLOAT_RESIZE_BILINEAR_KERNEL_H
#define LUCI_INTERPRETER_TEST_MODELS_FLOAT_RESIZE_BILINEAR_KERNEL_H

#include "TestDataResizeBilinearBase.h"

namespace luci_interpreter
{
namespace test_kernel
{
namespace resize_bilinear_float
{
/*
 * ResizeBilinear Kernel:
 *
 *      align_corners = false; half_pixel_centers = false;
 *
 *                       Input(2, 2, 2, 1) FLOAT
 *                               |
 *                               |   Constant Input(2) [3,3] INT32
 *                               |  /
 *                          ResizeBilinear
 *                                 |
 *                         Output(2, 3, 3, 1) FLOAT
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00,
  0x00, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x84, 0x01, 0x00, 0x00, 0xa0, 0x01,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
  0x24, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00,
  0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x8c, 0xff, 0xff, 0xff, 0x90, 0xff,
  0xff, 0xff, 0x94, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00,
  0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f,
  0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x00, 0xa0, 0xff, 0xff, 0xff, 0x0c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x6f, 0x66, 0x6d, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0f, 0x00, 0x08, 0x00,
  0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x73, 0x69,
  0x7a, 0x65, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00,
  0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x69, 0x66, 0x6d, 0x31, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00,
  0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e,
  0x45, 0x2d, 0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c,
  0x65, 0x00, 0x00, 0x00

};

const std::vector<float> input_data = {
  3,  6,  //
  9,  12, //
  4,  10, //
  10, 16  //
};

const std::vector<float> reference_output_data = {
  3,  5,  6,  //
  7,  9,  10, //
  9,  11, 12, //
  4,  8,  10, //
  8,  12, 14, //
  10, 14, 16, //
};

} // namespace resize_bilinear_float

namespace resize_bilinear_float_half_pixel_centers
{
/*
 * ResizeBilinear Kernel:
 *
 *        align_corners = false; half_pixel_centers = true;
 *
 *                       Input(2, 2, 2, 1) FLOAT
 *                               |
 *                               |   Constant Input(2) [3,3] INT32
 *                               |  /
 *                          ResizeBilinear
 *                                 |
 *                         Output(2, 3, 3, 1) FLOAT
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x94, 0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff,
  0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x6c, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x78, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xa0, 0xff, 0xff, 0xff,
  0x0c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x6f, 0x66, 0x6d, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0f, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x73, 0x69, 0x7a, 0x65,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x10, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x69, 0x66, 0x6d, 0x31,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d,
  0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00};

const std::vector<float> input_data = {
  1, 2, //
  3, 4, //
  1, 2, //
  3, 4  //
};

const std::vector<float> reference_output_data = {
  1, 1.5, 2, //
  2, 2.5, 3, //
  3, 3.5, 4, //
  1, 1.5, 2, //
  2, 2.5, 3, //
  3, 3.5, 4, //
};

} // namespace resize_bilinear_float_half_pixel_centers

class TestDataFloatResizeBilinear : public TestDataResizeBilinearBase<float>
{
public:
  TestDataFloatResizeBilinear(bool half_pixel_centers)
  {
    if (!half_pixel_centers)
    {
      _input_data = resize_bilinear_float::input_data;
      _reference_output_data = resize_bilinear_float::reference_output_data;
      _test_kernel_model_circle = resize_bilinear_float::test_kernel_model_circle;
    }
    else
    {
      _input_data = resize_bilinear_float_half_pixel_centers::input_data;
      _reference_output_data = resize_bilinear_float_half_pixel_centers::reference_output_data;
      _test_kernel_model_circle =
        resize_bilinear_float_half_pixel_centers::test_kernel_model_circle;
    }
  }

  ~TestDataFloatResizeBilinear() override = default;
};

} // namespace test_kernel
} // namespace luci_interpreter

#endif // LUCI_INTERPRETER_TEST_MODELS_FLOAT_RESIZE_BILINEAR_KERNEL_H