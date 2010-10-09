#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <vector>

namespace objects
{
    class Material
    {
        public:
            std::string getMaterialId();
            std::string getVisualAppearanceId();
            float getAngleOffsetForAnimation();
            b2FixtureDef getFixtureDefinition();
            b2BodyDef getBodyDefinition();
            bool thisIsACircle();
            b2CircleShape* getCircleShape();
            b2PolygonShape* getPolygonShape();
            Material( std::string materialId, std::string visualAppearanceId, b2BodyDef bodyDefinition, b2FixtureDef fixtureDefinition, float  angleOffsetForAnimation, b2CircleShape circleShape );
            Material( std::string materialId, std::string visualAppearanceId, b2BodyDef bodyDefinition, b2FixtureDef fixtureDefinition, float  angleOffsetForAnimation, b2PolygonShape polygonShape );
            Material();
            ~Material();
        protected:

        private:
            std::string     materialId_;
            std::string     visualAppearanceId_;

            float           angleOffsetForAnimation_;
            b2FixtureDef    fixtureDefinition_;
            b2BodyDef       bodyDefinition_;

            bool thisIsACircle_;
            b2CircleShape circleShape_;
            b2PolygonShape polygonShape_;
    };
}
#endif
