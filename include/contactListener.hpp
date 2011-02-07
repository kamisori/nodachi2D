#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
  void BeginContact(b2Contact* contact);
  void EndContact(b2Contact* contact);
  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
  ContactListener();
};
#endif
