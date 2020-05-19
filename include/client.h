#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "peer.h"

class Client : public Peer
{
public:
    Client(std::string name, std::string ip, int port) : Peer(name), m_IP(ip), m_Port(port) {}

    bool Connect() override;

    void Chat();

    long Receive();
    bool Send(std::string message);

private:
    std::string m_IP;
    int m_Port;
};

#endif