#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <gameWorld.hpp>
#include <Box2D/Box2D.h>

GameWorld::GameWorld()
{
    std::string visualAppearancesFile ( "data/visualAppearances.data" );
    std::string materialFile ( "data/materials.data" );
    std::string objectFile ( "data/spacialObjects.data" );

    this->globalGameObjectManager_ = new objects::GameObjectManager();

    b2Vec2 gravity(0.0,-9.8);
    bool doSleep = true;
    this->simulatedWorld_ = new b2World(gravity, doSleep);

    this->globalGameObjectManager_->loadVisualAppearances( visualAppearancesFile );
    this->globalGameObjectManager_->loadMaterials( materialFile );
    this->globalGameObjectManager_->loadObjects( objectFile );
}
GameWorld::~GameWorld(){
    delete this->globalGameObjectManager_;
}
