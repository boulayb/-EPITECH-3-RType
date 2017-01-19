//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_IUDPMONITOR_HH
#define RTYPE_IUDPMONITOR_HH

#ifdef __unix__
#include <netinet/in.h>
#elif defined(_WIN32) || defined(WIN32)
#include <winsock2.h>

#endif

#include "Message.hpp"
#include "ISocket.hh"

class IUDPMonitor
{
public:
  virtual ~IUDPMonitor() {}
  virtual void update() = 0;
  virtual const sockaddr_in &getUserInfo(unsigned int  ) const = 0;
  virtual bool isReadable() const = 0;
  virtual void sendMessage(Message  &) = 0;
  virtual Message &getNextMessage() = 0;
  virtual void setClients(std::vector<ISocket*> &sockets) = 0;
};

#endif //RTYPE_IUDPMONITOR_HH
