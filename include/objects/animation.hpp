#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
namespace objects
{
#define SPRITE_SIZE 32

    class Animation
    {
        public:
            sf::Sprite* getNextFrame();
            std::string getAnimationId();

            Animation( std::string animationId, std::string fileName, sf::Vector2i rowsAndCollumns, int delayPerFrame );

            Animation();
            ~Animation();
        protected:

        private:
            void iterateToNextFrame();
            int delayPerFrameInMs_;
            std::string animationId_;
            sf::Image* allFrames_;
            std::vector< sf::Sprite* > frames_;
            unsigned int currentFrame_;
    };
}
#endif
