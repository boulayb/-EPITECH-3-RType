//
// Created by salnik_a on 25/12/16.
//

#include "../../includes/component/Event.hh"

Event::Event(const std::string &id) : Component(id)
{

}

sf::Event& Event::getEvent()
{
    return _event;
}