#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
#endif
