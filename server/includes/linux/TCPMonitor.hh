//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_TCPMONITORKL_HH
#define RTYPE_TCPMONITORKL_HH

#include <queue>
#include "ATCPMonitor.hh"
#include "linux/TCPSocket.hh"
#include "UserAddr.hh"

class TCPMonitor : public ATCPMonitor
{
public:
  TCPMonitor(unsigned int port);
  virtual void update();
private:
  virtual void acceptUser(int fd);
  virtual void readUser(int fd);
  std::vector<ISocket *> &getClients();
  void eventAction(fd_set &fd_read, fd_set &fd_write);
};

#endif //RTYPE_TCPMONITORKL_HH
