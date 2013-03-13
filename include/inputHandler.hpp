/*
    nodachi2D is a client application for the gameserver heikiko2D.
    Copyright (C) 2010-2013  Paul Brüll

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

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct flags{
    bool Running;
    bool ApplyForceUpwardToPlayer;
    bool ApplyForceLeftToPlayer;
    bool ApplyForceRightToPlayer;
    bool ApplyForceDownwardToPlayer;
    bool Restart;
};

class InputHandler :public sf::Thread
{
    private:
        const sf::Input* keyInput_;
        virtual void Run();
    public:
        sf::Mutex* GlobalMutex_;
        flags globalflags_;
        InputHandler(sf::RenderWindow* appWindow, sf::Mutex* GlobalMutex);
        ~InputHandler();
};
#endif
