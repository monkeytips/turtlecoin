//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include "monitoring/instrumented_mutex.h"
#include "monitoring/perf_context_imp.h"
#include "monitoring/thread_status_util.h"
#include "util/sync_point.h"

namespace rocksdb {
namespace {
<<<<<<< HEAD
Statistics* stats_for_report(Env* env, Statistics* stats) {
  if (env != nullptr && stats != nullptr &&
      stats->stats_level_ > kExceptTimeForMutex) {
    return stats;
  } else {
    return nullptr;
  }
=======
bool ShouldReportToStats(Env* env, Statistics* stats) {
  return env != nullptr && stats != nullptr &&
          stats->stats_level_ > kExceptTimeForMutex;
>>>>>>> blood in blood out
}
}  // namespace

void InstrumentedMutex::Lock() {
<<<<<<< HEAD
  PERF_CONDITIONAL_TIMER_FOR_MUTEX_GUARD(
      db_mutex_lock_nanos, stats_code_ == DB_MUTEX_WAIT_MICROS,
      stats_for_report(env_, stats_), stats_code_);
  LockInternal();
=======
  PERF_CONDITIONAL_TIMER_FOR_MUTEX_GUARD(db_mutex_lock_nanos,
                                         stats_code_ == DB_MUTEX_WAIT_MICROS);
  uint64_t wait_time_micros = 0;
  if (ShouldReportToStats(env_, stats_)) {
    {
      StopWatch sw(env_, nullptr, 0, &wait_time_micros);
      LockInternal();
    }
    RecordTick(stats_, stats_code_, wait_time_micros);
  } else {
    LockInternal();
  }
>>>>>>> blood in blood out
}

void InstrumentedMutex::LockInternal() {
#ifndef NDEBUG
  ThreadStatusUtil::TEST_StateDelay(ThreadStatus::STATE_MUTEX_WAIT);
#endif
  mutex_.Lock();
}

void InstrumentedCondVar::Wait() {
<<<<<<< HEAD
  PERF_CONDITIONAL_TIMER_FOR_MUTEX_GUARD(
      db_condition_wait_nanos, stats_code_ == DB_MUTEX_WAIT_MICROS,
      stats_for_report(env_, stats_), stats_code_);
  WaitInternal();
=======
  PERF_CONDITIONAL_TIMER_FOR_MUTEX_GUARD(db_condition_wait_nanos,
                                         stats_code_ == DB_MUTEX_WAIT_MICROS);
  uint64_t wait_time_micros = 0;
  if (ShouldReportToStats(env_, stats_)) {
    {
      StopWatch sw(env_, nullptr, 0, &wait_time_micros);
      WaitInternal();
    }
    RecordTick(stats_, stats_code_, wait_time_micros);
  } else {
    WaitInternal();
  }
>>>>>>> blood in blood out
}

void InstrumentedCondVar::WaitInternal() {
#ifndef NDEBUG
  ThreadStatusUtil::TEST_StateDelay(ThreadStatus::STATE_MUTEX_WAIT);
#endif
  cond_.Wait();
}

bool InstrumentedCondVar::TimedWait(uint64_t abs_time_us) {
<<<<<<< HEAD
  PERF_CONDITIONAL_TIMER_FOR_MUTEX_GUARD(
      db_condition_wait_nanos, stats_code_ == DB_MUTEX_WAIT_MICROS,
      stats_for_report(env_, stats_), stats_code_);
  return TimedWaitInternal(abs_time_us);
=======
  PERF_CONDITIONAL_TIMER_FOR_MUTEX_GUARD(db_condition_wait_nanos,
                                         stats_code_ == DB_MUTEX_WAIT_MICROS);
  uint64_t wait_time_micros = 0;
  bool result = false;
  if (ShouldReportToStats(env_, stats_)) {
    {
      StopWatch sw(env_, nullptr, 0, &wait_time_micros);
      result = TimedWaitInternal(abs_time_us);
    }
    RecordTick(stats_, stats_code_, wait_time_micros);
  } else {
    result = TimedWaitInternal(abs_time_us);
  }
  return result;
>>>>>>> blood in blood out
}

bool InstrumentedCondVar::TimedWaitInternal(uint64_t abs_time_us) {
#ifndef NDEBUG
  ThreadStatusUtil::TEST_StateDelay(ThreadStatus::STATE_MUTEX_WAIT);
#endif

  TEST_SYNC_POINT_CALLBACK("InstrumentedCondVar::TimedWaitInternal",
                           &abs_time_us);

  return cond_.TimedWait(abs_time_us);
}

}  // namespace rocksdb
