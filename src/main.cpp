#include <iostream>
#include <cstring>
#include "server.h"
#include "client.h"

int main(int argc, char* argv[])
{
    bool isServerMode = false;

    if(argc == 2){
        isServerMode = std::string(argv[1]).compare("server") == 0;
    }

    std::string defaultServerName = "Home Server";
    std::string defaultPeerName = "Abdelaziz Elrashed";
    std::string defaultIP = "127.0.0.1";

    char name[128];
    char ip[16];
    int port;

    if (isServerMode)
    {
        std::cout << "What's your name(" << defaultServerName << "): ";
        std::cin.getline(name, sizeof(name));

        if (std::string(name).length() <= 0)
        {
            std::strncpy(name, defaultServerName.c_str(), sizeof(name));
        }

        auto server = new Server(name);
        server->Connect();
        server->Chat();
    }
    else
    {
        std::cout << "What's your name(" << defaultPeerName  << "): ";
        std::cin.getline(name, sizeof(name));

        if (std::string(name).length() <= 0)
        {
            std::strncpy(name, defaultPeerName.c_str(), sizeof(name));
        }

        std::cout << "Enter your name IP(default " << defaultIP  << "): ";
        std::cin.getline(ip, sizeof(ip));

        if(std::string(ip).length() <= 0)
        {
            std::strncpy(ip, defaultIP.c_str(), sizeof(ip));
        }

        do{

            std::cout << "Enter your name Port: ";
            std::cin >> port;

            if (port < MIN_PORT || port > MAX_PORT)
            {
                std::cout << "Invalid PORT, this should be between [" << MIN_PORT << "-" << MAX_PORT << "]" << std::endl;
            }

        } while (port < MIN_PORT || port > MAX_PORT);

        auto client = new Client(name, ip, port);
        client->Connect();
        client->Chat();
    }

    return 0;
}