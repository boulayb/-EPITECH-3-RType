//
// Created by Dimitri on 19/12/2016.
//

#ifndef RTYPE_DLLOADER_HPP_
# define RTYPE_DLLOADER_HPP_

# include <string>
# include <dlfcn.h>
# include <dirent.h>
# include <iostream>
# include <unordered_map>

# define FILE_TYPE              ".so"

template<typename T>
class                           DLLoader
{
 public:
  typedef std::pair
  <std::string, T*>             pair;
  typedef std::unordered_map
  <std::string, T*>             map;

 private:
  std::string                   _basePath;

 public:
  DLLoader(const std::string& baseDirectory = "./entities/linux/") :
    _basePath(baseDirectory)
  {
  }

  ~DLLoader()
  {
  }

  map                           getEntitiesByName(void) const
  {
    map                         entities;
    struct dirent               *entry;
    DIR                         *dir;

    dir = opendir(_basePath.c_str());
    if (dir == nullptr)
      {
        std::cerr << "Unknow lib path : " << _basePath << std::endl;
        throw std::exception();
      }
    while ((entry = readdir(dir)) != NULL)
      {
        std::string file = entry->d_name;
        std::string type;

        try
          {
            type = file.substr(file.find_last_of("."));
          }
        catch (std::exception &e)
          {
          }

        if (type == FILE_TYPE && file.substr(0, 3) == "lib")
          {
            try
              {
                entities.insert(pair(file.substr(0, file.size() -
                                                 type.size()).erase(0, 3),
                                     loadDL(_basePath + file, "entryPoint")));
              }
            catch (std::exception &e)
              {
                std::cerr << "Loading of lib " << file
                          << " failed" << std::endl;
              }
          }
      }
    return (entities);
  }

  T*                                    loadDL(std::string const &name,
                                               std::string const &entryPoint) const
  {
    void                                *handler;
    T*                                  (*fcnptr)();

    handler = dlopen(name.c_str(), RTLD_NOW);
    if (handler == nullptr)
      throw std::exception();
    fcnptr = reinterpret_cast<T* (*)()>(dlsym(handler, entryPoint.c_str()));
    if (fcnptr == nullptr)
      throw std::exception();
    return (fcnptr());
  }
};

#endif /* RTYPE_DLLOADER_HPP_ */
