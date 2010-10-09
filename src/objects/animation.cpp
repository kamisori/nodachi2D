#include <string>
#include <vector>
#include <objects/animation.hpp>
namespace objects
{
    void Animation::iterateToNextFrame(){
        this->currentFrame_++;
        if( this->currentFrame_ >= this->frames_.size() ){
            this->currentFrame_ = 0;
        }
    }


    sf::Sprite* Animation::getNextFrame()
    {
        this->iterateToNextFrame();
        return this->frames_[this->currentFrame_];
    }

    std::string Animation::getAnimationId()
    {
        return this->animationId_;
    }


    Animation::Animation( std::string animationId, std::string fileName, sf::Vector2i rowsAndCollumns, int delayPerFrameInMs )
    {
        this->allFrames_ = new sf::Image();

        this->animationId_ = animationId;
        this->delayPerFrameInMs_ = delayPerFrameInMs;

        if( allFrames_->LoadFromFile( fileName ) )
        {
            sf::Vector2i* imageDimensions = new sf::Vector2i();
            sf::Vector2i* spriteDimensions = new sf::Vector2i();

            imageDimensions->y = this->allFrames_->GetHeight();
            imageDimensions->x = this->allFrames_->GetWidth();

            spriteDimensions->y = imageDimensions->y / rowsAndCollumns.y;
            spriteDimensions->x = imageDimensions->x / rowsAndCollumns.x;

            for( int y = 0; y <= imageDimensions->y - spriteDimensions->y; y += spriteDimensions->y )
            {
                for( int x = 0; x <= imageDimensions->x - spriteDimensions->x; x += spriteDimensions->x )
                {
                    sf::Sprite* temporarySprite = new sf::Sprite();

                    temporarySprite->SetCenter( ( spriteDimensions->x / 2 ), ( spriteDimensions->y / 2 ) );
                    temporarySprite->SetImage( (*allFrames_) );
                    temporarySprite->SetBlendMode(sf::Blend::None);
                    temporarySprite->SetSubRect( sf::IntRect( x, y, spriteDimensions->x, spriteDimensions->y ) );

                    this->frames_.push_back( temporarySprite );
                }
            }

            if( this->frames_.size() != (unsigned) ( rowsAndCollumns.x * rowsAndCollumns.y ) )
            {
                exit(1);
            }
        }
    }

    Animation::Animation(){
        exit(1);
    }
    Animation::~Animation(){
        this->frames_.clear();
        delete this->allFrames_;
    }
}
