#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <nodachi2D.hpp>
#include <Box2D/Box2D.h>
#include <inputHandler.hpp>

void nodachi2D::intitializeRenderContext()
{
    resolution_.x = 800;
    resolution_.y = 600;
    resolutionColor_ = 32;

    ViewRect_ = sf::FloatRect(0, 0, resolution_.x, resolution_.y);
    twoDCam_ = sf::View(ViewRect_);
    appWindow_ = new sf::RenderWindow(sf::VideoMode(resolution_.x, resolution_.y, resolutionColor_), "nodachi2D");
    appWindow_->UseVerticalSync(true);
    appWindow_->SetView(twoDCam_);

    /* Creating a fullscreen window with the best video mode supported
    appWindow_->Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
    sf::VideoMode DesktopMode = sf::VideoMode::GetDesktopMode(); */


}

void nodachi2D::initializeThreads()
{
    GlobalMutex_ = new sf::Mutex();
    inputHandlerThread_ = new InputHandler(appWindow_, GlobalMutex_);
}

void nodachi2D::initializePhysics()
{
    this->contactListener_ = new ContactListener();
    this->globalGameObjectManager_ = new objects::GameObjectManager();
    bool doSleep = true;
    this->simulatedWorld_ = new b2World(EarthGravity, doSleep);
    this->simulatedWorld_->SetContactListener(contactListener_);
}

void nodachi2D::loadLevel()
{
    std::string visualAppearancesFile ( "data/visualAppearances.data" );
    std::string materialFile ( "data/materials.data" );
    std::string objectFile ( "data/spacialObjects.data" );

    this->globalGameObjectManager_->loadVisualAppearances( visualAppearancesFile );
    this->globalGameObjectManager_->loadMaterials( materialFile );
    this->globalGameObjectManager_->loadObjects( objectFile );
}

void nodachi2D::handleSystemEvents()
{
    sf::Event Event;
    while (appWindow_->GetEvent(Event))
    {
        // Window closed
        if (Event.Type == sf::Event::Closed){
            appWindow_->Close();
            inputHandlerThread_->globalflags_.Running = false;
        }

        // Escape key pressed
        if ((Event.Type == sf::Event::KeyPressed)){
            if((Event.Key.Code == sf::Key::Escape)){
                appWindow_->Close();
                inputHandlerThread_->globalflags_.Running = false;
            }
        }

        if((Event.Type == sf::Event::KeyPressed)){
            if((Event.Key.Code == sf::Key::R)){
                inputHandlerThread_->globalflags_.Restart = true;
            }
        }
    }
}

void nodachi2D::handleInputEvents(objects::SpacialObject* tmpObject)
{
    bool standing = tmpObject->standsOnSomething();
    b2Body* tmpB2Body = tmpObject->getB2Body();
    b2Vec2 position = tmpB2Body->GetPosition();
    b2Vec2 linearVelocity = tmpB2Body->GetLinearVelocity();
    b2Vec2 tmpForce;

    tmpForce.x = Fnull;
    tmpForce.y = Fnull;
    GlobalMutex_->Lock();
    if( standing && inputHandlerThread_->globalflags_.ApplyForceUpwardToPlayer && (Clock_.GetElapsedTime() >= 0.125))
    {
        //tmpForce.y = 50.0 * cos(angle);
        //tmpForce.x = 50.0 * sin(angle);
        tmpForce.y = jumpForce;
        tmpForce.x = Fnull;

        tmpB2Body->ApplyForce( tmpForce, position );
        tmpObject->iJumped();
        inputHandlerThread_->globalflags_.ApplyForceUpwardToPlayer = false;
        Clock_.Reset();
    }
    if(inputHandlerThread_->globalflags_.ApplyForceDownwardToPlayer)
    {
        //tmpForce.y = -50.0 * cos(angle);
        //tmpForce.x = -50.0 * sin(angle);
        tmpForce.y = -1 * fallForce;
        tmpForce.x = Fnull;
        tmpB2Body->ApplyForce( tmpForce, position );
    }
    if(inputHandlerThread_->globalflags_.ApplyForceLeftToPlayer)
    {
        tmpForce.y = Fnull;
        if( linearVelocity.x > (-1 * horizontalSpeedLimit) )
        {
            if(standing)
                tmpForce.x = -1 * horizontalForce;
            else
                tmpForce.x = -1 * horizontalForceMidAir;
            tmpB2Body->ApplyForce( tmpForce, position);
        }
    }
    if(inputHandlerThread_->globalflags_.ApplyForceRightToPlayer)
    {
        tmpForce.y = Fnull;
        if( linearVelocity.x < horizontalSpeedLimit )
        {
            if(standing)
                tmpForce.x = horizontalForce;
            else
                tmpForce.x = horizontalForceMidAir;
            tmpB2Body->ApplyForce( tmpForce, position);
        }
    }
    GlobalMutex_->Unlock();
}

void nodachi2D::calculateNextScene()
{
    simulatedWorld_->Step(timeStep,velocityIterations,positionIterations);
    simulatedWorld_->ClearForces();
}

void nodachi2D::displayNextScene()
{
     int i = 0;
        objects::SpacialObject* tmpObject = globalGameObjectManager_->nextSpacialObject( i );
        while( tmpObject != NULL )
        {
            b2Body* tmpB2Body = tmpObject->getB2Body();
            b2Vec2 position = tmpB2Body->GetPosition();
            float32 angle = tmpB2Body->GetAngle();

            std::string objectID = tmpObject->getSpacialObjectId();


            if( objectID.compare( "player" ) == 0 ){

                sf::Vector2f tmpPos;
                tmpPos.x = (position.x*physicsVisualsRatio);
                tmpPos.y = -(position.y*physicsVisualsRatio);

                twoDCam_.SetCenter(tmpPos);
                appWindow_->SetView(twoDCam_);

                handleInputEvents(tmpObject);
            }

            objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();
            sf::Sprite* tmpSprite = tmpAnim->getNextFrame();

            tmpSprite->Scale(spritesScale);
            tmpSprite->SetPosition( (position.x*physicsVisualsRatio) , -(position.y*physicsVisualsRatio) );
            tmpSprite->SetRotation( (angle + tmpObject->getAngleOffsetForAnimation()) *(180/3.14159265f) );
            appWindow_->Draw( (*tmpSprite) );

            i++;
            tmpObject = globalGameObjectManager_->nextSpacialObject( i );
        }
        appWindow_->Display();
        appWindow_->Clear();
}

void nodachi2D::runNodachi2D()
{
    while (inputHandlerThread_->globalflags_.Running)
    {
        handleSystemEvents();

        calculateNextScene();

        displayNextScene();
    }
}

nodachi2D::nodachi2D()
{
    initializePhysics();
    loadLevel();


    intitializeRenderContext();
    initializeThreads();
}

nodachi2D::~nodachi2D(){
    delete this->globalGameObjectManager_;
}
