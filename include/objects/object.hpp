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

#ifndef SPACIALOBJECT_HPP
#define SPACIALOBJECT_HPP

#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <Box2D/Box2D.h>

namespace objects
{
    class Object
    {
    	public:
            double getRotation();
            void setRotation( double newRotation );
            std::string getObjectId();
            VisualAppearance* getVisualAppearance();

            Object( std::string objectId, std::string visualAppearanceID, sf::Vector2f position, double rotation, double scale );
                                        /*std::string audialAppearanceId,*/

            ~Object();
    	protected:

    	private:
            std::string objectID_;
            sf::Vector2f position_;
            double rotation_;
            double scale_;

            VisualAppearance*   visualAppearance_;          //null means, this is either a zone for a script,
                                                            //or something is attached to the ground, like a
                                                            //pole for a line or something

            //AudioAppearance*    audialAppearance_;        //basically the same as visualAppearance.
                                                            //holds the samples this object can play.
    };
}

#endif
