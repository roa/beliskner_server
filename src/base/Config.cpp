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
        std::stringstream logstring;
        logstring << "cannot run config file: " << lua_tostring( L, -1 );
        logger->log(  logstring.str() );
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
        std::stringstream logstring;
        logstring << "port set to: " << port;
        logger->log( logstring.str() );
    }
    lua_pop( L, 1 );

    lua_close( L );
}

}
