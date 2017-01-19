//
// Created by bocque_c on 18/12/16.
//

#include <iostream>
#include <stdlib.h>
#include "linux/UDPMonitor.hh"

UDPMonitor::UDPMonitor(unsigned int port) :  AUDPMonitor(port)
{
  //std::cout << "CREATION UDP ADDRESS" << std::endl;
  UDPSocket *servSock = new UDPSocket();
  servSock->create(_port);
  _fdList.push_back(servSock);
}

void UDPMonitor::setClients(std::vector<ISocket*> &sockets)
{
  _fdListClients = &sockets;
}

void UDPMonitor::update()
{
  //std::cout << "update UDP" << std::endl;
  fd_set fd_read;
  fd_set fd_write;
  int fdMax;
  int i = 0;
  int selectRet;

  FD_ZERO(&fd_read);
  FD_ZERO(&fd_write);
  fdMax = 0;
  for (ISocket *tmpSock: _fdList)
  {
    //std::cout << "for update" << std::endl;
    UDPSocket *socket = reinterpret_cast<UDPSocket *>(tmpSock);
    if (socket->getType() != UDPSocket::FREE)
    {
      //std::cout << "Segfault ici" << std::endl;
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
    //std::cout << "event action" << std::endl;
    this->eventAction(fd_read, fd_write);
  }
  if (!_messageToWrite.empty())
  {
    Message *msg = _messageToWrite.front();
    _messageToWrite.pop();
    this->writeMessage(*msg);
  }
}

void UDPMonitor::eventAction(fd_set &fd_read, fd_set &fd_write)
{
  int i = 0;
  (void)fd_write;
  //std::cout << "event Action" << std::endl;
  for (ISocket *tmpSock: _fdList)
  {
    UDPSocket *socket = reinterpret_cast<UDPSocket *>(tmpSock);
    if (FD_ISSET(socket->getSock(), &fd_read))
      this->readUser(socket->getSock());
    i++;
  }
}


void UDPMonitor::readUser(int fd)
{
  Message *message = new Message();
  for (ISocket *tmpSock: _fdList)
  {
    UDPSocket *socket = reinterpret_cast<UDPSocket *>(tmpSock);
    if (fd == socket->getSock())
    {
      if (socket->recv(*message) > 0)
      {
        _receivedMsgs.push(message);
        break;
      }
      else
      {
        socket->close();
      }
    }
  }
}