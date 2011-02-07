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
    void SpacialObject::setBottomObject( SpacialObject* bottomObject )
    {
        std::cout << this->getSpacialObjectId() << ": ";
        for(uint32 i = 0; i < objects::sizeOfcontactIDlist; i++)
        {
            std::cout << bottom[i] << " ";
            if(this->bottom[i].empty())
            {
                this->bottom[i] = bottomObject->getSpacialObjectId();
                std::cout << "  ++  " << bottom[i] << std::endl;
                return;
            }
        }
        std::cout << std::endl;
    }

    void SpacialObject::removeBottomObject( SpacialObject* bottomObject )
    {
        std::string bottomID = bottomObject->getSpacialObjectId();
        std::cout << this->getSpacialObjectId() << ": ";
        for(uint32 i = 0; i < objects::sizeOfcontactIDlist; i++)
        {
            std::cout << bottom[i] << " ";
            if(this->bottom[i].compare(bottomID) == 0)
            {
                std::cout << "  --  " << bottom[i] << std::endl;
                this->bottom[i].clear();
                return;
            }
        }
        std::cout << std::endl;
    }

    void SpacialObject::iJumped()
    {
        for(uint32 i = 0; i<objects::sizeOfcontactIDlist;i++)
        {
            this->bottom[i].clear();
        }
    }

    bool SpacialObject::standsOnSomething()
    {
        uint32 tmp = 0;

        for(uint32 i = 0; i<objects::sizeOfcontactIDlist;i++)
        {
            if(!this->bottom[i].empty())
            {
                tmp += 1;
            }
        }

        if(tmp == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
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
