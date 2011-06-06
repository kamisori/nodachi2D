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

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/spacialObject.hpp>
#include <objects/gameObjectManager.hpp>
#include <main.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <iostream>

namespace objects
{
    double Object::getRotation()
    {
        return rotation_;
    }

    void Object::setRotation( double newRotation)
    {
        rotation_ = newRotation;
    }

    std::string Object::getObjectId()
    {
        return objectID_;
    }

    VisualAppearance* Object::getVisualAppearance()
    {
        return visualAppearance_;
    }

    Object::Object( std::string objectId, std::string visualAppearanceID, sf::Vector2f position, double rotation, double scale )
    {
        objectID_.assign( objectId );

        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( temporaryMaterial->getVisualAppearanceId() );

        std::string animId ("static");
        this->visualAppearance_->setCurrentAnimationByAnimationId( animId );

        position_ = position;
        rotation_ = rotation;
        scale_ = scale;
    }

    Object::~Object()
    {
        this->visualAppearance_ = NULL;
    }
}
