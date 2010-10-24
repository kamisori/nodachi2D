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
            FileData* parseFileData( std::string* fileName, int fields );

            void loadMaterials( std::string materialFile );
            void loadVisualAppearances( std::string visualAppearanceFile );
            void loadObjects( std::string spacialObjectsFile );

            VisualAppearance* provideVisualAppearance( std::string visualAppearanceId );
            Material* provideMaterial( std::string materialId );

            SpacialObject* nextSpacialObject( int current );

    		GameObjectManager();
    		~GameObjectManager();
    	private:
    	FileEntry* parseFileEntry( std::string* entry, std::string* dataDivider );
    	char* fetchFileData( std::string* fileName, int fields );

    	SpacialObject*                      player_;
    	std::vector< SpacialObject* >       spacialObjects_;
    	std::vector< VisualAppearance* >    visualAppearancesLibrary_;
    	std::vector< Material* >            materialLibrary_;
    };

}

#endif
