//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
#pragma once
#include "monitoring/perf_level_imp.h"
#include "rocksdb/env.h"
#include "util/stop_watch.h"

namespace rocksdb {

class PerfStepTimer {
 public:
<<<<<<< HEAD
  explicit PerfStepTimer(uint64_t* metric, bool for_mutex = false,
                         Statistics* statistics = nullptr,
                         uint32_t ticker_type = 0)
      : perf_counter_enabled_(
            perf_level >= PerfLevel::kEnableTime ||
            (!for_mutex && perf_level >= kEnableTimeExceptForMutex)),
        env_((perf_counter_enabled_ || statistics != nullptr) ? Env::Default()
                                                              : nullptr),
        start_(0),
        metric_(metric),
        statistics_(statistics),
        ticker_type_(ticker_type) {}
=======
  explicit PerfStepTimer(uint64_t* metric, bool for_mutex = false)
      : enabled_(perf_level >= PerfLevel::kEnableTime ||
                 (!for_mutex && perf_level >= kEnableTimeExceptForMutex)),
        env_(enabled_ ? Env::Default() : nullptr),
        start_(0),
        metric_(metric) {}
>>>>>>> blood in blood out

  ~PerfStepTimer() {
    Stop();
  }

  void Start() {
<<<<<<< HEAD
    if (perf_counter_enabled_ || statistics_ != nullptr) {
=======
    if (enabled_) {
>>>>>>> blood in blood out
      start_ = env_->NowNanos();
    }
  }

  void Measure() {
    if (start_) {
      uint64_t now = env_->NowNanos();
      *metric_ += now - start_;
      start_ = now;
    }
  }

  void Stop() {
    if (start_) {
<<<<<<< HEAD
      uint64_t duration = env_->NowNanos() - start_;
      if (perf_counter_enabled_) {
        *metric_ += duration;
      }

      if (statistics_ != nullptr) {
        RecordTick(statistics_, ticker_type_, duration);
      }
=======
      *metric_ += env_->NowNanos() - start_;
>>>>>>> blood in blood out
      start_ = 0;
    }
  }

 private:
<<<<<<< HEAD
  const bool perf_counter_enabled_;
  Env* const env_;
  uint64_t start_;
  uint64_t* metric_;
  Statistics* statistics_;
  uint32_t ticker_type_;
=======
  const bool enabled_;
  Env* const env_;
  uint64_t start_;
  uint64_t* metric_;
>>>>>>> blood in blood out
};

}  // namespace rocksdb
