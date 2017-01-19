#ifndef GRAPHICMODULE_DRAWTEXT_HH_HH
#define GRAPHICMODULE_DRAWTEXT_HH_HH

#include "../component/Window.hh"
#include "../../ecs/Engine.hpp"
#include "../component/Text.hh"
#include "../component/Position.hh"

class DrawText : public System
{
public:
    DrawText():
            System("DrawText")
    {

    }

    bool doAction(Entity& entity);
};

#endif //GRAPHICMODULE_DRAWTEXT_HH_HH
