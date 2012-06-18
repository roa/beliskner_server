#include <iostream>
#include "BaseServer.hpp"
#include "Logger.hpp"

using namespace Beliskner;

int main()
{
    BaseServer *server;
    server = new BaseServer();

    Logger * logger;
    logger = Logger::getSingletonPtr();
    logger->log();

    while( true )
        server->run();

    delete server;
    return 0;
}
