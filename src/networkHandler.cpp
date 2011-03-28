#include <networkHandler.hpp>


NetworkHandler::NetworkHandler( sf::IPAddress remoteHost, unsigned int Port, sf::Mutex* GlobalMutex)
{
    this->serverIP_ = remoteHost;
    this->serverPort_ = Port;
    GlobalMutex_ = GlobalMutex;
    this->Connect();
}

NetworkHandler::~NetworkHandler()
{

    Terminate();
}

bool NetworkHandler::Connect()
{
    if(client_.Connect(serverPort_, serverIP_) == sf::Socket::Done)
    {
        globalflags_.Running = true;
        globalflags_.Connected = true;
        Launch();
        return true;
    }
    else
    {
        globalflags_.Running = true;
        globalflags_.Connected = false;
        std::cout << "Can't connect to " << serverIP_.ToString() << " on port " << serverPort_ << ".";
        return false;
    }
}

void NetworkHandler::Run()
{
    while( globalflags_.Running )
    {
    }
}
