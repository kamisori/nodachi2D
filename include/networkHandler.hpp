#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

struct networkFlags{
    bool Running;
    bool Connected;
};

class NetworkHandler :public sf::Thread
{
    private:
        virtual void Run();
        sf::SocketTCP client_;
        sf::IPAddress serverIP_;
        unsigned int serverPort_;
    public:
        sf::Mutex* GlobalMutex_;
        networkFlags globalflags_;
        bool Connect();
        NetworkHandler(sf::IPAddress remoteHost, unsigned int Port, sf::Mutex* GlobalMutex);
        ~NetworkHandler();
};
#endif
