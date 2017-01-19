#ifndef RTYPE_HANDLEEVENT_HH
#define RTYPE_HANDLEEVENT_HH

#include "../component/Window.hh"
#include "../component/Event.hh"
#include "../../ecs/Engine.hpp"

class HandleEvent : public System
{
public:
  HandleEvent():
          System("Event")
  {
  }

  bool doAction(Entity& entity);
private:
  void  Shot(Entity& entity);
};

#endif //RTYPE_HANDLEEVENT_HH
