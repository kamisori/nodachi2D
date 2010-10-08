#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <gameWorld.hpp>
#include <Box2D/Box2D.h>

GameWorld::GameWorld()
{

    this->globalGameObjectManager_ = new objects::GameObjectManager();
    std::string visualAppearancesFile ("data/visualAppearances.data");
    this->globalGameObjectManager_->loadVisualAppearances( visualAppearancesFile );

    b2Vec2 gravity(0.0,-9.8);
    bool doSleep = true;
    this->simulatedWorld_ = new b2World(gravity, doSleep);
    std::string objectFile ("data/spacialObjects.data");
    this->globalGameObjectManager_->loadObjects( objectFile );
    /*
    //example:
    std::string groundId ("ground_concrete");
    std::string groundVisId ("ground_concrete");

    b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(10.0f, 15.0f);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(5.0f, 0.5f);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundBox;
	groundFixtureDef.density = 0.0f;
	this->globalGameObjectManager_->createSpacialObject( groundId, groundVisId, &groundBodyDef, &groundFixtureDef );

    std::string blockId ("block_concrete1");
    std::string blockVisId ("block_concrete");

    b2BodyDef blockBodyDef;
	blockBodyDef.position.Set(12.0f, 9.0f);

	b2PolygonShape blockBox;
	blockBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef blockFixtureDef;
	blockFixtureDef.shape = &blockBox;
	blockFixtureDef.density = 0.0f;
	this->globalGameObjectManager_->createSpacialObject( blockId, blockVisId, &blockBodyDef, &blockFixtureDef );

    std::string block2Id ("block_concrete2");
    std::string block2VisId ("block_concrete");

    b2BodyDef block2BodyDef;
	block2BodyDef.position.Set(9.0f, 6.0f);

	b2PolygonShape block2Box;
	block2Box.SetAsBox(0.5f, 0.5f);

	b2FixtureDef block2FixtureDef;
	block2FixtureDef.shape = &block2Box;
	block2FixtureDef.density = 0.0f;
	this->globalGameObjectManager_->createSpacialObject( block2Id, block2VisId, &block2BodyDef, &block2FixtureDef );

    std::string crateId ("crate_wood");
    std::string crateVisId ("crate_wood");

	b2BodyDef crateBodyDef;
	crateBodyDef.type = b2_dynamicBody;
	crateBodyDef.position.Set(10.0f, 1.0f);
	crateBodyDef.angle = 0.3f ;

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef cratefixtureDef;
	cratefixtureDef.shape = &dynamicBox;
	cratefixtureDef.density = 1.0f;
	cratefixtureDef.friction = 0.3f;
	this->globalGameObjectManager_->createSpacialObject( crateId, crateVisId, &crateBodyDef, &cratefixtureDef);
	*/
}
GameWorld::~GameWorld(){
    delete this->globalGameObjectManager_;
}
