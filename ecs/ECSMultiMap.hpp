//
// Created by coodie_d on 12/23/16.
//

#ifndef RTYPE_ECSMULTIMAP_HPP
#define RTYPE_ECSMULTIMAP_HPP

# include <map>
# include <list>
# include <string>
# include <vector>
# include <stdexcept>

template<typename T>
class                                   ECSMultiMap
{
public:
  typedef std::multimap<std::string, T*>  map;
  typedef std::pair<std::string, T*>      pair;
  typedef typename map::iterator          iterator;

private:
  map                                     _map;

public:
  ECSMultiMap()
  {
  }

  ECSMultiMap(const map& cpy) :
          _map(cpy)
  {
  }

  ~ECSMultiMap()
  {
  }

  inline void                           setMap(const map& cpy)
  {
    _map = cpy;
  }

  inline const map&                     getMap(void) const
  {
    return (_map);
  }

  template<typename U>
  inline bool                           getObjects(const std::string& key,
                                                   std::vector<U*> &objects)
  {
    std::pair<iterator, iterator> ret;

    ret = _map.equal_range(key);
    for (iterator it = ret.first; it != ret.second; ++it)
    {
      U *obj = dynamic_cast<U *>(it->second);
      if (obj != nullptr)
      {
        objects.push_back(obj);
      }
    }
    if (objects.size() > 0)
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }

  inline bool                           keyExist(const std::string& key)
  {
    iterator it = _map.find(key);
    if (it == _map.end())
    {
      return (false);
    }
    else
    {
      return (true);
    }
  }

  inline bool                           removeKey(std::string const &key)
  {
    if (this->keyExist(key))
    {
      _map.erase(key);
      return (true);
    }
    else
    {
      return (false);
    }
  }

  inline bool                           removeObject(T *obj)
  {
    std::string                         key;
    key = obj->getId();
    if (this->keyExist(key))
    {
      std::pair<iterator, iterator> ret;
      ret = _map.equal_range(key);
      for (iterator it = ret.first; it != ret.second; ++it)
      {
        if (it->second == obj)
        {
          _map.erase(it);
          return (true);
        }
      }
    }
    return (false);
  }

  inline bool                           removeObject(T &obj)
  {
    std::string                         key;
    key = obj.getId();
    if (this->keyExist(key))
    {
      std::pair<iterator, iterator> ret;
      ret = _map.equal_range(key);
      for (iterator it = ret.first; it != ret.second; ++it)
      {
        if (it->second == &obj)
        {
          _map.erase(it);
          return (true);
        }
      }
    }
    return (false);
  }

  inline bool                           addObject(T& obj)
  {
    std::string                         key;
    key = obj.getId();
    _map.insert(pair(key, &obj));
    return (true);
  }

  inline bool                           addObject(T* obj)
  {
    std::string                         key;
    key = obj->getId();
    _map.insert(pair(key, obj));
    return (true);
  }

  inline bool                           addObjects(std::list<T> objs)
  {
    for (T& obj : objs)
      this->addObject(&obj);
    return (true);
  }

  inline bool                           addObjects(std::list<T*> objs)
  {
    for (T* obj : objs)
      this->addObject(obj);
    return (true);
  }

  inline bool                           empty()
  {
    _map.clear();
    return (true);
  }
};

#endif //RTYPE_ECSMULTIMAP_HPP
