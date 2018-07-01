// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ for
// rocksdb::CompactionFilter.

#include <jni.h>

#include "include/org_rocksdb_AbstractCompactionFilter.h"
#include "rocksdb/compaction_filter.h"

// <editor-fold desc="org.rocksdb.AbstractCompactionFilter">

/*
 * Class:     org_rocksdb_AbstractCompactionFilter
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_AbstractCompactionFilter_disposeInternal(JNIEnv* /*env*/,
                                                               jobject /*jobj*/,
                                                               jlong handle) {
=======
void Java_org_rocksdb_AbstractCompactionFilter_disposeInternal(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  auto* cf = reinterpret_cast<rocksdb::CompactionFilter*>(handle);
  assert(cf != nullptr);
  delete cf;
}
// </editor-fold>
