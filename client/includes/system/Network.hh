//
// Created by bocque_c on 05/12/16.
//

#ifndef RTYPE_NETWORK_H
#define RTYPE_NETWORK_H

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <queue>
#include "Message.hpp"
#include "Engine.hpp"

class Network : public System
{
private:
  std::string             _ip;
  unsigned short int      _port;
  std::string             _name;
  std::queue<Message *>   _tcpQueue;
  std::queue<Message *>   _udpQueue;
  sf::TcpSocket           _tcpSocket;
  sf::UdpSocket           _udpSocket;

public:
  Network(std::string const &ip, unsigned short port, std::string const &name);
  //TCP
  bool        updateQueueTCP();
  Message     *getNextPacketTCP();
  int         sendTCP(Message const &msg);
  int         connectTCP();
  bool        doAction(Entity& entity);
  std::string getUserName() const;
  //UDP
  bool        updateQueueUDP();
  Message     *getNextPacketUDP();
  int         sendUDP(Message const &msg);
  int         connectUDP();
  std::string *createRandomId(int len);
private:
  void        convertToEntity(Message *msg);
};

#endif //RTYPE_NETWORK_H
