#ifndef BELISKNER_INPUTHANDLER_HPP
#define BELISKNER_INPUTHANDLER_HPP

#include <iostream>
#include <unistd.h>
#include <vector>

namespace Beliskner
{

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void handleInput( void* input, int fd );

    void delFD( int i );
    void addFD( int i );

private:
    std::vector<int> clients;

    enum statuscodes
    {
        ID_REQUEST      = 60000,
        POSITION_UPDATE = 60001,
        ID_UPDATE       = 60002,
        ID_ANSwER       = 60003,
        MOVED           = 60004,
        STOPPED         = 60005
    };

    struct message
    {
        int status;
        int info[3];
    };

};

}

#endif
