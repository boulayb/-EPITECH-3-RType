//
// Created by salnik_a on 25/12/16.
//


#include "../../includes/component/Speed.hh"

Speed::Speed(const std::string &id) : Component(id)
{
    _speed = 1;
}

const float&  Speed::getSpeed()
{
    return _speed;
}

void        Speed::setSpeed(float s)
{
    _speed = s;
}