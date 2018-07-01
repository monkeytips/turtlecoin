// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
<<<<<<< HEAD
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2019, The CyprusCoin Developers
//
// Please see the included LICENSE file for more information.

#include "NetNodeConfig.h"

#include <Common/Util.h>
#include "Common/StringTools.h"
#include <config/CryptoNoteConfig.h>
#include <crypto/random.h>
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

#include "NetNodeConfig.h"

#include <boost/utility/value_init.hpp>

#include <Common/Util.h>
#include "Common/CommandLine.h"
#include "Common/StringTools.h"
#include "crypto/crypto.h"
#include "CryptoNoteConfig.h"
>>>>>>> blood in blood out

namespace CryptoNote {
namespace {

<<<<<<< HEAD
bool parsePeerFromString(NetworkAddress& pe, const std::string& node_addr)
{
  return Common::parseIpAddressAndPort(pe.ip, pe.port, node_addr);
}

bool parsePeersAndAddToNetworkContainer(const std::vector<std::string> peerList, std::vector<NetworkAddress>& container)
{
  for (const std::string& peer : peerList)
  {
    NetworkAddress networkAddress = NetworkAddress();
    if (!parsePeerFromString(networkAddress, peer))
    {
      return false;
    }
    container.push_back(networkAddress);
  }
  return true;
}

bool parsePeersAndAddToPeerListContainer(const std::vector<std::string> peerList, std::vector<PeerlistEntry>& container)
{
  for (const std::string& peer : peerList)
  {
    PeerlistEntry peerListEntry = PeerlistEntry();
    peerListEntry.id = Random::randomValue<uint64_t>();
    if (!parsePeerFromString(peerListEntry.adr, peer))
    {
      return false;
    }
    container.push_back(peerListEntry);
  }
=======
const command_line::arg_descriptor<std::string> arg_p2p_bind_ip        = {"p2p-bind-ip", "Interface for p2p network protocol", "0.0.0.0"};
const command_line::arg_descriptor<uint16_t>    arg_p2p_bind_port      = {"p2p-bind-port", "Port for p2p network protocol", P2P_DEFAULT_PORT};
const command_line::arg_descriptor<uint16_t>    arg_p2p_external_port = { "p2p-external-port", "External port for p2p network protocol (if port forwarding used with NAT)", 0 };
const command_line::arg_descriptor<bool>        arg_p2p_allow_local_ip = {"allow-local-ip", "Allow local ip add to peer list, mostly in debug purposes"};
const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_add_peer   = {"add-peer", "Manually add peer to local peerlist"};
const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_add_priority_node   = {"add-priority-node", "Specify list of peers to connect to and attempt to keep the connection open"};
const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_add_exclusive_node   = {"add-exclusive-node", "Specify list of peers to connect to only."
      " If this option is given the options add-priority-node and seed-node are ignored"};
const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_seed_node   = {"seed-node", "Connect to a node to retrieve peer addresses, and disconnect"};
const command_line::arg_descriptor<bool> arg_p2p_hide_my_port   =    {"hide-my-port", "Do not announce yourself as peerlist candidate", false, true};

bool parsePeerFromString(NetworkAddress& pe, const std::string& node_addr) {
  return Common::parseIpAddressAndPort(pe.ip, pe.port, node_addr);
}

bool parsePeersAndAddToContainer(const boost::program_options::variables_map& vm,
    const command_line::arg_descriptor<std::vector<std::string>>& arg, std::vector<NetworkAddress>& container)
{
  std::vector<std::string> peers = command_line::get_arg(vm, arg);

  for(const std::string& str: peers) {
    NetworkAddress na = boost::value_initialized<NetworkAddress>();
    if (!parsePeerFromString(na, str)) {
      return false;
    }
    container.push_back(na);
  }

>>>>>>> blood in blood out
  return true;
}

} //namespace

<<<<<<< HEAD
=======
void NetNodeConfig::initOptions(boost::program_options::options_description& desc) {
  command_line::add_arg(desc, arg_p2p_bind_ip);
  command_line::add_arg(desc, arg_p2p_bind_port);
  command_line::add_arg(desc, arg_p2p_external_port);
  command_line::add_arg(desc, arg_p2p_allow_local_ip);
  command_line::add_arg(desc, arg_p2p_add_peer);
  command_line::add_arg(desc, arg_p2p_add_priority_node);
  command_line::add_arg(desc, arg_p2p_add_exclusive_node);
  command_line::add_arg(desc, arg_p2p_seed_node);
  command_line::add_arg(desc, arg_p2p_hide_my_port);
}

>>>>>>> blood in blood out
NetNodeConfig::NetNodeConfig() {
  bindIp = "";
  bindPort = 0;
  externalPort = 0;
  allowLocalIp = false;
  hideMyPort = false;
  configFolder = Tools::getDefaultDataDirectory();
  testnet = false;
<<<<<<< HEAD
  p2pStateReset = false;
}

bool NetNodeConfig::init(const std::string interface, const int port, const int external, const bool localIp,
                          const bool hidePort, const std::string dataDir, const std::vector<std::string> addPeers,
                          const std::vector<std::string> addExclusiveNodes, const std::vector<std::string> addPriorityNodes,
                          const std::vector<std::string> addSeedNodes, const bool p2pResetPeerState)
{
  bindIp = interface;
  bindPort = port;
  externalPort = external;
  allowLocalIp = localIp;
  hideMyPort = hidePort;
  configFolder = dataDir;
  p2pStateFilename = CryptoNote::parameters::P2P_NET_DATA_FILENAME;
  p2pStateReset = p2pResetPeerState;

  if (!addPeers.empty())
  {
    if (!parsePeersAndAddToPeerListContainer(addPeers, peers))
    {
      return false;
    }
  }

  if (!addExclusiveNodes.empty())
  {
    if (!parsePeersAndAddToNetworkContainer(addExclusiveNodes, exclusiveNodes))
    {
      return false;
    }
  }

  if (!addPriorityNodes.empty())
  {
    if (!parsePeersAndAddToNetworkContainer(addPriorityNodes, priorityNodes))
    {
      return false;
    }
  }

  if (!addSeedNodes.empty())
  {
    if (!parsePeersAndAddToNetworkContainer(addSeedNodes, seedNodes))
    {
      return false;
    }
=======
}

bool NetNodeConfig::init(const boost::program_options::variables_map& vm)
{
  if (vm.count(arg_p2p_bind_ip.name) != 0 && (!vm[arg_p2p_bind_ip.name].defaulted() || bindIp.empty())) {
    bindIp = command_line::get_arg(vm, arg_p2p_bind_ip);
  }

  if (vm.count(arg_p2p_bind_port.name) != 0 && (!vm[arg_p2p_bind_port.name].defaulted() || bindPort == 0)) {
    bindPort = command_line::get_arg(vm, arg_p2p_bind_port);
  }

  if (vm.count(arg_p2p_external_port.name) != 0 && (!vm[arg_p2p_external_port.name].defaulted() || externalPort == 0)) {
    externalPort = command_line::get_arg(vm, arg_p2p_external_port);
  }

  if (vm.count(arg_p2p_allow_local_ip.name) != 0 && (!vm[arg_p2p_allow_local_ip.name].defaulted() || !allowLocalIp)) {
    allowLocalIp = command_line::get_arg(vm, arg_p2p_allow_local_ip);
  }

  if (vm.count(command_line::arg_data_dir.name) != 0 && (!vm[command_line::arg_data_dir.name].defaulted() || configFolder == Tools::getDefaultDataDirectory())) {
    configFolder = command_line::get_arg(vm, command_line::arg_data_dir);
  }

  p2pStateFilename = CryptoNote::parameters::P2P_NET_DATA_FILENAME;

  if (command_line::has_arg(vm, arg_p2p_add_peer)) {
    std::vector<std::string> perrs = command_line::get_arg(vm, arg_p2p_add_peer);
    for(const std::string& pr_str: perrs) {
      PeerlistEntry pe = boost::value_initialized<PeerlistEntry>();
      pe.id = Crypto::rand<uint64_t>();
      if (!parsePeerFromString(pe.adr, pr_str)) {
        return false;
      }

      peers.push_back(pe);
    }
  }

  if (command_line::has_arg(vm,arg_p2p_add_exclusive_node)) {
    if (!parsePeersAndAddToContainer(vm, arg_p2p_add_exclusive_node, exclusiveNodes))
      return false;
  }

  if (command_line::has_arg(vm, arg_p2p_add_priority_node)) {
    if (!parsePeersAndAddToContainer(vm, arg_p2p_add_priority_node, priorityNodes))
      return false;
  }

  if (command_line::has_arg(vm, arg_p2p_seed_node)) {
    if (!parsePeersAndAddToContainer(vm, arg_p2p_seed_node, seedNodes))
      return false;
  }

  if (command_line::has_arg(vm, arg_p2p_hide_my_port)) {
    hideMyPort = true;
>>>>>>> blood in blood out
  }

  return true;
}

<<<<<<< HEAD
=======
void NetNodeConfig::setTestnet(bool isTestnet) {
  testnet = isTestnet;
}

>>>>>>> blood in blood out
std::string NetNodeConfig::getP2pStateFilename() const {
  if (testnet) {
    return "testnet_" + p2pStateFilename;
  }

  return p2pStateFilename;
}

bool NetNodeConfig::getTestnet() const {
  return testnet;
}

<<<<<<< HEAD
bool NetNodeConfig::getP2pStateReset() const {
  return p2pStateReset;
}

=======
>>>>>>> blood in blood out
std::string NetNodeConfig::getBindIp() const {
  return bindIp;
}

uint16_t NetNodeConfig::getBindPort() const {
  return bindPort;
}

uint16_t NetNodeConfig::getExternalPort() const {
  return externalPort;
}

bool NetNodeConfig::getAllowLocalIp() const {
  return allowLocalIp;
}

std::vector<PeerlistEntry> NetNodeConfig::getPeers() const {
  return peers;
}

std::vector<NetworkAddress> NetNodeConfig::getPriorityNodes() const {
  return priorityNodes;
}

std::vector<NetworkAddress> NetNodeConfig::getExclusiveNodes() const {
  return exclusiveNodes;
}

std::vector<NetworkAddress> NetNodeConfig::getSeedNodes() const {
  return seedNodes;
}

bool NetNodeConfig::getHideMyPort() const {
  return hideMyPort;
}

std::string NetNodeConfig::getConfigFolder() const {
  return configFolder;
}

<<<<<<< HEAD
=======
void NetNodeConfig::setP2pStateFilename(const std::string& filename) {
  p2pStateFilename = filename;
}

void NetNodeConfig::setBindIp(const std::string& ip) {
  bindIp = ip;
}

void NetNodeConfig::setBindPort(uint16_t port) {
  bindPort = port;
}

void NetNodeConfig::setExternalPort(uint16_t port) {
  externalPort = port;
}

void NetNodeConfig::setAllowLocalIp(bool allow) {
  allowLocalIp = allow;
}

void NetNodeConfig::setPeers(const std::vector<PeerlistEntry>& peerList) {
  peers = peerList;
}

void NetNodeConfig::setPriorityNodes(const std::vector<NetworkAddress>& addresses) {
  priorityNodes = addresses;
}

void NetNodeConfig::setExclusiveNodes(const std::vector<NetworkAddress>& addresses) {
  exclusiveNodes = addresses;
}

void NetNodeConfig::setSeedNodes(const std::vector<NetworkAddress>& addresses) {
  seedNodes = addresses;
}

void NetNodeConfig::setHideMyPort(bool hide) {
  hideMyPort = hide;
}

void NetNodeConfig::setConfigFolder(const std::string& folder) {
  configFolder = folder;
}


>>>>>>> blood in blood out
} //namespace nodetool
