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

    b2FixtureDef Material::getFixtureDefinition()
    {
        return fixtureDefinition_;
    }

    b2BodyDef Material::getBodyDefinition()
    {
        return bodyDefinition_;
    }

    float Material::getAngleOffsetForAnimation()
    {
        return angleOffsetForAnimation_;
    }

    bool Material::thisIsACircle()
    {
        return thisIsACircle_;
    }

    b2CircleShape* Material::getCircleShape()
    {
        return &circleShape_;
    }

    b2PolygonShape* Material::getPolygonShape()
    {
        return &polygonShape_;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, b2BodyDef bodyDefinition, b2FixtureDef fixtureDefinition, float  angleOffsetForAnimation, b2CircleShape circleShape )
    {
        this->thisIsACircle_ = true;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->circleShape_ = circleShape;

        this->bodyDefinition_ = bodyDefinition;
        this->fixtureDefinition_ = fixtureDefinition_;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, b2BodyDef bodyDefinition, b2FixtureDef fixtureDefinition, float angleOffsetForAnimation, b2PolygonShape polygonShape )
    {
        this->thisIsACircle_ = false;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->polygonShape_ = polygonShape;

        this->bodyDefinition_ = bodyDefinition;
        this->fixtureDefinition_ = fixtureDefinition_;
    }

    Material::Material()
    {
        exit(1);
    }

    Material::~Material()
    {
    }
}
