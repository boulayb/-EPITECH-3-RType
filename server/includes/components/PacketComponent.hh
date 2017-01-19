//
// Created by dimitri on 12/25/16.
//

#ifndef RTYPE_PACKET_HH
#define RTYPE_PACKET_HH

#include "Component.hpp"
#include "Packet.hh"

class PacketComponent : public Component
{
public:
  PacketComponent(std::string const &id);
  Protocol::rtypePacket *getPacket();
  void setPacket(unsigned char *, int size, int clientId);
  int getClientId() const;

private:
  Protocol::rtypePacket  _packet;
  int                    _clientId;
};

#endif //RTYPE_PACKET_HH
