#include <iostream>
#include "BaseServer.hpp"
#include "Logger.hpp"
#include "Config.hpp"
using namespace Beliskner;

int main()
{
    Config* conf;
    conf = new Config();

    BaseServer *server;
    server = new BaseServer( conf );

    while( true )
        server->run();

    delete server;
    return 0;
}
