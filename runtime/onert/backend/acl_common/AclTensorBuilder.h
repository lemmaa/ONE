/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ONERT_BACKEND_ACL_COMMON_TEMPL_TENSOR_BUILDER_H__
#define __ONERT_BACKEND_ACL_COMMON_TEMPL_TENSOR_BUILDER_H__

#include "AclTensorManager.h"
#include "AclTensorRegistry.h"

#include <cl_common/LifetimeMap.h>
#include <cl_common/ParentInfo.h>

#include <ir/OperandIndexMap.h>
#include <ir/Operands.h>
#include <util/Utils.h>

#include <arm_compute/core/Types.h>

#include <memory>
#include <queue>

namespace onert::backend::acl_common
{

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor> class AclTensorBuilder
{
public:
  using T_AclTensorManager = AclTensorManager<T_ITensor, T_Tensor, T_SubTensor>;
  // TODO Remove this alias and direct usage of this type
  using UsesType = cl_common::UsesType;

  AclTensorBuilder(const ir::Operands &operands, T_AclTensorManager *tensor_mgr);

  /**
   * @brief     Register tensor information to allocate on ACL-CL backend
   * @param[in] ind    Operand index
   * @param[in] info   Tensor information
   * @param[in] layout Tensor data layout
   */
  void registerTensorInfo(const ir::OperandIndex &ind, const ir::OperandInfo &info);

  void notifyFirstUse(const ir::OperandIndex &);
  void notifyLastUse(const ir::OperandIndex &);

  bool isRegistered(const ir::OperandIndex &) const;

  void prepare(void);
  void allocate();
  void postFunctionPrepare();

  T_AclTensorManager *acl_tensor_manager(void) { return _tensor_mgr.get(); }

  void setUsesCount(const ir::OperandIndex &index, size_t num_uses)
  {
    assert(_uses_count_map.find(index) != _uses_count_map.end() ? _uses_count_map[index] == num_uses
                                                                : true);
    _uses_count_map[index] = num_uses;
  }

  void parent_map(std::unordered_map<ir::OperandIndex, cl_common::ParentInfo> &&parent_map)
  {
    _parent_map = std::move(parent_map);
  }

  bool areSubTensorsOf(const ir::OperandIndex &parent, const ir::OperandIndexSequence &seq);

  /**
   * @brief     Check child tensor is allocated as subtensor of parent tensor
   * @param[in] parent  Index of parent
   * @param[in] child   Index of child
   * @return    @c true if child is allocated as subtensor of parent, otherwise @c false
   */
  bool isSubTensorOf(const ir::OperandIndex &parent, const ir::OperandIndex &child);

private:
  void buildTensors(void);
  ir::OperandIndex findRootParent(ir::OperandIndex index);

private:
  const ir::Operands &_operands;
  ir::OperandIndexMap<ir::OperandInfo> _tensor_info_map;
  ir::OperandIndexMap<size_t> _uses_count_map;

  std::unique_ptr<T_AclTensorManager> _tensor_mgr;

  // for linear executor
  cl_common::LifetimeSeq _lifetime_seq;

  // Extra info for concat elimination
  ir::OperandIndexMap<cl_common::ParentInfo> _parent_map;
};

} // namespace onert::backend::acl_common

#include <cassert>
#include <stack>

#include "Convert.h"

#include "util/logging.h"

