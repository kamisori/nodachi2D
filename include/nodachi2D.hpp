#ifndef KAJIYA2D_HPP
#define KAJIYA2D_HPP

#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <Box2D/Box2D.h>

const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

struct flags{
    bool Running;
    bool ApplyForceUpwardToPlayer;
    bool ApplyForceLeftToPlayer;
    bool ApplyForceRightToPlayer;
    bool ApplyForceDownwardToPlayer;
    bool Restart;
};

class InputHandler :public sf::Thread
{
    private:
        const sf::Input* keyInput_;
        virtual void Run();
    public:
        sf::Mutex* GlobalMutex_;
        flags globalflags_;
        InputHandler(sf::RenderWindow* appWindow, sf::Mutex* GlobalMutex);
        ~InputHandler();
};

class nodachi2D
{
    public:

        InputHandler* inputHandlerThread_;
        void runNodachi2D();

        nodachi2D();
        ~nodachi2D();

        objects::GameObjectManager* globalGameObjectManager_;

        b2World* simulatedWorld_;

        sf::RenderWindow* appWindow_;
        sf::FloatRect ViewRect_;
        sf::View twoDCam_;
        sf::Mutex* GlobalMutex_;
        sf::Vector2f resolution_;
        sf::Clock Clock_;
    protected:

    private:
        void loadLevel();
        void handleSystemEvents();
        void handleInputEvents( objects::SpacialObject* tmpObject );

        void initializePhysics();
        void intitializeRenderContext();
        void initializeThreads();
        void calculateNextScene();
        void displayNextScene();
};

#endif
