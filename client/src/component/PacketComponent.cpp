//
// Created by dimitri on 12/25/16.
//

#include <cstring>
#include "component/PacketComponent.hh"

PacketComponent::PacketComponent(std::string const &id) : Component(id)
{

}

Protocol::rtypePacket *PacketComponent::getPacket()
{
  return &_packet;
}

const Protocol::rtypePacket *PacketComponent::getPacket() const
{
  return &_packet;
}

void PacketComponent::setPacket(unsigned char *msg, int size)
{
  std::memcpy(&_packet, msg, size);
}