//
// Created by danilo_d on 30/11/16.
//

#ifndef RTYPE_SPACE_HH
#define RTYPE_SPACE_HH

#include <string>
//#include "EntityPool.hh"

class Space
{
public:
  Space(std::string const &name);
  ~Space();
  std::string const& getName() const;
//  EntityPool &getEntityPool() const;
private:
  std::string _name;
//  EntityPool _pool;
};

#endif //RTYPE_SPACE_HH
