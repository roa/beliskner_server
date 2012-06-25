#include "Config.hpp"

namespace Beliskner
{

Config::Config()
{
    logger = Logger::getSingletonPtr();
    load( "config/init.lua" );
}

Config::~Config()
{

}

void Config::load( const char* fname )
{
    L = luaL_newstate();
    if( luaL_loadfile( L, fname ) || lua_pcall( L, 0, 0, 0 ) )
    {
        logger->log( "cannot run config file: ", lua_tostring( L, -1 ) );
    }

    /**********************
     *    load port  *
     **********************/
    lua_getglobal( L, "port" );
    if( !lua_isstring( L, 1 ) )
    {
        logger->log( "port is not a string" );
    }
    else
    {
        port = lua_tostring( L, 1 );
        logger->log( "set port to: ", port );
    }
    lua_pop( L, 1 );

    lua_close( L );
}

std::string Config::getPort()
{
    return port;
}

}
