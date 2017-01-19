//
// Created by bocque_c on 05/12/16.
//

#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include "windows/UDPSocket.hh"

UDPSocket::UDPSocket()// : _sock(0), _type(FREE)
{
}

UDPSocket::~UDPSocket()
{

}

UDPSocket &UDPSocket::operator=(UDPSocket const &socket)
{
  /*if (&socket != this)
  {
    _sock = socket._sock;
    _type = socket._type;
    _sockAddr = socket._sockAddr;
    //_clientAddr = socket._clientAddr;
    //_clientlen = socket._clientlen;
  }
  return *this;*/
	return (*this);
}

unsigned int UDPSocket::send(Message &buffer, sockaddr_in const &addr)
{
  /*sockaddr_in cpy;

  std::memcpy(&cpy, &addr, sizeof(sockaddr_in));
  int fromsize = sizeof(sockaddr_in);
  cpy.sin_port = htons(4005 +1);
  //int ret = ::sendto(_sock, buffer.getMessage(), buffer.getSize(), 0, (struct sockaddr *) &cpy, fromsize);
  int ret = 0;
  return ret;*/
	return 0;
}


unsigned int UDPSocket::send(Message &buffer)
{
  /*//int ret = ::sendto(_sock, buffer.getMessage(), buffer.getSize(), 0, (struct sockaddr *) &_lastClientAddr, _clientlen);
	int ret = 0;
  perror("sendto");
  std::cout << ret << std::endl;
  return ret;*/
	return (0);
}

int UDPSocket::recv(Message &buffer)
{
  /*sockaddr_in clientAddr;
  _clientlen = sizeof(clientAddr);
  std::vector<unsigned char> tmpBuffer(BUFF_SIZE);
  //int ret = ::recvfrom(_sock, tmpBuffer.data(), tmpBuffer.size(), 0, (struct sockaddr *) &_lastClientAddr, &_clientlen);
  int ret = 0;
  buffer.setMessage(tmpBuffer.data(), ret, _sock);
  std::cout << ret << std::endl;
  return ret;*/
	return 0;
}

void UDPSocket::close()
{
  /*_type = FREE;
  closesocket(_sock);
  _sock = 0;*/
}

int UDPSocket::create(unsigned int port)
{
  /*_type = SERVER;
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
  return _sock;*/
	return (0);
}

const sockaddr_in &UDPSocket::getUserAddr() const
{
	sockaddr_in pepe;
	return (pepe);
	
  //return _sockAddr;
	
}

int UDPSocket::getSock() const
{
  //return _sock;
	return 0;
}

UDPSocket::SocketType UDPSocket::getType() const
{
  //return _type;
	return (SocketType::FREE);
}

void UDPSocket::createFromAccept(int fd, sockaddr_in &sockAddr)
{
  /*_sock = fd;
  _sockAddr = sockAddr;
  _type = CLIENT;*/
}