// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
<<<<<<< HEAD
// Copyright (c) 2018, The TurtleCoin Developers
// Copyright (c) 2019, The CyprusCoin Developers
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
#include "P2pProtocolTypes.h"

namespace CryptoNote {

class NetNodeConfig {
public:
  NetNodeConfig();
<<<<<<< HEAD
  bool init(const std::string interface, const int port, const int external, const bool localIp,
              const bool hidePort, const std::string dataDir, const std::vector<std::string> addPeers,
              const std::vector<std::string> addExclusiveNodes, const std::vector<std::string> addPriorityNodes,
              const std::vector<std::string> addSeedNodes, const bool p2pResetPeerState);

  std::string getP2pStateFilename() const;
  bool getTestnet() const;
  bool getP2pStateReset() const;
=======
  static void initOptions(boost::program_options::options_description& desc);
  bool init(const boost::program_options::variables_map& vm);

  std::string getP2pStateFilename() const;
  bool getTestnet() const;
>>>>>>> blood in blood out
  std::string getBindIp() const;
  uint16_t getBindPort() const;
  uint16_t getExternalPort() const;
  bool getAllowLocalIp() const;
  std::vector<PeerlistEntry> getPeers() const;
  std::vector<NetworkAddress> getPriorityNodes() const;
  std::vector<NetworkAddress> getExclusiveNodes() const;
  std::vector<NetworkAddress> getSeedNodes() const;
  bool getHideMyPort() const;
  std::string getConfigFolder() const;

<<<<<<< HEAD
=======
  void setP2pStateFilename(const std::string& filename);
  void setTestnet(bool isTestnet);
  void setBindIp(const std::string& ip);
  void setBindPort(uint16_t port);
  void setExternalPort(uint16_t port);
  void setAllowLocalIp(bool allow);
  void setPeers(const std::vector<PeerlistEntry>& peerList);
  void setPriorityNodes(const std::vector<NetworkAddress>& addresses);
  void setExclusiveNodes(const std::vector<NetworkAddress>& addresses);
  void setSeedNodes(const std::vector<NetworkAddress>& addresses);
  void setHideMyPort(bool hide);
  void setConfigFolder(const std::string& folder);

>>>>>>> blood in blood out
private:
  std::string bindIp;
  uint16_t bindPort;
  uint16_t externalPort;
  bool allowLocalIp;
  std::vector<PeerlistEntry> peers;
  std::vector<NetworkAddress> priorityNodes;
  std::vector<NetworkAddress> exclusiveNodes;
  std::vector<NetworkAddress> seedNodes;
  bool hideMyPort;
  std::string configFolder;
  std::string p2pStateFilename;
  bool testnet;
<<<<<<< HEAD
  bool p2pStateReset;
=======
>>>>>>> blood in blood out
};

} //namespace nodetool
