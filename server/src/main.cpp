#include "Protocol.hpp"
#include "systems/TasksSystem.hpp"
#include "ServerSystemFactory.hh"
#include <DLLoader.hpp>
#include <EntityAPI.hpp>

int main(void)
{

  ServerSystemFactory factory;

  try
  {
    factory.createNetwork(4005);
    factory.createTaskSystem();
    factory.createStageManager("pepe.stage");
//    EntityAPI *api = pepe.loadDL("libdomotro.so", "entryPoint");
  //  Entity &e = api->createEntity(engine::Instance());
    //engine::Instance().addToSystem(e, "StageManager");

  }
  catch (std::exception &e)
  {
    return (EXIT_FAILURE);
  }
  return (engine::Instance().run());
}
