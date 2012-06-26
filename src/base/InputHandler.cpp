#include "InputHandler.hpp"

namespace Beliskner
{

InputHandler::InputHandler( std::vector<int> *_clients) : clients( _clients )
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::handleInput( std::string input, int fd )
{
    std::cout << input;

    for( std::vector<int>::iterator it = clients->begin(); it != clients->end(); ++it )
    {
        int tempsock = *it;
        if( tempsock != fd )
        {
            write( tempsock, input.c_str(), input.size() );
        }
        std::cout << *it << std::endl;
    }
}

void InputHandler::removeFD( int i )
{
    int iter = 0;
    for( std::vector<int>::iterator it = clients->begin(); it != clients->end(); ++it )
    {
        int tempsock = *it;
        if( tempsock == i )
        {
            break;
        }
        ++iter;
    }
    clients->erase( clients->begin() + iter );
}

}
