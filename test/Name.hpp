#ifndef NAME_HPP_
# define NAME_HPP_

# include <string>
# include "Component.hpp"

class                           Name : public Component
{
  std::string                   _name;

 public:
  Name(const std::string& id, const std::string& name = "") :
    Component(id), _name(name)
  {
  }

  ~Name()
  {
  }

  inline void                   setName(const std::string& name)
  {
    _name = name;
  }

  inline const std::string&     getName(void) const
  {
    return (_name);
  }
};

#endif /* !NAME_HPP_ */
