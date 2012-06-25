#include "InputHandler.hpp"

namespace Beliskner
{

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::handleInput( std::string input, int fd )
{
    std::cout << input;
    write( fd, input.c_str(), input.size() );
}

}
