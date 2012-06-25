#ifndef BELISKNER_INPUTHANDLER_HPP
#define BELISKNER_INPUTHANDLER_HPP

#include <iostream>
#include <unistd.h>
namespace Beliskner
{

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void handleInput( std::string input, int fd );

private:

};

}

#endif
