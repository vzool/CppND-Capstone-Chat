#ifndef PEER_H
#define PEER_H

#include <string>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>

typedef struct sockaddr_in Address;

#define BUFFER_LIMIT 1024 // 1 KB
#define MIN_PORT     1024
#define MAX_PORT    65535

class Peer
{
public:

    Peer(std::string name);

    virtual bool Connect() = 0;

    void Chat(int socket);

    long Receive(int socket);
    std::string Message();
    bool Send(int socket, std::string message);

protected:

    Peer* Parent() const { return m_Parent; } 
    
    int m_SocketID = 0;
    char m_Buffer[BUFFER_LIMIT] = {0};
    std::string m_Name = "";
    std::unique_ptr<Address> m_Address;

private:

    Peer *m_Parent;
    std::mutex m_mutex;
};

#endif