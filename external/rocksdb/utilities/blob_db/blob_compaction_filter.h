//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
#pragma once
#ifndef ROCKSDB_LITE

<<<<<<< HEAD
#include <unordered_set>

#include "monitoring/statistics.h"
#include "rocksdb/compaction_filter.h"
#include "rocksdb/env.h"
#include "utilities/blob_db/blob_db_impl.h"
=======
#include "monitoring/statistics.h"
#include "rocksdb/compaction_filter.h"
#include "rocksdb/env.h"
>>>>>>> blood in blood out
#include "utilities/blob_db/blob_index.h"

namespace rocksdb {
namespace blob_db {

<<<<<<< HEAD
struct BlobCompactionContext {
  uint64_t next_file_number;
  std::unordered_set<uint64_t> current_blob_files;
  SequenceNumber fifo_eviction_seq;
  uint64_t evict_expiration_up_to;
=======
// CompactionFilter to delete expired blob index from base DB.
class BlobIndexCompactionFilter : public CompactionFilter {
 public:
  BlobIndexCompactionFilter(uint64_t current_time, Statistics* statistics)
      : current_time_(current_time), statistics_(statistics) {}

  virtual ~BlobIndexCompactionFilter() {
    RecordTick(statistics_, BLOB_DB_BLOB_INDEX_EXPIRED, expired_count_);
  }

  virtual const char* Name() const override {
    return "BlobIndexCompactionFilter";
  }

  // Filter expired blob indexes regardless of snapshots.
  virtual bool IgnoreSnapshots() const override { return true; }

  virtual Decision FilterV2(int /*level*/, const Slice& /*key*/,
                            ValueType value_type, const Slice& value,
                            std::string* /*new_value*/,
                            std::string* /*skip_until*/) const override {
    if (value_type != kBlobIndex) {
      return Decision::kKeep;
    }
    BlobIndex blob_index;
    Status s = blob_index.DecodeFrom(value);
    if (!s.ok()) {
      // Unable to decode blob index. Keeping the value.
      return Decision::kKeep;
    }
    if (blob_index.HasTTL() && blob_index.expiration() <= current_time_) {
      // Expired
      expired_count_++;
      return Decision::kRemove;
    }
    return Decision::kKeep;
  }

 private:
  const uint64_t current_time_;
  Statistics* statistics_;
  // It is safe to not using std::atomic since the compaction filter, created
  // from a compaction filter factroy, will not be called from multiple threads.
  mutable uint64_t expired_count_ = 0;
>>>>>>> blood in blood out
};

class BlobIndexCompactionFilterFactory : public CompactionFilterFactory {
 public:
<<<<<<< HEAD
  BlobIndexCompactionFilterFactory(BlobDBImpl* blob_db_impl, Env* env,
                                   Statistics* statistics)
      : blob_db_impl_(blob_db_impl), env_(env), statistics_(statistics) {}
=======
  BlobIndexCompactionFilterFactory(Env* env, Statistics* statistics)
      : env_(env), statistics_(statistics) {}
>>>>>>> blood in blood out

  virtual const char* Name() const override {
    return "BlobIndexCompactionFilterFactory";
  }

  virtual std::unique_ptr<CompactionFilter> CreateCompactionFilter(
<<<<<<< HEAD
      const CompactionFilter::Context& /*context*/) override;

 private:
  BlobDBImpl* blob_db_impl_;
=======
      const CompactionFilter::Context& /*context*/) override {
    int64_t current_time = 0;
    Status s = env_->GetCurrentTime(&current_time);
    if (!s.ok()) {
      return nullptr;
    }
    assert(current_time >= 0);
    return std::unique_ptr<CompactionFilter>(new BlobIndexCompactionFilter(
        static_cast<uint64_t>(current_time), statistics_));
  }

 private:
>>>>>>> blood in blood out
  Env* env_;
  Statistics* statistics_;
};

}  // namespace blob_db
}  // namespace rocksdb
#endif  // ROCKSDB_LITE
