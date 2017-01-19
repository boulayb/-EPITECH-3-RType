//
// Created by dimitri on 12/25/16.
//

#include <systems/StageManager.hh>
#include <systems/TasksSystem.hpp>
#include "ServerSystemFactory.hh"

ServerSystemFactory::ServerSystemFactory()
{
}

ServerSystemFactory::~ServerSystemFactory()
{

}

void ServerSystemFactory::createNetwork(unsigned int port)
{
  engine::Instance().addObject(new NetworkSystem(port));

  Entity& socket = engine::Instance().getEntity("Socket");
  engine::Instance().addToSystem(socket, "Network");
}

void ServerSystemFactory::createTaskSystem()
{
  try
  {
    engine::Instance().addObject({new TasksSystem()});
  }
  catch (std::exception &e)
  {
    throw e;
  }
}

void ServerSystemFactory::createStageManager(std::string const &fileName)
{
  try
  {
    StageManager *manager = new StageManager(fileName);
    manager->readStage();
    manager->getEntitiesToLoad();
    engine::Instance().addObject({manager});
    Entity& stage = engine::Instance().getEntity("Stage");
    engine::Instance().addToSystem(stage, "StageManager");
  }
  catch (std::exception &e)
  {
    std::cerr << "error: can't load stage " << fileName << std::endl;
    throw e;
  }
}
