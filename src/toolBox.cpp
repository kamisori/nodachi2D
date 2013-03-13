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

#include <toolBox.hpp>

b2Vec2 toolBox::sfVec_To_b2Vec(sf::Vector2f vector2f)
{
    b2Vec2 result;
    result.x = vector2f.x;
    result.y = vector2f.y;

    return result;
}

sf::Vector2f toolBox::b2Vec_To_sfVec_f(b2Vec2 vector2, int32 ratio, bool flipHorizontaly)
{
    sf::Vector2f result;
    result.x = vector2.x * ratio;
    if(flipHorizontaly)
        result.y = -(vector2.y * ratio);
    else
        result.y = vector2.y * ratio;

    return result;
}
