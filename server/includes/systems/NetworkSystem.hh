//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_NETWORKSYSTEM_HH
#define RTYPE_NETWORKSYSTEM_HH

#include <queue>
#include <thread>
#include <cstring>
#include "Engine.hpp"
#include "ITCPMonitor.hh"
#include "IUDPMonitor.hh"
#include "Message.hpp"


class NetworkSystem : public System
{
public:
  NetworkSystem(unsigned int port = 4005);
  ~NetworkSystem();
  void start();
  bool isTCPReadable() const;
  bool isUDPReadable() const;
  Message &getUDPMessage();
  Message &getTCPMessage();
  void pushTCPMessage(Message &);
  void pushUDPMessage(Message &);
  bool doAction(Entity& entity);

  template<typename T>
  Message &packetToMessage(T *packet, int clientID)
  {
    Message       *msg = new Message(clientID);
    size_t        size = sizeof(*packet);
    unsigned char *data = new unsigned char[size];

    std::memcpy(data, packet, size);
     msg->setMessage(data, static_cast<int>(size));
    return *msg;
  }

  template<typename T>
  void    pushTCPMessage(T  *packet, int clientID)
  {
    Message &msg = this->packetToMessage<T>(packet, clientID);

    _monitorTCP->sendMessage(msg);
  }

  template<typename T>
  void    pushUDPMessage(T const *packet, int clientID)
  {
    Message &msg = this->packetToMessage(packet, clientID);
    _monitorUDP->sendMessage(msg);
  }

private:
  std::string *createRandomId(int len);
  void        convertToEntity(Message &msg);


private:
  ITCPMonitor *_monitorTCP;
  IUDPMonitor *_monitorUDP;
};

#endif //RTYPE_NETWORKSYSTEM_HH
