//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_ITCPMONITOR_HH
#define RTYPE_ITCPMONITOR_HH

#ifdef __unix__
#include <netinet/in.h>
#elif defined(_WIN32) || defined(WIN32)
#include <winsock2.h>

#endif

#include "Message.hpp"
#include "ISocket.hh"

class ITCPMonitor
{
public:
  virtual ~ITCPMonitor() {}
  virtual void update() = 0;
  virtual const sockaddr_in &getUserInfo(unsigned int  ) const = 0;
  virtual bool isReadable() const = 0;
  virtual void sendMessage(Message  &) = 0;
  virtual Message &getNextMessage() = 0;
  virtual std::vector<ISocket*> &getClients() = 0;
private:
  virtual void acceptUser(int fd) = 0;
};

#endif //RTYPE_ITCPMONITOR_HH
