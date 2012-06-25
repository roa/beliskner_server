#include "Logger.hpp"

namespace Beliskner
{

Logger * Logger::singletonPtr = 0;

Logger * Logger::getSingletonPtr()
{
    if ( !singletonPtr )
    {
        singletonPtr = new Logger ();
    }
    return singletonPtr;
}

Logger::Logger()
{
    this->log( "created new logger instance" );
}

Logger::~Logger()
{

}

void Logger::log( std::string logMsg )
{
    std::ofstream logFile;
    logFile.open ("log/dev.log", std::ios::app );
    logFile << createTimestamp() << "\t" << logMsg << std::endl;
    logFile.close();
}

std::string Logger::createTimestamp()
{
    std::stringstream timestamp;
    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    timestamp   << timeinfo->tm_year + 1900 << "-";
    if( timeinfo->tm_mon < 10 )
    {
        timestamp << 0 << timeinfo->tm_mon  << "-";
    }
    else
    {
        timestamp << timeinfo->tm_mon  << "-";
    }

    if( timeinfo->tm_mday < 10 )
    {
        timestamp << 0 << timeinfo->tm_mday  << "-";
    }
    else
    {
        timestamp << timeinfo->tm_mday << " ";
    }

    if( timeinfo->tm_hour < 10 )
    {
        timestamp << 0 << timeinfo->tm_hour  << ":";
    }
    else
    {
        timestamp << timeinfo->tm_hour << ":";
    }

    if( timeinfo->tm_min < 10 )
    {
        timestamp << 0 << timeinfo->tm_min  << ":";
    }
    else
    {
        timestamp << timeinfo->tm_min << ":";
    }

    if( timeinfo->tm_sec < 10 )
    {
        timestamp << 0 << timeinfo->tm_sec;
    }
    else
    {
        timestamp << timeinfo->tm_sec;
    }
    return timestamp.str();
}

}
