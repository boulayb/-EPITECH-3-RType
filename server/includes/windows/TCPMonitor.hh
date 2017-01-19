
#ifndef RTYPE_TCPMONITORD_HH
#define RTYPE_TCPMONITORD_HH

#include <queue>
#include "ATCPMonitor.hh"

class TCPMonitor : public ATCPMonitor
{
public:
  TCPMonitor(unsigned int port);
  virtual void update();
private:
  virtual void acceptUser(int fd);
  void readUser(int fd);
  std::vector<ISocket *> &getClients();
  void eventAction(fd_set &fd_read, fd_set &fd_write);
  WSADATA _wsaData;
};

#endif //RTYPE_TCPMONITORD_HH
