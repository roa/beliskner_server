#include "InputHandler.hpp"

namespace Beliskner
{

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::handleInput( message* input, int fd )
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
    switch( input->status )
    {
        case ID_REQUEST:
        {
            //id_request answer
            std::cout << "id_request" << std::endl;
            break;
        }
        case POSITION_UPDATE:
        {
            //position update
            std::cout << "pos_update" << std::endl;
            break;
        }
        case MOVED:
        {
            //moved
            std::cout << "moved" << std::endl;
            break;
        }
        case STOPPED:
        {
            //stopped
            std::cout << "stopped" << std::endl;
            break;
        }
        default:
        {
            std::cout << "something wrong" << std::endl;
            message msg;
            msg.status = ID_ANSwER;
            msg.info[0] = 0;
            msg.info[1] = 0;
            msg.info[2] = 0;
            send( fd, &msg, sizeof( message ), 0 );
        }
    }
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
