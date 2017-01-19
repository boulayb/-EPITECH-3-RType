//
// Created by salnik_a on 25/12/16.
//

#include "../../includes/component/Loop.hh"

Loop::Loop(const std::string &id) : Component(id)
{
    _isLoop = true;
}

void    Loop::setLoop(bool loop)
{
    _isLoop = loop;
}

bool    Loop::getLoop()
{
    return _isLoop;
}