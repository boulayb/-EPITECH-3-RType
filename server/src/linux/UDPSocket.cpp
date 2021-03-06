//
// Created by bocque_c on 05/12/16.
//

#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include "linux/UDPSocket.hh"

UDPSocket::UDPSocket() : _sock(0), _type(FREE)
{
}

UDPSocket::~UDPSocket()
{

}

UDPSocket &UDPSocket::operator=(UDPSocket const &socket)
{
  if (&socket != this)
  {
    _sock = socket._sock;
    _type = socket._type;
    _sockAddr = socket._sockAddr;
    //_clientAddr = socket._clientAddr;
    //_clientlen = socket._clientlen;
  }
  return *this;
}

unsigned int UDPSocket::send(Message &buffer, sockaddr_in const &addr)
{
  sockaddr_in cpy;

  std::memcpy(&cpy, &addr, sizeof(sockaddr_in));
  int fromsize = sizeof(sockaddr_in);
  cpy.sin_port = htons(4005 +1);
  int ret = ::sendto(_sock, buffer.getMessage(), buffer.getSize(), 0, (struct sockaddr *) &cpy, fromsize);
  return ret;
}


unsigned int UDPSocket::send(Message &buffer)
{


  int ret = ::sendto(_sock, buffer.getMessage(), buffer.getSize(), 0, (struct sockaddr *) &_lastClientAddr, _clientlen);
  return ret;
}

int UDPSocket::recv(Message &buffer)
{
  sockaddr_in clientAddr;
  _clientlen = sizeof(clientAddr);
  unsigned char *tmpData = new unsigned char[BUFF_SIZE];
  int ret = ::recvfrom(_sock, tmpData, BUFF_SIZE, 0, (struct sockaddr *) &_lastClientAddr, &_clientlen);
  buffer.setMessage(tmpData, ret, _sock);

  return ret;
}

void UDPSocket::close()
{
  _type = FREE;
  ::close(_sock);
  _sock = 0;
}

int UDPSocket::create(unsigned int port)
{
  _type = SERVER;
  _port = port;
  _sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (_sock == -1)
  {
    perror("socket()");
    throw std::exception();
  }
  _sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  _sockAddr.sin_family = AF_INET;
  _sockAddr.sin_port = htons(port);

  if (bind(_sock, reinterpret_cast<struct sockaddr *>(&_sockAddr), sizeof(_sockAddr)) == -1)
  {
    perror("bind()");
    throw std::exception();
  }
  return _sock;
}

const sockaddr_in &UDPSocket::getUserAddr() const
{
  return _sockAddr;
}

int UDPSocket::getSock() const
{
  return _sock;
}

UDPSocket::SocketType UDPSocket::getType() const
{
  return _type;
}

void UDPSocket::createFromAccept(int fd, sockaddr_in &sockAddr)
{
  _sock = fd;
  _sockAddr = sockAddr;
  _type = CLIENT;
}