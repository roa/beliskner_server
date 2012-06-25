#ifndef BELISKNER_BASESERVER_HPP
#define BELISKNER_BASESERVER_HPP

#define MAXEVENTS 32
#define MAXBUFSIZE 512

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Logger.hpp"
#include "Config.hpp"

namespace Beliskner
{

class BaseServer
{
public:
    BaseServer( Config* _config );
    ~BaseServer();

    void run();

private:
    int socketfd, listener;
    int efd;
    struct epoll_event event;
    struct epoll_event events[MAXEVENTS];

    Logger *logger;
    Config *config;

    int bindSocket();
    void do_accept();
    void do_io( int i );
    int make_socket_non_blocking( int socketfd );

};

}

#endif
