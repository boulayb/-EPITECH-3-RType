//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_TCPSOCKETCPTRA_HH
#define RTYPE_TCPSOCKETCPTRA_HH

#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
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
#endif //WIN32

#include "ISocket.hh"
#include "Protocol.hpp"

typedef struct sockaddr_in sockaddr_in;

class TCPSocket : public ISocket
{
public:
  enum SocketType
  {
    SERVER = 1,
    CLIENT = 2,
    FREE = 3,
  };

public:
  TCPSocket();
  virtual ~TCPSocket();
  TCPSocket &operator=(TCPSocket const &socket);
  virtual unsigned int send(Message &buffer);
  virtual int recv(Message &buffer);
  virtual void close();

  int create(unsigned int port);
  void createFromAccept(int fd, sockaddr_in &sockAddr);
  const sockaddr_in &getUserAddr() const;
  SocketType getType() const;
  virtual int getSock() const;
private:
  int _sock;
  SocketType _type;
  sockaddr_in _sockAddr;
  const unsigned int BUFF_SIZE = sizeof(Protocol::rtypePacket);
  const int LISTEN_BACKLOG = 42;
};

#endif //RTYPE_TCPSOCKETCPTRA_HH