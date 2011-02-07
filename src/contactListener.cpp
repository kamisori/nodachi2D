#include <contactListener.hpp>
#include <objects/spacialObject.hpp>
#include <iostream>


ContactListener::ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Body* bodyA = fixtureA->GetBody();
    objects::SpacialObject* actorA = (objects::SpacialObject*)bodyA->GetUserData();

    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyB = fixtureB->GetBody();
    objects::SpacialObject* actorB = (objects::SpacialObject*)bodyB->GetUserData();

    std::string IDa = actorA->getSpacialObjectId();
    std::string IDb = actorB->getSpacialObjectId();

    if( IDa.compare("player") == 0 || IDb.compare("player") == 0 )
    {
        b2Manifold* contactsManifold = contact->GetManifold();
        std::string face;
        if( contactsManifold->type == b2Manifold::e_faceA )
        {
            face = IDa;
        }
        else if( contactsManifold->type == b2Manifold::e_faceB )
        {
            face = IDb;
        }


        if( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.375 )
        {
            std::cout << IDb <<" is higher than " << IDa << ". " << face << " " << contactsManifold->localPoint.y <<std::endl;
        }
        else if( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.375 )
        {
            std::cout << IDa <<" is higher than " << IDb << ". " << face << " " << contactsManifold->localPoint.y <<std::endl;
        }
        else
        {
            std::cout << IDa << " and " << IDb << " are equaly high. " << face << " " << contactsManifold->localPoint.y <<std::endl;
        }

        if( contactsManifold->type == b2Manifold::e_faceA )
        {
            if( bodyA->GetWorldPoint(contactsManifold->localPoint).y < bodyA->GetPosition().y  && IDa.compare("player") == 0 )
            {
                actorA->setBottomObject(actorB);
            }
            else if( bodyA->GetWorldPoint(contactsManifold->localPoint).y > bodyA->GetPosition().y  && IDb.compare("player") == 0 )
            {
                actorB->setBottomObject(actorA);
            }
        }
        else if( contactsManifold->type == b2Manifold::e_faceB )
        {
            if( bodyB->GetWorldPoint(contactsManifold->localPoint).y < bodyB->GetPosition().y  && IDb.compare("player") == 0 )
            {
                actorB->setBottomObject(actorA);
            }
            else if( bodyB->GetWorldPoint(contactsManifold->localPoint).y > bodyB->GetPosition().y  && IDa.compare("player") == 0 )
            {
                actorA->setBottomObject(actorB);
            }
        }
    }
    return;
}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Body* bodyA = fixtureA->GetBody();
    objects::SpacialObject* actorA = (objects::SpacialObject*)bodyA->GetUserData();

    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyB = fixtureB->GetBody();
    objects::SpacialObject* actorB = (objects::SpacialObject*)bodyB->GetUserData();

    b2Manifold* contactsManifold = contact->GetManifold();


    std::string IDa = actorA->getSpacialObjectId();
    std::string IDb = actorB->getSpacialObjectId();

    if( IDa.compare("player") == 0 || IDb.compare("player") == 0 )
    {
        if( contactsManifold->type == b2Manifold::e_faceA )
        {
            if( bodyA->GetWorldPoint(contactsManifold->localPoint).y < bodyA->GetPosition().y  && IDa.compare("player") == 0 )
            {
                actorA->removeBottomObject(actorB);
            }
            else if( bodyA->GetWorldPoint(contactsManifold->localPoint).y > bodyA->GetPosition().y  && IDb.compare("player") == 0 )
            {
                actorB->removeBottomObject(actorA);
            }
        }
        else if( contactsManifold->type == b2Manifold::e_faceB )
        {
            if( bodyB->GetWorldPoint(contactsManifold->localPoint).y < bodyB->GetPosition().y  && IDb.compare("player") == 0 )
            {
                actorB->removeBottomObject(actorA);
            }
            else if( bodyB->GetWorldPoint(contactsManifold->localPoint).y > bodyB->GetPosition().y  && IDa.compare("player") == 0 )
            {
                actorA->removeBottomObject(actorB);
            }
        }
    }
    return;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ // handle pre-solve event
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ // handle post-solve event
}
