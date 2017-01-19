//
// Created by bocque_c on 13/12/16.
//

#ifndef RTYPE_UDPMONITORDP_HH_HH
#define RTYPE_UDPMONITORDP_HH_HH

#include <queue>
#include "AUDPMonitor.hh"
#include "windows/UDPSocket.hh"
#include "UserAddr.hh"

class UDPMonitor : public AUDPMonitor
{
public:
  UDPMonitor(unsigned int port);
  virtual void update();
private:
  virtual void readUser(int fd);
  void eventAction(fd_set &fd_read, fd_set &fd_write);
  void setClients(std::vector<ISocket*> &sockets);
};

#endif //RTYPE_UDPMONITORDP_HH_HH