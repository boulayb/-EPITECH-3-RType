//
// Created by coodie_d on 12/24/16.
//

#ifndef RTYPE_PROTOCOL_HH
# define RTYPE_PROTOCOL_HH

# include <cstring>
# include "Packet.hh"

namespace Protocol
{
  class Protocol
  {
  public:
    static rtypePacket   *createPacket(Code code,
                                       const unsigned char *data,
                                       DataType type,
                                       unsigned int size)
    {
      rtypePacket *packet = reinterpret_cast<rtypePacket*>(new char[sizeof(rtypePacket)]);

      packet->magicNbr = MAGIC_NUMBER;
     packet->request = code;
      packet->size = size;
      packet->type = type;
      if (data != nullptr)
        std::memcpy(&packet->data, data, size);
      else
      {
        std::memset(&packet->data, 0, size);
      }
      return (packet);
    }
  };
}

#endif //RTYPE_PROTOCOL_HH
