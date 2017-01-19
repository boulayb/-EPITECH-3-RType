//
// Created by salnik_a on 25/12/16.
//

#ifndef RTYPE_CHARACTERCONTROLLER_HH
#define RTYPE_CHARACTERCONTROLLER_HH

#include "../component/Speed.hh"
#include "../component/Window.hh"
#include "../../../ecs/Engine.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class CharacterController : public System
{
public:
    CharacterController():
            System("CharacterController")
    {
    }
    bool    doAction(Entity& entity);
};

#endif //RTYPE_CHARACTERCONTROLLER_HH
