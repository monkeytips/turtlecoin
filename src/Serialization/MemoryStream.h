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

#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring> // memcpy
#include <vector>
#include <Common/IOutputStream.h>

namespace CryptoNote {

class MemoryStream: public Common::IOutputStream {
public:

  MemoryStream() : m_writePos(0) {
  }

<<<<<<< HEAD
  virtual uint64_t writeSome(const void* data, uint64_t size) override {
=======
  virtual size_t writeSome(const void* data, size_t size) override {
>>>>>>> blood in blood out
    if (size == 0) {
      return 0;
    }

    if (m_writePos + size > m_buffer.size()) {
      m_buffer.resize(m_writePos + size);
    }

    memcpy(&m_buffer[m_writePos], data, size);
    m_writePos += size;
    return size;
  }

<<<<<<< HEAD
  uint64_t size() {
=======
  size_t size() {
>>>>>>> blood in blood out
    return m_buffer.size();
  }

  const uint8_t* data() {
    return m_buffer.data();
  }

  void clear() {
    m_writePos = 0;
    m_buffer.resize(0);
  }

private:
<<<<<<< HEAD
  uint64_t m_writePos;
=======
  size_t m_writePos;
>>>>>>> blood in blood out
  std::vector<uint8_t> m_buffer;
};

}
