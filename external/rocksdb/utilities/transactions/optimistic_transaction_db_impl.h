//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once
#ifndef ROCKSDB_LITE

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/utilities/optimistic_transaction_db.h"

namespace rocksdb {

class OptimisticTransactionDBImpl : public OptimisticTransactionDB {
 public:
  explicit OptimisticTransactionDBImpl(DB* db, bool take_ownership = true)
<<<<<<< HEAD
      : OptimisticTransactionDB(db), db_owner_(take_ownership) {}

  ~OptimisticTransactionDBImpl() {
    // Prevent this stackable from destroying
    // base db
    if (!db_owner_) {
      db_ = nullptr;
=======
      : OptimisticTransactionDB(db), db_(db), db_owner_(take_ownership) {}

  ~OptimisticTransactionDBImpl() {
    if (!db_owner_) {
      db_.release();
>>>>>>> blood in blood out
    }
  }

  Transaction* BeginTransaction(const WriteOptions& write_options,
                                const OptimisticTransactionOptions& txn_options,
                                Transaction* old_txn) override;

<<<<<<< HEAD
 private:

   bool db_owner_;
=======
  DB* GetBaseDB() override { return db_.get(); }

 private:
  std::unique_ptr<DB> db_;
  bool db_owner_;
>>>>>>> blood in blood out

  void ReinitializeTransaction(Transaction* txn,
                               const WriteOptions& write_options,
                               const OptimisticTransactionOptions& txn_options =
                                   OptimisticTransactionOptions());
};

}  //  namespace rocksdb
#endif  // ROCKSDB_LITE
