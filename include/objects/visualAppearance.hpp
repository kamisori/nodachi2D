#ifndef VISUALAPPEARANCE_HPP
#define VISUALAPPEARANCE_HPP

#include <string>
#include <vector>
#include <objects/animation.hpp>
namespace objects
{
    class VisualAppearance
    {
        public:
            void        setCurrentAnimationByAnimationId( std::string animationId );
            Animation*  getCurrentAnimation();
            std::string getVisualAppearanceId();

            VisualAppearance( std::string visualAppearanceId, std::string animationsDescriptionFile );
            VisualAppearance();
            ~VisualAppearance();
        protected:

        private:
            std::string          visualAppearanceId_; //something like player, zombie1, zombie2, ..etc
            std::vector< Animation* >   possibleAnimations_;
            Animation*                  currentAnimation_;
    };
}
#endif
