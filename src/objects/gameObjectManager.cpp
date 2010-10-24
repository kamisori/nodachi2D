#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <objects/spacialObject.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/gameObjectManager.hpp>
namespace objects{

    char* GameObjectManager::fetchFileData( std::string* fileName, int fields )
    {
        std::ifstream ifs( fileName->c_str(), std::ifstream::in );
        char* buffer;
        if( ifs.is_open() ){
            int length;

            ifs.seekg( 0,std::ios::end );
            length = ifs.tellg();
            ifs.seekg( 0,std::ios::beg );

            buffer = new char[ length ];
            for(int i = 0; i < length; i++){
                buffer[i]=0;
            }

            ifs.read( buffer, length );
            ifs.close();
            return buffer;
        }
        exit(1);
    }

    FileEntry* GameObjectManager::parseFileEntry( std::string* entry, std::string* dataDivider )
    {
        unsigned int lastData = 0;
        unsigned int nextData = entry->find( (*dataDivider), lastData );
        unsigned int dataLength = nextData - lastData;
        FileEntry* tmpEntry = new FileEntry();

        while( ( nextData != std::string::npos) && ( nextData < entry->length()) )
        {
            std::string tmpstr = entry->substr( lastData, dataLength );
            tmpEntry->push_back( tmpstr );

            lastData = nextData + dataDivider->length();
            nextData = entry->find( (*dataDivider), lastData );
            dataLength = nextData - lastData;
        }

        return tmpEntry;
    }

    FileData* GameObjectManager::parseFileData( std::string* fileName, int fields )
    {
        std::string fileContent;
        fileContent.clear();
        fileContent.assign( fetchFileData( fileName, fields ) );

        std::string entryDivider ("\r\n");
        std::string dataDivider (";");

        unsigned int lastEntry = 0;
        unsigned int nextEntry = fileContent.find( entryDivider, lastEntry );
        unsigned int entryLength = nextEntry - lastEntry;
        FileData* tmpData = new FileData();

        while( (nextEntry != std::string::npos) && ( nextEntry < fileContent.length() ) )
        {
            std::string temporaryEntryString = fileContent.substr( lastEntry, entryLength );
            FileEntry* tmpEntry = parseFileEntry( &temporaryEntryString, &dataDivider );
            tmpData->push_back( (*tmpEntry) );

            lastEntry = nextEntry+entryDivider.length();
            nextEntry = fileContent.find( entryDivider, lastEntry );
            entryLength = nextEntry - lastEntry;
        }
        return tmpData;
    }


