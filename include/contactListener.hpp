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
