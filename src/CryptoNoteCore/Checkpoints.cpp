// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
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

#include "Checkpoints.h"
<<<<<<< HEAD

#include <Common/StringTools.h>

#include <config/Constants.h>

#include <fstream>
=======
#include "Common/StringTools.h"
#include <boost/regex.hpp>
>>>>>>> blood in blood out

using namespace Logging;

namespace CryptoNote {
//---------------------------------------------------------------------------
<<<<<<< HEAD
Checkpoints::Checkpoints(std::shared_ptr<Logging::ILogger> log) : logger(log, "checkpoints") {}
//---------------------------------------------------------------------------
bool Checkpoints::addCheckpoint(uint32_t index, const std::string &hash_str) {
  Crypto::Hash h = Constants::NULL_HASH;
=======
Checkpoints::Checkpoints(Logging::ILogger &log) : logger(log, "checkpoints") {}
//---------------------------------------------------------------------------
bool Checkpoints::addCheckpoint(uint32_t index, const std::string &hash_str) {
  Crypto::Hash h = NULL_HASH;
>>>>>>> blood in blood out

  if (!Common::podFromHex(hash_str, h)) {
    logger(ERROR, BRIGHT_RED) << "INVALID HASH IN CHECKPOINTS!";
    return false;
  }

<<<<<<< HEAD
  /* The return value lets us check if it was inserted or not. If it wasn't,
     there is already a key (i.e., a height value) existing */
  if (!points.insert({index, h}).second)
  {
=======
  if (!(0 == points.count(index))) {
>>>>>>> blood in blood out
    logger(ERROR, BRIGHT_RED) << "CHECKPOINT ALREADY EXISTS!";
    return false;
  }

<<<<<<< HEAD
  return true;
}

bool Checkpoints::loadCheckpointsFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        logger(ERROR, BRIGHT_RED) << "Could not load checkpoints file: "
                                  << filename;

        return false;
    }

    /* The block this checkpoint is for (as a string) */
    std::string indexString;

    /* The hash this block has (as a string) */
    std::string hash;

    /* The block index (as a uint64_t) */
    uint64_t index;

    /* Checkpoints file has this format:

       index,hash
       index2,hash2

       So, we do std::getline() on the file with the delimiter as ',' to take
       the index, then we do std::getline() on the file again with the standard
       delimiter of '\n', to get the hash. */
    while (std::getline(file, indexString, ','), std::getline(file, hash))
    {
        /* Try and parse the indexString as an int */
        try
        {
            index = std::stoull(indexString);
        }
        catch (const std::out_of_range &)
        {
            logger(ERROR, BRIGHT_RED) << "Invalid checkpoint file format - "
                                      << "height is out of range of uint64_t";
        }
        catch (const std::invalid_argument &)
        {
            logger(ERROR, BRIGHT_RED) << "Invalid checkpoint file format - "
                                      << "could not parse height as a number";

            return false;
        }

        /* Failed to parse hash, or checkpoint already exists */
        if (!addCheckpoint(index, hash))
        {
            return false;
        }
    }

    logger(INFO) << "Loaded " << points.size() << " checkpoints from "
                 << filename;

    return true;
}

=======
  points[index] = h;
  return true;
}
//---------------------------------------------------------------------------
const boost::regex linesregx("\\r\\n|\\n\\r|\\n|\\r");
const boost::regex fieldsregx(",(?=(?:[^\"]*\"[^\"]*\")*(?![^\"]*\"))");
bool Checkpoints::loadCheckpointsFromFile(const std::string& fileName) {
  std::string buff;
  if (!Common::loadFileToString(fileName, buff)) {
    logger(ERROR, BRIGHT_RED) << "Could not load checkpoints file: " << fileName;
    return false;
  }
  const char* data = buff.c_str();
  unsigned int length = strlen(data);

  boost::cregex_token_iterator li(data, data + length, linesregx, -1);
  boost::cregex_token_iterator end;

  int count = 0;
  while (li != end) {
    std::string line = li->str();
    ++li;
 
    boost::sregex_token_iterator ti(line.begin(), line.end(), fieldsregx, -1);
    boost::sregex_token_iterator end2;
 
    std::vector<std::string> row;
    while (ti != end2) {
      std::string token = ti->str();
      ++ti;
      row.push_back(token);
    }
    if (row.size() != 2) {
      logger(ERROR, BRIGHT_RED) << "Invalid checkpoint file format";
      return false;
    } else {
      uint32_t height = stoi(row[0]);
      bool r = addCheckpoint(height, row[1]);
      if (!r) {
        return false;
      }
      count += 1;
    }
  }

  logger(INFO) << "Loaded " << count << " checkpoints from " << fileName;
  return true;
}
>>>>>>> blood in blood out
//---------------------------------------------------------------------------
bool Checkpoints::isInCheckpointZone(uint32_t index) const {
  return !points.empty() && (index <= (--points.end())->first);
}
//---------------------------------------------------------------------------
bool Checkpoints::checkBlock(uint32_t index, const Crypto::Hash &h,
                            bool& isCheckpoint) const {
  auto it = points.find(index);
  isCheckpoint = it != points.end();
  if (!isCheckpoint)
    return true;

  if (it->second == h) {
    if (index % 100 == 0) {
      logger(Logging::INFO, BRIGHT_GREEN)
        << "CHECKPOINT PASSED FOR INDEX " << index << " " << h;
    }
    return true;
  } else {
    logger(Logging::WARNING, BRIGHT_YELLOW) << "CHECKPOINT FAILED FOR HEIGHT " << index
                                            << ". EXPECTED HASH: " << it->second
                                            << ", FETCHED HASH: " << h;
    return false;
  }
}
//---------------------------------------------------------------------------
bool Checkpoints::checkBlock(uint32_t index, const Crypto::Hash &h) const {
  bool ignored;
  return checkBlock(index, h, ignored);
}
<<<<<<< HEAD
=======
//---------------------------------------------------------------------------
bool Checkpoints::isAlternativeBlockAllowed(uint32_t  blockchainSize,
                                            uint32_t  blockIndex) const {
  if (blockchainSize == 0) {
    return false;
  }

  auto it = points.upper_bound(blockchainSize);
  // Is blockchainSize before the first checkpoint?
  if (it == points.begin()) {
    return true;
  }

  --it;
  uint32_t checkpointIndex = it->first;
  return checkpointIndex < blockIndex;
}

std::vector<uint32_t> Checkpoints::getCheckpointHeights() const {
  std::vector<uint32_t> checkpointHeights;
  checkpointHeights.reserve(points.size());
  for (const auto& it : points) {
    checkpointHeights.push_back(it.first);
  }

  return checkpointHeights;
}
>>>>>>> blood in blood out

}
