//
// Created by danilo_d on 06/12/16.
//

#ifdef __unix__
#include <linux/TCPMonitor.hh>
#include <linux/UDPMonitor.hh>
#elif defined(_WIN32) || defined(WIN32)
#include <windows/TCPMonitor.hh>
#include <windows/UDPMonitor.hh>
#endif

#include "components/PacketComponent.hh"
#include <stdexcept>
#include <iostream>
#include "systems/NetworkSystem.hh"

NetworkSystem::NetworkSystem(unsigned int port) : System("Network")
{
  #ifdef __unix__
  try
  {
    _monitorTCP = new TCPMonitor(port);
    _monitorUDP = new UDPMonitor(port);
    _monitorUDP->setClients(_monitorTCP->getClients());
  }
  catch (std::exception &e)
  {
    throw e;
  }
  #elif defined(_WIN32) || defined(WIN32)
  try
  {
    _monitorTCP = new TCPMonitor(port);
  }
  catch (std::exception &e)
  {
    throw e;
  }
  #endif
}

NetworkSystem::~NetworkSystem()
{

}

bool NetworkSystem::isTCPReadable() const
{
  return _monitorTCP->isReadable();
}

bool NetworkSystem::isUDPReadable() const
{
  return _monitorUDP->isReadable();
}

bool NetworkSystem::doAction(Entity& entity)
{
  (void)entity;
  try
  {
    _monitorTCP->update();
    _monitorUDP->update();
    if (_monitorTCP->isReadable())
    {
      Message &msg = _monitorTCP->getNextMessage();
      this->convertToEntity(msg);
    }
    if (_monitorUDP->isReadable())
    {
      Message &msg = _monitorUDP->getNextMessage();
      this->convertToEntity(msg);
    }
  }
  catch (std::exception &e)
  {
    throw e;
  }
  return true;
}

Message &NetworkSystem::getUDPMessage()
{
  return _monitorUDP->getNextMessage();
}

Message &NetworkSystem::getTCPMessage()
{
  return _monitorTCP->getNextMessage();
}

void NetworkSystem::pushTCPMessage(Message &msg)
{
  _monitorTCP->sendMessage(msg);
}

void NetworkSystem::pushUDPMessage(Message &msg)
{
  _monitorUDP->sendMessage(msg);
}

std::string *NetworkSystem::createRandomId(int len)
{
  std::string *randomString = new std::string;
  static const char alphanum[] =
          "0123456789"
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "abcdefghijklmnopqrstuvwxyz";

  for (int i = 0; i < len; ++i) {
    randomString->push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
  }
  randomString->push_back('\0');
  return randomString;
}

void        NetworkSystem::convertToEntity(Message &msg)
{
  PacketComponent &packetComponent = engine::Instance().getComponent<PacketComponent>("PacketComponent");
  packetComponent.setPacket(msg.getMessage(), msg.getSize(), msg.getClientID());
  Entity& packetEntity = engine::Instance().getEntity(*createRandomId(5));
  packetEntity.getComponents().addObject(packetComponent);
  engine::Instance().addToSystem(packetEntity, "EventManager");
}
