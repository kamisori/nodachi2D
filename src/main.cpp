#include <iostream>
#include <SFML/System.hpp>
#include <objects/gameObjectManager.hpp>
#include <objects/animation.hpp>
#include <gameWorld.hpp>
#include <main.hpp>
#include <stdio.h>
#include <objects/spacialObject.hpp>

struct flags{
    bool Running;
}globalflags;
bool ApplyForceUpwardToPlayer = false;
bool ApplyForceLeftToPlayer = false;
bool ApplyForceRightToPlayer = false;
bool ApplyForceDownwardToPlayer = false;
bool Restart = false;

sf::Mutex GlobalMutex;
GameWorld b2WorldAndVisualWorld;
sf::Vector2f resolution;
sf::Clock Clock_;

void inputThread(void* UserData)
{
    sf::Window* app = static_cast<sf::Window*>(UserData);
    const sf::Input* keyInput = &app->GetInput();
    while( globalflags.Running )
    {
        GlobalMutex.Lock();
        ApplyForceLeftToPlayer = keyInput->IsKeyDown(sf::Key::Left);
        ApplyForceRightToPlayer = keyInput->IsKeyDown(sf::Key::Right);
        ApplyForceDownwardToPlayer = keyInput->IsKeyDown(sf::Key::Down);
        ApplyForceUpwardToPlayer = keyInput->IsKeyDown(sf::Key::Up);
        GlobalMutex.Unlock();
    }
}

int main()
{
    globalflags.Running = true;
    resolution.x = 800;
    resolution.y = 600;

    //load settings and stuff
    sf::FloatRect ViewRect = sf::FloatRect(0, 0, resolution.x, resolution.y);
    sf::View twoDCam = sf::View(ViewRect);
    sf::RenderWindow App(sf::VideoMode(resolution.x, resolution.y, 32), "nodachi2D");
    App.UseVerticalSync(true);
    App.SetView(twoDCam);

    /* Creating a fullscreen window with the best video mode supported
    App.Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
    sf::VideoMode DesktopMode = sf::VideoMode::GetDesktopMode(); */

    sf::Thread inputHandler(&inputThread, &App);
    inputHandler.Launch();

    while (globalflags.Running)
    {
////////////////////            logic
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Window closed
            if (Event.Type == sf::Event::Closed){
                App.Close();
                globalflags.Running = false;
            }

            // Escape key pressed
            if ((Event.Type == sf::Event::KeyPressed)){
                if((Event.Key.Code == sf::Key::Escape)){
                    App.Close();
                    globalflags.Running = false;
                }
            }

            if((Event.Type == sf::Event::KeyPressed)){
                if((Event.Key.Code == sf::Key::R)){
                    Restart = true;
                }
            }
        }

////////////////////            physics calculations

        b2WorldAndVisualWorld.simulatedWorld_->Step(timeStep,velocityIterations,positionIterations);
        b2WorldAndVisualWorld.simulatedWorld_->ClearForces();
        //std::cout << "physics took: " << Clock_.GetElapsedTime() << std::endl;

////////////////////            drawing/evaluating data from the calculations

        int i = 0;
        objects::SpacialObject* tmpObject = b2WorldAndVisualWorld.globalGameObjectManager_->nextSpacialObject( i );
        while( tmpObject != NULL )
        {
            b2Body* tmpB2Body = tmpObject->getB2Body();

            objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();

            b2Vec2 position = tmpB2Body->GetPosition();

            float32 angle = tmpB2Body->GetAngle();
            std::string object = tmpObject->getSpacialObjectId();

            if(tmpB2Body->IsFixedRotation()){
                std::cout << "object can not rotate " << object << std::endl;
            }
            else{
                std::cout << "object can rotate " << object << std::endl;
            }

            GlobalMutex.Lock();
            if( object.compare( "player" ) == 0 ){
                bool standing = tmpObject->standsOnSomething();
                /*if(standing)
                {
                    std::cout << "player is standing"<< std::endl;
                }
                else
                {
                    std::cout << "player is airborne"<< std::endl;
                }*/
                b2Vec2 linearVelocity = tmpB2Body->GetLinearVelocity();

                sf::Vector2f tmpPos;
                tmpPos.x = (position.x*32);
                tmpPos.y = -(position.y*32);

                sf::View tmpView = App.GetView();
                tmpView.SetCenter(tmpPos);
                App.SetView(tmpView);
                if( ApplyForceUpwardToPlayer && standing && (Clock_.GetElapsedTime() >= 0.25)){

                    //std::cout << "JUMP!!" << Clock_.GetElapsedTime() << std::endl;
                    b2Vec2 tmpForce;
                    //tmpForce.y = 50.0 * cos(angle);
                    //tmpForce.x = 50.0 * sin(angle);
                    tmpForce.y = 500.0;
                    tmpForce.x = 0.0;
                    tmpB2Body->ApplyForce( tmpForce, position );
                    ApplyForceUpwardToPlayer = false;
                    Clock_.Reset();
                }
                if(ApplyForceDownwardToPlayer){
                    b2Vec2 tmpForce;
                    //tmpForce.y = -50.0 * cos(angle);
                    //tmpForce.x = -50.0 * sin(angle);
                    tmpForce.y = -30.0;
                    tmpForce.x = 0.0;
                    tmpB2Body->ApplyForce( tmpForce, position );
                    //ApplyForceDownwardToPlayer = false;
                }
                if(ApplyForceLeftToPlayer)
                {
                    if( linearVelocity.x > -10.0 )
                    {
                        b2Vec2 tmpForce;
                        tmpForce.y = 0.0;

                        if(standing)
                            tmpForce.x = -30.0;
                        else
                            tmpForce.x = -10.0;
                        tmpB2Body->ApplyForce( tmpForce, position);
                    }
                    //ApplyForceLeftToPlayer = false;
                }
                if(ApplyForceRightToPlayer)
                {
                    if( linearVelocity.x < 10.0 )
                    {
                        b2Vec2 tmpForce;
                        tmpForce.y = 0.0;

                        if(standing)
                            tmpForce.x = 30.0;
                        else
                            tmpForce.x = 10.0;
                        tmpB2Body->ApplyForce( tmpForce, position);
                    }
                    //ApplyForceRightToPlayer = false;
                }
            }
            GlobalMutex.Unlock();
            sf::Sprite* tmpSprite = tmpAnim->getNextFrame();

            tmpSprite->SetPosition( (position.x*32) , -(position.y*32) );
            tmpSprite->SetRotation( (angle + tmpObject->getAngleOffsetForAnimation()) *(180/3.1415f) );
            App.Draw( (*tmpSprite) );

            //std::cout << tmpObject->getSpacialObjectId() << " " << position.x << " " << position.y << " " << angle << std::endl;

            i++;
            tmpObject = b2WorldAndVisualWorld.globalGameObjectManager_->nextSpacialObject( i );
        }
        App.Display();
        App.Clear();
    }
    return EXIT_SUCCESS;
}
