// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++
// for rocksdb::OptimisticTransactionOptions.

#include <jni.h>

#include "include/org_rocksdb_OptimisticTransactionOptions.h"

#include "rocksdb/comparator.h"
#include "rocksdb/utilities/optimistic_transaction_db.h"

/*
 * Class:     org_rocksdb_OptimisticTransactionOptions
 * Method:    newOptimisticTransactionOptions
 * Signature: ()J
 */
jlong Java_org_rocksdb_OptimisticTransactionOptions_newOptimisticTransactionOptions(
<<<<<<< HEAD
    JNIEnv* /*env*/, jclass /*jcls*/) {
=======
    JNIEnv* env, jclass jcls) {
>>>>>>> blood in blood out
  rocksdb::OptimisticTransactionOptions* opts =
      new rocksdb::OptimisticTransactionOptions();
  return reinterpret_cast<jlong>(opts);
}

/*
 * Class:     org_rocksdb_OptimisticTransactionOptions
 * Method:    isSetSnapshot
 * Signature: (J)Z
 */
jboolean Java_org_rocksdb_OptimisticTransactionOptions_isSetSnapshot(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts =
      reinterpret_cast<rocksdb::OptimisticTransactionOptions*>(jhandle);
  return opts->set_snapshot;
}

/*
 * Class:     org_rocksdb_OptimisticTransactionOptions
 * Method:    setSetSnapshot
 * Signature: (JZ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_OptimisticTransactionOptions_setSetSnapshot(
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle, jboolean jset_snapshot) {
=======
void Java_org_rocksdb_OptimisticTransactionOptions_setSetSnapshot(JNIEnv* env,
    jobject jobj, jlong jhandle, jboolean jset_snapshot) {
>>>>>>> blood in blood out
  auto* opts =
      reinterpret_cast<rocksdb::OptimisticTransactionOptions*>(jhandle);
  opts->set_snapshot = jset_snapshot;
}

/*
 * Class:     org_rocksdb_OptimisticTransactionOptions
 * Method:    setComparator
 * Signature: (JJ)V
 */
void Java_org_rocksdb_OptimisticTransactionOptions_setComparator(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
    jlong jcomparator_handle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jlong jcomparator_handle) {
>>>>>>> blood in blood out
  auto* opts =
      reinterpret_cast<rocksdb::OptimisticTransactionOptions*>(jhandle);
  opts->cmp = reinterpret_cast<rocksdb::Comparator*>(jcomparator_handle);
}

/*
 * Class:     org_rocksdb_OptimisticTransactionOptions
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_OptimisticTransactionOptions_disposeInternal(
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
void Java_org_rocksdb_OptimisticTransactionOptions_disposeInternal(JNIEnv* env,
    jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  delete reinterpret_cast<rocksdb::OptimisticTransactionOptions*>(jhandle);
}
