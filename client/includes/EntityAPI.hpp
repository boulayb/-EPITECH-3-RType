#ifndef ENTITYAPI_HPP_
# define ENTITYAPI_HPP_

# include <string>
# include "Entity.hpp"

class                   EntityAPI
{
 public:
  EntityAPI()
  {
  }

  virtual ~EntityAPI()
  {
  }

  virtual Entity&       createEntity(void);
};

#endif /* !ENTITYAPI_HPP_ */
