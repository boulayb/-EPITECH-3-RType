//
// Created by dimitri on 12/25/16.
//

#ifndef RTYPE_SERVERSYSTEMFACTORY_HH
#define RTYPE_SERVERSYSTEMFACTORY_HH

#include "Engine.hpp"
#include "systems/NetworkSystem.hh"

class ServerSystemFactory
{
public:
  ServerSystemFactory();
  ~ServerSystemFactory();
  void createNetwork(unsigned int port);
  void createTaskSystem();
  void createStageManager(std::string const &fileName);
};

#endif //RTYPE_SYSTEMFACTORY_HH
