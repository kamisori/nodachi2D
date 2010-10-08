#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <Box2D/Box2D.h>
class GameWorld
{
    public:
        GameWorld();
        ~GameWorld();
        objects::GameObjectManager* globalGameObjectManager_;

        b2World* simulatedWorld_;

    protected:

    private:
};

#endif
