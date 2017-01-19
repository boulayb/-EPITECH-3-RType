#include <iostream>
#include <windows/TCPSocket.hh>
#include <windows/TCPMonitor.hh>
#include <cstdio>
#include <ws2tcpip.h>
#include "Protocol.hpp"

TCPMonitor::TCPMonitor(unsigned int port) : ATCPMonitor(port)
{
  int error;

  error = WSAStartup(MAKEWORD(2,2), &_wsaData);
  if (error)
  {
    std::cerr << "WSAStartup() failed with error:" << error << std::endl;
    throw std::exception();
  }
  TCPSocket *servSock = new TCPSocket();
  int fdCreated = servSock->create(_port);
  _fdList.push_back(servSock);
}

std::vector<ISocket*> &TCPMonitor::getClients()
{
	return _fdList;
}

void TCPMonitor::update()
{
	fd_set fd_read;
	fd_set fd_write;
	int fdMax;
	int i = 0;
	int selectRet;

	FD_ZERO(&fd_read);
	FD_ZERO(&fd_write);
	fdMax = 0;
	for (ISocket *tmpSock : _fdList)
	{
		TCPSocket *socket = reinterpret_cast<TCPSocket *>(tmpSock);
		if (socket->getType() != TCPSocket::FREE)
		{
			FD_SET(socket->getSock(), &fd_read);
			FD_SET(socket->getSock(), &fd_write);
			fdMax = socket->getSock();
		}
		i++;
	}
	if ((selectRet = select(fdMax + 1, &fd_read, &fd_write, NULL, NULL)) == -1)
	{
		perror("select");
		throw std::exception();
	}
	if (selectRet > 0)
	{
		this->eventAction(fd_read, fd_write);
	}
	if (!_messageToWrite.empty())
	{
		Message *msg = _messageToWrite.front();
		this->writeMessage(*msg);
		_messageToWrite.pop();
	}
}

void TCPMonitor::eventAction(fd_set &fd_read, fd_set &fd_write)
{
	int i = 0;
	(void)fd_write;
	for (ISocket *tmpSock : _fdList)
	{
		TCPSocket *socket = reinterpret_cast<TCPSocket *>(tmpSock);
		if (FD_ISSET(socket->getSock(), &fd_read))
		{
			if (socket->getType() == TCPSocket::SERVER)
			{
				this->acceptUser(socket->getSock());
			}
			else
			{
				this->readUser(socket->getSock());
			}
			break;
		}
		i++;
	}
}

void TCPMonitor::acceptUser(int fd)
{
	TCPSocket *clientSock = new TCPSocket();
	int			cs;
	socklen_t		client_sin_len;
	sockaddr_in	*client_sin = new sockaddr_in;

	client_sin_len = sizeof(sockaddr_in);
	if ((cs = accept(fd, reinterpret_cast<struct sockaddr *>(client_sin), &client_sin_len)) == -1)
	{
		perror("./server: accept");
		throw std::exception();
	}
	clientSock->createFromAccept(cs, *client_sin);
	_fdList.push_back(clientSock);
	Protocol::rtypePacket *packet = Protocol::Protocol::createPacket(Protocol::Code::HANDSHAKE, nullptr, Protocol::DataType::NONE, 0);
	Message *handShakeMessage = new Message;

	handShakeMessage->setMessage(reinterpret_cast<unsigned char *>(packet), sizeof(Protocol::rtypePacket), cs);
	_receivedMsgs.push(handShakeMessage);
}

void TCPMonitor::readUser(int fd)
{
	Message *message = new Message();


	for (auto it = _fdList.begin(); it != _fdList.end(); ++it)
	{
		TCPSocket *socket = reinterpret_cast<TCPSocket *>(*it);
		if (fd == socket->getSock())
		{
			if (socket->recv(*message) > 0)
			{
				_receivedMsgs.push(message);
			}
			else
			{
				socket->close();
				_fdList.erase(it);
			}
			break;
		}
	}
}