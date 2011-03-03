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

        if( IDa.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->setBottomObject(actorB);
            std::cout << IDa <<" is on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDb.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->setBottomObject(actorA);
            std::cout << IDb <<" is on top of " << IDa << ". " << face << " b" <<std::endl;
        }
        else if( IDb.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->setBottomObject(actorB);
            std::cout << IDa <<" is on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDa.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->setBottomObject(actorA);
            std::cout << IDb <<" is on top of " << IDa << ". " << face << " b" <<std::endl;
        }
        else
        {
            std::cout << IDa << " and " << IDb << " are equaly high. " << face <<std::endl;
        }

std::cout << "a "  << bodyA->GetPosition().y << " " << bodyA->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;
std::cout << "b "  << bodyB->GetPosition().y << " " << bodyB->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;

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

        if( IDa.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->removeBottomObject(actorB);
            std::cout << IDa <<" is no longer on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDb.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->removeBottomObject(actorA);
            std::cout << IDb <<" is no longer on top of " << IDa << ". " << face << " b" <<std::endl;
        }
        else if( IDb.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->removeBottomObject(actorB);
            std::cout << IDa <<" is no longer on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDa.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->removeBottomObject(actorA);
            std::cout << IDb <<" is no longer on top of " << IDa << ". " << face << " b" <<std::endl;
        }
std::cout << "--a "  << bodyA->GetPosition().y << " " << bodyA->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;
std::cout << "--b "  << bodyB->GetPosition().y << " " << bodyB->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;

    }
    return;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ // handle pre-solve event
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ // handle post-solve event
}
