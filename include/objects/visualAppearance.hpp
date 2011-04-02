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

#ifndef VISUALAPPEARANCE_HPP
#define VISUALAPPEARANCE_HPP

#include <string>
#include <vector>
#include <objects/animation.hpp>
namespace objects
{
    class VisualAppearance
    {
        public:
            void        setCurrentAnimationByAnimationId( std::string animationId );
            Animation*  getCurrentAnimation();
            std::string getVisualAppearanceId();

            VisualAppearance( std::string visualAppearanceId, std::string animationsDescriptionFile );
            VisualAppearance();
            ~VisualAppearance();
        protected:

        private:
            std::string          visualAppearanceId_; //something like player, zombie1, zombie2, ..etc
            std::vector< Animation* >   possibleAnimations_;
            Animation*                  currentAnimation_;
    };
}
#endif
