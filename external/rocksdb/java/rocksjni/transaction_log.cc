// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling c++ rocksdb::Iterator methods from Java side.

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/org_rocksdb_TransactionLogIterator.h"
#include "rocksdb/transaction_log.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_TransactionLogIterator
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionLogIterator_disposeInternal(JNIEnv* /*env*/,
                                                             jobject /*jobj*/,
                                                             jlong handle) {
=======
void Java_org_rocksdb_TransactionLogIterator_disposeInternal(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  delete reinterpret_cast<rocksdb::TransactionLogIterator*>(handle);
}

/*
 * Class:     org_rocksdb_TransactionLogIterator
 * Method:    isValid
 * Signature: (J)Z
 */
<<<<<<< HEAD
jboolean Java_org_rocksdb_TransactionLogIterator_isValid(JNIEnv* /*env*/,
                                                         jobject /*jobj*/,
                                                         jlong handle) {
=======
jboolean Java_org_rocksdb_TransactionLogIterator_isValid(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  return reinterpret_cast<rocksdb::TransactionLogIterator*>(handle)->Valid();
}

/*
 * Class:     org_rocksdb_TransactionLogIterator
 * Method:    next
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionLogIterator_next(JNIEnv* /*env*/,
                                                  jobject /*jobj*/,
                                                  jlong handle) {
=======
void Java_org_rocksdb_TransactionLogIterator_next(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  reinterpret_cast<rocksdb::TransactionLogIterator*>(handle)->Next();
}

/*
 * Class:     org_rocksdb_TransactionLogIterator
 * Method:    status
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionLogIterator_status(JNIEnv* env,
                                                    jobject /*jobj*/,
                                                    jlong handle) {
  rocksdb::Status s =
      reinterpret_cast<rocksdb::TransactionLogIterator*>(handle)->status();
=======
void Java_org_rocksdb_TransactionLogIterator_status(
    JNIEnv* env, jobject jobj, jlong handle) {
  rocksdb::Status s = reinterpret_cast<
      rocksdb::TransactionLogIterator*>(handle)->status();
>>>>>>> blood in blood out
  if (!s.ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
  }
}

/*
 * Class:     org_rocksdb_TransactionLogIterator
 * Method:    getBatch
 * Signature: (J)Lorg/rocksdb/TransactionLogIterator$BatchResult
 */
<<<<<<< HEAD
jobject Java_org_rocksdb_TransactionLogIterator_getBatch(JNIEnv* env,
                                                         jobject /*jobj*/,
                                                         jlong handle) {
=======
jobject Java_org_rocksdb_TransactionLogIterator_getBatch(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  rocksdb::BatchResult batch_result =
      reinterpret_cast<rocksdb::TransactionLogIterator*>(handle)->GetBatch();
  return rocksdb::BatchResultJni::construct(env, batch_result);
}
