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

    SpacialObject::SpacialObject( std::string spacialObjectId, std::string materialId, b2Vec2 position )
    {
        spacialObjectId_.assign( spacialObjectId );

        Material* temporaryMaterial;
        temporaryMaterial = b2WorldAndVisualWorld.globalGameObjectManager_->provideMaterial( materialId );

        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( temporaryMaterial->getVisualAppearanceId() );

        std::string visId ("static");
        this->visualAppearance_->setCurrentAnimationByAnimationId( visId );

        b2FixtureDef fixtureDefinition = temporaryMaterial->getFixtureDefinition();
        b2BodyDef bodyDefinition = temporaryMaterial->getBodyDefinition();

        bodyDefinition.userData = this;
        bodyDefinition.position = position;
        this->b2Body_ = b2WorldAndVisualWorld.simulatedWorld_->CreateBody( &bodyDefinition );

        if( temporaryMaterial->thisIsACircle() )
        {
            fixtureDefinition.shape = temporaryMaterial->getCircleShape();
        }
        else
        {
            fixtureDefinition.shape = temporaryMaterial->getPolygonShape();
        }

        this->b2Body_->CreateFixture( &fixtureDefinition );
        this->setAngleOffsetForAnimation( temporaryMaterial->getAngleOffsetForAnimation() );
    }

    SpacialObject::~SpacialObject()
    {
        b2WorldAndVisualWorld.simulatedWorld_->DestroyBody(this->b2Body_);
        this->visualAppearance_ = NULL;
    }

}
