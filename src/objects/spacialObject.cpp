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
    void SpacialObject::setBottomObject( SpacialObject* bottomObject )
    {
        this->bottom.push_back( bottomObject->getSpacialObjectId() );
    }

    void SpacialObject::removeBottomObject( SpacialObject* bottomObject )
    {
        for(std::vector<std::string>::iterator it = this->bottom.begin(); it < this->bottom.end(); it++ )
        {
            if(it->compare(bottomObject->getSpacialObjectId()) == 0)
            {
                this->bottom.erase(it);
            }
        }
    }

    void SpacialObject::iJumped()
    {
        this->bottom.clear();
    }

    bool SpacialObject::standsOnSomething()
    {
        return !(this->bottom.empty());
    }

    float SpacialObject::getAngleOffsetForAnimation()
    {
        return angleOffsetForAnimation_;
    }

    void SpacialObject::setAngleOffsetForAnimation( float tmp)
    {
        angleOffsetForAnimation_ = tmp;
    }

    std::string SpacialObject::getSpacialObjectId()
    {
        return spacialObjectId_;
    }

    b2Body* SpacialObject::getB2Body()
    {
        return b2Body_;
    }

    VisualAppearance* SpacialObject::getVisualAppearance()
    {
        return visualAppearance_;
    }

    SpacialObject::SpacialObject( std::string spacialObjectId, std::string materialId, b2Vec2 position )
    {
        spacialObjectId_.assign( spacialObjectId );

        Material* temporaryMaterial;
        temporaryMaterial = b2WorldAndVisualWorld.globalGameObjectManager_->provideMaterial( materialId );

        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( temporaryMaterial->getVisualAppearanceId() );

        std::string visId ("static");
        this->visualAppearance_->setCurrentAnimationByAnimationId( visId );

        b2FixtureDef* fixtureDefinition = temporaryMaterial->createFixtureDefinition();
        b2BodyDef* bodyDefinition = temporaryMaterial->createBodyDefinition();

        bodyDefinition->userData = this;
        bodyDefinition->position.x = position.x;
        bodyDefinition->position.y = position.y;
        this->b2Body_ = b2WorldAndVisualWorld.simulatedWorld_->CreateBody( bodyDefinition );


        if( temporaryMaterial->thisIsACircle() )
        {
            fixtureDefinition->shape = temporaryMaterial->createCircleShape();
        }
        else
        {
            fixtureDefinition->shape = temporaryMaterial->createPolygonShape();
        }

        this->b2Body_->CreateFixture( fixtureDefinition );
        this->setAngleOffsetForAnimation( temporaryMaterial->getAngleOffsetForAnimation() );
    }

    SpacialObject::~SpacialObject()
    {
        b2WorldAndVisualWorld.simulatedWorld_->DestroyBody(this->b2Body_);
        this->visualAppearance_ = NULL;
    }

}
