#include "../../includes/component/Position.hh"


PositionComponent::PositionComponent(const std::string &id, float x, float y): Component(id)
{
    _x = x;
    _y = y;
}

float PositionComponent::getX() const
{
    return _x;
}

void PositionComponent::setX(float x)
{
    _x = x;
}

float PositionComponent::getY() const
{
    return _y;
}

void PositionComponent::setY(float y)
{
    _y = y;
}

bool PositionComponent::getDirection() const
{
    return _direction;
}

void PositionComponent::setDirection(bool direction)
{
    _direction = direction;
}
