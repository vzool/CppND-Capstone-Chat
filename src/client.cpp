#include <sys/socket.h> // connect
#include <arpa/inet.h>  // inet_pton
#include <iostream>

#include "client.h"

bool Client::Connect()
{
    Address address;
    address.sin_family = AF_INET;
    address.sin_port = m_Port;

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, m_IP.c_str(), &address.sin_addr) <= 0)
    {
        std::cout << "Client: Invalid address/ Address not supported." << std::endl;
        return false;
    }

    if (connect(m_SocketID, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Client: Connection Failed." << std::endl;
        return false;
    }

    Send(m_Name); // send my name

    auto peerName = Receive() > 0 ? Message() : "unknown"; // get peer name

    std::cout << "Client: connected with(" << peerName << ")." << std::endl;

    return true;
}

void Client::Chat()
{
    Parent()->Chat(m_SocketID);
}

long Client::Receive()
{
    return Parent()->Receive(m_SocketID);
}

bool Client::Send(std::string message)
{
    return Parent()->Send(m_SocketID, message);
}
