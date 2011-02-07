#include <inputHandler.hpp>

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
