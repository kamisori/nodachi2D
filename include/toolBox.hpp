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

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
class toolBox
{
    public:
    static b2Vec2 sfVec_To_b2Vec(sf::Vector2f vector2f);
    static sf::Vector2f b2Vec_To_sfVec_f(b2Vec2 vector2, int32 ratio, bool flipHorizontaly);
};
