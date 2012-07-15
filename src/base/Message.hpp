#ifndef BELISKNER_MESSAGE_HPP
#define BELISKNER_MESSAGE_HPP

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

#endif
