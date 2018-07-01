// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ for MemTables.

<<<<<<< HEAD
#include "include/org_rocksdb_HashLinkedListMemTableConfig.h"
#include "include/org_rocksdb_HashSkipListMemTableConfig.h"
#include "include/org_rocksdb_SkipListMemTableConfig.h"
#include "include/org_rocksdb_VectorMemTableConfig.h"
#include "rocksdb/memtablerep.h"
#include "rocksjni/portal.h"
=======
#include "rocksjni/portal.h"
#include "include/org_rocksdb_HashSkipListMemTableConfig.h"
#include "include/org_rocksdb_HashLinkedListMemTableConfig.h"
#include "include/org_rocksdb_VectorMemTableConfig.h"
#include "include/org_rocksdb_SkipListMemTableConfig.h"
#include "rocksdb/memtablerep.h"
>>>>>>> blood in blood out

/*
 * Class:     org_rocksdb_HashSkipListMemTableConfig
 * Method:    newMemTableFactoryHandle
 * Signature: (JII)J
 */
jlong Java_org_rocksdb_HashSkipListMemTableConfig_newMemTableFactoryHandle(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/, jlong jbucket_count, jint jheight,
    jint jbranching_factor) {
  rocksdb::Status s = rocksdb::check_if_jlong_fits_size_t(jbucket_count);
  if (s.ok()) {
    return reinterpret_cast<jlong>(rocksdb::NewHashSkipListRepFactory(
        static_cast<size_t>(jbucket_count), static_cast<int32_t>(jheight),
=======
    JNIEnv* env, jobject jobj, jlong jbucket_count,
    jint jheight, jint jbranching_factor) {
  rocksdb::Status s = rocksdb::check_if_jlong_fits_size_t(jbucket_count);
  if (s.ok()) {
    return reinterpret_cast<jlong>(rocksdb::NewHashSkipListRepFactory(
        static_cast<size_t>(jbucket_count),
        static_cast<int32_t>(jheight),
>>>>>>> blood in blood out
        static_cast<int32_t>(jbranching_factor)));
  }
  rocksdb::IllegalArgumentExceptionJni::ThrowNew(env, s);
  return 0;
}

/*
 * Class:     org_rocksdb_HashLinkedListMemTableConfig
 * Method:    newMemTableFactoryHandle
 * Signature: (JJIZI)J
 */
jlong Java_org_rocksdb_HashLinkedListMemTableConfig_newMemTableFactoryHandle(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/, jlong jbucket_count,
    jlong jhuge_page_tlb_size, jint jbucket_entries_logging_threshold,
=======
    JNIEnv* env, jobject jobj, jlong jbucket_count, jlong jhuge_page_tlb_size,
    jint jbucket_entries_logging_threshold,
>>>>>>> blood in blood out
    jboolean jif_log_bucket_dist_when_flash, jint jthreshold_use_skiplist) {
  rocksdb::Status statusBucketCount =
      rocksdb::check_if_jlong_fits_size_t(jbucket_count);
  rocksdb::Status statusHugePageTlb =
      rocksdb::check_if_jlong_fits_size_t(jhuge_page_tlb_size);
  if (statusBucketCount.ok() && statusHugePageTlb.ok()) {
    return reinterpret_cast<jlong>(rocksdb::NewHashLinkListRepFactory(
        static_cast<size_t>(jbucket_count),
        static_cast<size_t>(jhuge_page_tlb_size),
        static_cast<int32_t>(jbucket_entries_logging_threshold),
        static_cast<bool>(jif_log_bucket_dist_when_flash),
        static_cast<int32_t>(jthreshold_use_skiplist)));
  }
<<<<<<< HEAD
  rocksdb::IllegalArgumentExceptionJni::ThrowNew(
      env, !statusBucketCount.ok() ? statusBucketCount : statusHugePageTlb);
=======
  rocksdb::IllegalArgumentExceptionJni::ThrowNew(env,
      !statusBucketCount.ok()?statusBucketCount:statusHugePageTlb);
>>>>>>> blood in blood out
  return 0;
}

/*
 * Class:     org_rocksdb_VectorMemTableConfig
 * Method:    newMemTableFactoryHandle
 * Signature: (J)J
 */
jlong Java_org_rocksdb_VectorMemTableConfig_newMemTableFactoryHandle(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/, jlong jreserved_size) {
  rocksdb::Status s = rocksdb::check_if_jlong_fits_size_t(jreserved_size);
  if (s.ok()) {
    return reinterpret_cast<jlong>(
        new rocksdb::VectorRepFactory(static_cast<size_t>(jreserved_size)));
=======
    JNIEnv* env, jobject jobj, jlong jreserved_size) {
  rocksdb::Status s = rocksdb::check_if_jlong_fits_size_t(jreserved_size);
  if (s.ok()) {
    return reinterpret_cast<jlong>(new rocksdb::VectorRepFactory(
        static_cast<size_t>(jreserved_size)));
>>>>>>> blood in blood out
  }
  rocksdb::IllegalArgumentExceptionJni::ThrowNew(env, s);
  return 0;
}

/*
 * Class:     org_rocksdb_SkipListMemTableConfig
 * Method:    newMemTableFactoryHandle0
 * Signature: (J)J
 */
jlong Java_org_rocksdb_SkipListMemTableConfig_newMemTableFactoryHandle0(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/, jlong jlookahead) {
  rocksdb::Status s = rocksdb::check_if_jlong_fits_size_t(jlookahead);
  if (s.ok()) {
    return reinterpret_cast<jlong>(
        new rocksdb::SkipListFactory(static_cast<size_t>(jlookahead)));
=======
    JNIEnv* env, jobject jobj, jlong jlookahead) {
  rocksdb::Status s = rocksdb::check_if_jlong_fits_size_t(jlookahead);
  if (s.ok()) {
    return reinterpret_cast<jlong>(new rocksdb::SkipListFactory(
        static_cast<size_t>(jlookahead)));
>>>>>>> blood in blood out
  }
  rocksdb::IllegalArgumentExceptionJni::ThrowNew(env, s);
  return 0;
}
