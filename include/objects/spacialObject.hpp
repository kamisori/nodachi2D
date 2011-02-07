#ifndef SPACIALOBJECT_HPP
#define SPACIALOBJECT_HPP

#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <Box2D/Box2D.h>

namespace objects
{
    const uint32 sizeOfcontactIDlist = 16;
    class SpacialObject
    {
    	public:
//            setB2Body();


            float getAngleOffsetForAnimation();
            void setAngleOffsetForAnimation(float tmp);
            std::string getSpacialObjectId();
            b2Body* getB2Body();
            VisualAppearance* getVisualAppearance();
            void setBottomObject( SpacialObject* bottomObject );
            void removeBottomObject( SpacialObject* bottomObject );
            bool standsOnSomething();
            void iJumped();

            SpacialObject( std::string spacialObjectId, std::string materialId, b2Vec2 position );
                            /*string* audialAppearanceId,*/ /*float objectHealth,*/ /*float objectHardness*/
            ~SpacialObject();
    	protected:

    	private:
            std::string bottom[sizeOfcontactIDlist];

            sf::Vector2f moveObject( sf::Vector2f addThis );
            std::string       spacialObjectId_;
            b2Body* b2Body_;
            float angleOffsetForAnimation_;
//    		float               objectHealth_;              //objects can be damaged
//    		float               objectHardness_;            //some objects resist damage better than others
                                                            //combined with collision, this means, you can
                                                            //use anything and everything as a shield against attacks.
//          float               objectTemperature_;
//          float               objectMoisture_;
//          pointer to material holding having certain properties,
//          like, meltable, flamable, temperature for meltpoint/inflamationpoint whatever

            VisualAppearance*   visualAppearance_;          //null means, this is either a zone for a script,
                                                            //or something is attached to the ground, like a
                                                            //pole for a line or something

            //AudioAppearance*    audialAppearance_;        //basically the same as visualAppearance.
                                                            //holds the samples this objects can play.
//probably not neccessary:
            //Attachment*         attachedTo_;              //Attach one Object to another
                                                            //in example: Flashlight to Shovel
                                                            //attachmentStrength determines if object can be removed
                                                            //objectHealth must be higher than attachment strength, else object breaks during removal
                                                            //orientation relative to attached object
                                                            //attached at top, bottom, hind, front, one side or the other
//probably neccessary
            //Script*             objectScript_;            //also for AI
    };
}

#endif
