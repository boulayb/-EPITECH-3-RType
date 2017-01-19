//
// Created by coodie_d on 12/31/16.
//

#ifndef RTYPE_GAMELAUNCHEDCOMPONENT_HPP
#define RTYPE_GAMELAUNCHEDCOMPONENT_HPP

#include "Component.hpp"

class GameLaunchedComponent: public Component
{
private:
  bool        _gameLaunched;
public:
  GameLaunchedComponent(std::string const &id)
  : Component(id), _gameLaunched(false)
  {

  }

  ~GameLaunchedComponent()
  {

  }

  void          setGameLaunched(bool val)
  {
    _gameLaunched = val;
  }

  bool          isGameLaunched() const
  {
    return (_gameLaunched);
  }
};

#endif //RTYPE_GAMELAUNCHEDCOMPONENT_HPP
