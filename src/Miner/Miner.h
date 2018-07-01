// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
<<<<<<< HEAD
// Copyright (c) 2014-2018, The Monero Project
// Copyright (c) 2018, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.
=======
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.
>>>>>>> blood in blood out

#pragma once

#include <atomic>
#include <thread>
<<<<<<< HEAD
#include <mutex>
=======
>>>>>>> blood in blood out

#include <System/Dispatcher.h>
#include <System/Event.h>
#include <System/RemoteContext.h>

#include "CryptoNote.h"
<<<<<<< HEAD

namespace CryptoNote {

struct BlockMiningParameters
{
    BlockTemplate blockTemplate;
    uint64_t difficulty;
};

class Miner
{
    public:
        Miner(System::Dispatcher& dispatcher);

        BlockTemplate mine(const BlockMiningParameters& blockMiningParameters, size_t threadCount);
        uint64_t getHashCount();

        //NOTE! this is blocking method
        void stop();

    private:
        System::Dispatcher& m_dispatcher;
        System::Event m_miningStopped;

        enum class MiningState : uint8_t { MINING_STOPPED, BLOCK_FOUND, MINING_IN_PROGRESS};
        std::atomic<MiningState> m_state;

        std::vector<std::unique_ptr<System::RemoteContext<void>>>  m_workers;

        BlockTemplate m_block;
        std::atomic<uint64_t> m_hash_count = 0;
        std::mutex m_hashes_mutex;

        void runWorkers(BlockMiningParameters blockMiningParameters, size_t threadCount);
        void workerFunc(const BlockTemplate& blockTemplate, uint64_t difficulty, uint32_t nonceStep);
        bool setStateBlockFound();
        void incrementHashCount();
=======
#include "CryptoNoteCore/Difficulty.h"

#include "Logging/LoggerRef.h"

namespace CryptoNote {

struct BlockMiningParameters {
  BlockTemplate blockTemplate;
  Difficulty difficulty;
};

class Miner {
public:
  Miner(System::Dispatcher& dispatcher, Logging::ILogger& logger);
  ~Miner();

  BlockTemplate mine(const BlockMiningParameters& blockMiningParameters, size_t threadCount);

  //NOTE! this is blocking method
  void stop();

private:
  System::Dispatcher& m_dispatcher;
  System::Event m_miningStopped;

  enum class MiningState : uint8_t { MINING_STOPPED, BLOCK_FOUND, MINING_IN_PROGRESS};
  std::atomic<MiningState> m_state;

  std::vector<std::unique_ptr<System::RemoteContext<void>>>  m_workers;

  BlockTemplate m_block;

  Logging::LoggerRef m_logger;

  void runWorkers(BlockMiningParameters blockMiningParameters, size_t threadCount);
  void workerFunc(const BlockTemplate& blockTemplate, Difficulty difficulty, uint32_t nonceStep);
  bool setStateBlockFound();
>>>>>>> blood in blood out
};

} //namespace CryptoNote