    void GameObjectManager::loadMaterials( std::string materialFile )
    {
        FileData* dataFromFile = parseFileData( &materialFile, 24 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string materialId = (*itEntry);
            itEntry++;
            std::string visualAppearanceId = (*itEntry);
            itEntry++;

            bodyDefinition bodyDefinitionTemplate;

            bodyDefinitionTemplate.position_.x = 0.0;
            bodyDefinitionTemplate.position_.y = 0.0;

            if( (*itEntry).compare( "static" ) == 0 ){
                bodyDefinitionTemplate.type_ = STATIC;
            }
            else if ( (*itEntry).compare( "dynamic" ) == 0 ){
                bodyDefinitionTemplate.type_ = DYNAMIC;
            }
            else if ( (*itEntry).compare( "kinematic" ) == 0 ){
                bodyDefinitionTemplate.type_ = KINEMATIC;
            }
            else{
                exit(1);
            }
            itEntry++;
            bodyDefinitionTemplate.angle_ = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.linearVelocity_.x = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.linearVelocity_.y = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.angularVelocity_ = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.linearDamping_ =  atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.angularDamping_ = atof((*itEntry).c_str());
            itEntry++;

            if( (*itEntry).compare( "allowSleep" ) == 0 ){
                bodyDefinitionTemplate.allowSleep_ = true;
            }
            else if( (*itEntry).compare( "denySleep" ) == 0 ){
                bodyDefinitionTemplate.allowSleep_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "awake" ) == 0 ){
                bodyDefinitionTemplate.awake_ = true;
            }
            else if( (*itEntry).compare( "asleep" ) == 0 ){
                bodyDefinitionTemplate.awake_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "denyRotation" ) == 0 ){
                bodyDefinitionTemplate.denyRotation_ = true;
            }
            else if( (*itEntry).compare( "allowRotation" ) == 0 ){
                bodyDefinitionTemplate.denyRotation_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "isBullet" ) == 0 ){
                bodyDefinitionTemplate.isBullet_ = true;
            }
            else if( (*itEntry).compare( "isNoBullet" ) == 0 ){
                bodyDefinitionTemplate.isBullet_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "active" ) == 0 ){
                bodyDefinitionTemplate.active_ = true;
            }
            else if( (*itEntry).compare( "inactive" ) == 0 ){
                bodyDefinitionTemplate.active_ = false;
            }
            else{
                exit(1);
            }

            itEntry++;
            fixtureDefinition fixtureDefinitionTemplate;
            fixtureDefinitionTemplate.friction_ = atof((*itEntry).c_str());
            itEntry++;
            fixtureDefinitionTemplate.restitution_ = atof((*itEntry).c_str());
            itEntry++;
            fixtureDefinitionTemplate.density_ = atof((*itEntry).c_str());
            itEntry++;
            if( (*itEntry).compare( "isSensor") == 0 ){
                fixtureDefinitionTemplate.isSensor_ = true;
            }
            else if( (*itEntry).compare( "isNoSensor" ) == 0 ){
                fixtureDefinitionTemplate.isSensor_ = false;
            }
            itEntry++;

            circle tmpCircle;
            polygon tmpPolygon;
            box tmpBox;
            float  angleOffsetForAnimation = 0;
            if( (*itEntry).compare( "circle" ) == 0 ){
                itEntry++;
                tmpCircle.center.x = atof((*itEntry).c_str());
                itEntry++;
                tmpCircle.center.y = atof((*itEntry).c_str());
                itEntry++;
                tmpCircle.radius = atof((*itEntry).c_str());

                Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, tmpCircle );
                this->materialLibrary_.push_back( temporaryMaterial );
            }
            else
            {
                Shape shapeType;
                if( (*itEntry).compare( "edge" ) == 0 ){
                    shapeType = EDGE;
                    itEntry++;
                    tmpPolygon.countOfVertices = 2;
                    tmpPolygon.vertices[0].x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpPolygon.vertices[0].y = atof((*itEntry).c_str());
                    itEntry++;
                    tmpPolygon.vertices[1].x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpPolygon.vertices[1].y = atof((*itEntry).c_str());

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpPolygon );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else if( (*itEntry).compare( "axisAlignedBox" ) == 0 ){
                    shapeType = ALIGNED_BOX;
                    itEntry++;

                    tmpBox.halfSize.x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.halfSize.y = atof((*itEntry).c_str());

                    tmpBox.center.x = 0;
                    tmpBox.center.x = 0;
                    tmpBox.angle = 0;

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpBox );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else if( (*itEntry).compare( "orientedBox" ) == 0 ){
                    shapeType = ORIENTED_BOX;

                    itEntry++;
                    tmpBox.halfSize.x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.halfSize.y = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.center.x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.center.y = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.angle = atof((*itEntry).c_str());
                    angleOffsetForAnimation = tmpBox.angle;

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpBox );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else if( (*itEntry).compare( "polygon" ) == 0 ){
                    shapeType = POLYGON;
                    itEntry++;
                    tmpPolygon.countOfVertices = atoi((*itEntry).c_str());

                    for( unsigned int i = 0; i < tmpPolygon.countOfVertices; i++ )
                    {
                        itEntry++;
                        tmpPolygon.vertices[i].x = atof((*itEntry).c_str());
                        itEntry++;
                        tmpPolygon.vertices[i].y = atof((*itEntry).c_str());
                    }

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpPolygon );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else
                {
                    exit(1);
                }

            }

        }
    }

    void GameObjectManager::loadVisualAppearances( std::string visualAppearanceFile )
    {
        FileData* dataFromFile = parseFileData( &visualAppearanceFile, 2 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string visualId = (*itEntry);
            itEntry++;
            std::string animationFile = (*itEntry);

            VisualAppearance* temporaryVisualAppearance = new VisualAppearance( visualId, animationFile );
            this->visualAppearancesLibrary_.push_back( temporaryVisualAppearance );
        }
    }

    void GameObjectManager::loadObjects( std::string spacialObjectsFile )
    {
        FileData* dataFromFile = parseFileData( &spacialObjectsFile, 4 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string objectId = (*itEntry);
            itEntry++;
            std::string materialId = (*itEntry);
            itEntry++;
            b2Vec2 position;
            position.x = atof((*itEntry).c_str());
            itEntry++;
            position.y = atof((*itEntry).c_str());

            SpacialObject* temporaryObject = new SpacialObject( objectId, materialId, position );
            if( temporaryObject != NULL )
            {
                this->spacialObjects_.push_back( temporaryObject );
            }
        }
    }

    VisualAppearance* GameObjectManager::provideVisualAppearance( std::string visualAppearanceId )
    {
        std::vector< VisualAppearance* >::iterator it;
        for( it = this->visualAppearancesLibrary_.begin(); it < this->visualAppearancesLibrary_.end(); it++ )
        {
            std::string foostr = (*it)->getVisualAppearanceId();
            if( visualAppearanceId.compare( (*it)->getVisualAppearanceId() ) == 0 )
            {
                return (*it);
            }
        }
        exit(1);
    }

    Material* GameObjectManager::provideMaterial( std::string materialId )
    {
        std::vector< Material* >::iterator it;
        for( it = this->materialLibrary_.begin(); it < this->materialLibrary_.end(); it++ )
        {
            if( materialId.compare( (*it)->getMaterialId() ) == 0 )
            {
                return (*it);
            }
        }
        exit(1);
    }

    SpacialObject* GameObjectManager::nextSpacialObject( int current )
    {
         std::vector< SpacialObject* >::iterator it;
         it = this->spacialObjects_.begin();
         it += current;
         if( it < this->spacialObjects_.end() )
         {
            return (*it);
         }
         return NULL;
    }

    GameObjectManager::GameObjectManager()
    {
    }

    GameObjectManager::~GameObjectManager()
    {
        this->spacialObjects_.clear();
        this->visualAppearancesLibrary_.clear();
        this->materialLibrary_.clear();
    }
}
