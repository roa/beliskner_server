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
    InputHandler( std::vector<int> *_clients );
    ~InputHandler();

    void handleInput( std::string input, int fd );
    void removeFD( int i );

private:
    std::vector<int> *clients;

};

}

#endif
