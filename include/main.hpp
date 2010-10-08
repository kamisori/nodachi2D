#ifndef MAIN_HPP
#define MAIN_HPP
#include <gameWorld.hpp>
    typedef std::vector< std::string > FileEntry;
    typedef std::vector< FileEntry > FileData;

    extern GameWorld b2WorldAndVisualWorld;
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
#endif
