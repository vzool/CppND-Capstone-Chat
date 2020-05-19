#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <unistd.h> // read
#include <thread>
#include <chrono>

#include "peer.h"

Peer::Peer(std::string name)
{
    if((m_SocketID = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Peer: socket failed." << std::endl;
    }

    m_Name = name;
    m_Parent = this;
}

void Peer::Chat(int socket)
{
    std::cout << "========================" << std::endl
              << "--- [ CHAT STARTED ] ---" << std::endl
              << "========================" << std::endl;

    // Read peer messages

    std::thread t1 = std::thread([socket](Peer* peer) {

        std::cout << "Waiting for peer messages..." << std::endl;

        for(;;)
        {
            if(peer->Receive(socket) > 0)
            {
                std::cout << peer->Message() << std::endl;
            }
            else
            {
                std::cout << "==============================" << std::endl
                          << "--- [ PEER DISCONNECTED ] ---" << std::endl
                          << "==============================" << std::endl;
                exit(0);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

    }, this);

    std::cout << "Start waiting your inputs..." << std::endl;

    // Wait for my messages then send them

    for(;;)
    {
        std::cin.getline(m_Buffer, BUFFER_LIMIT);

        if(std::string(m_Buffer).length() > 0)
        {
            Send(socket, m_Name + ": " + m_Buffer);
        }
    }
}

long Peer::Receive(int socket)
{
    const std::lock_guard<std::mutex> _(m_mutex);
    return read(socket, m_Buffer, BUFFER_LIMIT);
}

std::string Peer::Message()
{
    const std::lock_guard<std::mutex> _(m_mutex);
    return m_Buffer;
}

bool Peer::Send(int socket, std::string message)
{
    return send(socket, message.c_str(), message.length(), 0) > 0;
}
