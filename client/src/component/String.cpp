//
// Created by salnik_a on 27/12/16.
//

#include "../../includes/component/String.hh"

String::String(const std::string &id) : Component(id)
{

}

std::string&    String::getString()
{
  return _string;
}

void  String::setString(const std::string &string)
{
  _string  = string;
}