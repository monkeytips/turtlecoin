// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling c++ rocksdb::Iterator methods from Java side.

<<<<<<< HEAD
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/org_rocksdb_RocksIterator.h"
#include "rocksdb/iterator.h"
#include "rocksjni/portal.h"
=======
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

#include "include/org_rocksdb_RocksIterator.h"
#include "rocksjni/portal.h"
#include "rocksdb/iterator.h"
>>>>>>> blood in blood out

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_disposeInternal(JNIEnv* /*env*/,
                                                    jobject /*jobj*/,
                                                    jlong handle) {
=======
void Java_org_rocksdb_RocksIterator_disposeInternal(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  auto* it = reinterpret_cast<rocksdb::Iterator*>(handle);
  assert(it != nullptr);
  delete it;
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    isValid0
 * Signature: (J)Z
 */
<<<<<<< HEAD
jboolean Java_org_rocksdb_RocksIterator_isValid0(JNIEnv* /*env*/,
                                                 jobject /*jobj*/,
                                                 jlong handle) {
=======
jboolean Java_org_rocksdb_RocksIterator_isValid0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  return reinterpret_cast<rocksdb::Iterator*>(handle)->Valid();
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    seekToFirst0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_seekToFirst0(JNIEnv* /*env*/,
                                                 jobject /*jobj*/,
                                                 jlong handle) {
=======
void Java_org_rocksdb_RocksIterator_seekToFirst0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  reinterpret_cast<rocksdb::Iterator*>(handle)->SeekToFirst();
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    seekToLast0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_seekToLast0(JNIEnv* /*env*/,
                                                jobject /*jobj*/,
                                                jlong handle) {
=======
void Java_org_rocksdb_RocksIterator_seekToLast0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  reinterpret_cast<rocksdb::Iterator*>(handle)->SeekToLast();
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    next0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_next0(JNIEnv* /*env*/, jobject /*jobj*/,
                                          jlong handle) {
=======
void Java_org_rocksdb_RocksIterator_next0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  reinterpret_cast<rocksdb::Iterator*>(handle)->Next();
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    prev0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_prev0(JNIEnv* /*env*/, jobject /*jobj*/,
                                          jlong handle) {
=======
void Java_org_rocksdb_RocksIterator_prev0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  reinterpret_cast<rocksdb::Iterator*>(handle)->Prev();
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    seek0
 * Signature: (J[BI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_seek0(JNIEnv* env, jobject /*jobj*/,
                                          jlong handle, jbyteArray jtarget,
                                          jint jtarget_len) {
  jbyte* target = env->GetByteArrayElements(jtarget, nullptr);
  if (target == nullptr) {
=======
void Java_org_rocksdb_RocksIterator_seek0(
    JNIEnv* env, jobject jobj, jlong handle,
    jbyteArray jtarget, jint jtarget_len) {
  jbyte* target = env->GetByteArrayElements(jtarget, nullptr);
  if(target == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return;
  }

<<<<<<< HEAD
  rocksdb::Slice target_slice(reinterpret_cast<char*>(target), jtarget_len);
=======
  rocksdb::Slice target_slice(
      reinterpret_cast<char*>(target), jtarget_len);
>>>>>>> blood in blood out

  auto* it = reinterpret_cast<rocksdb::Iterator*>(handle);
  it->Seek(target_slice);

  env->ReleaseByteArrayElements(jtarget, target, JNI_ABORT);
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    seekForPrev0
 * Signature: (J[BI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_seekForPrev0(JNIEnv* env, jobject /*jobj*/,
                                                 jlong handle,
                                                 jbyteArray jtarget,
                                                 jint jtarget_len) {
  jbyte* target = env->GetByteArrayElements(jtarget, nullptr);
  if (target == nullptr) {
=======
void Java_org_rocksdb_RocksIterator_seekForPrev0(
    JNIEnv* env, jobject jobj, jlong handle,
    jbyteArray jtarget, jint jtarget_len) {
  jbyte* target = env->GetByteArrayElements(jtarget, nullptr);
  if(target == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return;
  }

<<<<<<< HEAD
  rocksdb::Slice target_slice(reinterpret_cast<char*>(target), jtarget_len);
=======
  rocksdb::Slice target_slice(
      reinterpret_cast<char*>(target), jtarget_len);
>>>>>>> blood in blood out

  auto* it = reinterpret_cast<rocksdb::Iterator*>(handle);
  it->SeekForPrev(target_slice);

  env->ReleaseByteArrayElements(jtarget, target, JNI_ABORT);
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    status0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RocksIterator_status0(JNIEnv* env, jobject /*jobj*/,
                                            jlong handle) {
=======
void Java_org_rocksdb_RocksIterator_status0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  auto* it = reinterpret_cast<rocksdb::Iterator*>(handle);
  rocksdb::Status s = it->status();

  if (s.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    key0
 * Signature: (J)[B
 */
<<<<<<< HEAD
jbyteArray Java_org_rocksdb_RocksIterator_key0(JNIEnv* env, jobject /*jobj*/,
                                               jlong handle) {
=======
jbyteArray Java_org_rocksdb_RocksIterator_key0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  auto* it = reinterpret_cast<rocksdb::Iterator*>(handle);
  rocksdb::Slice key_slice = it->key();

  jbyteArray jkey = env->NewByteArray(static_cast<jsize>(key_slice.size()));
<<<<<<< HEAD
  if (jkey == nullptr) {
    // exception thrown: OutOfMemoryError
    return nullptr;
  }
  env->SetByteArrayRegion(
      jkey, 0, static_cast<jsize>(key_slice.size()),
      const_cast<jbyte*>(reinterpret_cast<const jbyte*>(key_slice.data())));
=======
  if(jkey == nullptr) {
    // exception thrown: OutOfMemoryError
    return nullptr;
  }
  env->SetByteArrayRegion(jkey, 0, static_cast<jsize>(key_slice.size()),
                          const_cast<jbyte*>(reinterpret_cast<const jbyte*>(key_slice.data())));
>>>>>>> blood in blood out
  return jkey;
}

/*
 * Class:     org_rocksdb_RocksIterator
 * Method:    value0
 * Signature: (J)[B
 */
<<<<<<< HEAD
jbyteArray Java_org_rocksdb_RocksIterator_value0(JNIEnv* env, jobject /*jobj*/,
                                                 jlong handle) {
=======
jbyteArray Java_org_rocksdb_RocksIterator_value0(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  auto* it = reinterpret_cast<rocksdb::Iterator*>(handle);
  rocksdb::Slice value_slice = it->value();

  jbyteArray jkeyValue =
      env->NewByteArray(static_cast<jsize>(value_slice.size()));
<<<<<<< HEAD
  if (jkeyValue == nullptr) {
    // exception thrown: OutOfMemoryError
    return nullptr;
  }
  env->SetByteArrayRegion(
      jkeyValue, 0, static_cast<jsize>(value_slice.size()),
      const_cast<jbyte*>(reinterpret_cast<const jbyte*>(value_slice.data())));
=======
  if(jkeyValue == nullptr) {
    // exception thrown: OutOfMemoryError
    return nullptr;
  }
  env->SetByteArrayRegion(jkeyValue, 0, static_cast<jsize>(value_slice.size()),
                          const_cast<jbyte*>(reinterpret_cast<const jbyte*>(value_slice.data())));
>>>>>>> blood in blood out
  return jkeyValue;
}
