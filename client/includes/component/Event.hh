//
// Created by salnik_a on 25/12/16.
//

#ifndef RTYPE_EVENT_HH
#define RTYPE_EVENT_HH

#include "../../ecs/Component.hpp"
#include <SFML/Window.hpp>

class Event : public Component
{
public:
    Event(const std::string &id);
    sf::Event& getEvent();

private:
    sf::Event _event;
};

#endif //RTYPE_EVENT_HH
