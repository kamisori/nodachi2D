#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <objects/animation.hpp>
#include <objects/visualAppearance.hpp>
#include <main.hpp>

namespace objects
{
    std::string Material::getMaterialId()
    {
        return materialId_;
    }

    std::string Material::getVisualAppearanceId()
    {
        return visualAppearanceId_;
    }

    b2FixtureDef* Material::createFixtureDefinition()
    {
        b2FixtureDef* fixtureDefinition = new b2FixtureDef;

        fixtureDefinition->friction = fixtureDefinitionTemplate_.friction_;
        fixtureDefinition->restitution = fixtureDefinitionTemplate_.restitution_;
        fixtureDefinition->density = fixtureDefinitionTemplate_.density_;
        fixtureDefinition->isSensor = fixtureDefinitionTemplate_.isSensor_;

        return fixtureDefinition;
    }

    b2BodyDef* Material::createBodyDefinition()
    {
        b2BodyDef* bodyDefinition = new b2BodyDef;

        if( bodyDefinitionTemplate_.type_ == STATIC )
        {
            bodyDefinition->type = b2_staticBody;
        }
        else if ( bodyDefinitionTemplate_.type_ == DYNAMIC )
        {
            bodyDefinition->type = b2_dynamicBody;
        }
        else if ( bodyDefinitionTemplate_.type_ == KINEMATIC )
        {
            bodyDefinition->type = b2_kinematicBody;
        }
        bodyDefinition->position.x = bodyDefinitionTemplate_.position_.x;
        bodyDefinition->position.y = bodyDefinitionTemplate_.position_.y;
        bodyDefinition->angle = bodyDefinitionTemplate_.angle_;
        bodyDefinition->linearVelocity.x = bodyDefinitionTemplate_.linearVelocity_.x;
        bodyDefinition->linearVelocity.y = bodyDefinitionTemplate_.linearVelocity_.y;
        bodyDefinition->angularVelocity = bodyDefinitionTemplate_.angularVelocity_;
        bodyDefinition->linearDamping =  bodyDefinitionTemplate_.linearDamping_;
        bodyDefinition->angularDamping = bodyDefinitionTemplate_.angularDamping_;
        bodyDefinition->allowSleep = bodyDefinitionTemplate_.allowSleep_;
        bodyDefinition->awake = bodyDefinitionTemplate_.awake_;
        bodyDefinition->fixedRotation = bodyDefinitionTemplate_.denyRotation_;
        bodyDefinition->bullet = bodyDefinitionTemplate_.isBullet_;
        bodyDefinition->active = bodyDefinitionTemplate_.active_;

        return bodyDefinition;
    }

    float Material::getAngleOffsetForAnimation()
    {
        return angleOffsetForAnimation_;
    }

    bool Material::thisIsACircle()
    {
        if( shapeType_ == CIRCLE )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    b2CircleShape* Material::createCircleShape()
    {
        b2CircleShape* circleShape = new b2CircleShape;

        circleShape->m_p.x = circleShapeTemplate_.center.x;
        circleShape->m_p.y = circleShapeTemplate_.center.y;
        circleShape->m_radius = circleShapeTemplate_.radius;

        return circleShape;
    }

    b2PolygonShape* Material::createPolygonShape()
    {
        b2PolygonShape* polygonShape = new b2PolygonShape;

        if( shapeType_ == EDGE )
        {
                b2Vec2 v1,v2;

                v1.x = polygonShapeTemplate_.vertices[0].x;
                v1.y = polygonShapeTemplate_.vertices[0].y;
                v2.x = polygonShapeTemplate_.vertices[1].x;
                v2.y = polygonShapeTemplate_.vertices[1].y;

                polygonShape->SetAsEdge( v1, v2 );
        }
        else if( shapeType_ == ALIGNED_BOX )
        {
            b2Vec2 v1;
            v1.x = boxShapeTemplate_.halfSize.x;
            v1.y = boxShapeTemplate_.halfSize.y;
            polygonShape->SetAsBox( v1.x, v1.y );
        }
        else if( shapeType_ == ORIENTED_BOX )
        {
            b2Vec2 v1,v2;
            v1.x = boxShapeTemplate_.halfSize.x;
            v1.y = boxShapeTemplate_.halfSize.y;
            v2.x = boxShapeTemplate_.center.x;
            v2.y = boxShapeTemplate_.center.y;
            float  angle = boxShapeTemplate_.angle;
            polygonShape->SetAsBox( v1.x, v1.y, v2, angle);
        }
        else if( shapeType_ == POLYGON )
        {
            int countVertices = polygonShapeTemplate_.countOfVertices;
            b2Vec2 vertices[ b2_maxPolygonVertices ];
            for( int i = 0; i < countVertices; i++ )
            {
                b2Vec2 v1;
                v1.x = polygonShapeTemplate_.vertices[i].x;
                v1.y = polygonShapeTemplate_.vertices[i].y;
                vertices[i].Set( v1.x, v1.y );
            }
            polygonShape->Set( vertices, countVertices );
        }
        return polygonShape;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, circle shapeTemplate )
    {
        this->shapeType_ = CIRCLE;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->circleShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, polygon shapeTemplate )
    {
        this->shapeType_ = shapeType;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->polygonShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, box shapeTemplate )
    {
        this->shapeType_ = shapeType;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->boxShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material()
    {
        exit(1);
    }

    Material::~Material()
    {
    }
}
