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

#ifndef NODACHI2D_HPP
#define NODACHI2D_HPP

#include <string>
#include <vector>
#include <map>
#include <Box2D/Box2D.h>

#include <objects/gameObjectManager.hpp>
#include <inputHandler.hpp>
#include <contactListener.hpp>

const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

const int32 physicsVisualsRatio = 64;
//dont change the scale, it wont work
const sf::Vector2f spritesScale(1.0, 1.0);

const float32 jumpForce = 400.0;
const float32 fallForce = 15.0;
const float32 horizontalForce = 15.0;
const float32 horizontalForceMidAir = 10.0;
const float32 horizontalSpeedLimit = 10.0;

const float32 Fnull = 0.0;

const b2Vec2 EarthGravity(0.0,-9.8);

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
        int32 resolutionColor_;
        sf::Clock Clock_;
        ContactListener* contactListener_;
    protected:

    private:
        void loadLevel();
        void handleSystemEvents();
        void closeWindow();
        void handleInputEvents( objects::SpacialObject* tmpObject );

        void initializePhysics();
        void intitializeRenderContext();
        void initializeThreads();
        void calculateNextScene();
        void displayNextScene();
};

#endif
