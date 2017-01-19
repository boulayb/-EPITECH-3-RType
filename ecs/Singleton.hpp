  //
// Created by coodie_d on 12/25/16.
//

#ifndef RTYPE_SINGLETON_HPP
#define RTYPE_SINGLETON_HPP

template <typename T>
class Singleton
{
public:
  static T& Instance()
  {
    if (Singleton::_instance == 0)
    {
      Singleton::_instance = CreateInstance();
    }
    return *(Singleton::_instance);
  }

protected:
  virtual ~Singleton()
  {
    if(Singleton::_instance != 0)
    {
      delete Singleton::_instance;
    }
    Singleton::_instance = 0;
  }

  inline explicit Singleton()
  {
    assert(Singleton::_instance == 0);
    Singleton::_instance = static_cast<T*>(this);
  }

private:
  static T* _instance;
  static T* CreateInstance()
  {
    return new T();
  }
};

template<typename T>
T* Singleton<T>::_instance = 0;

#endif //RTYPE_SINGLETON_HPP
