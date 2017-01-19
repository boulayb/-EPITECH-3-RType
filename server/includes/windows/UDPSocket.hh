//
// Created by bocque_c on 13/12/16.
//

#ifndef RTYPE_UDPSOCKETW_HH
#define RTYPE_UDPSOCKETW_HH

#include "ISocket.hh"

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
  const unsigned int BUFF_SIZE = 4096;
  const int LISTEN_BACKLOG = 42;
};

#endif //RTYPE_UDPSOCKETW_HH
