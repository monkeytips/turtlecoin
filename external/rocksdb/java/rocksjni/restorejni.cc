// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling C++ rocksdb::RestoreOptions methods
// from Java side.

<<<<<<< HEAD
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "include/org_rocksdb_RestoreOptions.h"
#include "rocksdb/utilities/backupable_db.h"
#include "rocksjni/portal.h"
=======
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <string>

#include "include/org_rocksdb_RestoreOptions.h"
#include "rocksjni/portal.h"
#include "rocksdb/utilities/backupable_db.h"
>>>>>>> blood in blood out
/*
 * Class:     org_rocksdb_RestoreOptions
 * Method:    newRestoreOptions
 * Signature: (Z)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_RestoreOptions_newRestoreOptions(
    JNIEnv* /*env*/, jclass /*jcls*/, jboolean keep_log_files) {
=======
jlong Java_org_rocksdb_RestoreOptions_newRestoreOptions(JNIEnv* env,
    jclass jcls, jboolean keep_log_files) {
>>>>>>> blood in blood out
  auto* ropt = new rocksdb::RestoreOptions(keep_log_files);
  return reinterpret_cast<jlong>(ropt);
}

/*
 * Class:     org_rocksdb_RestoreOptions
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_RestoreOptions_disposeInternal(JNIEnv* /*env*/,
                                                     jobject /*jobj*/,
                                                     jlong jhandle) {
=======
void Java_org_rocksdb_RestoreOptions_disposeInternal(JNIEnv* env, jobject jobj,
    jlong jhandle) {
>>>>>>> blood in blood out
  auto* ropt = reinterpret_cast<rocksdb::RestoreOptions*>(jhandle);
  assert(ropt);
  delete ropt;
}
