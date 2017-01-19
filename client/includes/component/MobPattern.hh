//
// Created by dimitri on 12/27/16.
//

#ifndef RTYPE_MOBPATTERN_HH
#define RTYPE_MOBPATTERN_HH

#include <functional>
#include "Component.hpp"
#include "Position.hh"

class MobPattern : public Component
{
public:
  MobPattern(const std::string &id);

  void setPattern(std::function<void(PositionComponent&, PositionComponent const&)> func);
  void getPatternResult(PositionComponent &pos, PositionComponent const &origin);

private:
  std::function<void(PositionComponent &pos, PositionComponent const &origin)> _func;

};

#endif //RTYPE_MOBPATTERN_HH
