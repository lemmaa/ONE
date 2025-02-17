/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_RUN_ARGS_H__
#define __ONERT_RUN_ARGS_H__

#include <string>
#include <unordered_map>
#include <vector>

#include <arser/arser.h>

#include "types.h"

namespace onert_run
{

using TensorShapeMap = std::unordered_map<uint32_t, TensorShape>;

#if defined(ONERT_HAVE_HDF5) && ONERT_HAVE_HDF5 == 1
enum class WhenToUseH5Shape
{
  NOT_PROVIDED, // Param not provided
  PREPARE, // read shapes in h5 file and set them as inputs' shape before calling nnfw_prepare()
  RUN,     // read shapes in h5 file and set them as inputs' shape before calling nnfw_run()
};
#endif

class Args
{
public:
  Args(const int argc, char **argv);
  void print(void);

  const std::string &getPackageFilename(void) const { return _package_filename; }
  const std::string &getModelFilename(void) const { return _model_filename; }
  bool useSingleModel(void) const { return _use_single_model; }
#if defined(ONERT_HAVE_HDF5) && ONERT_HAVE_HDF5 == 1
  const std::string &getDumpFilename(void) const { return _dump_filename; }
  const std::string &getLoadFilename(void) const { return _load_filename; }
  WhenToUseH5Shape getWhenToUseH5Shape(void) const { return _when_to_use_h5_shape; }
#endif
  const std::string &getDumpRawFilename(void) const { return _dump_raw_filename; }
  const std::string &getDumpRawInputFilename(void) const { return _dump_raw_input_filename; }
  const std::string &getLoadRawFilename(void) const { return _load_raw_filename; }
  int32_t getNumRuns(void) const { return _num_runs; }
  bool getFixedInput(void) const { return _fixed_input; }
  bool getForceFloat(void) const { return _force_float; }
  int32_t getWarmupRuns(void) const { return _warmup_runs; }
  int32_t getMinmaxRuns(void) const { return _minmax_runs; }
  int32_t getRunDelay(void) const { return _run_delay; }
  std::unordered_map<uint32_t, uint32_t> getOutputSizes(void) const { return _output_sizes; }
  bool getGpuMemoryPoll(void) const { return _gpumem_poll; }
  bool getMemoryPoll(void) const { return _mem_poll; }
  bool getWriteReport(void) const { return _write_report; }
  bool printVersion(void) const { return _print_version; }
  TensorShapeMap &getShapeMapForPrepare() { return _shape_prepare; }
  TensorShapeMap &getShapeMapForRun() { return _shape_run; }
  TensorShapeMap &getOutputShapeMap() { return _output_shape; }
  /// @brief Return true if "--shape_run" or "--shape_prepare" is provided
  bool shapeParamProvided();
  int32_t getVerboseLevel(void) const { return _verbose_level; }
  const std::string &getQuantize(void) const { return _quantize; }
  const std::string &getQuantizedModelPath(void) const { return _quantized_model_path; }
  const std::string &getCodegen(void) const { return _codegen; }
  const std::string &getCodegenModelPath(void) const { return _codegen_model_path; }

private:
  void Initialize();
  void Parse(const int argc, char **argv);

private:
  arser::Arser _arser;

  std::string _package_filename;
  std::string _model_filename;
#if defined(ONERT_HAVE_HDF5) && ONERT_HAVE_HDF5 == 1
  std::string _dump_filename;
  std::string _load_filename;
  WhenToUseH5Shape _when_to_use_h5_shape = WhenToUseH5Shape::NOT_PROVIDED;
#endif
  std::string _dump_raw_filename;
  std::string _dump_raw_input_filename;
  std::string _load_raw_filename;
  TensorShapeMap _shape_prepare;
  TensorShapeMap _shape_run;
  TensorShapeMap _output_shape;
  int32_t _num_runs;
  bool _fixed_input = false;
  bool _force_float = false;
  int32_t _warmup_runs;
  int32_t _minmax_runs;
  int32_t _run_delay;
  std::unordered_map<uint32_t, uint32_t> _output_sizes;
  bool _gpumem_poll;
  bool _mem_poll;
  bool _write_report;
  bool _print_version = false;
  int32_t _verbose_level;
  bool _use_single_model = false;
  std::string _quantize;
  std::string _quantized_model_path;
  std::string _codegen;
  std::string _codegen_model_path;
};

} // end of namespace onert_run

#endif // __ONERT_RUN_ARGS_H__