namespace onert::backend::acl_common
{

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::AclTensorBuilder(const ir::Operands &operands,
                                                                     T_AclTensorManager *tensor_mgr)
  : _operands{operands}, _tensor_mgr{tensor_mgr}
{
  assert(_tensor_mgr);
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::registerTensorInfo(
  const ir::OperandIndex &ind, const ir::OperandInfo &info)
{
  assert(_tensor_mgr->constTensors().size() == 0);
  assert(_tensor_mgr->nonconstTensors().size() == 0);

  _uses_count_map[ind] = _operands.at(ind).getUses().size();

  // SubTensors
  assert((_parent_map.count(ind) == 0 || !info.isConstant()) &&
         "Subtensors of constants are not supported yet.");

  _tensor_info_map.emplace(ind, info);
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::notifyFirstUse(const ir::OperandIndex &ind)
{
  _lifetime_seq.emplace_back(UsesType::FIRST, ind);
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::notifyLastUse(const ir::OperandIndex &ind)
{
  _lifetime_seq.emplace_back(UsesType::LAST, ind);
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
bool AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::isRegistered(
  const ir::OperandIndex &ind) const
{
  return _tensor_info_map.find(ind) != _tensor_info_map.end();
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::prepare(void)
{
  buildTensors();
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::allocate(void)
{
  auto lifetime_map = cl_common::createLifetimeMap(_lifetime_seq, _parent_map);

  for (const auto &entry : lifetime_map)
  {
    const auto &[use_type, use_index] = entry.second;
    assert(use_index.valid());
    if (use_type == UsesType::FIRST)
      _tensor_mgr->startLifetime(use_index);
    else
      _tensor_mgr->finishLifetime(use_index);
  }

  _tensor_mgr->allocateConsts();

  // TODO Since `_parent_map` is filled for all Concat nodes even if the node this backend uses
  //      After refactoring BackendContext we can uncomment this
  // assert(_tensor_info_map.size() ==
  //       _tensor_mgr->nonconstTensors().size() + num of constants of _tensor_info_map +
  //       _parent_map.size());
  _tensor_mgr->allocateNonconsts();

  _tensor_mgr->allocateInternalBufferManager();
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::postFunctionPrepare(void)
{
  _tensor_mgr->tryDeallocConstants();
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
void AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::buildTensors(void)
{
  assert(_tensor_mgr->constTensors().size() == 0);
  assert(_tensor_mgr->nonconstTensors().size() == 0);

  // Normal tensors
  for (const auto &[ind, info] : _tensor_info_map)
  {
    if (_parent_map.count(ind) > 0)
      continue;

    auto tensor_info = asTensorInfo(info.shape(), info.typeInfo(), true);
    _tensor_mgr->buildTensor(ind, tensor_info, info.shape().rank(), info.isConstant(),
                             _uses_count_map[ind]);
  }

  // Subtensors
  assert(_tensor_mgr->nonconstSubtensors().size() == 0);
  // TODO Iterate `_parent_map` instead, once the optimizer bug is fixed
  //      `Optimizer` iterates the entire Operations, so there is a bug if iterating _parent_map
  for (const auto &entry : _tensor_info_map)
  {
    const auto &ind = entry.first;
    if (_parent_map.count(ind) == 0)
      continue;

    // To make subtensor, parent tensor must be made first
    // For this condition, use stack
    //  1) Push one subtensor index to stack (iterate subtensors)
    //  2) If tensor at stack top is already made, pop and go to 4)
    //  3) If tensor pushed at 1) is not made, check parent tensor
    //    3-1) If parent tensor is already made, we can make child tensor
    //         Make child tensor and pop, go to 4)
    //    3-2) If parent tensor is not made, we can't make child tensor yet
    //         Push parent tensor index to stack and return to 4)
    //  4) If stack is empty, return to 1), else return to 2)
    auto &subtensors = _tensor_mgr->nonconstSubtensors();

    std::stack<ir::OperandIndex> stack;
    stack.push(ind);

    while (!stack.empty())
    {
      const auto current = stack.top();
      const auto &tensor_info = _tensor_info_map.at(current);
      const auto &parent_info = _parent_map.at(current);

      // Already generated SubTensor
      if (subtensors.find(current) != subtensors.end())
      {
        stack.pop();
        continue;
      }

      auto parent = parent_info.parent;
      std::shared_ptr<T_ITensor> parent_tensor = _tensor_mgr->findTensorAsParent(parent);
      if (!parent_tensor)
      {
        // Cannot find allocated parent tensor: allocate parent first
        assert(_parent_map.count(parent) > 0);
        stack.push(parent);
        continue;
      }
      assert(parent_tensor != nullptr);

      // Child's type should be same with parent
      assert(tensor_info.typeInfo().zero_point() ==
             parent_tensor->info()->quantization_info().uniform().offset);
      assert(tensor_info.typeInfo().scale() ==
             parent_tensor->info()->quantization_info().uniform().scale);
      assert(tensor_info.typeInfo().type() == parent_tensor->data_type());

      auto shape = asTensorShape(tensor_info.shape(), true);
      ::arm_compute::Coordinates coordinates = asTensorCoordinate(parent_info.coordinates);
      _tensor_mgr->buildSubtensor(parent, current, shape, coordinates, tensor_info.shape().rank(),
                                  true);
      stack.pop();
    }
  }
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
bool AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::areSubTensorsOf(
  const ir::OperandIndex &parent, const ir::OperandIndexSequence &seq)
{
  for (const auto &cand : seq)
  {
    if (!isSubTensorOf(parent, cand))
    {
      return false;
    }
  }
  return true;
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
bool AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::isSubTensorOf(
  const ir::OperandIndex &parent, const ir::OperandIndex &child)
{
  auto itr = _parent_map.find(child);
  if (itr == _parent_map.end())
  {
    return false;
  }

  return itr->second.parent == parent;
}

template <typename T_ITensor, typename T_Tensor, typename T_SubTensor>
ir::OperandIndex
AclTensorBuilder<T_ITensor, T_Tensor, T_SubTensor>::findRootParent(ir::OperandIndex ind)
{
  if (_parent_map.find(ind) == _parent_map.end())
    return ind;

  auto parent_ind = _parent_map.at(ind).parent;
  return findRootParent(parent_ind);
}

} // namespace onert::backend::acl_common

#endif // __ONERT_BACKEND_ACL_COMMON_TEMPL_TENSOR_BUILDER_H__
