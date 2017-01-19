//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_TCPSOCKETSOP_HH
#define RTYPE_TCPSOCKETSOP_HH

#include "ISocket.hh"

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
  SOCKET _sock;
  SocketType _type;
  sockaddr_in _sockAddr;
  const unsigned int BUFF_SIZE = 4096;
  const int LISTEN_BACKLOG = 42;
};

#endif //RTYPE_TCPSOCKETSOP_HH
