//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include "table/partitioned_filter_block.h"

<<<<<<< HEAD
#ifdef ROCKSDB_MALLOC_USABLE_SIZE
#ifdef OS_FREEBSD
#include <malloc_np.h>
#else
#include <malloc.h>
#endif
#endif
=======
>>>>>>> blood in blood out
#include <utility>

#include "monitoring/perf_context_imp.h"
#include "port/port.h"
#include "rocksdb/filter_policy.h"
#include "table/block.h"
#include "table/block_based_table_reader.h"
#include "util/coding.h"

namespace rocksdb {

PartitionedFilterBlockBuilder::PartitionedFilterBlockBuilder(
    const SliceTransform* prefix_extractor, bool whole_key_filtering,
    FilterBitsBuilder* filter_bits_builder, int index_block_restart_interval,
    PartitionedIndexBuilder* const p_index_builder,
    const uint32_t partition_size)
    : FullFilterBlockBuilder(prefix_extractor, whole_key_filtering,
                             filter_bits_builder),
      index_on_filter_block_builder_(index_block_restart_interval),
<<<<<<< HEAD
      index_on_filter_block_builder_without_seq_(index_block_restart_interval),
      p_index_builder_(p_index_builder),
      filters_in_partition_(0),
      num_added_(0) {
=======
      p_index_builder_(p_index_builder),
      filters_in_partition_(0) {
>>>>>>> blood in blood out
  filters_per_partition_ =
      filter_bits_builder_->CalculateNumEntry(partition_size);
}

PartitionedFilterBlockBuilder::~PartitionedFilterBlockBuilder() {}

void PartitionedFilterBlockBuilder::MaybeCutAFilterBlock() {
  // Use == to send the request only once
  if (filters_in_partition_ == filters_per_partition_) {
    // Currently only index builder is in charge of cutting a partition. We keep
    // requesting until it is granted.
    p_index_builder_->RequestPartitionCut();
  }
  if (!p_index_builder_->ShouldCutFilterBlock()) {
    return;
  }
  filter_gc.push_back(std::unique_ptr<const char[]>(nullptr));
  Slice filter = filter_bits_builder_->Finish(&filter_gc.back());
  std::string& index_key = p_index_builder_->GetPartitionKey();
  filters.push_back({index_key, filter});
  filters_in_partition_ = 0;
<<<<<<< HEAD
  Reset();
=======
>>>>>>> blood in blood out
}

void PartitionedFilterBlockBuilder::AddKey(const Slice& key) {
  MaybeCutAFilterBlock();
  filter_bits_builder_->AddKey(key);
  filters_in_partition_++;
<<<<<<< HEAD
  num_added_++;
=======
>>>>>>> blood in blood out
}

Slice PartitionedFilterBlockBuilder::Finish(
    const BlockHandle& last_partition_block_handle, Status* status) {
  if (finishing_filters == true) {
    // Record the handle of the last written filter block in the index
    FilterEntry& last_entry = filters.front();
    std::string handle_encoding;
    last_partition_block_handle.EncodeTo(&handle_encoding);
    index_on_filter_block_builder_.Add(last_entry.key, handle_encoding);
<<<<<<< HEAD
    if (!p_index_builder_->seperator_is_key_plus_seq()) {
      index_on_filter_block_builder_without_seq_.Add(
          ExtractUserKey(last_entry.key), handle_encoding);
    }
=======
>>>>>>> blood in blood out
    filters.pop_front();
  } else {
    MaybeCutAFilterBlock();
  }
  // If there is no filter partition left, then return the index on filter
  // partitions
  if (UNLIKELY(filters.empty())) {
    *status = Status::OK();
    if (finishing_filters) {
<<<<<<< HEAD
      if (p_index_builder_->seperator_is_key_plus_seq()) {
        return index_on_filter_block_builder_.Finish();
      } else {
        return index_on_filter_block_builder_without_seq_.Finish();
      }
=======
      return index_on_filter_block_builder_.Finish();
>>>>>>> blood in blood out
    } else {
      // This is the rare case where no key was added to the filter
      return Slice();
    }
  } else {
    // Return the next filter partition in line and set Incomplete() status to
    // indicate we expect more calls to Finish
    *status = Status::Incomplete();
    finishing_filters = true;
    return filters.front().filter;
  }
}

PartitionedFilterBlockReader::PartitionedFilterBlockReader(
    const SliceTransform* prefix_extractor, bool _whole_key_filtering,
<<<<<<< HEAD
    BlockContents&& contents, FilterBitsReader* /*filter_bits_reader*/,
    Statistics* stats, const InternalKeyComparator comparator,
    const BlockBasedTable* table, const bool index_key_includes_seq)
    : FilterBlockReader(contents.data.size(), stats, _whole_key_filtering),
      prefix_extractor_(prefix_extractor),
      comparator_(comparator),
      table_(table),
      index_key_includes_seq_(index_key_includes_seq) {
=======
    BlockContents&& contents, FilterBitsReader* filter_bits_reader,
    Statistics* stats, const Comparator& comparator,
    const BlockBasedTable* table)
    : FilterBlockReader(contents.data.size(), stats, _whole_key_filtering),
      prefix_extractor_(prefix_extractor),
      comparator_(comparator),
      table_(table) {
>>>>>>> blood in blood out
  idx_on_fltr_blk_.reset(new Block(std::move(contents),
                                   kDisableGlobalSequenceNumber,
                                   0 /* read_amp_bytes_per_bit */, stats));
}

PartitionedFilterBlockReader::~PartitionedFilterBlockReader() {
  // TODO(myabandeh): if instead of filter object we store only the blocks in
  // block cache, then we don't have to manually earse them from block cache
  // here.
  auto block_cache = table_->rep_->table_options.block_cache.get();
  if (UNLIKELY(block_cache == nullptr)) {
    return;
  }
  char cache_key[BlockBasedTable::kMaxCacheKeyPrefixSize + kMaxVarint64Length];
<<<<<<< HEAD
  IndexBlockIter biter;
  BlockHandle handle;
  Statistics* kNullStats = nullptr;
  idx_on_fltr_blk_->NewIterator<IndexBlockIter>(
      &comparator_, comparator_.user_comparator(), &biter, kNullStats, true,
      index_key_includes_seq_);
=======
  BlockIter biter;
  BlockHandle handle;
  idx_on_fltr_blk_->NewIterator(&comparator_, &biter, true);
>>>>>>> blood in blood out
  biter.SeekToFirst();
  for (; biter.Valid(); biter.Next()) {
    auto input = biter.value();
    auto s = handle.DecodeFrom(&input);
    assert(s.ok());
    if (!s.ok()) {
      continue;
    }
    auto key = BlockBasedTable::GetCacheKey(table_->rep_->cache_key_prefix,
                                            table_->rep_->cache_key_prefix_size,
                                            handle, cache_key);
    block_cache->Erase(key);
  }
}

bool PartitionedFilterBlockReader::KeyMayMatch(
<<<<<<< HEAD
    const Slice& key, const SliceTransform* prefix_extractor,
    uint64_t block_offset, const bool no_io,
=======
    const Slice& key, uint64_t block_offset, const bool no_io,
>>>>>>> blood in blood out
    const Slice* const const_ikey_ptr) {
  assert(const_ikey_ptr != nullptr);
  assert(block_offset == kNotValid);
  if (!whole_key_filtering_) {
    return true;
  }
  if (UNLIKELY(idx_on_fltr_blk_->size() == 0)) {
    return true;
  }
  auto filter_handle = GetFilterPartitionHandle(*const_ikey_ptr);
  if (UNLIKELY(filter_handle.size() == 0)) {  // key is out of range
    return false;
  }
  bool cached = false;
<<<<<<< HEAD
  auto filter_partition =
      GetFilterPartition(nullptr /* prefetch_buffer */, &filter_handle, no_io,
                         &cached, prefix_extractor);
  if (UNLIKELY(!filter_partition.value)) {
    return true;
  }
  auto res = filter_partition.value->KeyMayMatch(key, prefix_extractor,
                                                 block_offset, no_io);
=======
  auto filter_partition = GetFilterPartition(nullptr /* prefetch_buffer */,
                                             &filter_handle, no_io, &cached);
  if (UNLIKELY(!filter_partition.value)) {
    return true;
  }
  auto res = filter_partition.value->KeyMayMatch(key, block_offset, no_io);
>>>>>>> blood in blood out
  if (cached) {
    return res;
  }
  if (LIKELY(filter_partition.IsSet())) {
    filter_partition.Release(table_->rep_->table_options.block_cache.get());
  } else {
    delete filter_partition.value;
  }
  return res;
}

bool PartitionedFilterBlockReader::PrefixMayMatch(
<<<<<<< HEAD
    const Slice& prefix, const SliceTransform* prefix_extractor,
    uint64_t block_offset, const bool no_io,
    const Slice* const const_ikey_ptr) {
#ifdef NDEBUG
  (void)block_offset;
#endif
  assert(const_ikey_ptr != nullptr);
  assert(block_offset == kNotValid);
  if (!prefix_extractor_ && !prefix_extractor) {
=======
    const Slice& prefix, uint64_t block_offset, const bool no_io,
    const Slice* const const_ikey_ptr) {
  assert(const_ikey_ptr != nullptr);
  assert(block_offset == kNotValid);
  if (!prefix_extractor_) {
>>>>>>> blood in blood out
    return true;
  }
  if (UNLIKELY(idx_on_fltr_blk_->size() == 0)) {
    return true;
  }
  auto filter_handle = GetFilterPartitionHandle(*const_ikey_ptr);
  if (UNLIKELY(filter_handle.size() == 0)) {  // prefix is out of range
    return false;
  }
  bool cached = false;
<<<<<<< HEAD
  auto filter_partition =
      GetFilterPartition(nullptr /* prefetch_buffer */, &filter_handle, no_io,
                         &cached, prefix_extractor);
  if (UNLIKELY(!filter_partition.value)) {
    return true;
  }
  auto res = filter_partition.value->PrefixMayMatch(prefix, prefix_extractor,
                                                    kNotValid, no_io);
=======
  auto filter_partition = GetFilterPartition(nullptr /* prefetch_buffer */,
                                             &filter_handle, no_io, &cached);
  if (UNLIKELY(!filter_partition.value)) {
    return true;
  }
  auto res = filter_partition.value->PrefixMayMatch(prefix, kNotValid, no_io);
>>>>>>> blood in blood out
  if (cached) {
    return res;
  }
  if (LIKELY(filter_partition.IsSet())) {
    filter_partition.Release(table_->rep_->table_options.block_cache.get());
  } else {
    delete filter_partition.value;
  }
  return res;
}

Slice PartitionedFilterBlockReader::GetFilterPartitionHandle(
    const Slice& entry) {
<<<<<<< HEAD
  IndexBlockIter iter;
  Statistics* kNullStats = nullptr;
  idx_on_fltr_blk_->NewIterator<IndexBlockIter>(
      &comparator_, comparator_.user_comparator(), &iter, kNullStats, true,
      index_key_includes_seq_);
=======
  BlockIter iter;
  idx_on_fltr_blk_->NewIterator(&comparator_, &iter, true);
>>>>>>> blood in blood out
  iter.Seek(entry);
  if (UNLIKELY(!iter.Valid())) {
    return Slice();
  }
  assert(iter.Valid());
  Slice handle_value = iter.value();
  return handle_value;
}

BlockBasedTable::CachableEntry<FilterBlockReader>
PartitionedFilterBlockReader::GetFilterPartition(
    FilePrefetchBuffer* prefetch_buffer, Slice* handle_value, const bool no_io,
<<<<<<< HEAD
    bool* cached, const SliceTransform* prefix_extractor) {
=======
    bool* cached) {
>>>>>>> blood in blood out
  BlockHandle fltr_blk_handle;
  auto s = fltr_blk_handle.DecodeFrom(handle_value);
  assert(s.ok());
  const bool is_a_filter_partition = true;
  auto block_cache = table_->rep_->table_options.block_cache.get();
  if (LIKELY(block_cache != nullptr)) {
    if (filter_map_.size() != 0) {
      auto iter = filter_map_.find(fltr_blk_handle.offset());
      // This is a possible scenario since block cache might not have had space
      // for the partition
      if (iter != filter_map_.end()) {
        PERF_COUNTER_ADD(block_cache_hit_count, 1);
        RecordTick(statistics(), BLOCK_CACHE_FILTER_HIT);
        RecordTick(statistics(), BLOCK_CACHE_HIT);
        RecordTick(statistics(), BLOCK_CACHE_BYTES_READ,
                   block_cache->GetUsage(iter->second.cache_handle));
        *cached = true;
        return iter->second;
      }
    }
    return table_->GetFilter(/*prefetch_buffer*/ nullptr, fltr_blk_handle,
                             is_a_filter_partition, no_io,
<<<<<<< HEAD
                             /* get_context */ nullptr, prefix_extractor);
  } else {
    auto filter = table_->ReadFilter(prefetch_buffer, fltr_blk_handle,
                                     is_a_filter_partition, prefix_extractor);
=======
                             /* get_context */ nullptr);
  } else {
    auto filter = table_->ReadFilter(prefetch_buffer, fltr_blk_handle,
                                     is_a_filter_partition);
>>>>>>> blood in blood out
    return {filter, nullptr};
  }
}

size_t PartitionedFilterBlockReader::ApproximateMemoryUsage() const {
<<<<<<< HEAD
  size_t usage = idx_on_fltr_blk_->usable_size();
#ifdef ROCKSDB_MALLOC_USABLE_SIZE
  usage += malloc_usable_size((void*)this);
#else
  usage += sizeof(*this);
#endif  // ROCKSDB_MALLOC_USABLE_SIZE
  return usage;
  // TODO(myabandeh): better estimation for filter_map_ size
}

// Release the cached entry and decrement its ref count.
void ReleaseFilterCachedEntry(void* arg, void* h) {
  Cache* cache = reinterpret_cast<Cache*>(arg);
  Cache::Handle* handle = reinterpret_cast<Cache::Handle*>(h);
  cache->Release(handle);
}

// TODO(myabandeh): merge this with the same function in IndexReader
void PartitionedFilterBlockReader::CacheDependencies(
    bool pin, const SliceTransform* prefix_extractor) {
  // Before read partitions, prefetch them to avoid lots of IOs
  auto rep = table_->rep_;
  IndexBlockIter biter;
  BlockHandle handle;
  Statistics* kNullStats = nullptr;
  idx_on_fltr_blk_->NewIterator<IndexBlockIter>(
      &comparator_, comparator_.user_comparator(), &biter, kNullStats, true,
      index_key_includes_seq_);
=======
  return idx_on_fltr_blk_->size();
}

// TODO(myabandeh): merge this with the same function in IndexReader
void PartitionedFilterBlockReader::CacheDependencies(bool pin) {
  // Before read partitions, prefetch them to avoid lots of IOs
  auto rep = table_->rep_;
  BlockIter biter;
  BlockHandle handle;
  idx_on_fltr_blk_->NewIterator(&comparator_, &biter, true);
>>>>>>> blood in blood out
  // Index partitions are assumed to be consecuitive. Prefetch them all.
  // Read the first block offset
  biter.SeekToFirst();
  Slice input = biter.value();
  Status s = handle.DecodeFrom(&input);
  assert(s.ok());
  if (!s.ok()) {
    ROCKS_LOG_WARN(rep->ioptions.info_log,
                   "Could not read first index partition");
    return;
  }
  uint64_t prefetch_off = handle.offset();

  // Read the last block's offset
  biter.SeekToLast();
  input = biter.value();
  s = handle.DecodeFrom(&input);
  assert(s.ok());
  if (!s.ok()) {
    ROCKS_LOG_WARN(rep->ioptions.info_log,
                   "Could not read last index partition");
    return;
  }
  uint64_t last_off = handle.offset() + handle.size() + kBlockTrailerSize;
  uint64_t prefetch_len = last_off - prefetch_off;
  std::unique_ptr<FilePrefetchBuffer> prefetch_buffer;
  auto& file = table_->rep_->file;
  prefetch_buffer.reset(new FilePrefetchBuffer());
<<<<<<< HEAD
  s = prefetch_buffer->Prefetch(file.get(), prefetch_off,
    static_cast<size_t>(prefetch_len));
=======
  s = prefetch_buffer->Prefetch(file.get(), prefetch_off, prefetch_len);
>>>>>>> blood in blood out

  // After prefetch, read the partitions one by one
  biter.SeekToFirst();
  Cache* block_cache = rep->table_options.block_cache.get();
  for (; biter.Valid(); biter.Next()) {
    input = biter.value();
    s = handle.DecodeFrom(&input);
    assert(s.ok());
    if (!s.ok()) {
      ROCKS_LOG_WARN(rep->ioptions.info_log, "Could not read index partition");
      continue;
    }

    const bool no_io = true;
    const bool is_a_filter_partition = true;
<<<<<<< HEAD
    auto filter = table_->GetFilter(
        prefetch_buffer.get(), handle, is_a_filter_partition, !no_io,
        /* get_context */ nullptr, prefix_extractor);
    if (LIKELY(filter.IsSet())) {
      if (pin) {
        filter_map_[handle.offset()] = std::move(filter);
        RegisterCleanup(&ReleaseFilterCachedEntry, block_cache,
                        filter.cache_handle);
=======
    auto filter = table_->GetFilter(prefetch_buffer.get(), handle,
                                    is_a_filter_partition, !no_io,
                                    /* get_context */ nullptr);
    if (LIKELY(filter.IsSet())) {
      if (pin) {
        filter_map_[handle.offset()] = std::move(filter);
>>>>>>> blood in blood out
      } else {
        block_cache->Release(filter.cache_handle);
      }
    } else {
      delete filter.value;
    }
  }
}

}  // namespace rocksdb
