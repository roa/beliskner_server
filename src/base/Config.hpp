#ifndef BELISKNER_CONFIG_HPP
#define BELISKNER_CONFIG_HPP

#include <lua.hpp>
#include <iostream>
#include "Logger.hpp"

namespace Beliskner
{

class Config
{
public:
    Config();
    ~Config();

    lua_State *L;

    void load( const char* fname );

private:

    Logger *logger;

    std::string port;
};

}
#endif
