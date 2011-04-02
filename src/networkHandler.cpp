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

#include <networkHandler.hpp>


NetworkHandler::NetworkHandler( sf::IPAddress remoteHost, unsigned int Port, sf::Mutex* GlobalMutex)
{
    this->serverIP_ = remoteHost;
    this->serverPort_ = Port;
    globalflags_.Running = true;
    GlobalMutex_ = GlobalMutex;
}

NetworkHandler::~NetworkHandler()
{

    Terminate();
}

void NetworkHandler::Connect()
{
    if(client_.Connect(serverPort_, serverIP_) == sf::Socket::Done)
    {
        globalflags_.Connected = true;
        Launch();
    }
    else
    {
        globalflags_.Connected = false;
        std::cout << "Can't connect to " << serverIP_.ToString() << " on port " << serverPort_ << ".";
    }
}

void NetworkHandler::Run()
{
    while( globalflags_.Running )
    {
    }
}
