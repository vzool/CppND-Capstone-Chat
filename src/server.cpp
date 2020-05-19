#include <sys/socket.h> // setsockopt, bind, listen, accept
#include <iostream> // std::cout
#include <random>   // std::random_device, std::mt19937, std::uniform_int_distribution
#include <memory>   // std::make_unique, std::move

#include "server.h"

bool Server::Connect()
{
    int opt = 1;
    if(setsockopt(m_SocketID, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cout << "Server: setsockopt failed." << std::endl;
        return false;
    }

    Address address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    auto address_length = sizeof(address);

    while(true){

        address.sin_port = RandomPort();

        if(bind(m_SocketID, (struct sockaddr*)&address, address_length) < 0)
        {
            std::cout << "Server: bind failed - maybe Port(" << address.sin_port << ") is occupied, try another port..." << std::endl;

        }else{

            std::cout << "Server: bind success - Port(" << address.sin_port << ")." << std::endl;

            break;
        }
    }

    m_Address = std::make_unique<Address>(std::move(address));

    if (listen(m_SocketID, 3) < 0)
    {
        std::cout << "Server: listen failed." << std::endl;
        return false;
    }

    std::cout << "Server: ready, waiting connection on Port(" << address.sin_port << ")..." << std::endl;

    if ((m_Socket = accept(m_SocketID, (struct sockaddr *)&address, (socklen_t *)&address_length)) < 0)
    {
        std::cout << "Server: accept failed." << std::endl;
        return false;
    }

    auto peerName = Receive() > 0 ? Message() : "unknown"; // get peer name

    std::cout << "Server: connected with(" << peerName << ")." << std::endl;

    Send(m_Name); // send my name

    return true;
}

void Server::Chat()
{
    Parent()->Chat(m_Socket);
}

long Server::Receive()
{
    return Parent()->Receive(m_Socket);
}

bool Server::Send(std::string message)
{
    return Parent()->Send(m_Socket, message);
}

int Server::RandomPort() const
{
    std::random_device rd;                                   //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());                                  //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(MIN_PORT, MAX_PORT); // port range without permission

    return dis(gen);
}
