#include <string>
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

    bool SpacialObject::standsOnSomething()
    {
        b2Body* thisB2Body = this->getB2Body();
        float32 thisB2BodyYPos= thisB2Body->GetPosition().y;
        for( b2ContactEdge* contactEdge = thisB2Body->GetContactList();
             contactEdge; contactEdge = contactEdge->next )
        {
            if( thisB2BodyYPos > contactEdge->other->GetPosition().y )
            {
                b2Manifold* contactManifold = contactEdge->contact->GetManifold();
                if( contactManifold->pointCount == 2 )
                {
                    if( contactManifold->points[0].localPoint.x !=  contactManifold->points[1].localPoint.x )
                    {
                        return true;
                    }
                }
                else if( contactManifold->pointCount == 1 )
                {
                    if( contactManifold->points[0].localPoint.y < ( thisB2BodyYPos - 0.5 ) )
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    SpacialObject::SpacialObject( std::string spacialObjectId, std::string visualAppearanceId, b2BodyDef* bodyDefinition, b2FixtureDef* fixtureDefinition )
    {
        std::cout <<"created "<<spacialObjectId<<std::endl;;
        spacialObjectId_.assign( spacialObjectId );

        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( visualAppearanceId );

        std::string visId ("static");
        this->visualAppearance_->setCurrentAnimationByAnimationId( visId );


        bodyDefinition->userData = this;
        this->b2Body_ = b2WorldAndVisualWorld.simulatedWorld_->CreateBody( bodyDefinition );
        this->b2Body_->CreateFixture( fixtureDefinition );
    }

    SpacialObject::~SpacialObject()
    {
        b2WorldAndVisualWorld.simulatedWorld_->DestroyBody(this->b2Body_);
        this->visualAppearance_ = NULL;
    }

}
