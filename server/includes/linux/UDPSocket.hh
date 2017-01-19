//
// Created by bocque_c on 13/12/16.
//

#ifndef RTYPE_UDPSOCKET_HH
#define RTYPE_UDPSOCKET_HH

#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif //RTYPE_UDPSOCKET_HH

#include "ISocket.hh"
#include "Protocol.hpp"

typedef struct sockaddr_in sockaddr_in;

class UDPSocket : public ISocket
{
public:
  enum SocketType
  {
    SERVER = 1,
    CLIENT = 2,
    FREE = 3,
  };

public:
  UDPSocket();
  virtual ~UDPSocket();
  UDPSocket &operator=(UDPSocket const &socket);
  virtual unsigned int send(Message &buffer);
  virtual int recv(Message &buffer);
  virtual void close();
  int create(unsigned int port);
  void createFromAccept(int fd, sockaddr_in &sockAddr);
  const sockaddr_in &getUserAddr() const;
  SocketType getType() const;
  int getSock() const;
  unsigned int send(Message &buffer, sockaddr_in const &addr);
private:
  int _sock;
  int _port;
  SocketType _type;
  sockaddr_in _sockAddr;
  sockaddr_in _lastClientAddr;
  socklen_t _clientlen = 0;
  const unsigned int BUFF_SIZE = sizeof(Protocol::rtypePacket);
  const int LISTEN_BACKLOG = 42;
};
#endif /*RTYPE_UDPSOCKET_HH*/
