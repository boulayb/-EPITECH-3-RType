#include <string>
#include "Age.hpp"
#include "Name.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "EntityAPI.hpp"

Entity&                 EntityAPI::createEntity(void)
{
  Engine& engine = engine::Instance();

  Age& domotroAge = engine.getComponent<Age>("Age");
  Name& domotroName = engine.getComponent<Name>("Name");

  domotroName.setName("Domotro");

  Entity& domotro = engine.getEntity("Domotro");

  domotro.getComponents().addObject({&domotroAge, &domotroName});
  return (domotro);
}

extern "C"
EntityAPI               *entryPoint()
{
  return (new EntityAPI);
}
