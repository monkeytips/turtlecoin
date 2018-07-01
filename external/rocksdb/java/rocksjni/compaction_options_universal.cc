// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ for
// rocksdb::CompactionOptionsUniversal.

#include <jni.h>

#include "include/org_rocksdb_CompactionOptionsUniversal.h"
#include "rocksdb/advanced_options.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    newCompactionOptionsUniversal
 * Signature: ()J
 */
jlong Java_org_rocksdb_CompactionOptionsUniversal_newCompactionOptionsUniversal(
<<<<<<< HEAD
    JNIEnv* /*env*/, jclass /*jcls*/) {
=======
    JNIEnv* env, jclass jcls) {
>>>>>>> blood in blood out
  const auto* opt = new rocksdb::CompactionOptionsUniversal();
  return reinterpret_cast<jlong>(opt);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setSizeRatio
 * Signature: (JI)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setSizeRatio(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle, jint jsize_ratio) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jint jsize_ratio) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->size_ratio = static_cast<unsigned int>(jsize_ratio);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    sizeRatio
 * Signature: (J)I
 */
<<<<<<< HEAD
jint Java_org_rocksdb_CompactionOptionsUniversal_sizeRatio(JNIEnv* /*env*/,
                                                           jobject /*jobj*/,
                                                           jlong jhandle) {
=======
jint Java_org_rocksdb_CompactionOptionsUniversal_sizeRatio(
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return static_cast<jint>(opt->size_ratio);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setMinMergeWidth
 * Signature: (JI)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setMinMergeWidth(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle, jint jmin_merge_width) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jint jmin_merge_width) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->min_merge_width = static_cast<unsigned int>(jmin_merge_width);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    minMergeWidth
 * Signature: (J)I
 */
<<<<<<< HEAD
jint Java_org_rocksdb_CompactionOptionsUniversal_minMergeWidth(JNIEnv* /*env*/,
                                                               jobject /*jobj*/,
                                                               jlong jhandle) {
=======
jint Java_org_rocksdb_CompactionOptionsUniversal_minMergeWidth(
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return static_cast<jint>(opt->min_merge_width);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setMaxMergeWidth
 * Signature: (JI)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setMaxMergeWidth(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle, jint jmax_merge_width) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jint jmax_merge_width) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->max_merge_width = static_cast<unsigned int>(jmax_merge_width);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    maxMergeWidth
 * Signature: (J)I
 */
<<<<<<< HEAD
jint Java_org_rocksdb_CompactionOptionsUniversal_maxMergeWidth(JNIEnv* /*env*/,
                                                               jobject /*jobj*/,
                                                               jlong jhandle) {
=======
jint Java_org_rocksdb_CompactionOptionsUniversal_maxMergeWidth(
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return static_cast<jint>(opt->max_merge_width);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setMaxSizeAmplificationPercent
 * Signature: (JI)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setMaxSizeAmplificationPercent(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
=======
    JNIEnv* env, jobject jobj, jlong jhandle,
>>>>>>> blood in blood out
    jint jmax_size_amplification_percent) {
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->max_size_amplification_percent =
      static_cast<unsigned int>(jmax_size_amplification_percent);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    maxSizeAmplificationPercent
 * Signature: (J)I
 */
jint Java_org_rocksdb_CompactionOptionsUniversal_maxSizeAmplificationPercent(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return static_cast<jint>(opt->max_size_amplification_percent);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setCompressionSizePercent
 * Signature: (JI)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setCompressionSizePercent(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
    jint jcompression_size_percent) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jint jcompression_size_percent) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->compression_size_percent =
      static_cast<unsigned int>(jcompression_size_percent);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    compressionSizePercent
 * Signature: (J)I
 */
jint Java_org_rocksdb_CompactionOptionsUniversal_compressionSizePercent(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return static_cast<jint>(opt->compression_size_percent);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setStopStyle
 * Signature: (JB)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setStopStyle(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle, jbyte jstop_style_value) {
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->stop_style = rocksdb::CompactionStopStyleJni::toCppCompactionStopStyle(
      jstop_style_value);
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jbyte jstop_style_value) {
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->stop_style =
      rocksdb::CompactionStopStyleJni::toCppCompactionStopStyle(
          jstop_style_value); 
>>>>>>> blood in blood out
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    stopStyle
 * Signature: (J)B
 */
<<<<<<< HEAD
jbyte Java_org_rocksdb_CompactionOptionsUniversal_stopStyle(JNIEnv* /*env*/,
                                                            jobject /*jobj*/,
                                                            jlong jhandle) {
=======
jbyte Java_org_rocksdb_CompactionOptionsUniversal_stopStyle(
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return rocksdb::CompactionStopStyleJni::toJavaCompactionStopStyle(
      opt->stop_style);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    setAllowTrivialMove
 * Signature: (JZ)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_setAllowTrivialMove(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle,
    jboolean jallow_trivial_move) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle, jboolean jallow_trivial_move) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  opt->allow_trivial_move = static_cast<bool>(jallow_trivial_move);
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    allowTrivialMove
 * Signature: (J)Z
 */
jboolean Java_org_rocksdb_CompactionOptionsUniversal_allowTrivialMove(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  auto* opt = reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
  return opt->allow_trivial_move;
}

/*
 * Class:     org_rocksdb_CompactionOptionsUniversal
 * Method:    disposeInternal
 * Signature: (J)V
 */
void Java_org_rocksdb_CompactionOptionsUniversal_disposeInternal(
<<<<<<< HEAD
    JNIEnv* /*env*/, jobject /*jobj*/, jlong jhandle) {
=======
    JNIEnv* env, jobject jobj, jlong jhandle) {
>>>>>>> blood in blood out
  delete reinterpret_cast<rocksdb::CompactionOptionsUniversal*>(jhandle);
}
