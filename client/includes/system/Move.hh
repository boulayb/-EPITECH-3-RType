//
// Created by salnik_a on 25/12/16.
//

#ifndef RTYPE_MOVE_HH
#define RTYPE_MOVE_HH

#include "../../../ecs/Engine.hpp"
#include "../component/Position.hh"
#include "../component/Size.hh"
#include "../component/Speed.hh"
#include "../component/Loop.hh"

class Move : public System
{
public:
    Move():
            System("Move")
    {

    }

    bool doAction(Entity& entity);
};


#endif //RTYPE_MOVE_HH
