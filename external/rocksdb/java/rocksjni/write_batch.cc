// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling c++ rocksdb::WriteBatch methods from Java side.
#include <memory>

#include "db/memtable.h"
#include "db/write_batch_internal.h"
#include "include/org_rocksdb_WriteBatch.h"
#include "include/org_rocksdb_WriteBatch_Handler.h"
#include "rocksdb/db.h"
#include "rocksdb/env.h"
#include "rocksdb/memtablerep.h"
#include "rocksdb/status.h"
#include "rocksdb/write_batch.h"
#include "rocksdb/write_buffer_manager.h"
#include "rocksjni/portal.h"
#include "rocksjni/writebatchhandlerjnicallback.h"
#include "table/scoped_arena_iterator.h"
#include "util/logging.h"

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    newWriteBatch
 * Signature: (I)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_WriteBatch_newWriteBatch__I(JNIEnv* /*env*/,
                                                   jclass /*jcls*/,
                                                   jint jreserved_bytes) {
=======
jlong Java_org_rocksdb_WriteBatch_newWriteBatch__I(
    JNIEnv* env, jclass jcls, jint jreserved_bytes) {
>>>>>>> blood in blood out
  auto* wb = new rocksdb::WriteBatch(static_cast<size_t>(jreserved_bytes));
  return reinterpret_cast<jlong>(wb);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    newWriteBatch
 * Signature: ([BI)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_WriteBatch_newWriteBatch___3BI(JNIEnv* env,
                                                      jclass /*jcls*/,
                                                      jbyteArray jserialized,
                                                      jint jserialized_length) {
  jboolean has_exception = JNI_FALSE;
  std::string serialized = rocksdb::JniUtil::byteString<std::string>(
      env, jserialized, jserialized_length,
      [](const char* str, const size_t len) { return std::string(str, len); },
      &has_exception);
  if (has_exception == JNI_TRUE) {
=======
jlong Java_org_rocksdb_WriteBatch_newWriteBatch___3BI(
    JNIEnv* env, jclass jcls, jbyteArray jserialized,
    jint jserialized_length) {
  jboolean has_exception = JNI_FALSE;
  std::string serialized = rocksdb::JniUtil::byteString<std::string>(env,
    jserialized, jserialized_length,
    [](const char* str, const size_t len) { return std::string(str, len); },
    &has_exception);
  if(has_exception == JNI_TRUE) {
>>>>>>> blood in blood out
    // exception occurred
    return 0;
  }

  auto* wb = new rocksdb::WriteBatch(serialized);
  return reinterpret_cast<jlong>(wb);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    count0
 * Signature: (J)I
 */
<<<<<<< HEAD
jint Java_org_rocksdb_WriteBatch_count0(JNIEnv* /*env*/, jobject /*jobj*/,
                                        jlong jwb_handle) {
=======
jint Java_org_rocksdb_WriteBatch_count0(JNIEnv* env, jobject jobj,
    jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return static_cast<jint>(wb->Count());
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    clear0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_clear0(JNIEnv* /*env*/, jobject /*jobj*/,
                                        jlong jwb_handle) {
=======
void Java_org_rocksdb_WriteBatch_clear0(JNIEnv* env, jobject jobj,
    jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  wb->Clear();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    setSavePoint0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_setSavePoint0(JNIEnv* /*env*/,
                                               jobject /*jobj*/,
                                               jlong jwb_handle) {
=======
void Java_org_rocksdb_WriteBatch_setSavePoint0(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  wb->SetSavePoint();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    rollbackToSavePoint0
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_rollbackToSavePoint0(JNIEnv* env,
                                                      jobject /*jobj*/,
                                                      jlong jwb_handle) {
=======
void Java_org_rocksdb_WriteBatch_rollbackToSavePoint0(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  auto s = wb->RollbackToSavePoint();

  if (s.ok()) {
    return;
  }
  rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    popSavePoint
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_popSavePoint(JNIEnv* env, jobject /*jobj*/,
                                              jlong jwb_handle) {
=======
void Java_org_rocksdb_WriteBatch_popSavePoint(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  auto s = wb->PopSavePoint();

  if (s.ok()) {
    return;
  }
  rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    setMaxBytes
 * Signature: (JJ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_setMaxBytes(JNIEnv* /*env*/, jobject /*jobj*/,
                                             jlong jwb_handle,
                                             jlong jmax_bytes) {
=======
void Java_org_rocksdb_WriteBatch_setMaxBytes(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jlong jmax_bytes) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  wb->SetMaxBytes(static_cast<size_t>(jmax_bytes));
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    put
 * Signature: (J[BI[BI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_put__J_3BI_3BI(JNIEnv* env, jobject jobj,
                                                jlong jwb_handle,
                                                jbyteArray jkey, jint jkey_len,
                                                jbyteArray jentry_value,
                                                jint jentry_value_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto put = [&wb](rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Put(key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(
      put, env, jobj, jkey, jkey_len, jentry_value, jentry_value_len);
=======
void Java_org_rocksdb_WriteBatch_put__J_3BI_3BI(
    JNIEnv* env, jobject jobj, jlong jwb_handle,
    jbyteArray jkey, jint jkey_len,
    jbyteArray jentry_value, jint jentry_value_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto put = [&wb] (rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Put(key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(put, env,
      jobj, jkey, jkey_len, jentry_value, jentry_value_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    put
 * Signature: (J[BI[BIJ)V
 */
void Java_org_rocksdb_WriteBatch_put__J_3BI_3BIJ(
<<<<<<< HEAD
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jkey, jint jkey_len,
=======
    JNIEnv* env, jobject jobj, jlong jwb_handle,
    jbyteArray jkey, jint jkey_len,
>>>>>>> blood in blood out
    jbyteArray jentry_value, jint jentry_value_len, jlong jcf_handle) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto* cf_handle = reinterpret_cast<rocksdb::ColumnFamilyHandle*>(jcf_handle);
  assert(cf_handle != nullptr);
<<<<<<< HEAD
  auto put = [&wb, &cf_handle](rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Put(cf_handle, key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(
      put, env, jobj, jkey, jkey_len, jentry_value, jentry_value_len);
=======
  auto put = [&wb, &cf_handle] (rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Put(cf_handle, key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(put, env,
      jobj, jkey, jkey_len, jentry_value, jentry_value_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    merge
 * Signature: (J[BI[BI)V
 */
void Java_org_rocksdb_WriteBatch_merge__J_3BI_3BI(
<<<<<<< HEAD
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jkey, jint jkey_len,
    jbyteArray jentry_value, jint jentry_value_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto merge = [&wb](rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Merge(key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(
      merge, env, jobj, jkey, jkey_len, jentry_value, jentry_value_len);
=======
    JNIEnv* env, jobject jobj, jlong jwb_handle,
    jbyteArray jkey, jint jkey_len,
    jbyteArray jentry_value, jint jentry_value_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto merge = [&wb] (rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Merge(key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(merge, env,
      jobj, jkey, jkey_len, jentry_value, jentry_value_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    merge
 * Signature: (J[BI[BIJ)V
 */
void Java_org_rocksdb_WriteBatch_merge__J_3BI_3BIJ(
<<<<<<< HEAD
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jkey, jint jkey_len,
=======
    JNIEnv* env, jobject jobj, jlong jwb_handle,
    jbyteArray jkey, jint jkey_len,
>>>>>>> blood in blood out
    jbyteArray jentry_value, jint jentry_value_len, jlong jcf_handle) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto* cf_handle = reinterpret_cast<rocksdb::ColumnFamilyHandle*>(jcf_handle);
  assert(cf_handle != nullptr);
<<<<<<< HEAD
  auto merge = [&wb, &cf_handle](rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Merge(cf_handle, key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(
      merge, env, jobj, jkey, jkey_len, jentry_value, jentry_value_len);
=======
  auto merge = [&wb, &cf_handle] (rocksdb::Slice key, rocksdb::Slice value) {
    return wb->Merge(cf_handle, key, value);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(merge, env,
      jobj, jkey, jkey_len, jentry_value, jentry_value_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    delete
 * Signature: (J[BI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_delete__J_3BI(JNIEnv* env, jobject jobj,
                                               jlong jwb_handle,
                                               jbyteArray jkey, jint jkey_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto remove = [&wb](rocksdb::Slice key) { return wb->Delete(key); };
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::k_op(remove, env, jobj, jkey, jkey_len);
=======
void Java_org_rocksdb_WriteBatch_delete__J_3BI(
    JNIEnv* env, jobject jobj, jlong jwb_handle,
    jbyteArray jkey, jint jkey_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto remove = [&wb] (rocksdb::Slice key) {
    return wb->Delete(key);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::k_op(remove, env,
      jobj, jkey, jkey_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    delete
 * Signature: (J[BIJ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_delete__J_3BIJ(JNIEnv* env, jobject jobj,
                                                jlong jwb_handle,
                                                jbyteArray jkey, jint jkey_len,
                                                jlong jcf_handle) {
=======
void Java_org_rocksdb_WriteBatch_delete__J_3BIJ(
    JNIEnv* env, jobject jobj, jlong jwb_handle,
    jbyteArray jkey, jint jkey_len, jlong jcf_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto* cf_handle = reinterpret_cast<rocksdb::ColumnFamilyHandle*>(jcf_handle);
  assert(cf_handle != nullptr);
<<<<<<< HEAD
  auto remove = [&wb, &cf_handle](rocksdb::Slice key) {
    return wb->Delete(cf_handle, key);
  };
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::k_op(remove, env, jobj, jkey, jkey_len);
=======
  auto remove = [&wb, &cf_handle] (rocksdb::Slice key) {
    return wb->Delete(cf_handle, key);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::k_op(remove, env,
      jobj, jkey, jkey_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    singleDelete
 * Signature: (J[BI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_singleDelete__J_3BI(JNIEnv* env, jobject jobj,
                                                     jlong jwb_handle,
                                                     jbyteArray jkey,
                                                     jint jkey_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto single_delete = [&wb](rocksdb::Slice key) {
    return wb->SingleDelete(key);
  };
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::k_op(single_delete, env, jobj, jkey, jkey_len);
=======
void Java_org_rocksdb_WriteBatch_singleDelete__J_3BI(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jkey,
    jint jkey_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto single_delete = [&wb] (rocksdb::Slice key) {
    return wb->SingleDelete(key);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::k_op(single_delete,
      env, jobj, jkey, jkey_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    singleDelete
 * Signature: (J[BIJ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_singleDelete__J_3BIJ(JNIEnv* env, jobject jobj,
                                                      jlong jwb_handle,
                                                      jbyteArray jkey,
                                                      jint jkey_len,
                                                      jlong jcf_handle) {
=======
void Java_org_rocksdb_WriteBatch_singleDelete__J_3BIJ(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jkey,
    jint jkey_len, jlong jcf_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto* cf_handle = reinterpret_cast<rocksdb::ColumnFamilyHandle*>(jcf_handle);
  assert(cf_handle != nullptr);
<<<<<<< HEAD
  auto single_delete = [&wb, &cf_handle](rocksdb::Slice key) {
    return wb->SingleDelete(cf_handle, key);
  };
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::k_op(single_delete, env, jobj, jkey, jkey_len);
=======
  auto single_delete = [&wb, &cf_handle] (rocksdb::Slice key) {
    return wb->SingleDelete(cf_handle, key);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::k_op(single_delete,
      env, jobj, jkey, jkey_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    deleteRange
 * Signature: (J[BI[BI)V
 */
void Java_org_rocksdb_WriteBatch_deleteRange__J_3BI_3BI(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jbegin_key,
    jint jbegin_key_len, jbyteArray jend_key, jint jend_key_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto deleteRange = [&wb](rocksdb::Slice beginKey, rocksdb::Slice endKey) {
    return wb->DeleteRange(beginKey, endKey);
  };
<<<<<<< HEAD
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::kv_op(deleteRange, env, jobj, jbegin_key,
                              jbegin_key_len, jend_key, jend_key_len);
=======
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(
      deleteRange, env, jobj, jbegin_key, jbegin_key_len, jend_key,
      jend_key_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    deleteRange
 * Signature: (J[BI[BIJ)V
 */
void Java_org_rocksdb_WriteBatch_deleteRange__J_3BI_3BIJ(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jbegin_key,
    jint jbegin_key_len, jbyteArray jend_key, jint jend_key_len,
    jlong jcf_handle) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto* cf_handle = reinterpret_cast<rocksdb::ColumnFamilyHandle*>(jcf_handle);
  assert(cf_handle != nullptr);
  auto deleteRange = [&wb, &cf_handle](rocksdb::Slice beginKey,
<<<<<<< HEAD
                                       rocksdb::Slice endKey) {
    return wb->DeleteRange(cf_handle, beginKey, endKey);
  };
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::kv_op(deleteRange, env, jobj, jbegin_key,
                              jbegin_key_len, jend_key, jend_key_len);
=======
      rocksdb::Slice endKey) {
    return wb->DeleteRange(cf_handle, beginKey, endKey);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::kv_op(
      deleteRange, env, jobj, jbegin_key, jbegin_key_len, jend_key,
      jend_key_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    putLogData
 * Signature: (J[BI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_putLogData(JNIEnv* env, jobject jobj,
                                            jlong jwb_handle, jbyteArray jblob,
                                            jint jblob_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto putLogData = [&wb](rocksdb::Slice blob) { return wb->PutLogData(blob); };
  std::unique_ptr<rocksdb::Status> status =
      rocksdb::JniUtil::k_op(putLogData, env, jobj, jblob, jblob_len);
=======
void Java_org_rocksdb_WriteBatch_putLogData(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jbyteArray jblob,
    jint jblob_len) {
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);
  auto putLogData = [&wb] (rocksdb::Slice blob) {
    return wb->PutLogData(blob);
  };
  std::unique_ptr<rocksdb::Status> status = rocksdb::JniUtil::k_op(putLogData,
      env, jobj, jblob, jblob_len);
>>>>>>> blood in blood out
  if (status != nullptr && !status->ok()) {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
  }
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    iterate
 * Signature: (JJ)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_iterate(JNIEnv* env, jobject /*jobj*/,
                                         jlong jwb_handle,
                                         jlong handlerHandle) {
=======
void Java_org_rocksdb_WriteBatch_iterate(
    JNIEnv* env, jobject jobj, jlong jwb_handle, jlong handlerHandle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  rocksdb::Status s = wb->Iterate(
<<<<<<< HEAD
      reinterpret_cast<rocksdb::WriteBatchHandlerJniCallback*>(handlerHandle));
=======
    reinterpret_cast<rocksdb::WriteBatchHandlerJniCallback*>(handlerHandle));
>>>>>>> blood in blood out

  if (s.ok()) {
    return;
  }
  rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    data
 * Signature: (J)[B
 */
<<<<<<< HEAD
jbyteArray Java_org_rocksdb_WriteBatch_data(JNIEnv* env, jobject /*jobj*/,
                                            jlong jwb_handle) {
=======
jbyteArray Java_org_rocksdb_WriteBatch_data(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  auto data = wb->Data();
  return rocksdb::JniUtil::copyBytes(env, data);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    getDataSize
 * Signature: (J)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_WriteBatch_getDataSize(JNIEnv* /*env*/, jobject /*jobj*/,
                                              jlong jwb_handle) {
=======
jlong Java_org_rocksdb_WriteBatch_getDataSize(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  auto data_size = wb->GetDataSize();
  return static_cast<jlong>(data_size);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasPut
 * Signature: (J)Z
 */
<<<<<<< HEAD
jboolean Java_org_rocksdb_WriteBatch_hasPut(JNIEnv* /*env*/, jobject /*jobj*/,
                                            jlong jwb_handle) {
=======
jboolean Java_org_rocksdb_WriteBatch_hasPut(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasPut();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasDelete
 * Signature: (J)Z
 */
<<<<<<< HEAD
jboolean Java_org_rocksdb_WriteBatch_hasDelete(JNIEnv* /*env*/,
                                               jobject /*jobj*/,
                                               jlong jwb_handle) {
=======
jboolean Java_org_rocksdb_WriteBatch_hasDelete(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasDelete();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasSingleDelete
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasSingleDelete(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasSingleDelete();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasDeleteRange
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasDeleteRange(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasDeleteRange();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasMerge
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasMerge(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasMerge();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasBeginPrepare
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasBeginPrepare(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasBeginPrepare();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasEndPrepare
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasEndPrepare(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasEndPrepare();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasCommit
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasCommit(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasCommit();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    hasRollback
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_rocksdb_WriteBatch_hasRollback(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jwb_handle) {
=======
    JNIEnv* env , jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  return wb->HasRollback();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    markWalTerminationPoint
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_markWalTerminationPoint(JNIEnv* /*env*/,
                                                         jobject /*jobj*/,
                                                         jlong jwb_handle) {
=======
void Java_org_rocksdb_WriteBatch_markWalTerminationPoint(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  wb->MarkWalTerminationPoint();
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    getWalTerminationPoint
 * Signature: (J)Lorg/rocksdb/WriteBatch/SavePoint;
 */
<<<<<<< HEAD
jobject Java_org_rocksdb_WriteBatch_getWalTerminationPoint(JNIEnv* env,
                                                           jobject /*jobj*/,
                                                           jlong jwb_handle) {
=======
jobject Java_org_rocksdb_WriteBatch_getWalTerminationPoint(
    JNIEnv* env, jobject jobj, jlong jwb_handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(jwb_handle);
  assert(wb != nullptr);

  auto save_point = wb->GetWalTerminationPoint();
  return rocksdb::WriteBatchSavePointJni::construct(env, save_point);
}

/*
 * Class:     org_rocksdb_WriteBatch
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_WriteBatch_disposeInternal(JNIEnv* /*env*/,
                                                 jobject /*jobj*/,
                                                 jlong handle) {
=======
void Java_org_rocksdb_WriteBatch_disposeInternal(
    JNIEnv* env, jobject jobj, jlong handle) {
>>>>>>> blood in blood out
  auto* wb = reinterpret_cast<rocksdb::WriteBatch*>(handle);
  assert(wb != nullptr);
  delete wb;
}

/*
 * Class:     org_rocksdb_WriteBatch_Handler
 * Method:    createNewHandler0
 * Signature: ()J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_WriteBatch_00024Handler_createNewHandler0(JNIEnv* env,
                                                                 jobject jobj) {
=======
jlong Java_org_rocksdb_WriteBatch_00024Handler_createNewHandler0(
    JNIEnv* env, jobject jobj) {
>>>>>>> blood in blood out
  auto* wbjnic = new rocksdb::WriteBatchHandlerJniCallback(env, jobj);
  return reinterpret_cast<jlong>(wbjnic);
}
