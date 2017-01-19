#ifndef OBJECTSPOOL_HPP_
# define OBJECTSPOOL_HPP_

# include <vector>
# include <memory>
# include <iterator>
# include <algorithm>

template <typename T>
class ObjectsPool
{
public:
  typedef std::unique_ptr<T>             objectPtr;
  typedef std::vector<objectPtr>         objectVector;

private:
  objectVector                           _used;
  objectVector                           _unused;

public:
  ObjectsPool()
  {
  }

  ObjectsPool(const objectVector& vector) :
    _used(vector)
  {
  }

  ~ObjectsPool()
  {
  }

  template<typename U>
  U&                                    getObjects(std::string const &id)
  {
    typename objectVector::iterator     objectIt;
    for (objectIt = _unused.begin(); objectIt != _unused.end(); ++objectIt)
      if (objectIt->get()->getId() == id)
        break;

    if (objectIt == _unused.end())
      {
        _used.push_back(std::make_unique<U>(id));
        return (static_cast<U&>(*_used.back()));
      }

    auto lastIt = _unused.end() - 1;
    std::iter_swap(objectIt, lastIt);
    std::move(lastIt, lastIt, std::back_inserter(_used));
    _unused.pop_back();
    return (static_cast<U&>(*(objectIt->get())));
  }

  bool                                  isKey(std::string const &id)
  {
    typename objectVector::iterator     objectIt;
    for (objectIt = _used.begin(); objectIt != _used.end(); ++objectIt)
      if (objectIt->get()->getId() == id)
        break;
    if (objectIt == _used.end())
      return false;
    return true;
  }

  template<typename U>
  inline U&                             getUsedObjects(std::string const &id)
  {
    typename objectVector::iterator     objectIt;
    for (objectIt = _used.begin(); objectIt != _used.end(); ++objectIt)
      if (objectIt->get()->getId() == id)
        break;

    if (objectIt == _used.end())
    {
      _used.push_back(std::make_unique<U>(id));
      return (static_cast<U&>(*_used.back()));
    }
    return (static_cast<U&>(*(objectIt->get())));
  }


  void                            backToPool(const T& object)
  {
    auto objectIt = std::find_if(_used.begin(), _used.end(),
                                 [&](std::unique_ptr<T> const& obj)
                                 {
                                   return (obj.get() == &object);
                                 });
    if (objectIt == _used.end())
      return ;
    auto lastIt = _used.end() - 1;
    std::iter_swap(objectIt, lastIt);
    std::move(lastIt, lastIt, std::back_inserter(_unused));
    _used.pop_back();
  }

  inline void                            clearUnused(void)
  {
    _unused.clear();
  }
};

#endif /* !OBJECTSPOOL_HPP_ */
