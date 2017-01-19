//
// Created by bocque_c on 18/12/16.
//


#include <linux/TCPSocket.hh>
#include <linux/UDPSocket.hh>
#include "AUDPMonitor.hh"

AUDPMonitor::AUDPMonitor(unsigned int port) : _port(port)
{
}
AUDPMonitor::~AUDPMonitor()
{

}

void AUDPMonitor::setClients(std::vector<ISocket*> &sockets)
{
  _fdListClients = &sockets;
}

const sockaddr_in &AUDPMonitor::getUserInfo(unsigned int userId) const
{
  return _fdList[userId]->getUserAddr();
}

bool AUDPMonitor::isReadable() const
{
  return !_receivedMsgs.empty();
}

Message &AUDPMonitor::getNextMessage()
{
  std::unique_lock<std::mutex> lock(this->_mutex);
  Message *message = _receivedMsgs.front();
  _receivedMsgs.pop();
  return *message;
}

void AUDPMonitor::sendMessage(Message &msg)
{
  std::unique_lock<std::mutex> lock(this->_mutex);
  _messageToWrite.push(&msg);
}


void AUDPMonitor::writeMessage(Message &msg)
{
  for (ISocket *socket: *_fdListClients)
  {
    if (msg.getClientID() == socket->getSock())
    {
      UDPSocket *UdpSocket = reinterpret_cast<UDPSocket *>(_fdList.front());

      UdpSocket->send(msg, socket->getUserAddr());
      break;
    }
  }
}