#ifndef BELISKNER_INPUTHANDLER_HPP
#define BELISKNER_INPUTHANDLER_HPP

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>

#include "Message.hpp"

namespace Beliskner
{

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void handleInput( message* input, int fd );

    void delFD( int i );
    void addFD( int i );

private:
    std::vector<int> clients;

};

}

#endif
