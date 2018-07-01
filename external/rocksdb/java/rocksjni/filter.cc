// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ for
// rocksdb::FilterPolicy.

<<<<<<< HEAD
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "include/org_rocksdb_BloomFilter.h"
#include "include/org_rocksdb_Filter.h"
#include "rocksdb/filter_policy.h"
#include "rocksjni/portal.h"
=======
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <string>

#include "include/org_rocksdb_Filter.h"
#include "include/org_rocksdb_BloomFilter.h"
#include "rocksjni/portal.h"
#include "rocksdb/filter_policy.h"
>>>>>>> blood in blood out

/*
 * Class:     org_rocksdb_BloomFilter
 * Method:    createBloomFilter
 * Signature: (IZ)J
 */
jlong Java_org_rocksdb_BloomFilter_createNewBloomFilter(
<<<<<<< HEAD
    JNIEnv* /*env*/, jclass /*jcls*/, jint bits_per_key,
    jboolean use_block_base_builder) {
  auto* sptr_filter = new std::shared_ptr<const rocksdb::FilterPolicy>(
      rocksdb::NewBloomFilterPolicy(bits_per_key, use_block_base_builder));
=======
    JNIEnv* env, jclass jcls, jint bits_per_key,
    jboolean use_block_base_builder) {
  auto* sptr_filter =
      new std::shared_ptr<const rocksdb::FilterPolicy>(
          rocksdb::NewBloomFilterPolicy(bits_per_key, use_block_base_builder));
>>>>>>> blood in blood out
  return reinterpret_cast<jlong>(sptr_filter);
}

/*
 * Class:     org_rocksdb_Filter
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_Filter_disposeInternal(JNIEnv* /*env*/, jobject /*jobj*/,
                                             jlong jhandle) {
  auto* handle =
      reinterpret_cast<std::shared_ptr<const rocksdb::FilterPolicy>*>(jhandle);
=======
void Java_org_rocksdb_Filter_disposeInternal(
    JNIEnv* env, jobject jobj, jlong jhandle) {
  auto* handle =
      reinterpret_cast<std::shared_ptr<const rocksdb::FilterPolicy> *>(jhandle);
>>>>>>> blood in blood out
  delete handle;  // delete std::shared_ptr
}
