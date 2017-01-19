#ifndef TESTSFML_POSITIONCOMPONENT_HH
#define TESTSFML_POSITIONCOMPONENT_HH


#include "../../ecs/Component.hpp"
#include <iostream>

class PositionComponent : public Component
{
public:
    PositionComponent(const std::string &id, float x = 0, float y = 0);

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    bool getDirection() const;
    void setDirection(bool direction);

private:
    float _x;
    float _y;
    bool _direction;

};


#endif //TESTSFML_POSITIONCOMPONENT_HH
