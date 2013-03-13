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
