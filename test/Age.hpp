#ifndef AGE_HPP_
# define AGE_HPP_

# include <string>
# include "Component.hpp"

class                           Age : public Component
{
  int                           _age;

 public:
  Age(const std::string& id, int age = 0) :
    Component(id), _age(age)
  {
  }

  ~Age()
  {
  }

  inline void                   setAge(int age)
  {
    _age = age;
  }

  inline int                    getAge(void) const
  {
    return (_age);
  }
};

#endif /* !AGE_HPP_ */
