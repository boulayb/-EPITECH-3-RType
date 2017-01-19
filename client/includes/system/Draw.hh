#ifndef TESTSFML_DRAWSYSTEM_HH
#define TESTSFML_DRAWSYSTEM_HH

#include <memory>
#include "../component/Position.hh"
#include "../component/Window.hh"
#include "../component/Sprite.hh"
#include "../../ecs/Engine.hpp"

class DrawSystem : public System
{
public:
    DrawSystem() :
            System("Draw")
    {

    }

    bool doAction(Entity& entity);
};


#endif //TESTSFML_DRAWSYSTEM_HH
