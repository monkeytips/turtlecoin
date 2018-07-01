// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling c++ rocksdb::TtlDB methods.
// from Java side.

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <memory>
#include <string>
#include <vector>
=======
#include <string>
#include <vector>
#include <memory>
>>>>>>> blood in blood out

#include "include/org_rocksdb_TtlDB.h"
#include "rocksdb/utilities/db_ttl.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_TtlDB
 * Method:    open
 * Signature: (JLjava/lang/String;IZ)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_TtlDB_open(JNIEnv* env, jclass /*jcls*/,
                                  jlong joptions_handle, jstring jdb_path,
                                  jint jttl, jboolean jread_only) {
  const char* db_path = env->GetStringUTFChars(jdb_path, nullptr);
  if (db_path == nullptr) {
=======
jlong Java_org_rocksdb_TtlDB_open(JNIEnv* env,
    jclass jcls, jlong joptions_handle, jstring jdb_path,
    jint jttl, jboolean jread_only) {
  const char* db_path = env->GetStringUTFChars(jdb_path, nullptr);
  if(db_path == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return 0;
  }

  auto* opt = reinterpret_cast<rocksdb::Options*>(joptions_handle);
  rocksdb::DBWithTTL* db = nullptr;
<<<<<<< HEAD
  rocksdb::Status s =
      rocksdb::DBWithTTL::Open(*opt, db_path, &db, jttl, jread_only);
=======
  rocksdb::Status s = rocksdb::DBWithTTL::Open(*opt, db_path, &db,
      jttl, jread_only);
>>>>>>> blood in blood out
  env->ReleaseStringUTFChars(jdb_path, db_path);

  // as TTLDB extends RocksDB on the java side, we can reuse
  // the RocksDB portal here.
  if (s.ok()) {
    return reinterpret_cast<jlong>(db);
  } else {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
    return 0;
  }
}

/*
 * Class:     org_rocksdb_TtlDB
 * Method:    openCF
 * Signature: (JLjava/lang/String;[[B[J[IZ)[J
 */
<<<<<<< HEAD
jlongArray Java_org_rocksdb_TtlDB_openCF(JNIEnv* env, jclass /*jcls*/,
                                         jlong jopt_handle, jstring jdb_path,
                                         jobjectArray jcolumn_names,
                                         jlongArray jcolumn_options,
                                         jintArray jttls, jboolean jread_only) {
  const char* db_path = env->GetStringUTFChars(jdb_path, nullptr);
  if (db_path == nullptr) {
=======
jlongArray
    Java_org_rocksdb_TtlDB_openCF(
    JNIEnv* env, jclass jcls, jlong jopt_handle, jstring jdb_path,
    jobjectArray jcolumn_names, jlongArray jcolumn_options,
    jintArray jttls, jboolean jread_only) {
  const char* db_path = env->GetStringUTFChars(jdb_path, nullptr);
  if(db_path == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return 0;
  }

  const jsize len_cols = env->GetArrayLength(jcolumn_names);
  jlong* jco = env->GetLongArrayElements(jcolumn_options, nullptr);
<<<<<<< HEAD
  if (jco == nullptr) {
=======
  if(jco == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    env->ReleaseStringUTFChars(jdb_path, db_path);
    return nullptr;
  }

  std::vector<rocksdb::ColumnFamilyDescriptor> column_families;
  jboolean has_exception = JNI_FALSE;
  rocksdb::JniUtil::byteStrings<std::string>(
<<<<<<< HEAD
      env, jcolumn_names,
      [](const char* str_data, const size_t str_len) {
        return std::string(str_data, str_len);
      },
      [&jco, &column_families](size_t idx, std::string cf_name) {
        rocksdb::ColumnFamilyOptions* cf_options =
            reinterpret_cast<rocksdb::ColumnFamilyOptions*>(jco[idx]);
        column_families.push_back(
            rocksdb::ColumnFamilyDescriptor(cf_name, *cf_options));
      },
      &has_exception);

  env->ReleaseLongArrayElements(jcolumn_options, jco, JNI_ABORT);

  if (has_exception == JNI_TRUE) {
=======
    env,
    jcolumn_names,
    [](const char* str_data, const size_t str_len) {
      return std::string(str_data, str_len);
    },
    [&jco, &column_families](size_t idx, std::string cf_name) {
      rocksdb::ColumnFamilyOptions* cf_options =
          reinterpret_cast<rocksdb::ColumnFamilyOptions*>(jco[idx]);
      column_families.push_back(
          rocksdb::ColumnFamilyDescriptor(cf_name, *cf_options));
    },
    &has_exception);

  env->ReleaseLongArrayElements(jcolumn_options, jco, JNI_ABORT);

  if(has_exception == JNI_TRUE) {
>>>>>>> blood in blood out
    // exception occurred
    env->ReleaseStringUTFChars(jdb_path, db_path);
    return nullptr;
  }

  std::vector<int32_t> ttl_values;
  jint* jttlv = env->GetIntArrayElements(jttls, nullptr);
<<<<<<< HEAD
  if (jttlv == nullptr) {
=======
  if(jttlv == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    env->ReleaseStringUTFChars(jdb_path, db_path);
    return nullptr;
  }
  const jsize len_ttls = env->GetArrayLength(jttls);
<<<<<<< HEAD
  for (jsize i = 0; i < len_ttls; i++) {
=======
  for(jsize i = 0; i < len_ttls; i++) {
>>>>>>> blood in blood out
    ttl_values.push_back(jttlv[i]);
  }
  env->ReleaseIntArrayElements(jttls, jttlv, JNI_ABORT);

  auto* opt = reinterpret_cast<rocksdb::DBOptions*>(jopt_handle);
  std::vector<rocksdb::ColumnFamilyHandle*> handles;
  rocksdb::DBWithTTL* db = nullptr;
<<<<<<< HEAD
  rocksdb::Status s = rocksdb::DBWithTTL::Open(
      *opt, db_path, column_families, &handles, &db, ttl_values, jread_only);
=======
  rocksdb::Status s = rocksdb::DBWithTTL::Open(*opt, db_path, column_families,
      &handles, &db, ttl_values, jread_only);
>>>>>>> blood in blood out

  // we have now finished with db_path
  env->ReleaseStringUTFChars(jdb_path, db_path);

  // check if open operation was successful
  if (s.ok()) {
<<<<<<< HEAD
    const jsize resultsLen = 1 + len_cols;  // db handle + column family handles
    std::unique_ptr<jlong[]> results =
        std::unique_ptr<jlong[]>(new jlong[resultsLen]);
    results[0] = reinterpret_cast<jlong>(db);
    for (int i = 1; i <= len_cols; i++) {
=======
    const jsize resultsLen = 1 + len_cols; //db handle + column family handles
    std::unique_ptr<jlong[]> results =
        std::unique_ptr<jlong[]>(new jlong[resultsLen]);
    results[0] = reinterpret_cast<jlong>(db);
    for(int i = 1; i <= len_cols; i++) {
>>>>>>> blood in blood out
      results[i] = reinterpret_cast<jlong>(handles[i - 1]);
    }

    jlongArray jresults = env->NewLongArray(resultsLen);
<<<<<<< HEAD
    if (jresults == nullptr) {
=======
    if(jresults == nullptr) {
>>>>>>> blood in blood out
      // exception thrown: OutOfMemoryError
      return nullptr;
    }

    env->SetLongArrayRegion(jresults, 0, resultsLen, results.get());
<<<<<<< HEAD
    if (env->ExceptionCheck()) {
=======
    if(env->ExceptionCheck()) {
>>>>>>> blood in blood out
      // exception thrown: ArrayIndexOutOfBoundsException
      env->DeleteLocalRef(jresults);
      return nullptr;
    }

    return jresults;
  } else {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
    return NULL;
  }
}

/*
 * Class:     org_rocksdb_TtlDB
 * Method:    createColumnFamilyWithTtl
 * Signature: (JLorg/rocksdb/ColumnFamilyDescriptor;[BJI)J;
 */
jlong Java_org_rocksdb_TtlDB_createColumnFamilyWithTtl(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jobj*/, jlong jdb_handle, jbyteArray jcolumn_name,
    jlong jcolumn_options, jint jttl) {
  jbyte* cfname = env->GetByteArrayElements(jcolumn_name, nullptr);
  if (cfname == nullptr) {
=======
    JNIEnv* env, jobject jobj, jlong jdb_handle,
    jbyteArray jcolumn_name, jlong jcolumn_options, jint jttl) {

  jbyte* cfname = env->GetByteArrayElements(jcolumn_name, nullptr);
  if(cfname == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return 0;
  }
  const jsize len = env->GetArrayLength(jcolumn_name);

  auto* cfOptions =
      reinterpret_cast<rocksdb::ColumnFamilyOptions*>(jcolumn_options);

  auto* db_handle = reinterpret_cast<rocksdb::DBWithTTL*>(jdb_handle);
  rocksdb::ColumnFamilyHandle* handle;
  rocksdb::Status s = db_handle->CreateColumnFamilyWithTtl(
<<<<<<< HEAD
      *cfOptions, std::string(reinterpret_cast<char*>(cfname), len), &handle,
      jttl);
=======
      *cfOptions, std::string(reinterpret_cast<char *>(cfname),
          len), &handle, jttl);
>>>>>>> blood in blood out

  env->ReleaseByteArrayElements(jcolumn_name, cfname, 0);

  if (s.ok()) {
    return reinterpret_cast<jlong>(handle);
  }
  rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
  return 0;
}
