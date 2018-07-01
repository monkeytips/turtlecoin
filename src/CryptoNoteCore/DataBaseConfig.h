// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
<<<<<<< HEAD
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

#include <cstdint>
#include <vector>
#include <string>

<<<<<<< HEAD
=======
#include <boost/program_options.hpp>

>>>>>>> blood in blood out
namespace CryptoNote {

class DataBaseConfig {
public:
  DataBaseConfig();
<<<<<<< HEAD
  bool init(
    const std::string dataDirectory, const int backgroundThreads, const int maxOpenFiles, 
    const int writeBufferSizeMB, const int readCacheSizeMB, const bool enableDbCompression);
=======
  static void initOptions(boost::program_options::options_description& desc);
  bool init(const boost::program_options::variables_map& vm);
>>>>>>> blood in blood out

  bool isConfigFolderDefaulted() const;
  std::string getDataDir() const;
  uint16_t getBackgroundThreadsCount() const;
  uint32_t getMaxOpenFiles() const;
  uint64_t getWriteBufferSize() const; //Bytes
  uint64_t getReadCacheSize() const; //Bytes
  bool getTestnet() const;
<<<<<<< HEAD
  bool getCompressionEnabled() const;
=======

  void setConfigFolderDefaulted(bool defaulted);
  void setDataDir(const std::string& dataDir);
  void setBackgroundThreadsCount(uint16_t backgroundThreadsCount);
  void setMaxOpenFiles(uint32_t maxOpenFiles);
  void setWriteBufferSize(uint64_t writeBufferSize); //Bytes
  void setReadCacheSize(uint64_t readCacheSize); //Bytes
  void setTestnet(bool testnet);
>>>>>>> blood in blood out

private:
  bool configFolderDefaulted;
  std::string dataDir;
  uint16_t backgroundThreadsCount;
  uint32_t maxOpenFiles;
  uint64_t writeBufferSize;
  uint64_t readCacheSize;
  bool testnet;
<<<<<<< HEAD
  bool compressionEnabled;
=======
>>>>>>> blood in blood out
};
} //namespace CryptoNote
