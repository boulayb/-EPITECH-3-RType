//
// Created by danilo_d on 04/12/16.
//

#ifndef RTYPE_ISOCKET_HH
#define RTYPE_ISOCKET_HH

#ifdef __unix__
#include <sys/socket.h>
#elif defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#endif
#include "Message.hpp"

typedef struct sockaddr_in sockaddr_in;

class ISocket
{
public:
  virtual ~ISocket() {}
  virtual unsigned int send(Message &buffer) = 0;
  virtual int recv(Message &buffer) = 0;
  virtual const sockaddr_in &getUserAddr() const = 0;
  virtual int getSock() const = 0;
  virtual void close() = 0;
};

#endif //RTYPE_ISOCKET_HH
