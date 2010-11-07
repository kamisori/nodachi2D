#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <nodachi2D.hpp>
#include <Box2D/Box2D.h>

InputHandler::InputHandler(sf::RenderWindow* appWindow, sf::Mutex* GlobalMutex)
{
    keyInput_ = &appWindow->GetInput();
    GlobalMutex_ = GlobalMutex;

    globalflags_.Running = true;

    globalflags_.ApplyForceUpwardToPlayer = false;
    globalflags_.ApplyForceLeftToPlayer = false;
    globalflags_.ApplyForceRightToPlayer = false;
    globalflags_.ApplyForceDownwardToPlayer = false;
    globalflags_.Restart = false;

    Launch();
}
InputHandler::~InputHandler()
{
    Terminate();
}

void InputHandler::Run()
{
    while( globalflags_.Running )
    {
        GlobalMutex_->Lock();
        globalflags_.ApplyForceLeftToPlayer = keyInput_->IsKeyDown(sf::Key::Left);
        globalflags_.ApplyForceRightToPlayer = keyInput_->IsKeyDown(sf::Key::Right);
        globalflags_.ApplyForceDownwardToPlayer = keyInput_->IsKeyDown(sf::Key::Down);
        globalflags_.ApplyForceUpwardToPlayer = keyInput_->IsKeyDown(sf::Key::Up);
        GlobalMutex_->Unlock();
    }
}

void nodachi2D::intitializeRenderContext()
{
    resolution_.x = 800;
    resolution_.y = 600;

    ViewRect_ = sf::FloatRect(0, 0, resolution_.x, resolution_.y);
    twoDCam_ = sf::View(ViewRect_);
    appWindow_ = new sf::RenderWindow(sf::VideoMode(resolution_.x, resolution_.y, 32), "nodachi2D");
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
    this->globalGameObjectManager_ = new objects::GameObjectManager();
    b2Vec2 gravity(0.0,-9.8);
    bool doSleep = true;
    this->simulatedWorld_ = new b2World(gravity, doSleep);
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

    tmpForce.x = 0.0;
    tmpForce.y = 0.0;
    GlobalMutex_->Lock();
    if( inputHandlerThread_->globalflags_.ApplyForceUpwardToPlayer && standing && (Clock_.GetElapsedTime() >= 0.25))
    {
        //tmpForce.y = 50.0 * cos(angle);
        //tmpForce.x = 50.0 * sin(angle);
        tmpForce.y = 500.0;

        tmpB2Body->ApplyForce( tmpForce, position );
        inputHandlerThread_->globalflags_.ApplyForceUpwardToPlayer = false;
        Clock_.Reset();
    }
    if(inputHandlerThread_->globalflags_.ApplyForceDownwardToPlayer)
    {
        //tmpForce.y = -50.0 * cos(angle);
        //tmpForce.x = -50.0 * sin(angle);
        tmpForce.y = -30.0;
        tmpB2Body->ApplyForce( tmpForce, position );
    }
    if(inputHandlerThread_->globalflags_.ApplyForceLeftToPlayer)
    {
        if( linearVelocity.x > -10.0 )
        {
            if(standing)
                tmpForce.x = -30.0;
            else
                tmpForce.x = -10.0;
            tmpB2Body->ApplyForce( tmpForce, position);
        }
    }
    if(inputHandlerThread_->globalflags_.ApplyForceRightToPlayer)
    {
        if( linearVelocity.x < 10.0 )
        {
            if(standing)
                tmpForce.x = 30.0;
            else
                tmpForce.x = 10.0;
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

            std::string object = tmpObject->getSpacialObjectId();


            if( object.compare( "player" ) == 0 ){

                sf::Vector2f tmpPos;
                tmpPos.x = (position.x*32);
                tmpPos.y = -(position.y*32);

                twoDCam_.SetCenter(tmpPos);
                appWindow_->SetView(twoDCam_);

                handleInputEvents(tmpObject);
            }

            objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();
            sf::Sprite* tmpSprite = tmpAnim->getNextFrame();

            tmpSprite->SetPosition( (position.x*32) , -(position.y*32) );
            tmpSprite->SetRotation( (angle + tmpObject->getAngleOffsetForAnimation()) *(180/3.1415f) );
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
