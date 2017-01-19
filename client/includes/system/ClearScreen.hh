#ifndef GRAPHICMODULE_SYSTEMCLEARSCREEN_HH
#define GRAPHICMODULE_SYSTEMCLEARSCREEN_HH

#include "../component/Window.hh"
#include "../../ecs/Engine.hpp"
#include <memory>

class SystemClearScreen : public System
{
private:

public:
    SystemClearScreen() :
            System("Clear")
    {

    }

    bool doAction(Entity& entity);
};


#endif //GRAPHICMODULE_SYSTEMCLEARSCREEN_HH
