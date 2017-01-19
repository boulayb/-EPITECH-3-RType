#ifndef COLOR_HPP_
# define COLOR_HPP_

# include <string>
# include "Component.hpp"

class                           Color : public Component
{
  std::string                   _color;

 public:
  Color(const std::string& id, const std::string& color = "") :
    Component(id), _color(color)
  {
  }

  ~Color()
  {
  }

  inline void                   setColor(const std::string& color)
  {
    _color = color;
  }

  inline const std::string&     getColor(void) const
  {
    return (_color);
  }
};

#endif /* !COLOR_HPP_ */
