//
// Created by bocque_c on 18/12/16.
//

#ifndef RTYPE_AUDPMONITORLM_HH_HH
#define RTYPE_AUDPMONITORLM_HH_HH

#include <queue>
#include <mutex>
#include "IUDPMonitor.hh"
#include "ISocket.hh"

class AUDPMonitor : public IUDPMonitor
{
public:
  AUDPMonitor(unsigned int port);
  virtual ~AUDPMonitor();
  virtual void update() = 0;
  virtual const sockaddr_in &getUserInfo(unsigned int userId) const;
  virtual bool isReadable() const;
  virtual Message &getNextMessage();
  virtual void sendMessage(Message &);
  virtual void setClients(std::vector<ISocket*> &sockets);
  void writeMessage(Message &msg);

protected:
  unsigned int _port;
  std::vector<ISocket *> _fdList;
  std::vector<ISocket *> * _fdListClients;
  std::queue<Message *> _receivedMsgs;
  std::queue<Message *> _messageToWrite;
  std::mutex            _mutex;
  unsigned int MAX_FD = 255;

};

#endif //RTYPE_AUDPMONITORLM_HH_HH
