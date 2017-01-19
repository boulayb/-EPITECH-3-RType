//
// Created by dimitri on 12/25/16.
//

#include <iostream>
#include <system/Network.hh>
#include <component/Position.hh>
#include <Game.hh>
#include "system/TaskManager.hh"
#include "Message.hpp"
#include "Packet.hh"

TaskManager::TaskManager() : System("TaskManager")
{

}

TaskManager::~TaskManager()
{

}

bool TaskManager::doAction(Entity& entity)
{
  auto &packet = entity.getComponents().getObject<PacketComponent &>("PacketComponent");
  if (packet.getPacket()->magicNbr == MAGIC_NUMBER)
  {
    auto it = _tasks.find(packet.getPacket()->request);
    if (it != _tasks.end())
    {
      (this->*(it->second))(packet);
    }
  }
  else {
    std::cerr << "Corrupted packet received" << std::endl;
  }
  engine::Instance().deleteEntity(entity);
  return true;
}

void TaskManager::handShakeTask(PacketComponent const &packet) const // Complete
{
  Message msg;
  Protocol::rtypePacket *newPacket = Protocol::Protocol::createPacket(Protocol::Code::HANDSHAKE_SUCCESS, nullptr,
                                                                      Protocol::DataType::NONE, 0);
  (void)packet;
  msg.setMessage(reinterpret_cast<unsigned char *>(newPacket), sizeof(Protocol::rtypePacket));
  Network &network = reinterpret_cast<Network &>(engine::Instance().getObject("Network"));

  network.sendTCP(msg);
  this->connection(reinterpret_cast<Network&>(engine::Instance().getObject
          ("Network")).getUserName());
  delete newPacket;
}

void TaskManager::connectionSuccess(PacketComponent const &packet) const
{
  (void)packet;
  Game::waitPlay();
//  this->startGame(packet);
//  this->connection(reinterpret_cast<Network&>(engine::Instance().getObject("Network")).getUserName());
}

void TaskManager::connection(std::string const &name) const // Complete
{
  Message msg;
  unsigned char  *info = new unsigned char[name.size()];

  if (name.size() < 50)
    std::strcpy(reinterpret_cast<char *>(info), name.c_str());
  Protocol::rtypePacket *newPacket = Protocol::Protocol::createPacket(Protocol::Code::CONNECTION, reinterpret_cast<unsigned char *>(&info),
                                                                      Protocol::DataType::CHARACTER,
                                                                      static_cast<int>(name.size()));
  msg.setMessage(reinterpret_cast<unsigned char *>(newPacket), sizeof(Protocol::rtypePacket));
  Network &network = reinterpret_cast<Network &>(engine::Instance().getObject("Network"));

  network.sendTCP(msg);
  delete newPacket;
}

void TaskManager::startGame(PacketComponent const &packet)  const // Complete
{
  (void) packet;
  Game::startGame();
}

void TaskManager::spawnPlayer(PacketComponent const &packet) const
{
  SystemFactory &factory = Singleton<SystemFactory>::Instance();
  const std::string name (reinterpret_cast<const char *>(packet.getPacket()->data));
  std::cout << "spawning " << name << std::endl;
  factory.createOtherPlayer(1, 50, 50, name);
}

void TaskManager::spawnEntity(PacketComponent const &packet) const // Complete
{
  const Protocol::EntityLoad *load = reinterpret_cast<const Protocol::EntityLoad *>(packet.getPacket()->data);
  SystemFactory &factory = Singleton<SystemFactory>::Instance();

  factory.createMonster(load->entityName, load->posY);
}

void TaskManager::requestStartGame() const // Complete
{
  Message msg;

  Protocol::rtypePacket *newPacket = Protocol::Protocol::createPacket(Protocol::Code::START_GAME, nullptr,
                                                                      Protocol::DataType::NONE,
                                                                      0);
  msg.setMessage(reinterpret_cast<unsigned char *>(newPacket), sizeof(Protocol::rtypePacket));
  Network &network = reinterpret_cast<Network &>(engine::Instance().getObject("Network"));

  network.sendTCP(msg);
  delete newPacket;
}

void TaskManager::updateEntityByServer(PacketComponent const &packet)  const // Complete
{
  const Protocol::EntityInformation *information = reinterpret_cast<const Protocol::EntityInformation *>(packet.getPacket()->data);

  std::string id = reinterpret_cast<const char *>(information->entityType);
  try
  {
    std::cout << "moving " << id << std::endl;
    Entity &ent = engine::Instance().getUsedEntity(id);
    PositionComponent &pos = ent.getComponents().getObject<PositionComponent>("Position");
    pos.setX(information->posX);
    pos.setY(information->posY);
  }
  catch (std::exception &e)
  {
    //std::cerr << "not found" << std::endl;
  }
}

void TaskManager::updateEntityToServer(Entity &entity, Protocol::PlayerAction action) // Complete
{
  Message msg;
  Protocol::EntityInformation info;
  PositionComponent &pos = entity.getComponents().getObject<PositionComponent>("Position");
  std::strcpy(reinterpret_cast<char *>(info.entityType), entity.getId().c_str());
  info.posX = pos.getX();
  info.posY = pos.getY();
  info.action = action;
  Protocol::rtypePacket *newPacket = Protocol::Protocol::createPacket(Protocol::Code::PLAYER_POSITION, reinterpret_cast<unsigned char *>(&info),
                                                                      Protocol::DataType::ENTITY_INFORMATION, sizeof(Protocol::EntityInformation));
  msg.setMessage(reinterpret_cast<unsigned char *>(newPacket), sizeof(Protocol::rtypePacket));
  Network &network = reinterpret_cast<Network &>(engine::Instance().getObject("Network"));

  network.sendTCP(msg);
  delete newPacket;
}
