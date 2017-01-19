//
// Created by bocque_c on 05/12/16.
//

#include <iostream>
#include <cstdio>
#include "system/Network.hh"
#include "Packet.hh"
#include "component/PacketComponent.hh"

Network::Network(std::string const &ip, unsigned short port, std::string const &name) : System("Network"), _ip(ip), _port(port), _name(name)
{
  if (this->connectTCP() == -1)
    throw std::exception();
  if (this->connectUDP() == -1)
    throw std::exception();
}

bool            Network::updateQueueTCP()
{
  unsigned char *data = new unsigned char [sizeof(Protocol::rtypePacket)];
  std::size_t   received = 0;

  if (_tcpSocket.receive(data, sizeof(Protocol::rtypePacket), received) == sf::Socket::Done)
  {
    Message *msg = new Message();
    msg->setMessage(data, received, 0);
    _tcpQueue.push(msg);
    return true;
  }
  delete data;
  return false;
}

bool              Network::updateQueueUDP()
{
  unsigned char *data = new unsigned char [sizeof(Protocol::rtypePacket)];
  std::size_t     received;
  sf::IpAddress   sender;
  unsigned short  senderPort;
  if ((_udpSocket.receive(data, sizeof(Protocol::rtypePacket), received, sender, senderPort)) == sf::Socket::Done)
  {
    Message *msg = new Message();
    msg->setMessage(data, sizeof(Protocol::rtypePacket), 0);
    _udpQueue.push(msg);
    return true;
  }
  delete data;
  return true;
}

Message   *Network::getNextPacketTCP()
{
  Message *ret = nullptr;

  if (_tcpQueue.empty())
    return nullptr;
  ret = _tcpQueue.front();
  _tcpQueue.pop();
  return (ret);
}

Message   *Network::getNextPacketUDP()
{
  Message *ret;

  if (_udpQueue.empty())
    return nullptr;
  ret = _udpQueue.front();
  _udpQueue.pop();
  return (ret);
}

std::string Network::getUserName() const
{
  return _name;
}

int Network::connectUDP()
{
  _udpSocket.setBlocking(false);
  if (_udpSocket.bind(_port + 1) != sf::Socket::Done)
  {
    perror("bind");
    return 1;
  }
  return (0);
}

int Network::connectTCP()
{
  sf::Socket::Status status = _tcpSocket.connect(_ip , _port);

  if (status != sf::Socket::Done)
  {
    std::cerr << "Connexion Failed" << std::endl;
    return (-1);
  }
  _tcpSocket.setBlocking(false);
  return (0);
}

int                   Network::sendTCP(Message const &msg)
{
  unsigned short int  size = msg.getSize();
  std::size_t sent;

  if (_tcpSocket.send(msg.getMessage(), size, sent) != sf::Socket::Done)
  {
    std::cerr << "Send TCD Failed" << std::endl;
    return (-1);
  }
  return (0);
}

int                   Network::sendUDP(Message const &msg)
{
  unsigned short int  size = msg.getSize();

  if (_udpSocket.send(msg.getMessage(), size, _ip.c_str(), _port) != sf::Socket::Done)
  {
    std::cerr << "Send UDP Failed" << std::endl;
    return (-1);
  }
  return (0);
}

std::string *Network::createRandomId(int len)
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

void        Network::convertToEntity(Message *msg)
{
  PacketComponent &packetComponent = engine::Instance().getComponent<PacketComponent>("PacketComponent");
  packetComponent.setPacket(msg->getMessage(), msg->getSize());
  Entity& packetEntity = engine::Instance().getEntity(*createRandomId(5));
  packetEntity.getComponents().addObject(packetComponent);
  engine::Instance().addToSystem(packetEntity, "TaskManager");
}

bool        Network::doAction(Entity& entity)
{
  Message *msg = nullptr;

  (void)entity;
  this->updateQueueTCP();
  this->updateQueueUDP();
  msg = this->getNextPacketUDP();
  if (msg != nullptr)
  {
    this->convertToEntity(msg);
  }
  msg = this->getNextPacketTCP();
  if (msg != nullptr)
  {
    this->convertToEntity(msg);
  }
  return true;
}