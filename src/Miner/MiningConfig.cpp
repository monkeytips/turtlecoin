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

#include "MiningConfig.h"

#include <iostream>
#include <thread>
<<<<<<< HEAD
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <cxxopts.hpp>
#include <config/CliHeader.h>

#include <config/CryptoNoteConfig.h>
#include "Common/StringTools.h"
#include <Common/Util.h>

#include "Logging/ILogger.h"
#include "version.h"

#include <Errors/ValidateParameters.h>

#include <Utilities/ColouredMsg.h>
#include <Utilities/String.h>
#include <Utilities/Utilities.h>
=======

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "CryptoNoteConfig.h"
#include "Logging/ILogger.h"

namespace po = boost::program_options;
>>>>>>> blood in blood out

namespace CryptoNote {

namespace {
<<<<<<< HEAD
const size_t CONCURRENCY_LEVEL = std::thread::hardware_concurrency();
}

MiningConfig::MiningConfig():
    help(false),
    version(false)
{
}

void MiningConfig::parse(int argc, char** argv)
{
    cxxopts::Options options(argv[0], getProjectCLIHeader());

    options.add_options("Core")
        ("help", "Display this help message", cxxopts::value<bool>(help)->implicit_value("true"))
        ("version", "Output software version information", cxxopts::value<bool>(version)->default_value("false")->implicit_value("true"));

    options.add_options("Daemon")
        ("daemon-address", "The daemon [host:port] combination to use for node operations. This option overrides --daemon-host and --daemon-rpc-port", 
          cxxopts::value<std::string>(daemonAddress), "<host:port>")
        ("daemon-host", "The daemon host to use for node operations", cxxopts::value<std::string>(daemonHost)->default_value("127.0.0.1"), "<host>")
        ("daemon-rpc-port", "The daemon RPC port to use for node operations", cxxopts::value<uint16_t>(daemonPort)->default_value(std::to_string(CryptoNote::RPC_DEFAULT_PORT)), "#")
        ("scan-time", "Blockchain polling interval (seconds). How often miner will check the Blockchain for updates", cxxopts::value<size_t>(scanPeriod)->default_value("1"), "#");

    options.add_options("Mining")
        ("address", "The valid CryptoNote miner's address", cxxopts::value<std::string>(miningAddress), "<address>")
        ("block-timestamp-interval", "Timestamp incremental step for each subsequent block. May be set only if --first-block-timestamp has been set.",
          cxxopts::value<int64_t>(blockTimestampInterval) ->default_value("0"), "#")
        ("first-block-timestamp", "Set timestamp to the first mined block. 0 means leave timestamp unchanged", cxxopts::value<uint64_t>(firstBlockTimestamp)->default_value("0"), "#")
        ("limit", "Mine this exact quantity of blocks and then stop. 0 means no limit", cxxopts::value<size_t>(blocksLimit)->default_value("0"), "#")
        ("threads", "The mining threads count. Must not exceed hardware capabilities.", cxxopts::value<size_t>(threadCount)->default_value(std::to_string(CONCURRENCY_LEVEL)), "#");

    try
    {
        auto result = options.parse(argc, argv);
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << WarningMsg("Error: Unable to parse command line argument options: ")
                  << WarningMsg(e.what()) << "\n\n";
        std::cout << options.help({}) << std::endl;
        exit(1);
    }

    if (help) // Do we want to display the help message?
    {
        std::cout << options.help({}) << std::endl;
        exit(0);
    }
    else if (version) // Do we want to display the software version?
    {
        std::cout << InformationMsg(getProjectCLIHeader()) << std::endl;
        exit(0);
    }

    const bool integratedAddressesAllowed = false;

    Error error = validateAddresses({miningAddress}, integratedAddressesAllowed);

    while (error != SUCCESS)
    {
        /* If they didn't enter an address, don't report an error. Probably just
         unaware of cli options. */
        if (!miningAddress.empty())
        {
            std::cout << WarningMsg("Address is not valid: ")
                      << WarningMsg(error) << std::endl;
        }

        std::cout << InformationMsg("What address do you want to mine to?: ");
        std::getline(std::cin, miningAddress);
        Utilities::trim(miningAddress);

        error = validateAddresses({miningAddress}, integratedAddressesAllowed);
    }

    if (!daemonAddress.empty())
    {
        if (!Utilities::parseDaemonAddressFromString(daemonHost, daemonPort, daemonAddress))
        {
          throw std::runtime_error("Could not parse --daemon-address option");
        }
    }

    if (threadCount == 0 || threadCount > CONCURRENCY_LEVEL)
    {
        throw std::runtime_error("--threads option must be 1.." + std::to_string(CONCURRENCY_LEVEL));
    }

    if (scanPeriod == 0)
    {
        throw std::runtime_error("--scan-time must not be zero");
    }

    if (firstBlockTimestamp == 0 && blockTimestampInterval != 0)
    {
        throw std::runtime_error("If you specify --block-timestamp-interval you must also specify --first-block-timestamp");
    }
=======

const size_t DEFAULT_SCANT_PERIOD = 30;
const char* DEFAULT_DAEMON_HOST = "127.0.0.1";
const size_t CONCURRENCY_LEVEL = std::thread::hardware_concurrency();

po::options_description cmdOptions;

void parseDaemonAddress(const std::string& daemonAddress, std::string& daemonHost, uint16_t& daemonPort) {
  std::vector<std::string> splittedAddress;
  boost::algorithm::split(splittedAddress, daemonAddress, boost::algorithm::is_any_of(":"));

  if (splittedAddress.size() != 2) {
    throw std::runtime_error("Wrong daemon address format");
  }

  if (splittedAddress[0].empty() || splittedAddress[1].empty()) {
    throw std::runtime_error("Wrong daemon address format");
  }

  daemonHost = splittedAddress[0];

  try {
    daemonPort = boost::lexical_cast<uint16_t>(splittedAddress[1]);
  } catch (std::exception&) {
    throw std::runtime_error("Wrong daemon address format");
  }
}

}

MiningConfig::MiningConfig(): help(false), version(false) {
  cmdOptions.add_options()
      ("help,h", "Produce this help message and exit")
      ("version", "Print the version number and exit")
      ("address", po::value<std::string>(), "Valid cryptonote miner's address")
      ("daemon-host", po::value<std::string>()->default_value(DEFAULT_DAEMON_HOST), "Daemon host")
      ("daemon-rpc-port", po::value<uint16_t>()->default_value(static_cast<uint16_t>(RPC_DEFAULT_PORT)), "Daemon's RPC port")
      ("daemon-address", po::value<std::string>(), "Daemon host:port. If you use this option you must not use --daemon-host and --daemon-port options")
      ("threads", po::value<size_t>()->default_value(CONCURRENCY_LEVEL), "Mining threads count. Must not be greater than you concurrency level. Default value is your hardware concurrency level")
      ("scan-time", po::value<size_t>()->default_value(DEFAULT_SCANT_PERIOD), "Blockchain polling interval (seconds). How often miner will check blockchain for updates")
      ("log-level", po::value<int>()->default_value(1), "Log level. Must be 0..5")
      ("limit", po::value<size_t>()->default_value(0), "Mine exact quantity of blocks. 0 means no limit")
      ("first-block-timestamp", po::value<uint64_t>()->default_value(0), "Set timestamp to the first mined block. 0 means leave timestamp unchanged")
      ("block-timestamp-interval", po::value<int64_t>()->default_value(0), "Timestamp step for each subsequent block. May be set only if --first-block-timestamp has been set."
                                                         " If not set blocks' timestamps remain unchanged");
}

void MiningConfig::parse(int argc, char** argv) {
  po::variables_map options;
  po::store(po::parse_command_line(argc, argv, cmdOptions), options);
  po::notify(options);

  if (options.count("help") != 0) {
    help = true;
    return;
  }

  if (options.count("version") != 0) {
    version = true;
    return;
  }

  if (options.count("address") == 0) {
    throw std::runtime_error("Specify --address option");
  }

  miningAddress = options["address"].as<std::string>();

  if (!options["daemon-address"].empty()) {
    if (!options["daemon-host"].defaulted() || !options["daemon-rpc-port"].defaulted()) {
      throw std::runtime_error("Either --daemon-host or --daemon-rpc-port is already specified. You must not specify --daemon-address");
    }

    parseDaemonAddress(options["daemon-address"].as<std::string>(), daemonHost, daemonPort);
  } else {
    daemonHost = options["daemon-host"].as<std::string>();
    daemonPort = options["daemon-rpc-port"].as<uint16_t>();
  }

  threadCount = options["threads"].as<size_t>();
  if (threadCount == 0 || threadCount > CONCURRENCY_LEVEL) {
    throw std::runtime_error("--threads option must be 1.." + std::to_string(CONCURRENCY_LEVEL));
  }

  scanPeriod = options["scan-time"].as<size_t>();
  if (scanPeriod == 0) {
    throw std::runtime_error("--scan-time must not be zero");
  }

  logLevel = static_cast<uint8_t>(options["log-level"].as<int>());
  if (logLevel > static_cast<uint8_t>(Logging::TRACE)) {
    throw std::runtime_error("--log-level value is too big");
  }

  blocksLimit = options["limit"].as<size_t>();

  if (!options["block-timestamp-interval"].defaulted() && options["first-block-timestamp"].defaulted()) {
    throw std::runtime_error("If you specify --block-timestamp-interval you must specify --first-block-timestamp either");
  }

  firstBlockTimestamp = options["first-block-timestamp"].as<uint64_t>();
  blockTimestampInterval = options["block-timestamp-interval"].as<int64_t>();
}

void MiningConfig::printHelp() {
  std::cout << cmdOptions << std::endl;
}

void MiningConfig::printVersion() {
  std::cout << "monkeytips v" << PROJECT_VERSION << " Miner" << std::endl;
>>>>>>> blood in blood out
}

}
