// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <jni.h>

#include "include/org_rocksdb_RocksDBExceptionTest.h"

#include "rocksdb/slice.h"
#include "rocksdb/status.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_RocksDBExceptionTest
 * Method:    raiseException
 * Signature: ()V
 */
void Java_org_rocksdb_RocksDBExceptionTest_raiseException(JNIEnv* env,
<<<<<<< HEAD
                                                          jobject /*jobj*/) {
=======
                                                          jobject jobj) {
>>>>>>> blood in blood out
  rocksdb::RocksDBExceptionJni::ThrowNew(env, std::string("test message"));
}

/*
 * Class:     org_rocksdb_RocksDBExceptionTest
 * Method:    raiseExceptionWithStatusCode
 * Signature: ()V
 */
void Java_org_rocksdb_RocksDBExceptionTest_raiseExceptionWithStatusCode(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/) {
=======
    JNIEnv* env, jobject jobj) {
>>>>>>> blood in blood out
  rocksdb::RocksDBExceptionJni::ThrowNew(env, "test message",
                                         rocksdb::Status::NotSupported());
}

/*
 * Class:     org_rocksdb_RocksDBExceptionTest
 * Method:    raiseExceptionNoMsgWithStatusCode
 * Signature: ()V
 */
void Java_org_rocksdb_RocksDBExceptionTest_raiseExceptionNoMsgWithStatusCode(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/) {
=======
    JNIEnv* env, jobject jobj) {
>>>>>>> blood in blood out
  rocksdb::RocksDBExceptionJni::ThrowNew(env, rocksdb::Status::NotSupported());
}

/*
 * Class:     org_rocksdb_RocksDBExceptionTest
 * Method:    raiseExceptionWithStatusCodeSubCode
 * Signature: ()V
 */
void Java_org_rocksdb_RocksDBExceptionTest_raiseExceptionWithStatusCodeSubCode(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/) {
=======
    JNIEnv* env, jobject jobj) {
>>>>>>> blood in blood out
  rocksdb::RocksDBExceptionJni::ThrowNew(
      env, "test message",
      rocksdb::Status::TimedOut(rocksdb::Status::SubCode::kLockTimeout));
}

/*
 * Class:     org_rocksdb_RocksDBExceptionTest
 * Method:    raiseExceptionNoMsgWithStatusCodeSubCode
 * Signature: ()V
 */
void Java_org_rocksdb_RocksDBExceptionTest_raiseExceptionNoMsgWithStatusCodeSubCode(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/) {
=======
    JNIEnv* env, jobject jobj) {
>>>>>>> blood in blood out
  rocksdb::RocksDBExceptionJni::ThrowNew(
      env, rocksdb::Status::TimedOut(rocksdb::Status::SubCode::kLockTimeout));
}

/*
 * Class:     org_rocksdb_RocksDBExceptionTest
 * Method:    raiseExceptionWithStatusCodeState
 * Signature: ()V
 */
void Java_org_rocksdb_RocksDBExceptionTest_raiseExceptionWithStatusCodeState(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/) {
=======
    JNIEnv* env, jobject jobj) {
>>>>>>> blood in blood out
  rocksdb::Slice state("test state");
  rocksdb::RocksDBExceptionJni::ThrowNew(env, "test message",
                                         rocksdb::Status::NotSupported(state));
}
