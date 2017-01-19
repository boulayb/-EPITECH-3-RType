#include "../../includes/component/Size.hh"


Size::Size(const std::string &id, unsigned int x, unsigned int y): Component(id)
{
    _x = x;
    _y = y;
}

unsigned int Size::getX() const
{
    return _x;
}

void Size::setX(unsigned int x)
{
    _x = x;
}

unsigned int Size::getY() const
{
    return _y;
}

void Size::setY(unsigned int y)
{
    _y = y;
}
