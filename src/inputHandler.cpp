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

#include <inputHandler.hpp>

InputHandler::InputHandler(sf::RenderWindow* appWindow, sf::Mutex* GlobalMutex)
{
    keyInput_ = &appWindow->GetInput();
    GlobalMutex_ = GlobalMutex;

    globalflags_.Running = true;

    globalflags_.ApplyForceUpwardToPlayer = false;
    globalflags_.ApplyForceLeftToPlayer = false;
    globalflags_.ApplyForceRightToPlayer = false;
    globalflags_.ApplyForceDownwardToPlayer = false;
    globalflags_.Restart = false;///TODO

    Launch();
}
InputHandler::~InputHandler()
{
    Terminate();
}

void InputHandler::Run()
{
    while( globalflags_.Running )
    {
        GlobalMutex_->Lock();
        globalflags_.ApplyForceLeftToPlayer = keyInput_->IsKeyDown(sf::Key::Left);
        globalflags_.ApplyForceRightToPlayer = keyInput_->IsKeyDown(sf::Key::Right);
        globalflags_.ApplyForceDownwardToPlayer = keyInput_->IsKeyDown(sf::Key::Down);
        globalflags_.ApplyForceUpwardToPlayer = keyInput_->IsKeyDown(sf::Key::Up);
        GlobalMutex_->Unlock();
    }
}
