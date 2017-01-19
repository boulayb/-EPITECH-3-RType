//
// Created by danilo_d on 05/12/16.
//

#ifndef RTYPE_USERADDR_HH
#define RTYPE_USERADDR_HH

template <typename T>
class UserAddr
{
public:
  UserAddr()
  {

  }

  ~UserAddr()
  {

  }

  UserAddr(T addr)
  {
    _addr = addr;
  }

  void setAddr(T addr)
  {
    _addr = addr;
  }

  T getAddr() const
  {
    return _addr;
  }

private:
  T _addr;
};

#endif //RTYPE_USERADDR_HH
