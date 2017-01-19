//
// Created by 49715 on 06/12/2016.
//

#ifndef RTYPE_ATCPMONITOR_HH
#define RTYPE_ATCPMONITOR_HH

#include <queue>
#include <mutex>
#include "ITCPMonitor.hh"
#include "ISocket.hh"

class ATCPMonitor : public ITCPMonitor
{
public:
  ATCPMonitor(unsigned int port);
  virtual ~ATCPMonitor();
  virtual void update() = 0;
  virtual const sockaddr_in &getUserInfo(unsigned int userId) const;
  virtual bool isReadable() const;
  virtual Message &getNextMessage();
  virtual void sendMessage(Message &);
  virtual void writeMessage(Message &);
  virtual std::vector<ISocket*> &getClients();

protected:
  unsigned int _port;
  std::vector<ISocket *> _fdList;
  std::queue<Message *> _receivedMsgs;
  std::queue<Message *> _messageToWrite;
  std::mutex            _mutex;
  unsigned int MAX_FD = 255;

};

#endif //RTYPE_ATCPMONITOR_HH
