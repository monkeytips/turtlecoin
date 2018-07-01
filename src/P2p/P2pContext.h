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

#include <chrono>
#include <vector>

#include <System/ContextGroup.h>
#include <System/Dispatcher.h>
#include <System/Event.h>
#include <System/TcpConnection.h>
#include <System/Timer.h>

<<<<<<< HEAD
#include <config/CryptoNoteConfig.h>
=======
#include "CryptoNoteConfig.h"
>>>>>>> blood in blood out
#include "LevinProtocol.h"
#include "P2pInterfaces.h"
#include "P2pProtocolDefinitions.h"
#include "P2pProtocolTypes.h"

namespace CryptoNote {
  
class P2pContext {
public:
  using Clock = std::chrono::steady_clock;
  using TimePoint = Clock::time_point;

  struct Message : P2pMessage {
    enum Type {
      NOTIFY,
      REQUEST,
      REPLY
    };

    Type messageType;
    uint32_t returnCode;

    Message(P2pMessage&& msg, Type messageType, uint32_t returnCode = 0);
    size_t size() const;
  };

  P2pContext(System::Dispatcher& dispatcher, System::TcpConnection&& conn, 
    bool isIncoming, const NetworkAddress& remoteAddress, std::chrono::nanoseconds timedSyncInterval, const CORE_SYNC_DATA& timedSyncData);
  ~P2pContext();

<<<<<<< HEAD
  uint64_t getPeerId() const;
=======
  PeerIdType getPeerId() const;
>>>>>>> blood in blood out
  uint16_t getPeerPort() const;
  const NetworkAddress& getRemoteAddress() const;
  bool isIncoming() const;

<<<<<<< HEAD
  void setPeerInfo(uint8_t protocolVersion, uint64_t id, uint16_t port);
=======
  void setPeerInfo(uint8_t protocolVersion, PeerIdType id, uint16_t port);
>>>>>>> blood in blood out
  bool readCommand(LevinProtocol::Command& cmd);
  void writeMessage(const Message& msg);
 
  void start();
  void stop();

private:

  uint8_t version = 0;
  const bool incoming;
  const NetworkAddress remoteAddress;
<<<<<<< HEAD
  uint64_t peerId = 0;
=======
  PeerIdType peerId = 0;
>>>>>>> blood in blood out
  uint16_t peerPort = 0;

  System::Dispatcher& dispatcher;
  System::ContextGroup contextGroup;
  const TimePoint timeStarted;
  bool stopped = false;
  TimePoint lastReadTime;

  // timed sync info
  const std::chrono::nanoseconds timedSyncInterval;
  const CORE_SYNC_DATA& timedSyncData;
  System::Timer timedSyncTimer;
  System::Event timedSyncFinished;

  System::TcpConnection connection;
  System::Event writeEvent;
  System::Event readEvent;

  void timedSyncLoop();
};

P2pContext::Message makeReply(uint32_t command, const BinaryArray& data, uint32_t returnCode);
P2pContext::Message makeRequest(uint32_t command, const BinaryArray& data);

std::ostream& operator <<(std::ostream& s, const P2pContext& conn);

}
