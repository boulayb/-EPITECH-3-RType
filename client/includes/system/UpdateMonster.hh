//
// Created by salnik_a on 27/12/16.
//

#ifndef RTYPE_UPDATEMONSTER_HH
#define RTYPE_UPDATEMONSTER_HH

#include "../../../ecs/Engine.hpp"

class UpdateMonster : public System
{
public:
  UpdateMonster():
          System("UpdateMonster")
  {

  }

  bool doAction(Entity &entity);

private:
  void shot(Entity &entity);
};

#endif //RTYPE_UPDATEMONSTER_HH
