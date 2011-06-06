/*
    nodachi2D is a client application for the gameserver heikiko2D.
    Copyright (C) 2010-2011  Paul Predkiewicz

    nodachi2D is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

struct networkFlags{
    bool Running;
    bool Connected;
    bool LoggedIn;
};

//we transmit position, rotation, animationID and maybe scale

class NetworkHandler :public sf::Thread
{
    private:
        virtual void Run();
        bool sendMessage();
        void askForUsername();
        void askForPassword();

        sf::SocketTCP client_;
        sf::IPAddress* serverIP_;
        unsigned int serverPort_;
        std::string username_;
        std::string password_;

    public:
        sf::Mutex* GlobalMutex_;
        networkFlags globalflags_;
        void connect();
        bool login();
        NetworkHandler(sf::IPAddress* remoteHost, unsigned int Port, sf::Mutex* GlobalMutex);
        ~NetworkHandler();
};
#endif
