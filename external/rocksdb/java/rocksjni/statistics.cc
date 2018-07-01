// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling c++ rocksdb::Statistics methods from Java side.

#include <jni.h>
#include <memory>
#include <set>

#include "include/org_rocksdb_Statistics.h"
<<<<<<< HEAD
#include "rocksdb/statistics.h"
#include "rocksjni/portal.h"
#include "rocksjni/statisticsjni.h"
=======
#include "rocksjni/portal.h"
#include "rocksjni/statisticsjni.h"
#include "rocksdb/statistics.h"
>>>>>>> blood in blood out

/*
 * Class:     org_rocksdb_Statistics
 * Method:    newStatistics
 * Signature: ()J
 */
jlong Java_org_rocksdb_Statistics_newStatistics__(JNIEnv* env, jclass jcls) {
<<<<<<< HEAD
  return Java_org_rocksdb_Statistics_newStatistics___3BJ(env, jcls, nullptr, 0);
=======
  return Java_org_rocksdb_Statistics_newStatistics___3BJ(
      env, jcls, nullptr, 0);
>>>>>>> blood in blood out
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    newStatistics
 * Signature: (J)J
 */
jlong Java_org_rocksdb_Statistics_newStatistics__J(
    JNIEnv* env, jclass jcls, jlong jother_statistics_handle) {
  return Java_org_rocksdb_Statistics_newStatistics___3BJ(
      env, jcls, nullptr, jother_statistics_handle);
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    newStatistics
 * Signature: ([B)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_Statistics_newStatistics___3B(JNIEnv* env, jclass jcls,
                                                     jbyteArray jhistograms) {
  return Java_org_rocksdb_Statistics_newStatistics___3BJ(env, jcls, jhistograms,
                                                         0);
=======
jlong Java_org_rocksdb_Statistics_newStatistics___3B(
    JNIEnv* env, jclass jcls, jbyteArray jhistograms) {
  return Java_org_rocksdb_Statistics_newStatistics___3BJ(
      env, jcls, jhistograms, 0);
>>>>>>> blood in blood out
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    newStatistics
 * Signature: ([BJ)J
 */
jlong Java_org_rocksdb_Statistics_newStatistics___3BJ(
<<<<<<< HEAD
    JNIEnv* env, jclass /*jcls*/, jbyteArray jhistograms,
    jlong jother_statistics_handle) {
=======
    JNIEnv* env, jclass jcls, jbyteArray jhistograms,
    jlong jother_statistics_handle) {

>>>>>>> blood in blood out
  std::shared_ptr<rocksdb::Statistics>* pSptr_other_statistics = nullptr;
  if (jother_statistics_handle > 0) {
    pSptr_other_statistics =
        reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(
            jother_statistics_handle);
  }

  std::set<uint32_t> histograms;
  if (jhistograms != nullptr) {
    const jsize len = env->GetArrayLength(jhistograms);
    if (len > 0) {
      jbyte* jhistogram = env->GetByteArrayElements(jhistograms, nullptr);
<<<<<<< HEAD
      if (jhistogram == nullptr) {
=======
      if (jhistogram == nullptr ) {
>>>>>>> blood in blood out
        // exception thrown: OutOfMemoryError
        return 0;
      }

      for (jsize i = 0; i < len; i++) {
        const rocksdb::Histograms histogram =
            rocksdb::HistogramTypeJni::toCppHistograms(jhistogram[i]);
        histograms.emplace(histogram);
      }

      env->ReleaseByteArrayElements(jhistograms, jhistogram, JNI_ABORT);
    }
  }

  std::shared_ptr<rocksdb::Statistics> sptr_other_statistics = nullptr;
  if (pSptr_other_statistics != nullptr) {
<<<<<<< HEAD
    sptr_other_statistics = *pSptr_other_statistics;
=======
      sptr_other_statistics =   *pSptr_other_statistics;
>>>>>>> blood in blood out
  }

  auto* pSptr_statistics = new std::shared_ptr<rocksdb::StatisticsJni>(
      new rocksdb::StatisticsJni(sptr_other_statistics, histograms));

  return reinterpret_cast<jlong>(pSptr_statistics);
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    disposeInternal
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_Statistics_disposeInternal(JNIEnv* /*env*/,
                                                 jobject /*jobj*/,
                                                 jlong jhandle) {
  if (jhandle > 0) {
=======
void Java_org_rocksdb_Statistics_disposeInternal(
    JNIEnv* env, jobject jobj, jlong jhandle) {
  if(jhandle > 0) {
>>>>>>> blood in blood out
    auto* pSptr_statistics =
        reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
    delete pSptr_statistics;
  }
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    statsLevel
 * Signature: (J)B
 */
<<<<<<< HEAD
jbyte Java_org_rocksdb_Statistics_statsLevel(JNIEnv* /*env*/, jobject /*jobj*/,
                                             jlong jhandle) {
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  return rocksdb::StatsLevelJni::toJavaStatsLevel(
      pSptr_statistics->get()->stats_level_);
=======
jbyte Java_org_rocksdb_Statistics_statsLevel(
    JNIEnv* env, jobject jobj, jlong jhandle) {
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  return rocksdb::StatsLevelJni::toJavaStatsLevel(pSptr_statistics->get()->stats_level_);
>>>>>>> blood in blood out
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    setStatsLevel
 * Signature: (JB)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_Statistics_setStatsLevel(JNIEnv* /*env*/,
                                               jobject /*jobj*/, jlong jhandle,
                                               jbyte jstats_level) {
=======
void Java_org_rocksdb_Statistics_setStatsLevel(
    JNIEnv* env, jobject jobj, jlong jhandle, jbyte jstats_level) {
>>>>>>> blood in blood out
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  auto stats_level = rocksdb::StatsLevelJni::toCppStatsLevel(jstats_level);
  pSptr_statistics->get()->stats_level_ = stats_level;
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    getTickerCount
 * Signature: (JB)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_Statistics_getTickerCount(JNIEnv* /*env*/,
                                                 jobject /*jobj*/,
                                                 jlong jhandle,
                                                 jbyte jticker_type) {
=======
jlong Java_org_rocksdb_Statistics_getTickerCount(
    JNIEnv* env, jobject jobj, jlong jhandle, jbyte jticker_type) {
>>>>>>> blood in blood out
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  auto ticker = rocksdb::TickerTypeJni::toCppTickers(jticker_type);
  return pSptr_statistics->get()->getTickerCount(ticker);
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    getAndResetTickerCount
 * Signature: (JB)J
 */
<<<<<<< HEAD
jlong Java_org_rocksdb_Statistics_getAndResetTickerCount(JNIEnv* /*env*/,
                                                         jobject /*jobj*/,
                                                         jlong jhandle,
                                                         jbyte jticker_type) {
=======
jlong Java_org_rocksdb_Statistics_getAndResetTickerCount(
    JNIEnv* env, jobject jobj, jlong jhandle, jbyte jticker_type) {
>>>>>>> blood in blood out
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  auto ticker = rocksdb::TickerTypeJni::toCppTickers(jticker_type);
  return pSptr_statistics->get()->getAndResetTickerCount(ticker);
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    getHistogramData
 * Signature: (JB)Lorg/rocksdb/HistogramData;
 */
<<<<<<< HEAD
jobject Java_org_rocksdb_Statistics_getHistogramData(JNIEnv* env,
                                                     jobject /*jobj*/,
                                                     jlong jhandle,
                                                     jbyte jhistogram_type) {
=======
jobject Java_org_rocksdb_Statistics_getHistogramData(
    JNIEnv* env, jobject jobj, jlong jhandle, jbyte jhistogram_type) {
>>>>>>> blood in blood out
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);

<<<<<<< HEAD
  rocksdb::HistogramData
      data;  // TODO(AR) perhaps better to construct a Java Object Wrapper that
             // uses ptr to C++ `new HistogramData`
=======
  rocksdb::HistogramData data;  // TODO(AR) perhaps better to construct a Java Object Wrapper that uses ptr to C++ `new HistogramData`
>>>>>>> blood in blood out
  auto histogram = rocksdb::HistogramTypeJni::toCppHistograms(jhistogram_type);
  pSptr_statistics->get()->histogramData(
      static_cast<rocksdb::Histograms>(histogram), &data);

  jclass jclazz = rocksdb::HistogramDataJni::getJClass(env);
<<<<<<< HEAD
  if (jclazz == nullptr) {
=======
  if(jclazz == nullptr) {
>>>>>>> blood in blood out
    // exception occurred accessing class
    return nullptr;
  }

<<<<<<< HEAD
  jmethodID mid = rocksdb::HistogramDataJni::getConstructorMethodId(env);
  if (mid == nullptr) {
=======
  jmethodID mid = rocksdb::HistogramDataJni::getConstructorMethodId(
      env);
  if(mid == nullptr) {
>>>>>>> blood in blood out
    // exception occurred accessing method
    return nullptr;
  }

<<<<<<< HEAD
  return env->NewObject(jclazz, mid, data.median, data.percentile95,
                        data.percentile99, data.average,
                        data.standard_deviation);
=======
  return env->NewObject(
      jclazz,
      mid, data.median, data.percentile95,data.percentile99, data.average,
      data.standard_deviation);
>>>>>>> blood in blood out
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    getHistogramString
 * Signature: (JB)Ljava/lang/String;
 */
<<<<<<< HEAD
jstring Java_org_rocksdb_Statistics_getHistogramString(JNIEnv* env,
                                                       jobject /*jobj*/,
                                                       jlong jhandle,
                                                       jbyte jhistogram_type) {
=======
jstring Java_org_rocksdb_Statistics_getHistogramString(
    JNIEnv* env, jobject jobj, jlong jhandle, jbyte jhistogram_type) {
>>>>>>> blood in blood out
  auto* pSptr_statistics =
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  auto histogram = rocksdb::HistogramTypeJni::toCppHistograms(jhistogram_type);
  auto str = pSptr_statistics->get()->getHistogramString(histogram);
  return env->NewStringUTF(str.c_str());
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    reset
 * Signature: (J)V
 */
<<<<<<< HEAD
void Java_org_rocksdb_Statistics_reset(JNIEnv* env, jobject /*jobj*/,
                                       jlong jhandle) {
  auto* pSptr_statistics =
=======
void Java_org_rocksdb_Statistics_reset(
    JNIEnv* env, jobject jobj, jlong jhandle) {
   auto* pSptr_statistics =
>>>>>>> blood in blood out
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  rocksdb::Status s = pSptr_statistics->get()->Reset();
  if (!s.ok()) {
<<<<<<< HEAD
    rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
=======
   rocksdb::RocksDBExceptionJni::ThrowNew(env, s);
>>>>>>> blood in blood out
  }
}

/*
 * Class:     org_rocksdb_Statistics
 * Method:    toString
 * Signature: (J)Ljava/lang/String;
 */
<<<<<<< HEAD
jstring Java_org_rocksdb_Statistics_toString(JNIEnv* env, jobject /*jobj*/,
                                             jlong jhandle) {
  auto* pSptr_statistics =
=======
jstring Java_org_rocksdb_Statistics_toString(
    JNIEnv* env, jobject jobj, jlong jhandle) {
   auto* pSptr_statistics =
>>>>>>> blood in blood out
      reinterpret_cast<std::shared_ptr<rocksdb::Statistics>*>(jhandle);
  assert(pSptr_statistics != nullptr);
  auto str = pSptr_statistics->get()->ToString();
  return env->NewStringUTF(str.c_str());
}
