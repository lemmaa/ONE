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

#include "kernels/TestUtils.h"
#include "luci_interpreter/test_models/select_v2/FloatSelectV2Kernel.h"
#include "luci_interpreter/test_models/select_v2/NegSelectV2Kernel.h"

#include "loader/ModuleLoader.h"

namespace luci_interpreter
{
namespace
{

using namespace testing;

class SelectV2Test : public ::testing::Test
{
  // Do nothing
};

template <typename T>
std::vector<T> checkSelectV2Kernel(test_kernel::TestDataSelectV2Base<T> *test_data_base)
{
  MemoryManager memory_manager{};
  RuntimeModule runtime_module{};
  bool dealloc_input = true;

  // Load model with single op
  auto *model_data_raw = reinterpret_cast<const char *>(test_data_base->get_model_ptr());
  ModuleLoader::load(&runtime_module, &memory_manager, model_data_raw, dealloc_input);

  auto *main_runtime_graph = runtime_module.getMainGraph();
  assert(main_runtime_graph->getNumOfInputTensors() == 3);

  // set input data
  {
    auto *input_tensor_data_1 =
      reinterpret_cast<bool *>(main_runtime_graph->configureGraphInput(0));
    std::copy(test_data_base->get_cond_input().begin(), test_data_base->get_cond_input().end(),
              input_tensor_data_1);

    auto *input_tensor_data_2 = reinterpret_cast<T *>(main_runtime_graph->configureGraphInput(1));
    std::copy(test_data_base->get_input_data_by_index(1).begin(),
              test_data_base->get_input_data_by_index(1).end(), input_tensor_data_2);

    auto *input_tensor_data_3 = reinterpret_cast<T *>(main_runtime_graph->configureGraphInput(2));
    std::copy(test_data_base->get_input_data_by_index(2).begin(),
              test_data_base->get_input_data_by_index(2).end(), input_tensor_data_3);
  }

  runtime_module.execute();

  assert(main_runtime_graph->getNumOfOutputTensors() == 1);

  T *output_data = reinterpret_cast<T *>(main_runtime_graph->getOutputDataByIndex(0));
  const size_t num_elements = (main_runtime_graph->getOutputDataSizeByIndex(0) / sizeof(T));
  std::vector<T> output_data_vector(output_data, output_data + num_elements);
  return output_data_vector;
}

TEST_F(SelectV2Test, Float_P)
{
  test_kernel::TestDataFloatSelectV2 test_data_kernel;
  std::vector<float> output_data_vector = checkSelectV2Kernel(&test_data_kernel);
  EXPECT_THAT(output_data_vector, kernels::testing::FloatArrayNear(
                                    test_data_kernel.get_output_data_by_index(0), 0.0001f));
}

TEST_F(SelectV2Test, Input_type_mismatch_NEG)
{
  test_kernel::NegTestDataInputMismatchSelectV2Kernel test_data_kernel;

  MemoryManager memory_manager{};
  RuntimeModule runtime_module{};
  bool dealloc_input = true;
  // Load model with single op
  auto *model_data_raw = reinterpret_cast<const char *>(test_data_kernel.get_model_ptr());
  EXPECT_DEATH(ModuleLoader::load(&runtime_module, &memory_manager, model_data_raw, dealloc_input),
               "");
}

} // namespace
} // namespace luci_interpreter
