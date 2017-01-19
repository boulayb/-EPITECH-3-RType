//
// Created by salnik_a on 25/12/16.
//

#ifndef RTYPE_LOOP_HH
#define RTYPE_LOOP_HH

#include "../../../ecs/Component.hpp"

class Loop : public Component
{
public:
    Loop(const std::string &id);

    void    setLoop(bool);
    bool    getLoop();

private:
    bool _isLoop;
};

#endif //RTYPE_LOOP_HH
