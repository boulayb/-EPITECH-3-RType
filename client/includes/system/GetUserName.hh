//
// Created by salnik_a on 26/12/16.
//

#ifndef RTYPE_GETUSERNAME_HH
#define RTYPE_GETUSERNAME_HH

#include "Engine.hpp"
#include "../Game.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GetUserName : public System
{
public:
  GetUserName() :
          System("GetUserName")
  {

  }

  bool doAction(Entity &entity);
};

#endif //RTYPE_GETUSERNAME_HH
