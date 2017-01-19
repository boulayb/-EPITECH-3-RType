//
// Created by dimitri on 12/27/16.
//

#include "component/MobPattern.hh"

MobPattern::MobPattern(const std::string &id) : Component(id)
{

}

void MobPattern::setPattern(std::function<void(PositionComponent&, PositionComponent const&)> func)
{
  _func = func;
}

void MobPattern::getPatternResult(PositionComponent &pos, PositionComponent const &origin)
{
  _func(pos, origin);
}