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

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
namespace objects
{
#define SPRITE_SIZE 32

    class Animation
    {
        public:
            sf::Sprite* getNextFrame();
            std::string getAnimationId();

            Animation( std::string animationId, std::string fileName, sf::Vector2i rowsAndCollumns, int delayPerFrame );

            Animation();
            ~Animation();
        protected:

        private:
            void iterateToNextFrame();
            int delayPerFrameInMs_;
            std::string animationId_;
            sf::Image* allFrames_;
            std::vector< sf::Sprite* > frames_;
            unsigned int currentFrame_;
    };
}
#endif
