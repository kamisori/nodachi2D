#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <objects/spacialObject.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/gameObjectManager.hpp>
namespace objects{

    void GameObjectManager::createSpacialObject( std::string spacialObjectId, std::string visualAppearanceId, b2BodyDef* bodyDefinition, b2FixtureDef* fixtureDefinition )
    {
        SpacialObject* temporaryObject = new SpacialObject( spacialObjectId, visualAppearanceId, bodyDefinition, fixtureDefinition );
        this->spacialObjects_.push_back( temporaryObject );
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
        //throw exception
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

//    AudioAppearance* GameObjectManager::provideAudioAppearance( std::string* audioAppearanceId )
 //std::string spacialObjectId, std::string visualAppearanceId, b2BodyDef* bodyDefinition, b2FixtureDef* fixtureDefinition
    //std::string* spacialObjectId, float posX, float posY, PositionInZ posZ, float orientation, bool collides, float collisionR, std::string* visualAppearanceId
    void GameObjectManager::loadObjects( std::string spacialObjectsFile )
    {
        FileData* dataFromFile = fetchFileData( &spacialObjectsFile, 38 );
        FileData::iterator itData;
        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string objectId = (*itEntry);
            itEntry++;
            std::string visualAppearanceId = (*itEntry);
            itEntry++;
            b2BodyDef bodyDefinition;
            if( (*itEntry).compare( "static" ) == 0 ){
                bodyDefinition.type = b2_staticBody;
            }
            else if ( (*itEntry).compare( "dynamic" ) == 0 ){
                bodyDefinition.type = b2_dynamicBody;
            }
            else if ( (*itEntry).compare( "kinematic" ) == 0 ){
                bodyDefinition.type = b2_kinematicBody;
            }
            else{
                exit(1);
            }
            itEntry++;
            bodyDefinition.position.x = atof((*itEntry).c_str());;
            itEntry++;
            bodyDefinition.position.y = atof((*itEntry).c_str());;
            itEntry++;
            bodyDefinition.angle = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinition.linearVelocity.x = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinition.linearVelocity.y = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinition.angularVelocity = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinition.linearDamping =  atof((*itEntry).c_str());
            itEntry++;
            bodyDefinition.angularDamping = atof((*itEntry).c_str());
            itEntry++;

            if( (*itEntry).compare( "allowSleep" ) == 0 ){
                bodyDefinition.allowSleep = true;
            }
            else if( (*itEntry).compare( "denySleep" ) == 0 ){
                bodyDefinition.allowSleep = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "awake" ) == 0 ){
                bodyDefinition.awake = true;
            }
            else if( (*itEntry).compare( "asleep" ) == 0 ){
                bodyDefinition.awake = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "denyRotation" ) == 0 ){
                bodyDefinition.fixedRotation = true;
            }
            else if( (*itEntry).compare( "allowRotation" ) == 0 ){
                bodyDefinition.fixedRotation = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "isBullet" ) == 0 ){
                bodyDefinition.bullet = true;
            }
            else if( (*itEntry).compare( "isNoBullet" ) == 0 ){
                bodyDefinition.bullet = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "active" ) == 0 ){
                bodyDefinition.active = true;
            }
            else if( (*itEntry).compare( "inactive" ) == 0 ){
                bodyDefinition.active = false;
            }
            else{
                exit(1);
            }
            itEntry++;
            b2FixtureDef fixtureDefinition;
            fixtureDefinition.friction = atof((*itEntry).c_str());
            itEntry++;
            fixtureDefinition.restitution = atof((*itEntry).c_str());
            itEntry++;
            fixtureDefinition.density = atof((*itEntry).c_str());
            itEntry++;
            if( (*itEntry).compare( "isSensor") == 0 ){
                fixtureDefinition.isSensor = true;
            }
            else if( (*itEntry).compare( "isNoSensor" ) == 0 ){
                fixtureDefinition.isSensor = false;
            }
            itEntry++;

            b2CircleShape tmpCircle;
            b2PolygonShape tmpBox;
            float  angleOffsetForAnimation = 0;
            if( (*itEntry).compare( "circle" ) == 0 ){
                itEntry++;
                tmpCircle.m_p.x = atof((*itEntry).c_str());
                itEntry++;
                tmpCircle.m_p.y = atof((*itEntry).c_str());
                itEntry++;
                tmpCircle.m_radius = atof((*itEntry).c_str());

                fixtureDefinition.shape = &tmpCircle;
            }
            else if( (*itEntry).compare( "edge" ) == 0 ){
                itEntry++;
                b2Vec2 v1,v2;
                v1.x = atof((*itEntry).c_str());
                itEntry++;
                v1.y = atof((*itEntry).c_str());
                itEntry++;
                v2.x = atof((*itEntry).c_str());
                itEntry++;
                v2.y = atof((*itEntry).c_str());

                tmpBox.SetAsEdge( v1, v2 );

                fixtureDefinition.shape = &tmpBox;
            }
            else if( (*itEntry).compare( "axisAlignedBox" ) == 0 ){
                itEntry++;

                b2Vec2 v1;
                v1.x = atof((*itEntry).c_str());
                itEntry++;
                v1.y = atof((*itEntry).c_str());

                tmpBox.SetAsBox( v1.x, v1.y );

                fixtureDefinition.shape = &tmpBox;
            }
            else if( (*itEntry).compare( "orientedBox" ) == 0 ){
                itEntry++;
                b2Vec2 v1,v2;
                v1.x = atof((*itEntry).c_str());
                itEntry++;
                v1.y = atof((*itEntry).c_str());
                itEntry++;
                v2.x = atof((*itEntry).c_str());
                itEntry++;
                v2.y = atof((*itEntry).c_str());
                itEntry++;
                float  angle = atof((*itEntry).c_str());
                angleOffsetForAnimation = angle;
                tmpBox.SetAsBox( v1.x, v1.y, v2, angle);

                fixtureDefinition.shape = &tmpBox;
            }
            else if( (*itEntry).compare( "polygon" ) == 0 ){
                itEntry++;
                int countVertices = atoi((*itEntry).c_str());

                b2Vec2 vertices[ b2_maxPolygonVertices ];

                for( int i = 0; i < countVertices; i++ ){
                    b2Vec2 v1;
                    itEntry++;
                    v1.x = atof((*itEntry).c_str());
                    itEntry++;
                    v1.y = atof((*itEntry).c_str());

                    vertices[i].Set( v1.x, v1.y );
                }
                tmpBox.Set( vertices, countVertices );

                fixtureDefinition.shape = &tmpBox;
            }
            else{
                exit(1);
            }

            SpacialObject* temporaryObject = new SpacialObject( objectId, visualAppearanceId, &bodyDefinition, &fixtureDefinition );
            if( temporaryObject != NULL )
            {
                temporaryObject->setAngleOffsetForAnimation( angleOffsetForAnimation );
                this->spacialObjects_.push_back( temporaryObject );
            }
        }
    }

    FileData* GameObjectManager::fetchFileData( std::string* fileName, int fields )
    {
        std::ifstream ifs( fileName->c_str(), std::ifstream::in );
        if( ifs.is_open() ){
            char* buffer;
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

            std::string tmp;
            tmp.clear();
            tmp.assign(buffer);

            delete[] buffer;

            unsigned int lastPos = 0;
            unsigned int lastCarriageRet = 0;
            FileData* tmpData = new FileData();
            std::string entryDivider ("!");
            std::string dataDivider (";");
            unsigned int foo = entryDivider.length();
            unsigned int goo = dataDivider.length();
            while( tmp.find( dataDivider, lastPos ) != std::string::npos && tmp.find( entryDivider, lastCarriageRet ) != std::string::npos )
            {
                unsigned int nextCarriageRet = tmp.find( entryDivider, lastCarriageRet );
                FileEntry tmpEntry;
                while( tmp.find( dataDivider, lastPos ) != std::string::npos && tmp.find( dataDivider, lastPos ) < nextCarriageRet)
                {
                    unsigned int nextPos = tmp.find( dataDivider, lastPos );
                    std::string tmpstr = tmp.substr( lastPos, (nextPos - lastPos) );
                    tmpEntry.push_back( tmpstr );

                    lastPos = nextPos+goo;
                }
                lastCarriageRet = nextCarriageRet+foo+2;
                lastPos = lastCarriageRet;
                tmpData->push_back( tmpEntry );
                tmpEntry.clear();
            }
            return tmpData;
        }
        exit(1);
    }

    // std::string* visualAppearanceId; std::string* animationsDescriptionFile
    void GameObjectManager::loadVisualAppearances( std::string visualAppearanceFile )
    {
        FileData* dataFromFile = fetchFileData( &visualAppearanceFile, 2 );
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

//    void GameObjectManager::loadAudioAppearances( std::string* audioAppearanceFile )

    GameObjectManager::GameObjectManager()
    {
    }

    GameObjectManager::~GameObjectManager()
    {
        this->spacialObjects_.clear();
        this->visualAppearancesLibrary_.clear();
    }
}
