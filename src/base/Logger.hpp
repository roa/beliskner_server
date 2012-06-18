#ifndef BELISKNER_LOGGER_HPP
#define BELISKNER_LOGGER_HPP

#include <iostream>
#include <fstream>

namespace Beliskner
{

class Logger
{
public:
    static Logger* getSingletonPtr();
    void log();

private:
    static Logger* singletonPtr;
    Logger();
    Logger( const Logger& );
    ~Logger();
};

}

#endif
