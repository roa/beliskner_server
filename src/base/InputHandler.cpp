#include "InputHandler.hpp"

namespace Beliskner
{

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::handleInput( void* input, int fd )
{
    /*
    std::string test = (char *) input;

    for( std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it )
    {
        int tempsock = *it;
        if( tempsock != fd )
        {
            write( tempsock, test.c_str(), test.size() );
        }
        std::cout << *it << std::endl;
    }
    */
    message * test = (message *) input;
    std::cout << test->status << test->info[0] << test->info[1] << test->info[2] << std::endl;
}

void InputHandler::delFD( int i )
{
    int iter = 0;
    for( std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it )
    {
        int tempsock = *it;
        if( tempsock == i )
        {
            break;
        }
        ++iter;
    }
    clients.erase( clients.begin() + iter );
}

void InputHandler::addFD( int i )
{
    clients.push_back( i );
}

}
