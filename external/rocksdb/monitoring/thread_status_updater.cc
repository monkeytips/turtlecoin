// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include "monitoring/thread_status_updater.h"
#include <memory>
#include "port/likely.h"
#include "rocksdb/env.h"
#include "util/mutexlock.h"

namespace rocksdb {

#ifdef ROCKSDB_USING_THREAD_STATUS

__thread ThreadStatusData* ThreadStatusUpdater::thread_status_data_ = nullptr;

<<<<<<< HEAD
void ThreadStatusUpdater::RegisterThread(ThreadStatus::ThreadType ttype,
                                         uint64_t thread_id) {
=======
void ThreadStatusUpdater::RegisterThread(
    ThreadStatus::ThreadType ttype, uint64_t thread_id) {
>>>>>>> blood in blood out
  if (UNLIKELY(thread_status_data_ == nullptr)) {
    thread_status_data_ = new ThreadStatusData();
    thread_status_data_->thread_type = ttype;
    thread_status_data_->thread_id = thread_id;
    std::lock_guard<std::mutex> lck(thread_list_mutex_);
    thread_data_set_.insert(thread_status_data_);
  }

  ClearThreadOperationProperties();
}

void ThreadStatusUpdater::UnregisterThread() {
  if (thread_status_data_ != nullptr) {
    std::lock_guard<std::mutex> lck(thread_list_mutex_);
    thread_data_set_.erase(thread_status_data_);
    delete thread_status_data_;
    thread_status_data_ = nullptr;
  }
}

void ThreadStatusUpdater::ResetThreadStatus() {
  ClearThreadState();
  ClearThreadOperation();
  SetColumnFamilyInfoKey(nullptr);
}

<<<<<<< HEAD
void ThreadStatusUpdater::SetColumnFamilyInfoKey(const void* cf_key) {
=======
void ThreadStatusUpdater::SetColumnFamilyInfoKey(
    const void* cf_key) {
>>>>>>> blood in blood out
  auto* data = Get();
  if (data == nullptr) {
    return;
  }
  // set the tracking flag based on whether cf_key is non-null or not.
  // If enable_thread_tracking is set to false, the input cf_key
  // would be nullptr.
  data->enable_tracking = (cf_key != nullptr);
  data->cf_key.store(const_cast<void*>(cf_key), std::memory_order_relaxed);
}

const void* ThreadStatusUpdater::GetColumnFamilyInfoKey() {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return nullptr;
  }
  return data->cf_key.load(std::memory_order_relaxed);
}

void ThreadStatusUpdater::SetThreadOperation(
    const ThreadStatus::OperationType type) {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  // NOTE: Our practice here is to set all the thread operation properties
  //       and stage before we set thread operation, and thread operation
  //       will be set in std::memory_order_release.  This is to ensure
  //       whenever a thread operation is not OP_UNKNOWN, we will always
  //       have a consistent information on its properties.
  data->operation_type.store(type, std::memory_order_release);
  if (type == ThreadStatus::OP_UNKNOWN) {
    data->operation_stage.store(ThreadStatus::STAGE_UNKNOWN,
<<<<<<< HEAD
                                std::memory_order_relaxed);
=======
        std::memory_order_relaxed);
>>>>>>> blood in blood out
    ClearThreadOperationProperties();
  }
}

<<<<<<< HEAD
void ThreadStatusUpdater::SetThreadOperationProperty(int i, uint64_t value) {
=======
void ThreadStatusUpdater::SetThreadOperationProperty(
    int i, uint64_t value) {
>>>>>>> blood in blood out
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  data->op_properties[i].store(value, std::memory_order_relaxed);
}

<<<<<<< HEAD
void ThreadStatusUpdater::IncreaseThreadOperationProperty(int i,
                                                          uint64_t delta) {
=======
void ThreadStatusUpdater::IncreaseThreadOperationProperty(
    int i, uint64_t delta) {
>>>>>>> blood in blood out
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  data->op_properties[i].fetch_add(delta, std::memory_order_relaxed);
}

void ThreadStatusUpdater::SetOperationStartTime(const uint64_t start_time) {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  data->op_start_time.store(start_time, std::memory_order_relaxed);
}

void ThreadStatusUpdater::ClearThreadOperation() {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  data->operation_stage.store(ThreadStatus::STAGE_UNKNOWN,
<<<<<<< HEAD
                              std::memory_order_relaxed);
  data->operation_type.store(ThreadStatus::OP_UNKNOWN,
                             std::memory_order_relaxed);
=======
      std::memory_order_relaxed);
  data->operation_type.store(
      ThreadStatus::OP_UNKNOWN, std::memory_order_relaxed);
>>>>>>> blood in blood out
  ClearThreadOperationProperties();
}

void ThreadStatusUpdater::ClearThreadOperationProperties() {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  for (int i = 0; i < ThreadStatus::kNumOperationProperties; ++i) {
    data->op_properties[i].store(0, std::memory_order_relaxed);
  }
}

ThreadStatus::OperationStage ThreadStatusUpdater::SetThreadOperationStage(
    ThreadStatus::OperationStage stage) {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return ThreadStatus::STAGE_UNKNOWN;
  }
<<<<<<< HEAD
  return data->operation_stage.exchange(stage, std::memory_order_relaxed);
}

void ThreadStatusUpdater::SetThreadState(const ThreadStatus::StateType type) {
=======
  return data->operation_stage.exchange(
      stage, std::memory_order_relaxed);
}

void ThreadStatusUpdater::SetThreadState(
    const ThreadStatus::StateType type) {
>>>>>>> blood in blood out
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
  data->state_type.store(type, std::memory_order_relaxed);
}

void ThreadStatusUpdater::ClearThreadState() {
  auto* data = GetLocalThreadStatus();
  if (data == nullptr) {
    return;
  }
<<<<<<< HEAD
  data->state_type.store(ThreadStatus::STATE_UNKNOWN,
                         std::memory_order_relaxed);
=======
  data->state_type.store(
      ThreadStatus::STATE_UNKNOWN, std::memory_order_relaxed);
>>>>>>> blood in blood out
}

Status ThreadStatusUpdater::GetThreadList(
    std::vector<ThreadStatus>* thread_list) {
  thread_list->clear();
  std::vector<std::shared_ptr<ThreadStatusData>> valid_list;
  uint64_t now_micros = Env::Default()->NowMicros();

  std::lock_guard<std::mutex> lck(thread_list_mutex_);
  for (auto* thread_data : thread_data_set_) {
    assert(thread_data);
<<<<<<< HEAD
    auto thread_id = thread_data->thread_id.load(std::memory_order_relaxed);
    auto thread_type = thread_data->thread_type.load(std::memory_order_relaxed);
    // Since any change to cf_info_map requires thread_list_mutex,
    // which is currently held by GetThreadList(), here we can safely
    // use "memory_order_relaxed" to load the cf_key.
    auto cf_key = thread_data->cf_key.load(std::memory_order_relaxed);

=======
    auto thread_id = thread_data->thread_id.load(
        std::memory_order_relaxed);
    auto thread_type = thread_data->thread_type.load(
        std::memory_order_relaxed);
    // Since any change to cf_info_map requires thread_list_mutex,
    // which is currently held by GetThreadList(), here we can safely
    // use "memory_order_relaxed" to load the cf_key.
    auto cf_key = thread_data->cf_key.load(
        std::memory_order_relaxed);
    
>>>>>>> blood in blood out
    ThreadStatus::OperationType op_type = ThreadStatus::OP_UNKNOWN;
    ThreadStatus::OperationStage op_stage = ThreadStatus::STAGE_UNKNOWN;
    ThreadStatus::StateType state_type = ThreadStatus::STATE_UNKNOWN;
    uint64_t op_elapsed_micros = 0;
    uint64_t op_props[ThreadStatus::kNumOperationProperties] = {0};

    auto iter = cf_info_map_.find(cf_key);
    if (iter != cf_info_map_.end()) {
<<<<<<< HEAD
      op_type = thread_data->operation_type.load(std::memory_order_acquire);
      // display lower-level info only when higher-level info is available.
      if (op_type != ThreadStatus::OP_UNKNOWN) {
        op_elapsed_micros = now_micros - thread_data->op_start_time.load(
                                             std::memory_order_relaxed);
        op_stage = thread_data->operation_stage.load(std::memory_order_relaxed);
        state_type = thread_data->state_type.load(std::memory_order_relaxed);
        for (int i = 0; i < ThreadStatus::kNumOperationProperties; ++i) {
          op_props[i] =
              thread_data->op_properties[i].load(std::memory_order_relaxed);
=======
      op_type = thread_data->operation_type.load(
          std::memory_order_acquire);
      // display lower-level info only when higher-level info is available.
      if (op_type != ThreadStatus::OP_UNKNOWN) {
        op_elapsed_micros = now_micros - thread_data->op_start_time.load(
            std::memory_order_relaxed);
        op_stage = thread_data->operation_stage.load(
            std::memory_order_relaxed);
        state_type = thread_data->state_type.load(
            std::memory_order_relaxed);
        for (int i = 0; i < ThreadStatus::kNumOperationProperties; ++i) {
          op_props[i] = thread_data->op_properties[i].load(
              std::memory_order_relaxed);
>>>>>>> blood in blood out
        }
      }
    }

    thread_list->emplace_back(
        thread_id, thread_type,
        iter != cf_info_map_.end() ? iter->second.db_name : "",
<<<<<<< HEAD
        iter != cf_info_map_.end() ? iter->second.cf_name : "", op_type,
        op_elapsed_micros, op_stage, op_props, state_type);
=======
        iter != cf_info_map_.end() ? iter->second.cf_name : "",
        op_type, op_elapsed_micros, op_stage, op_props,
        state_type);
>>>>>>> blood in blood out
  }

  return Status::OK();
}

ThreadStatusData* ThreadStatusUpdater::GetLocalThreadStatus() {
  if (thread_status_data_ == nullptr) {
    return nullptr;
  }
  if (!thread_status_data_->enable_tracking) {
<<<<<<< HEAD
    assert(thread_status_data_->cf_key.load(std::memory_order_relaxed) ==
           nullptr);
=======
    assert(thread_status_data_->cf_key.load(
        std::memory_order_relaxed) == nullptr);
>>>>>>> blood in blood out
    return nullptr;
  }
  return thread_status_data_;
}

<<<<<<< HEAD
void ThreadStatusUpdater::NewColumnFamilyInfo(const void* db_key,
                                              const std::string& db_name,
                                              const void* cf_key,
                                              const std::string& cf_name) {
=======
void ThreadStatusUpdater::NewColumnFamilyInfo(
    const void* db_key, const std::string& db_name,
    const void* cf_key, const std::string& cf_name) {
>>>>>>> blood in blood out
  // Acquiring same lock as GetThreadList() to guarantee
  // a consistent view of global column family table (cf_info_map).
  std::lock_guard<std::mutex> lck(thread_list_mutex_);

<<<<<<< HEAD
  cf_info_map_.emplace(std::piecewise_construct, std::make_tuple(cf_key),
                       std::make_tuple(db_key, db_name, cf_name));
=======
  cf_info_map_.emplace(std::piecewise_construct,
      std::make_tuple(cf_key),
      std::make_tuple(db_key, db_name, cf_name));
>>>>>>> blood in blood out
  db_key_map_[db_key].insert(cf_key);
}

void ThreadStatusUpdater::EraseColumnFamilyInfo(const void* cf_key) {
  // Acquiring same lock as GetThreadList() to guarantee
  // a consistent view of global column family table (cf_info_map).
  std::lock_guard<std::mutex> lck(thread_list_mutex_);
<<<<<<< HEAD

=======
  
>>>>>>> blood in blood out
  auto cf_pair = cf_info_map_.find(cf_key);
  if (cf_pair != cf_info_map_.end()) {
    // Remove its entry from db_key_map_ by the following steps:
    // 1. Obtain the entry in db_key_map_ whose set contains cf_key
    // 2. Remove it from the set.
    ConstantColumnFamilyInfo& cf_info = cf_pair->second;
    auto db_pair = db_key_map_.find(cf_info.db_key);
    assert(db_pair != db_key_map_.end());
    size_t result __attribute__((__unused__));
    result = db_pair->second.erase(cf_key);
    assert(result);
    cf_info_map_.erase(cf_pair);
  }
}

void ThreadStatusUpdater::EraseDatabaseInfo(const void* db_key) {
  // Acquiring same lock as GetThreadList() to guarantee
  // a consistent view of global column family table (cf_info_map).
  std::lock_guard<std::mutex> lck(thread_list_mutex_);
  auto db_pair = db_key_map_.find(db_key);
  if (UNLIKELY(db_pair == db_key_map_.end())) {
    // In some occasional cases such as DB::Open fails, we won't
    // register ColumnFamilyInfo for a db.
    return;
  }

  for (auto cf_key : db_pair->second) {
    auto cf_pair = cf_info_map_.find(cf_key);
    if (cf_pair != cf_info_map_.end()) {
      cf_info_map_.erase(cf_pair);
    }
  }
  db_key_map_.erase(db_key);
}

#else

<<<<<<< HEAD
void ThreadStatusUpdater::RegisterThread(ThreadStatus::ThreadType /*ttype*/,
                                         uint64_t /*thread_id*/) {}

void ThreadStatusUpdater::UnregisterThread() {}

void ThreadStatusUpdater::ResetThreadStatus() {}

void ThreadStatusUpdater::SetColumnFamilyInfoKey(const void* /*cf_key*/) {}

void ThreadStatusUpdater::SetThreadOperation(
    const ThreadStatus::OperationType /*type*/) {}

void ThreadStatusUpdater::ClearThreadOperation() {}

void ThreadStatusUpdater::SetThreadState(
    const ThreadStatus::StateType /*type*/) {}

void ThreadStatusUpdater::ClearThreadState() {}

Status ThreadStatusUpdater::GetThreadList(
    std::vector<ThreadStatus>* /*thread_list*/) {
=======
void ThreadStatusUpdater::RegisterThread(
    ThreadStatus::ThreadType ttype, uint64_t thread_id) {
}

void ThreadStatusUpdater::UnregisterThread() {
}

void ThreadStatusUpdater::ResetThreadStatus() {
}

void ThreadStatusUpdater::SetColumnFamilyInfoKey(
    const void* cf_key) {
}

void ThreadStatusUpdater::SetThreadOperation(
    const ThreadStatus::OperationType type) {
}

void ThreadStatusUpdater::ClearThreadOperation() {
}

void ThreadStatusUpdater::SetThreadState(
    const ThreadStatus::StateType type) {
}

void ThreadStatusUpdater::ClearThreadState() {
}

Status ThreadStatusUpdater::GetThreadList(
    std::vector<ThreadStatus>* thread_list) {
>>>>>>> blood in blood out
  return Status::NotSupported(
      "GetThreadList is not supported in the current running environment.");
}

<<<<<<< HEAD
void ThreadStatusUpdater::NewColumnFamilyInfo(const void* /*db_key*/,
                                              const std::string& /*db_name*/,
                                              const void* /*cf_key*/,
                                              const std::string& /*cf_name*/) {}

void ThreadStatusUpdater::EraseColumnFamilyInfo(const void* /*cf_key*/) {}

void ThreadStatusUpdater::EraseDatabaseInfo(const void* /*db_key*/) {}

void ThreadStatusUpdater::SetThreadOperationProperty(int /*i*/,
                                                     uint64_t /*value*/) {}

void ThreadStatusUpdater::IncreaseThreadOperationProperty(int /*i*/,
                                                          uint64_t /*delta*/) {}
=======
void ThreadStatusUpdater::NewColumnFamilyInfo(
    const void* db_key, const std::string& db_name,
    const void* cf_key, const std::string& cf_name) {
}

void ThreadStatusUpdater::EraseColumnFamilyInfo(const void* cf_key) {
}

void ThreadStatusUpdater::EraseDatabaseInfo(const void* db_key) {
}

void ThreadStatusUpdater::SetThreadOperationProperty(
    int i, uint64_t value) {
}

void ThreadStatusUpdater::IncreaseThreadOperationProperty(
    int i, uint64_t delta) {
}
>>>>>>> blood in blood out

#endif  // ROCKSDB_USING_THREAD_STATUS
}  // namespace rocksdb
