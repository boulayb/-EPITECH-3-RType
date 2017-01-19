//
// Created by salnik_a on 28/12/16.
//

#ifndef RTYPE_WAITGAME_HH
#define RTYPE_WAITGAME_HH

#include "../../../ecs/Engine.hpp"
#include <component/Window.hh>
#include <component/Event.hh>
#include <Game.hh>

class WaitGame : public System
{
public:
  WaitGame() :
          System("WaitGame"), _alreadyPressed(false)
  {
  }

  bool doAction(Entity& entity);

private:
  bool _alreadyPressed;
};

#endif //RTYPE_WAITGAME_HH
