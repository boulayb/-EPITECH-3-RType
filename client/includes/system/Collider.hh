//
// Created by salnik_a on 28/12/16.
//

#ifndef RTYPE_COLLIDER_HH
#define RTYPE_COLLIDER_HH

#include "../../ecs/Engine.hpp"
#include <Graphics.hh>
#include <component/Collide.hh>

class Collider : public System
{
public:
  Collider() :
          System("Collider")
  {
  }

  bool doAction(Entity& entity);
};

#endif //RTYPE_COLLIDER_HH
