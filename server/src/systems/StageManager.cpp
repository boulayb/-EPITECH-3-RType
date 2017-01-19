//
// Created by dimitri on 12/26/16.
//

#include <sstream>
#include <systems/TasksSystem.hpp>
#include "systems/StageManager.hh"

StageManager::StageManager(std::string const &fileName) : System("StageManager"), _fileName(fileName), _file(fileName), _timeStampDone(0), _started(false)
{
}

StageManager::~StageManager()
{
  _file.close();
}

std::vector<std::string> &StageManager::explode(std::string const & s, char delim)
{
  std::vector<std::string> *result = new std::vector<std::string>;
  std::istringstream iss(s);

  for (std::string token; std::getline(iss, token, delim); )
  {
    result->push_back(std::move(token));
  }

  return *result;
}

void StageManager::readStage()
{
  std::string line;
  int         lineNumber = 0;

  if (_file.is_open())
  {
    while (std::getline(_file, line))
    {
      std::vector<std::string> &values = this->explode(line, ';');
      int timestamp = 0;
      if (line != "")
      {
        try
        {
          timestamp = std::stoi(values[0]);
          bool first = true;
          for (std::string &value : values)
          {
            if (first)
            {
              first = false;
              continue;
            }
            std::vector<std::string> &entitieValues = this->explode(value, '-');
            std::string entityName = entitieValues[0];
            int entityPos = std::stoi(entitieValues[1]);
            _level[timestamp].push_back(std::pair<std::string, int>(entityName, entityPos));
          }
        }
        catch (std::exception &e)
        {
          std::cerr << "Error while reading line " << lineNumber << " of file " << _fileName << std::endl;
        }
        lineNumber++;
      }
    }
  }
  else
  {
    throw std::exception();
  }
}

std::vector<std::string > &StageManager::getEntitiesToLoad() const
{
  std::vector<std::string> *entityList = new std::vector<std::string>;
  for (auto &timestamps : _level)
  {
    for (auto &timestamp : timestamps.second)
    {
      auto it = std::find_if(entityList->begin(), entityList->end(), [timestamp] (std::string &str)
      {
        if (timestamp.first == str)
        {
          return true;
        }
        return false;
      });
      if (it == entityList->end())
        entityList->push_back(timestamp.first);
    }
  }
  return *entityList;
}

void StageManager::start()
{
  _started = true;
  _timer.reset();
}


bool StageManager::doAction(Entity& entity)
{
  (void)entity;
  if (!_started)
    return true;
 // std::cout << "elapsed" << _timer.elapsed() << std::endl;
  if (_timeStampDone < static_cast<int>(_timer.elapsed()))
  {
  //  std::cout << "New second ! " << std::endl;
    _timeStampDone = static_cast<int>(_timer.elapsed());
    auto it = _level.find(_timeStampDone);
    if (it != _level.end())
    {
      for (auto &timestamp : (*it).second)
      {
        reinterpret_cast<TasksSystem &>(engine::Instance().getObject("EventManager")).spawnEntity(timestamp.first, timestamp.second);
      }
    }
  }
  return true;
}
