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

#ifndef LUCI_INTERPRETER_TEST_MODELS_WHILE_KERNEL_H
#define LUCI_INTERPRETER_TEST_MODELS_WHILE_KERNEL_H

#include "luci_interpreter/test_models/TestDataBase.h"

namespace luci_interpreter
{
namespace test_kernel
{

namespace while_kernel
{
/*
 * While Kernel:
 *    Main graph:
 *            Input(1)
 *                |
 *             While
 *                |
 *           Output(1)
 *
 *    Cond graph:
 *            CInput(1)
 *                |
 *            Less (Const = 10)
 *                |
 *            COutput(1)
 *
 *    Body Graph:
 *            BInput(1)
 *                |
 *           Add (Const = 1)
 *                |
 *           BOutput(1)
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x7c, 0x00, 0x00, 0x00, 0x78, 0x03, 0x00, 0x00, 0xb0, 0x03, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
  0x68, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
  0x48, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xe2, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x94, 0xfc, 0xff, 0xff, 0x04, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0xb8, 0xfc, 0xff, 0xff, 0xbc, 0xfc, 0xff, 0xff,
  0xc0, 0xfc, 0xff, 0xff, 0xc4, 0xfc, 0xff, 0xff, 0xc8, 0xfc, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00,
  0x10, 0x02, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0a, 0xfe, 0xff, 0xff,
  0x14, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
  0x68, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x57, 0x48, 0x49, 0x4c, 0x45, 0x5f, 0x42, 0x4f,
  0x44, 0x59, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0b, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x30, 0xfd, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xd0, 0xfd, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x62, 0x6f, 0x66, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0xf8, 0xfd, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x62, 0x69, 0x66, 0x6d, 0x33, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1c, 0xfe, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x62, 0x69, 0x66, 0x6d,
  0x31, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0xff, 0xff, 0xff,
  0x14, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00,
  0x5c, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x57, 0x48, 0x49, 0x4c, 0x45, 0x5f, 0x43, 0x4f,
  0x4e, 0x44, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x29, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x24, 0xfe, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x58, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xc4, 0xfe, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x10, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x63, 0x6f, 0x66, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0xec, 0xfe, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x63, 0x69, 0x66, 0x6d,
  0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x63, 0x69, 0x66, 0x6d, 0x31, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00,
  0x70, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x4d, 0x61, 0x69, 0x6e,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x5d, 0x18, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xdc, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x6f, 0x66, 0x6d, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0f, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x69, 0x66, 0x6d, 0x31,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xf4, 0xff, 0xff, 0xff,
  0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a,
  0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d,
  0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00};

const std::vector<int32_t> input_data = {35};

const std::vector<int32_t> reference_output_data = {35};
} // namespace while_kernel

template <typename T> class TestDataWhileKernel : public TestDataBase<T>
{
public:
  TestDataWhileKernel()
  {
    _input_data = while_kernel::input_data;
    _reference_output_data = while_kernel::reference_output_data;
    _test_kernel_model_circle = while_kernel::test_kernel_model_circle;
  }

  ~TestDataWhileKernel() override = default;

  const unsigned char *get_model_ptr() override final { return _test_kernel_model_circle; }

  const std::vector<T> &get_input_data_by_index(int i) override final
  {
    switch (i)
    {
      case 0:
        return _input_data;
      default:
        assert(false && "Wrong input index");
    }
  }

  const std::vector<T> &get_output_data_by_index(int i) override final
  {
    assert(i == 0);
    return _reference_output_data;
  }

protected:
  std::vector<T> _input_data;
  std::vector<T> _reference_output_data;
  const unsigned char *_test_kernel_model_circle;
};

} // namespace test_kernel
} // namespace luci_interpreter

#endif // LUCI_INTERPRETER_TEST_MODELS_WHILE_KERNEL_H
