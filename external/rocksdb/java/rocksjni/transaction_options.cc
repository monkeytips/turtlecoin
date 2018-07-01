// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++
// for rocksdb::TransactionOptions.

#include <jni.h>

#include "include/org_rocksdb_TransactionOptions.h"

#include "rocksdb/utilities/transaction_db.h"

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    newTransactionOptions
 * Signature: ()J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_TransactionOptions_newTransactionOptions(
    JNIEnv* /*env*/, jclass /*jcls*/) {
=======
jlong Java_org_rocksdb_TransactionOptions_newTransactionOptions(JNIEnv* env,
    jclass jcls) {
>>>>>>> blood in blood out
  auto* opts = new rocksdb::TransactionOptions();
  return reinterpret_cast<jlong>(opts);
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    isSetSnapshot
 * Signature: (J)Z
 */
<<<<<<< HEAD
jboolean Java_org_rocksdb_TransactionOptions_isSetSnapshot(JNIEnv* /*env*/,
                                                           jobject /*jobj*/,
                                                           jlong jhandle) {
=======
jboolean Java_org_rocksdb_TransactionOptions_isSetSnapshot(JNIEnv* env,
    jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  return opts->set_snapshot;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    setSetSnapshot
 * Signature: (JZ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionOptions_setSetSnapshot(
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle, jboolean jset_snapshot) {
=======
void Java_org_rocksdb_TransactionOptions_setSetSnapshot(JNIEnv* env,
    jobject jobj, jlong jhandle, jboolean jset_snapshot) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  opts->set_snapshot = jset_snapshot;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    isDeadlockDetect
 * Signature: (J)Z
 */
<<<<<<< HEAD
jboolean Java_org_rocksdb_TransactionOptions_isDeadlockDetect(JNIEnv* /*env*/,
                                                              jobject /*jobj*/,
                                                              jlong jhandle) {
=======
jboolean Java_org_rocksdb_TransactionOptions_isDeadlockDetect(
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  return opts->deadlock_detect;
}

/*
<<<<<<< HEAD
 * Class:     org_rocksdb_TransactionOptions
 * Method:    setDeadlockDetect
 * Signature: (JZ)V
 */
void Java_org_rocksdb_TransactionOptions_setDeadlockDetect(
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
    jboolean jdeadlock_detect) {
=======
* Class:     org_rocksdb_TransactionOptions
* Method:    setDeadlockDetect
* Signature: (JZ)V
*/
void Java_org_rocksdb_TransactionOptions_setDeadlockDetect(
    JNIEnv* env, jobject jobj, jlong jhandle, jboolean jdeadlock_detect) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  opts->deadlock_detect = jdeadlock_detect;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    getLockTimeout
 * Signature: (J)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_TransactionOptions_getLockTimeout(JNIEnv* /*env*/,
                                                         jobject /*jobj*/,
                                                         jlong jhandle) {
=======
jlong Java_org_rocksdb_TransactionOptions_getLockTimeout(JNIEnv* env,
    jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  return opts->lock_timeout;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    setLockTimeout
 * Signature: (JJ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionOptions_setLockTimeout(JNIEnv* /*env*/,
                                                        jobject /*jobj*/,
                                                        jlong jhandle,
                                                        jlong jlock_timeout) {
=======
void Java_org_rocksdb_TransactionOptions_setLockTimeout(JNIEnv* env,
    jobject jobj, jlong jhandle, jlong jlock_timeout) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  opts->lock_timeout = jlock_timeout;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    getExpiration
 * Signature: (J)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_TransactionOptions_getExpiration(JNIEnv* /*env*/,
                                                        jobject /*jobj*/,
                                                        jlong jhandle) {
=======
jlong Java_org_rocksdb_TransactionOptions_getExpiration(JNIEnv* env,
    jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  return opts->expiration;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    setExpiration
 * Signature: (JJ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionOptions_setExpiration(JNIEnv* /*env*/,
                                                       jobject /*jobj*/,
                                                       jlong jhandle,
                                                       jlong jexpiration) {
=======
void Java_org_rocksdb_TransactionOptions_setExpiration(JNIEnv* env,
    jobject jobj, jlong jhandle, jlong jexpiration) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  opts->expiration = jexpiration;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    getDeadlockDetectDepth
 * Signature: (J)J
 */
jlong Java_org_rocksdb_TransactionOptions_getDeadlockDetectDepth(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  return opts->deadlock_detect_depth;
}

/*
<<<<<<< HEAD
 * Class:     org_rocksdb_TransactionOptions
 * Method:    setDeadlockDetectDepth
 * Signature: (JJ)V
 */
void Java_org_rocksdb_TransactionOptions_setDeadlockDetectDepth(
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
    jlong jdeadlock_detect_depth) {
=======
* Class:     org_rocksdb_TransactionOptions
* Method:    setDeadlockDetectDepth
* Signature: (JJ)V
*/
void Java_org_rocksdb_TransactionOptions_setDeadlockDetectDepth(
    JNIEnv* env, jobject jobj, jlong jhandle, jlong jdeadlock_detect_depth) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  opts->deadlock_detect_depth = jdeadlock_detect_depth;
}

/*
<<<<<<< HEAD
 * Class:     org_rocksdb_TransactionOptions
 * Method:    getMaxWriteBatchSize
 * Signature: (J)J
 */
jlong Java_org_rocksdb_TransactionOptions_getMaxWriteBatchSize(JNIEnv* /*env*/,
                                                               jobject /*jobj*/,
                                                               jlong jhandle) {
=======
* Class:     org_rocksdb_TransactionOptions
* Method:    getMaxWriteBatchSize
* Signature: (J)J
*/
jlong Java_org_rocksdb_TransactionOptions_getMaxWriteBatchSize(
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  return opts->max_write_batch_size;
}

/*
<<<<<<< HEAD
 * Class:     org_rocksdb_TransactionOptions
 * Method:    setMaxWriteBatchSize
 * Signature: (JJ)V
 */
void Java_org_rocksdb_TransactionOptions_setMaxWriteBatchSize(
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
    jlong jmax_write_batch_size) {
=======
* Class:     org_rocksdb_TransactionOptions
* Method:    setMaxWriteBatchSize
* Signature: (JJ)V
*/
void Java_org_rocksdb_TransactionOptions_setMaxWriteBatchSize(
    JNIEnv* env, jobject jobj, jlong jhandle, jlong jmax_write_batch_size) {
>>>>>>> blood in blood out
  auto* opts = reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
  opts->max_write_batch_size = jmax_write_batch_size;
}

/*
 * Class:     org_rocksdb_TransactionOptions
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_TransactionOptions_disposeInternal(JNIEnv* /*env*/,
                                                         jobject /*jobj*/,
                                                         jlong jhandle) {
=======
void Java_org_rocksdb_TransactionOptions_disposeInternal(JNIEnv* env,
    jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  delete reinterpret_cast<rocksdb::TransactionOptions*>(jhandle);
}
