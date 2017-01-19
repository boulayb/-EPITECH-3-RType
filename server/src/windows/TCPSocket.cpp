#include <iostream>
#include <cstdio>
#include <Packet.hh>
#include "windows/TCPSocket.hh"

TCPSocket::TCPSocket() : _sock(0), _type(FREE)
{

}

TCPSocket::~TCPSocket()
{

}

TCPSocket &TCPSocket::operator=(TCPSocket const &socket)
{
  if (&socket != this)
  {
    _sock = socket._sock;
    _type = socket._type;
    _sockAddr = socket._sockAddr;
  }
  return *this;
}

unsigned int TCPSocket::send(Message &buffer)
{
	int ret = ::send(_sock,
		reinterpret_cast<char *> (buffer.getMessage()), buffer.getSize(), 0);
	return ret;
}

int TCPSocket::recv(Message &buffer)
{
	unsigned char *tmpBuffer = new unsigned char[BUFF_SIZE];
	int ret = ::recv(_sock, reinterpret_cast<char *> (tmpBuffer), BUFF_SIZE, 0);
	buffer.setMessage(tmpBuffer, ret, _sock);
	return ret;
}

void TCPSocket::close()
{
  _type = FREE;
  closesocket(_sock);
  _sock = 0;
}

int TCPSocket::create(unsigned int port)
{
	_type = SERVER;
	_sock = socket(AF_INET, SOCK_STREAM, 0);
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
	if (listen(_sock, LISTEN_BACKLOG) == -1)
	{
		perror("./server: listen");
		throw std::exception();
	}
	return _sock;

}

const sockaddr_in &TCPSocket::getUserAddr() const
{
  return _sockAddr;
}

int TCPSocket::getSock() const
{
  return _sock;
}

TCPSocket::SocketType TCPSocket::getType() const
{
  return _type;
}

void TCPSocket::createFromAccept(int fd, sockaddr_in &sockAddr)
{
  _sock = fd;
  _sockAddr = sockAddr;
  _type = CLIENT;
}