//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_MESSAGE_HH
# define RTYPE_MESSAGE_HH

# include <string>
# include <vector>
# include <cstring>

class Message
{
private:
  unsigned char *_buff;
  int           _size;
  int           _clientID;

public:
  Message(int clientID) : _buff(nullptr), _size(0), _clientID(clientID)
  {
  }

  Message()
  {

  }

  ~Message()
  {

  }

  void              setClientId(int clientID)
  {
    _clientID = clientID;
  }

  int const         &getClientID() const
  {
    return _clientID;
  }

  void              setMessage(unsigned char *data, int size, int clientID)
  {
    _size = size;
    _clientID = clientID;
    _buff = data;
  }

  void              setMessage(unsigned char *data, int size)
  {
    _size = size;
    _buff = data;
  }

  unsigned char     *getMessage() const
  {
    return _buff;
  }

  int const         &getSize() const
  {
    return _size;
  }
};

#endif //RTYPE_MESSAGE_HH
