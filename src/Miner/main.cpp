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

#include "Common/SignalHandler.h"

#include "Logging/LoggerGroup.h"
#include "Logging/ConsoleLogger.h"
#include "Logging/LoggerRef.h"
>>>>>>> blood in blood out

#include "MinerManager.h"

#include <System/Dispatcher.h>

<<<<<<< HEAD
int main(int argc, char **argv)
{
    while (true)
    {
        CryptoNote::MiningConfig config;
        config.parse(argc, argv);

        try
        {
            System::Dispatcher dispatcher;

            auto httpClient = std::make_shared<httplib::Client>(
                config.daemonHost.c_str(), config.daemonPort, 10 /* 10 second timeout */
            );

            Miner::MinerManager app(dispatcher, config, httpClient);

            app.start();
        }
        catch (const std::exception& e)
        {
            std::cout << "Unhandled exception caught: " << e.what()
                      << "\nAttempting to relaunch..." << std::endl;
        }
    }
=======
int main(int argc, char** argv) {
  try {
    CryptoNote::MiningConfig config;
    config.parse(argc, argv);

    if (config.help) {
      config.printHelp();
      return 0;
    }

    if (config.version) {
      config.printVersion();
      return 0;
    }

    Logging::LoggerGroup loggerGroup;
    Logging::ConsoleLogger consoleLogger(static_cast<Logging::Level>(config.logLevel));
    loggerGroup.addLogger(consoleLogger);

    System::Dispatcher dispatcher;
    Miner::MinerManager app(dispatcher, config, loggerGroup);

    app.start();
  } catch (std::exception& e) {
    std::cerr << "Fatal: " << e.what() << std::endl;
    return 1;
  }

  return 0;
>>>>>>> blood in blood out
}
