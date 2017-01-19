#ifndef ECSVECTOR_HPP_
# define ECSVECTOR_HPP_

# include <list>
# include <vector>
# include <string>
# include <algorithm>
# include <stdexcept>
# include <iostream>

template<typename T>
class                                   ECSVector
{
 public:
  typedef std::vector<T*>               vector;
  typedef typename vector::iterator     iterator;

 private:
  vector                                _vector;

 public:
  ECSVector()
  {
  }

  ECSVector(const vector& cpy) :
    _vector(cpy)
  {
  }

  ~ECSVector()
  {
  }

  T&                                    getObject(const T& obj)
  {
    iterator it = std::find(_vector.begin(), _vector.end(), &obj);
    if (it == _vector.end())
      throw std::out_of_range("Object doesn't exist");
    return (**it);
  }

  bool                                  objectExist(const T& obj)
  {
    if (std::find(_vector.begin(), _vector.end(), &obj) == _vector.end())
      return (false);
    return (true);
  }

  bool                                  idExist(const std::string& id)
  {
    for (const T* obj : _vector)
      if (obj->getId() == id)
        return (true);
    return (false);
  }

  bool                                  objectExist(const std::string& id)
  {
    if (std::find_if(_vector.begin(), _vector.end(),
                     [id] (const T* object)->bool
                     {
                       if (object->getId() == id)
                         return true;
                       else
                         return false;
                     }) == _vector.end())
      return (false);
    return (true);
  }

  bool                                  removeObject(const T& obj)
  {
    iterator it = std::find(_vector.begin(), _vector.end(), &obj);
    if (it == _vector.end())
      return (false);
    std::iter_swap(it, _vector.end() - 1);
    _vector.pop_back();
    return (true);
  }

  T&                                    getObject(const std::string& id)
  {
    iterator it = std::find_if(_vector.begin(), _vector.end(),
                               [id] (const T* object)->bool
                               {
                                 /*
                                 std::cout << "objectID = " << object->getId
                                         () << ", id = " << id << std::endl;
                                         */
                                 if (object->getId() == id)
                                   return true;
                                 else
                                   return false;
                               });
    if (it == _vector.end())
      throw std::out_of_range("Object doesn't exist");
    return (**it);
  }

  bool                                  removeObject(const std::string& id)
  {
    iterator it = std::find_if(_vector.begin(), _vector.end(),
                               [id] (const T* object)->bool
                               {
                                 if (object->getId() == id)
                                   return true;
                                 else
                                   return false;
                               });
    if (it == _vector.end())
      return (false);
    std::iter_swap(it, _vector.end() - 1);
    _vector.pop_back();
    return (true);
  }

  bool                                  addObject(T& obj)
  {
    iterator it = std::find(_vector.begin(), _vector.end(), &obj);
    if (_vector.size() != 0 && it != _vector.end())
      return (false);
    _vector.push_back(&obj);
    return (true);
  }

  bool                                  addObject(T* obj)
  {
    iterator it = std::find(_vector.begin(), _vector.end(), obj);
    if (_vector.size() != 0 && it != _vector.end())
      return (false);
    _vector.push_back(obj);
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

  bool                                  addObjectAt(int pos, T* obj)
  {
    int i = 0;
    iterator found = _vector.end();
    for (iterator it = _vector.begin(); it != _vector.end(); ++it)
      {
        if (*it == obj)
          return (false);
        else if (i == pos)
          found = it;
        ++i;
      }
    _vector.insert(found, obj);
    return (true);
  }

  inline void                           empty(void)
  {
    _vector.clear();
  }

  inline void                           setVector(const vector& cpy)
  {
    _vector = cpy;
  }

  inline const vector&                  getVector(void) const
  {
    return (_vector);
  }
};

#endif /* !ECSVECTOR_HPP_ */
