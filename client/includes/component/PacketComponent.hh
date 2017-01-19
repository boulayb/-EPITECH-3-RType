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
  const Protocol::rtypePacket *getPacket() const;
  Protocol::rtypePacket *getPacket();
  void setPacket(unsigned char *, int size);
private:
  Protocol::rtypePacket _packet;
};

#endif //RTYPE_PACKET_HH
