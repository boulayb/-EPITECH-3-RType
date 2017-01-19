//
// Created by salnik_a on 25/12/16.
//

#ifndef RTYPE_SPEED_HH
#define RTYPE_SPEED_HH

#include "../../../ecs/Component.hpp"

class Speed : public Component
{
public:
    Speed(const std::string &id);

    const float     &getSpeed();
    void    setSpeed(float s);

private:
    float _speed;
};

#endif //RTYPE_SPEED_HH
