//
// Created by dimitri on 12/24/16.
//

#ifndef RTYPE_SYSTEMFACTORY_HH
#define RTYPE_SYSTEMFACTORY_HH

#include "Engine.hpp"
#include "Graphics.hh"
#include "system/Network.hh"

class SystemFactory
{
public:
  SystemFactory();
  ~SystemFactory();
  bool createGraphics(std::string const &windowName, int sizeX, int sizeY);
  bool createNetwork(std::string const &ip, unsigned short port, std::string const &name);
  void createBack(const std::string &filePath, int x, int y, int sizeX, int sizeY, float speed, bool loop, const std::string& loopType = "BackgroundLoop");
  void createPlayer(const std::string &filePath, int x, int y, int sizeX, int sizeY);
  void createMonster(const std::string & mob, int y);
  void createOtherPlayer(int color, int x, int y, const std::string &id);
  void createText(const std::string& font, const std::string& str, int size, int x, int y, int r, int g, int b, const std::string& id);
  WindowComponent *getWin();
private:
  WindowComponent *_win;
};

#endif //RTYPE_SYSTEMFACTORY_HH
