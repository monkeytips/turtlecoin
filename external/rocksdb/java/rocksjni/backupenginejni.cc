// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling C++ rocksdb::BackupEngine methods from the Java side.

#include <jni.h>
#include <vector>

#include "include/org_rocksdb_BackupEngine.h"
#include "rocksdb/utilities/backupable_db.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    open
 * Signature: (JJ)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_BackupEngine_open(JNIEnv* env, jclass /*jcls*/,
                                         jlong env_handle,
                                         jlong backupable_db_options_handle) {
  auto* rocks_env = reinterpret_cast<rocksdb::Env*>(env_handle);
  auto* backupable_db_options = reinterpret_cast<rocksdb::BackupableDBOptions*>(
      backupable_db_options_handle);
  rocksdb::BackupEngine* backup_engine;
  auto status = rocksdb::BackupEngine::Open(rocks_env, *backupable_db_options,
                                            &backup_engine);
=======
jlong Java_org_rocksdb_BackupEngine_open(
    JNIEnv* env, jclass jcls, jlong env_handle,
    jlong backupable_db_options_handle) {
  auto* rocks_env = reinterpret_cast<rocksdb::Env*>(env_handle);
  auto* backupable_db_options =
      reinterpret_cast<rocksdb::BackupableDBOptions*>(
      backupable_db_options_handle);
  rocksdb::BackupEngine* backup_engine;
  auto status = rocksdb::BackupEngine::Open(rocks_env,
      *backupable_db_options, &backup_engine);
>>>>>>> blood in blood out

  if (status.ok()) {
    return reinterpret_cast<jlong>(backup_engine);
  } else {
    rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
    return 0;
  }
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    createNewBackup
 * Signature: (JJZ)V
 */
void Java_org_rocksdb_BackupEngine_createNewBackup(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jbe*/, jlong jbe_handle, jlong db_handle,
    jboolean jflush_before_backup) {
  auto* db = reinterpret_cast<rocksdb::DB*>(db_handle);
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  auto status = backup_engine->CreateNewBackup(
      db, static_cast<bool>(jflush_before_backup));

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    createNewBackupWithMetadata
 * Signature: (JJLjava/lang/String;Z)V
 */
void Java_org_rocksdb_BackupEngine_createNewBackupWithMetadata(
    JNIEnv* env, jobject /*jbe*/, jlong jbe_handle, jlong db_handle,
    jstring japp_metadata, jboolean jflush_before_backup) {
  auto* db = reinterpret_cast<rocksdb::DB*>(db_handle);
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);

  jboolean has_exception = JNI_FALSE;
  std::string app_metadata =
      rocksdb::JniUtil::copyStdString(env, japp_metadata, &has_exception);
  if (has_exception == JNI_TRUE) {
    rocksdb::RocksDBExceptionJni::ThrowNew(
        env, "Could not copy jstring to std::string");
    return;
  }

  auto status = backup_engine->CreateNewBackupWithMetadata(
      db, app_metadata, static_cast<bool>(jflush_before_backup));
=======
    JNIEnv* env, jobject jbe, jlong jbe_handle, jlong db_handle,
    jboolean jflush_before_backup) {
  auto* db = reinterpret_cast<rocksdb::DB*>(db_handle);
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  auto status = backup_engine->CreateNewBackup(db,
      static_cast<bool>(jflush_before_backup));
>>>>>>> blood in blood out

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    getBackupInfo
 * Signature: (J)Ljava/util/List;
 */
<<<<<<< HEAD
jobject Java_org_rocksdb_BackupEngine_getBackupInfo(JNIEnv* env,
                                                    jobject /*jbe*/,
                                                    jlong jbe_handle) {
=======
jobject Java_org_rocksdb_BackupEngine_getBackupInfo(
    JNIEnv* env, jobject jbe, jlong jbe_handle) {
>>>>>>> blood in blood out
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  std::vector<rocksdb::BackupInfo> backup_infos;
  backup_engine->GetBackupInfo(&backup_infos);
  return rocksdb::BackupInfoListJni::getBackupInfo(env, backup_infos);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    getCorruptedBackups
 * Signature: (J)[I
 */
<<<<<<< HEAD
jintArray Java_org_rocksdb_BackupEngine_getCorruptedBackups(JNIEnv* env,
                                                            jobject /*jbe*/,
                                                            jlong jbe_handle) {
=======
jintArray Java_org_rocksdb_BackupEngine_getCorruptedBackups(
    JNIEnv* env, jobject jbe, jlong jbe_handle) {
>>>>>>> blood in blood out
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  std::vector<rocksdb::BackupID> backup_ids;
  backup_engine->GetCorruptedBackups(&backup_ids);
  // store backupids in int array
  std::vector<jint> int_backup_ids(backup_ids.begin(), backup_ids.end());
<<<<<<< HEAD

=======
  
>>>>>>> blood in blood out
  // Store ints in java array
  // Its ok to loose precision here (64->32)
  jsize ret_backup_ids_size = static_cast<jsize>(backup_ids.size());
  jintArray ret_backup_ids = env->NewIntArray(ret_backup_ids_size);
<<<<<<< HEAD
  if (ret_backup_ids == nullptr) {
=======
  if(ret_backup_ids == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return nullptr;
  }
  env->SetIntArrayRegion(ret_backup_ids, 0, ret_backup_ids_size,
<<<<<<< HEAD
                         int_backup_ids.data());
=======
      int_backup_ids.data());
>>>>>>> blood in blood out
  return ret_backup_ids;
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    garbageCollect
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_BackupEngine_garbageCollect(JNIEnv* env, jobject /*jbe*/,
                                                  jlong jbe_handle) {
=======
void Java_org_rocksdb_BackupEngine_garbageCollect(
    JNIEnv* env, jobject jbe, jlong jbe_handle) {
>>>>>>> blood in blood out
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  auto status = backup_engine->GarbageCollect();

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    purgeOldBackups
 * Signature: (JI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_BackupEngine_purgeOldBackups(JNIEnv* env, jobject /*jbe*/,
                                                   jlong jbe_handle,
                                                   jint jnum_backups_to_keep) {
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  auto status = backup_engine->PurgeOldBackups(
      static_cast<uint32_t>(jnum_backups_to_keep));
=======
void Java_org_rocksdb_BackupEngine_purgeOldBackups(
    JNIEnv* env, jobject jbe, jlong jbe_handle, jint jnum_backups_to_keep) {
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  auto status =
      backup_engine->
          PurgeOldBackups(static_cast<uint32_t>(jnum_backups_to_keep));
>>>>>>> blood in blood out

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    deleteBackup
 * Signature: (JI)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_BackupEngine_deleteBackup(JNIEnv* env, jobject /*jbe*/,
                                                jlong jbe_handle,
                                                jint jbackup_id) {
=======
void Java_org_rocksdb_BackupEngine_deleteBackup(
    JNIEnv* env, jobject jbe, jlong jbe_handle, jint jbackup_id) {
>>>>>>> blood in blood out
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  auto status =
      backup_engine->DeleteBackup(static_cast<rocksdb::BackupID>(jbackup_id));

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    restoreDbFromBackup
 * Signature: (JILjava/lang/String;Ljava/lang/String;J)V
 */
void Java_org_rocksdb_BackupEngine_restoreDbFromBackup(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jbe*/, jlong jbe_handle, jint jbackup_id,
    jstring jdb_dir, jstring jwal_dir, jlong jrestore_options_handle) {
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  const char* db_dir = env->GetStringUTFChars(jdb_dir, nullptr);
  if (db_dir == nullptr) {
=======
    JNIEnv* env, jobject jbe, jlong jbe_handle, jint jbackup_id,
    jstring jdb_dir, jstring jwal_dir, jlong jrestore_options_handle) {
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  const char* db_dir = env->GetStringUTFChars(jdb_dir, nullptr);
  if(db_dir == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return;
  }
  const char* wal_dir = env->GetStringUTFChars(jwal_dir, nullptr);
<<<<<<< HEAD
  if (wal_dir == nullptr) {
=======
  if(wal_dir == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    env->ReleaseStringUTFChars(jdb_dir, db_dir);
    return;
  }
  auto* restore_options =
      reinterpret_cast<rocksdb::RestoreOptions*>(jrestore_options_handle);
<<<<<<< HEAD
  auto status = backup_engine->RestoreDBFromBackup(
      static_cast<rocksdb::BackupID>(jbackup_id), db_dir, wal_dir,
      *restore_options);
=======
  auto status =
      backup_engine->RestoreDBFromBackup(
          static_cast<rocksdb::BackupID>(jbackup_id), db_dir, wal_dir,
          *restore_options);
>>>>>>> blood in blood out

  env->ReleaseStringUTFChars(jwal_dir, wal_dir);
  env->ReleaseStringUTFChars(jdb_dir, db_dir);

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    restoreDbFromLatestBackup
 * Signature: (JLjava/lang/String;Ljava/lang/String;J)V
 */
void Java_org_rocksdb_BackupEngine_restoreDbFromLatestBackup(
<<<<<<< HEAD
    JNIEnv* env, jobject /*jbe*/, jlong jbe_handle, jstring jdb_dir,
    jstring jwal_dir, jlong jrestore_options_handle) {
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  const char* db_dir = env->GetStringUTFChars(jdb_dir, nullptr);
  if (db_dir == nullptr) {
=======
    JNIEnv* env, jobject jbe, jlong jbe_handle, jstring jdb_dir,
    jstring jwal_dir, jlong jrestore_options_handle) {
  auto* backup_engine = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  const char* db_dir = env->GetStringUTFChars(jdb_dir, nullptr);
  if(db_dir == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    return;
  }
  const char* wal_dir = env->GetStringUTFChars(jwal_dir, nullptr);
<<<<<<< HEAD
  if (wal_dir == nullptr) {
=======
  if(wal_dir == nullptr) {
>>>>>>> blood in blood out
    // exception thrown: OutOfMemoryError
    env->ReleaseStringUTFChars(jdb_dir, db_dir);
    return;
  }
  auto* restore_options =
      reinterpret_cast<rocksdb::RestoreOptions*>(jrestore_options_handle);
<<<<<<< HEAD
  auto status = backup_engine->RestoreDBFromLatestBackup(db_dir, wal_dir,
                                                         *restore_options);
=======
  auto status =
      backup_engine->RestoreDBFromLatestBackup(db_dir, wal_dir,
          *restore_options);
>>>>>>> blood in blood out

  env->ReleaseStringUTFChars(jwal_dir, wal_dir);
  env->ReleaseStringUTFChars(jdb_dir, db_dir);

  if (status.ok()) {
    return;
  }

  rocksdb::RocksDBExceptionJni::ThrowNew(env, status);
}

/*
 * Class:     org_rocksdb_BackupEngine
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_BackupEngine_disposeInternal(JNIEnv* /*env*/,
                                                   jobject /*jbe*/,
                                                   jlong jbe_handle) {
=======
void Java_org_rocksdb_BackupEngine_disposeInternal(
    JNIEnv* env, jobject jbe, jlong jbe_handle) {
>>>>>>> blood in blood out
  auto* be = reinterpret_cast<rocksdb::BackupEngine*>(jbe_handle);
  assert(be != nullptr);
  delete be;
}
