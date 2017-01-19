//
// Created by Dimitri on 19/12/2016.
//

#ifndef RTYPE_DLLOADER_HPP_
# define RTYPE_DLLOADER_HPP_

# include <iostream>
# include <windows.h>
# include <unordered_map>
# include <cstring>
# define FILE_TYPE              ".dll"

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

  std::string                   executable_directory_path(void) const
  {
    std::vector<char>           full_path_exe(MAX_PATH);

    for (;;)
      {
        const DWORD result = GetModuleFileName(NULL,
                                               &full_path_exe[0],
                                               full_path_exe.size());
        if (result == 0)
          {
            throw std::exception();
          }
        else if (full_path_exe.size() == result)
          {
            full_path_exe.resize(full_path_exe.size() * 2);
          }
        else
          {
            break;
          }
      }
    std::string result(full_path_exe.begin(), full_path_exe.end());
    std::string::size_type i = result.find_last_of("\\/");
    if (std::string::npos != i)
      result.erase(i);
    return result;
  }

public:
  DLLoader(const std::string& baseDirectory = "./entities/windows/")
  {
    _basePath = executable_directory_path();
    _basePath += baseDirectory;
  }

  ~DLLoader()
  {
  }

  map                                   getEntitiesByName(void) const
  {
    map                                 entities;
    WIN32_FIND_DATA                     search_data;

    std::memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
    HANDLE handle = FindFirstFile(_basePath.c_str(), &search_data);
    while (handle != INVALID_HANDLE_VALUE)
      {
        std::string file = search_data.cFileName;
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
        if (FindNextFile(handle, &search_data) == FALSE)
          break;
      }
    FindClose(handle);
    return (entities);
  }

  T*                                    loadDL(std::string const &name,
                                               std::string const &entryPoint) const
  {
    T                                   *(*fcnptr)();

    HINSTANCE hGetProcIDDLL = ::LoadLibrary(name.c_str());
    if (hGetProcIDDLL == nullptr)
      throw std::exception();
    fcnptr = reinterpret_cast<T*  (*)()>(::GetProcAddress(hGetProcIDDLL,
                                                          entryPoint.c_str()));
    if (fcnptr == nullptr)
      throw std::exception();
    return fcnptr();
  }
};

#endif /* RTYPE_DLLOADER_HPP_ */
