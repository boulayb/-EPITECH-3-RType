//
// Created by Dimitri on 19/12/2016.
//

#ifndef RTYPE_IDLLOADER_HPP
#define RTYPE_IDLLOADER_HPP

#include <list>
#include <string>
#include <vector>

template <typename T>
class IDLLoader
{
public:
  virtual ~IDLLoader() {}
  virtual std::vector<T *> &getEntitiesByName(std::list<std::string> names) = 0;
};

#endif //RTYPE_IDLLOADER_HPP
