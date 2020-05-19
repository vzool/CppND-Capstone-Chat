#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "peer.h"

class Server : public Peer 
{
public:
    Server(std::string name) : Peer(name) {}

    bool Connect() override;

    void Chat();

    long Receive();
    bool Send(std::string message);

private:
    int RandomPort() const;
    int m_Socket;
};

#endif