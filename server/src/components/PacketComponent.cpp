//
// Created by dimitri on 12/25/16.
//

#include <cstring>
#include "components/PacketComponent.hh"

PacketComponent::PacketComponent(std::string const &id) : Component(id)
{

}

Protocol::rtypePacket *PacketComponent::getPacket()
{
  return &_packet;
}

int PacketComponent::getClientId() const
{
  return _clientId;
}

void PacketComponent::setPacket(unsigned char *msg, int size, int clientId)
{
  std::memcpy(&_packet, msg, size);
  _clientId = clientId;
}