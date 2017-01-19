//
// Created by salnik_a on 27/12/16.
//

#ifndef RTYPE_GETIP_HH
#define RTYPE_GETIP_HH

#include "Engine.hpp"
#include "../Game.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GetIp : public System
{
public:
  GetIp() :
          System("GetIp")
  {

  }

  bool doAction(Entity &entity);

private:
  bool isFormat(const std::string &);
};

#endif //RTYPE_GETIP_HH
