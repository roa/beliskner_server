#include "BaseServer.hpp"

namespace Beliskner
{

BaseServer::BaseServer( Config* _config ) : config( _config )
{
    logger = Logger::getSingletonPtr();

    socketfd = bindSocket();
    make_socket_non_blocking( socketfd );
    efd = epoll_create1( 0 );

    if ( efd == -1 )
    {
        logger->log( "failed epoll_create1" );
        logger->log( strerror( errno ) );
        abort();
    }

    event.data.fd = socketfd;

    event.events = EPOLLIN | EPOLLET;

    listen( socketfd, SOMAXCONN );

    listener = epoll_ctl( efd, EPOLL_CTL_ADD, socketfd, &event );
    if ( listener == -1 )
    {
        logger->log( "failed epoll_ctl" );
        logger->log( strerror( errno ) );
        abort();
    }
}

BaseServer::~BaseServer()
{
    std::cout << "should destruct" << std::endl;
}

void BaseServer::run()
{
    int n, i;
    n = epoll_wait( efd, events, MAXEVENTS, -1 );
    for ( i = 0; i < n; i++ )
    {
        if( ( events[i].events & EPOLLERR ) ||
            ( events[i].events & EPOLLHUP ) ||
            ( !( events[i].events & EPOLLIN ) ) )
        {
            logger->log( "epoll error on fd" );
            logger->log( strerror( errno ) );
            close (events[i].data.fd);
            continue;
        }
        else
        {
            if ( socketfd == events[i].data.fd )
            {
                /********************************************************
                * We have a notification on the listening socket, which *
                * means one or more incoming connections.               *
                *********************************************************/
                do_accept();
                continue;
            }
            else
            {
                /**************************
                * we have data to process *
                ***************************/
                do_io( i );
            }
        }
    }
    /******************************
    * free events is no good idea *
    * we want to reuse the set!   *
    * //free( events );           *
    *******************************/
}

int BaseServer::bindSocket()
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int listener;
    int socketfd;

    memset( &hints, 0, sizeof( struct addrinfo) );

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    listener = getaddrinfo( NULL, config->getPort().c_str(), &hints, &result );
    if ( listener != 0 )
    {
        logger->log( "getaddrinfo" );
        logger->log( gai_strerror ( listener ) );
        return -1;
    }

    for ( rp = result; rp != NULL; rp = rp->ai_next )
    {
        socketfd = socket( rp->ai_family, rp->ai_socktype, rp->ai_protocol );
        if ( socketfd == -1 )
        {
            logger->log( "could not bind" );
            logger->log( strerror( errno ) );
            continue;
        }

        int on = 1;

        if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        {
            logger->log( "could not set socketopt REUSEADDR" );
            logger->log( strerror( errno ) );
        }

        listener = bind (socketfd, rp->ai_addr, rp->ai_addrlen);

        if ( listener == 0 )
        {
            break;
        }
        else
        {
            logger->log( "could not bind" );
            logger->log( strerror(errno));
        }
        close( socketfd );
    }

    if ( rp == NULL )
    {
        logger->log( "gave up to bind" );
        return -1;
    }

    freeaddrinfo( result );

    return socketfd;
}

void BaseServer::do_accept()
{
    while ( 1 )
    {
        struct sockaddr in_addr;
        socklen_t in_len;
        int infd;
        in_len = sizeof in_addr;

        infd = accept( socketfd, &in_addr, &in_len );

        if ( infd == -1 )
        {
            if ( ( errno == EAGAIN ) ||
                 ( errno == EWOULDBLOCK )
               )
            {
                break;
            }
            else
            {
                logger->log( " accept failed" );
                logger->log( strerror( errno ) );
                break;
            }
        }

        listener = make_socket_non_blocking( infd );
        if ( listener == -1 )
        {
            logger->log( "failed to make_socket_non_blocking: do_accept" );
        }

        event.data.fd = infd;
        event.events = EPOLLIN | EPOLLET;
        listener = epoll_ctl( efd, EPOLL_CTL_ADD, infd, &event );
        if ( listener == -1 )
        {
            logger->log( "failed to epoll_ctl: do_accept");
            abort();
        }
    }
}

void BaseServer::do_io( int i )
{
   while ( 1 )
    {
        ssize_t count;
        char buf[MAXBUFSIZE];

        count = read( events[i].data.fd, buf, sizeof( buf ) );
        if ( count == -1 )
        {
            break;
        }
        else
        {
            if ( count == 0 )
            {
                /*************************
                * connection closed from *
                * remote side            *
                **************************/
                break;
            }

            /*******************************
            * we can process the data      *
            * right now it is only printed *
            * and the buffer is cleaned    *
            * afterwards                   *
            ********************************/
            std::cout << buf << std::endl;
            memset( buf, '\0', sizeof( buf ) );

            /********************************************
            * right no no port is closed,               *
            * but we should do that in the future :X    *
            * //shutdown( events[i].data.fd, SHUT_WR ); *
            * //close( events[i].data.fd );             *
            *********************************************/
        }
    }
}

int BaseServer::make_socket_non_blocking( int socketfd )
{
    int flags;
    int listener;

    flags = fcntl( socketfd, F_GETFL, 0 );
    if ( flags == -1 )
    {
        logger->log( "failed reading fd flags" );
        return -1;
    }

    flags |= O_NONBLOCK;
    listener = fcntl( socketfd, F_SETFL, flags );
    if ( listener == -1 )
    {
        logger->log( "failed setting fd flags" );
        return -1;
    }

    int on = 1;

    if( setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0 )
    {
        logger->log( "could not set socketopt REUSEADDR" );
    }

    return 0;
}

}
