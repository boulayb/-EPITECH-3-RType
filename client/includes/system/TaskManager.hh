//
// Created by dimitri on 12/25/16.
//

#ifndef RTYPE_TASKMANAGER_HH
#define RTYPE_TASKMANAGER_HH

#include "Engine.hpp"
#include "Protocol.hpp"
#include "component/PacketComponent.hh"

class TaskManager : public System
{
public:
  typedef void (TaskManager::*taskFunctions)(PacketComponent const &packet) const;
  TaskManager();
  ~TaskManager();
  bool doAction(Entity& entity);

  // receive functions
  void handShakeTask(PacketComponent const &packet) const;
  void connectionSuccess(PacketComponent const &packet) const;
  void startGame(PacketComponent const &packet) const;
  void spawnEntity(PacketComponent const &packet) const;
  void spawnPlayer(PacketComponent const &packet) const;

  void updateEntityByServer(PacketComponent const &packet) const;

  // send functions
  void connection(std::string const &name) const;
  void requestStartGame() const;
  void updateEntityToServer(Entity &, Protocol::PlayerAction);

private:
  std::map<Protocol::Code, taskFunctions> _tasks =
          {{Protocol::Code::HANDSHAKE, &TaskManager::handShakeTask},
           {Protocol::Code::CONNECTION_SUCCESS, &TaskManager::connectionSuccess},
           {Protocol::Code::GAME_STARTED, &TaskManager::startGame},
           {Protocol::Code::SPAWN_ENTITY, &TaskManager::spawnEntity},
           {Protocol::Code::SPAWN_PLAYER, &TaskManager::spawnPlayer},
           {Protocol::Code::PLAYER_POSITION, &TaskManager::updateEntityByServer}};
};

#endif //RTYPE_TASKMANAGER_HH
