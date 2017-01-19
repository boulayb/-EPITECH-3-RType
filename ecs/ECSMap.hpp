#ifndef ECSMAP_HPP_
# define ECSMAP_HPP_

# include <list>
# include <string>
# include <stdexcept>
# include <unordered_map>

template<typename T>
class                                   ECSMap
{
 public:
  typedef std::unordered_map
  <std::string, T*>                     map;
  typedef std::pair<std::string, T*>    pair;
  typedef typename map::iterator        iterator;

 private:
  map                                   _map;

 public:
  ECSMap()
  {
  }

  ECSMap(const map& cpy) :
    _map(cpy)
  {
  }

  ~ECSMap()
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

  inline void                           empty(void)
  {
    _map.clear();
  }

  template<typename U>
  U&                                    getObject(const std::string& key)
  {
    return (static_cast<U&>(*(_map.at(key))));
  }

  bool                                  keyExist(const std::string& key)
  {
    try
      {
        _map.at(key);
        return (true);
      }
    catch (const std::out_of_range& err)
      {
        return (false);
      }
  }

  bool                                  removeObject(const std::string& key)
  {
    if (this->keyExist(key) == false)
      return (false);
    _map.erase(key);
    return (true);
  }

  bool                                  addObject(T& obj)
  {
    std::string                         key;
    key = obj.getId();
    if (this->keyExist(key) == true)
      return (false);
    _map.insert(pair(key, &obj));
    return (true);
  }

  bool                                  addObject(T* obj)
  {
    std::string                         key;
    key = obj->getId();
    if (this->keyExist(key) == true)
      return (false);
    _map.insert(pair(key, obj));
    return (true);
  }

  bool                                  addObject(std::list<T> objs)
  {
    for (T& obj : objs)
      if (this->addObject(obj) == false)
        return (false);
    return (true);
  }

  bool                                  addObject(std::list<T*> objs)
  {
    for (T* obj : objs)
      if (this->addObject(*obj) == false)
        return (false);
    return (true);
  }
};

#endif /* !ECSMAP_HPP_ */
