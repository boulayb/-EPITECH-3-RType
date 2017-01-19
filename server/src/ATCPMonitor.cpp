//
// Created by 49715 on 13/12/2016.
//

#include <iostream>
#include <Packet.hh>
#include "ATCPMonitor.hh"

ATCPMonitor::ATCPMonitor(unsigned int port) : _port(port)
{
}
ATCPMonitor::~ATCPMonitor()
{

}

std::vector<ISocket*> &ATCPMonitor::getClients()
{
  return _fdList;
}

const sockaddr_in &ATCPMonitor::getUserInfo(unsigned int userId) const
{
  return _fdList[userId]->getUserAddr();
}

bool ATCPMonitor::isReadable() const
{
  return !_receivedMsgs.empty();
}

Message &ATCPMonitor::getNextMessage()
{
  Message *message = _receivedMsgs.front();
  _receivedMsgs.pop();
  return *message;
}

void ATCPMonitor::sendMessage(Message &msg)
{
  _messageToWrite.push(&msg);
}

void ATCPMonitor::writeMessage(Message &msg)
{
  for (ISocket *client : _fdList)
  {
    if (client->getSock() == msg.getClientID())
    {
      client->send(msg);
      break;
    }
  }
}