//
// Created by dimitri on 12/26/16.
//

#ifndef RTYPE_STAGEMANAGER_HH
#define RTYPE_STAGEMANAGER_HH

#include <iostream>
#include <fstream>
#include <map>
#include "Timer.hpp"
#include "Engine.hpp"

class StageManager : public System
{
public:
  StageManager(std::string const &fileName);
  ~StageManager();
  void readStage();
  std::vector<std::string > &getEntitiesToLoad() const;
  bool doAction(Entity& entity);
  void start();
private:
  std::vector<std::string> &explode(std::string const & s, char delim);
private:
  std::string   _fileName;
  std::ifstream _file;
  std::map<int, std::vector<std::pair<std::string, int>>>  _level;
  Timer         _timer;
  int           _timeStampDone;
  bool          _started;
};

#endif //RTYPE_STAGEMANAGER_HH
