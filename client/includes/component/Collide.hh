//
// Created by salnik_a on 28/12/16.
//

#ifndef RTYPE_COLLIDE_HH
#define RTYPE_COLLIDE_HH

#include "../../../ecs/Component.hpp"

class Collide : public Component
{
public:
  Collide(const std::string &id);
  bool  isCollided();
  void  setCollide(bool);

private:
  bool _collide;
};

#endif //RTYPE_COLLIDE_HH
