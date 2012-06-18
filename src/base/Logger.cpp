#include "Logger.hpp"

namespace Beliskner
{

Logger * Logger::singletonPtr = 0;

Logger * Logger::getSingletonPtr()
{
    if ( !singletonPtr )
    {
        singletonPtr = new Logger ();
        std::cout << "created new logger" << std::endl;
    }
    return singletonPtr;
}

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::log()
{
    std::ofstream logFile;
    logFile.open ("log/dev.log", std::ios::app );
    logFile << "Writing this to a file.\n";
    logFile.close();
}

}
