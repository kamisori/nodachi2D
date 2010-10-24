#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <objects/animation.hpp>
#include <objects/visualAppearance.hpp>
#include <main.hpp>

namespace objects
{
    typedef std::vector< std::string > FileEntry;
    typedef std::vector< FileEntry > FileData;

    void VisualAppearance::setCurrentAnimationByAnimationId( std::string animationId )
    {
        std::vector< Animation* >::iterator it;
        for( it = possibleAnimations_.begin(); it < possibleAnimations_.end(); it++ )
        {
            if( animationId.compare( (*it)->getAnimationId() ) == 0 )
            {
                this->currentAnimation_ = *it;
                return;
            }
        }
        this->currentAnimation_ = NULL;
    }

    Animation*  VisualAppearance::getCurrentAnimation()
    {
        return this->currentAnimation_;
    }

    std::string VisualAppearance::getVisualAppearanceId()
    {
        return visualAppearanceId_;
    }

    VisualAppearance::VisualAppearance( std::string visualAppearanceId, std::string animationsDescriptionFile )
    {
        this->visualAppearanceId_ = visualAppearanceId;

        FileData* dataFromFile = b2WorldAndVisualWorld.globalGameObjectManager_->parseFileData( &animationsDescriptionFile, 5 );

        FileData::iterator itData;
        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string animationId = (*itEntry);
            itEntry++;
            std::string animationFileName = (*itEntry);
            itEntry++;
            sf::Vector2i rowsAndCollumns;
            rowsAndCollumns.x = atoi((*itEntry).c_str());
            itEntry++;
            rowsAndCollumns.y = atoi((*itEntry).c_str());
            itEntry++;
            int delayPerFrame = atoi((*itEntry).c_str());

            Animation* temporaryAnimation = new Animation( animationId, animationFileName, rowsAndCollumns, delayPerFrame );

            if( temporaryAnimation != NULL )
            {
                this->possibleAnimations_.push_back( temporaryAnimation );
            }
        }

        if(possibleAnimations_.empty())
        {
            exit(1);
        }
    }

    VisualAppearance::VisualAppearance()
    {
        exit(1);
    }

    VisualAppearance::~VisualAppearance()
    {
        this->possibleAnimations_.clear();
        delete this->currentAnimation_;
    }
}
