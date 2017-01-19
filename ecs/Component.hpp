#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

# include <string>
# include "Id.hpp"

class                                   Component : public Id
{
 public:
  Component(const std::string& id) :
    Id(id)
  {
  }

  ~Component()
  {
  }
};

#endif /* !COMPONENT_HPP_ */
