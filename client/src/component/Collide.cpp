//
// Created by salnik_a on 28/12/16.
//

#include "../../includes/component/Collide.hh"


Collide::Collide(const std::string &id) : Component(id)
{
 _collide = false;
}

bool Collide::isCollided()
{
  return _collide;
}

void Collide::setCollide(bool collide)
{
  _collide = collide;
}