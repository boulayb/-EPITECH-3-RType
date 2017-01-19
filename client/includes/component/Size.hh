#ifndef TESTSFML_SIZE_HH
#define TESTSFML_SIZE_HH


#include "../../ecs/Component.hpp"
#include <iostream>

class Size : public Component
{
public:
    Size(const std::string &id, unsigned int x = 0, unsigned int y = 0);

    unsigned int getX() const;
    void setX(unsigned int x);
    unsigned int getY() const;
    void setY(unsigned int y);

private:
    unsigned int _x;
    unsigned int _y;
};


#endif //TESTSFML_SIZE_HH
