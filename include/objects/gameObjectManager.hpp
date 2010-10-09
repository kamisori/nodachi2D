#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <objects/spacialObject.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/material.hpp>

namespace objects
{
    typedef std::vector< std::string > FileEntry;
    typedef std::vector< FileEntry > FileData;

    class GameObjectManager
    {
    	public:

//            void createSpacialObject( std::string spacialObjectId, std::string visualAppearanceId, b2BodyDef* bodyDefinition, b2FixtureDef* fixtureDefinition );
            VisualAppearance* provideVisualAppearance( std::string visualAppearanceId );
            Material* provideMaterial( std::string materialId );
//            AudioAppearance* provideAudioAppearance( std::string* audioAppearanceId );
            SpacialObject* nextSpacialObject( int current );

            void loadObjects( std::string spacialObjectsFile );
            void loadVisualAppearances( std::string visualAppearanceFile );
            void loadMaterials( std::string materialFile );
//            void loadAudioAppearances( std::string* audioAppearanceFile );

            FileData* fetchFileData( std::string* fileName, int fields );

    		GameObjectManager();
    		~GameObjectManager();
    	protected:

    	private:
    	SpacialObject*                      player_;
    	std::vector< SpacialObject* >       spacialObjects_;
    	std::vector< VisualAppearance* >    visualAppearancesLibrary_;
    	std::vector< Material* >            materialLibrary_;
//    	std::vector< AudioAppearance* >     audioAppearancesLibrary_;
//      std::vector< Script* >              scriptLibrary_;
    };

}

#endif
