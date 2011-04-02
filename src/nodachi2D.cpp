/*
    nodachi2D is a client application for the gameserver heikiko2D.
    Copyright (C) 2010-2011  Paul Predkiewicz

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

#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <nodachi2D.hpp>
#include <Box2D/Box2D.h>
#include <inputHandler.hpp>
#include <iostream>
#include <toolBox.hpp>

nodachi2D::nodachi2D()
{
    initializePhysics();
    loadLevel();

    intitializeRenderContext();
    initializeThreads();
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

void nodachi2D::intitializeRenderContext()
{
    resolution_.x = 1024;
    resolution_.y = 768;
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

void nodachi2D::runNodachi2D()
{
    while (inputHandlerThread_->globalflags_.Running)
    {
        handleSystemEvents();

        calculateNextScene();

        displayNextScene();
    }
}

void nodachi2D::handleSystemEvents()
{
    sf::Event Event;
    while (appWindow_->GetEvent(Event))
    {
        if (Event.Type == sf::Event::Closed)
        {
            closeWindow();
        }
        else if ((Event.Type == sf::Event::KeyPressed))
        {
            if((Event.Key.Code == sf::Key::Escape))
            {
                closeWindow();
            }
        }
    }
}

void nodachi2D::closeWindow()
{
    appWindow_->Close();
    inputHandlerThread_->globalflags_.Running = false;
}

void nodachi2D::calculateNextScene()
{
    simulatedWorld_->Step(timeStep,velocityIterations,positionIterations);
    simulatedWorld_->ClearForces();
}

void nodachi2D::displayNextScene()
{
    sf::Vector2f playerPos;
    bool isOnFloor;

    int currentSpacialObject = 0;

    objects::SpacialObject* tmpObject = globalGameObjectManager_->nextSpacialObject( currentSpacialObject );
    while( tmpObject != NULL )
    {
        sf::Vector2f positionOfCurrentObject;
        b2Body* tmpB2Body = tmpObject->getB2Body();
        positionOfCurrentObject = toolBox::b2Vec_To_sfVec_f(tmpB2Body->GetPosition(), physicsVisualsRatio, true);

        if( tmpObject->getSpacialObjectId().compare( "player" ) == 0 )
        {
            playerPos = positionOfCurrentObject;

            twoDCam_.SetCenter(playerPos);
            appWindow_->SetView(twoDCam_);

            if(tmpObject->standsOnSomething())
            {
                isOnFloor = true;
            }

            handleInputEvents(tmpObject);
        }

        objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();
        sf::Sprite* tmpSprite = tmpAnim->getNextFrame();

        tmpSprite->Scale(spritesScale);
        tmpSprite->SetPosition( positionOfCurrentObject );
        tmpSprite->SetRotation( (tmpB2Body->GetAngle() + tmpObject->getAngleOffsetForAnimation()) *(180/3.14159265f) );

        appWindow_->Draw( (*tmpSprite) );

        currentSpacialObject++;
        tmpObject = globalGameObjectManager_->nextSpacialObject( currentSpacialObject );
    }

    if(isOnFloor)
    {
        sf::String onFloor("On Floor");
        sf::Shape BGRect = sf::Shape::Rectangle(0.0,0.0,250.0,80.0,sf::Color::Black);

        onFloor.SetScale(2.0,2.0);
        onFloor.SetColor(sf::Color::Green);

        BGRect.SetPosition( playerPos.x+280, playerPos.y+320);
        onFloor.SetPosition( playerPos.x+280, playerPos.y+320);

        appWindow_->Draw(BGRect);
        appWindow_->Draw(onFloor);
    }

    appWindow_->Display();
    appWindow_->Clear();
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
    if( standing && inputHandlerThread_->globalflags_.ApplyForceUpwardToPlayer && (Clock_.GetElapsedTime() >= 0.5))
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

nodachi2D::~nodachi2D(){
    delete this->globalGameObjectManager_;
}
