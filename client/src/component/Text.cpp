#include "../../includes/component/Text.hh"

Text::Text(const std::string &id) : Component(id)
{
}

bool    Text::setText(unsigned int size, const std::string &str, Font &font)
{
  _string = str;
  _text.setFont(font.getFont());
  _text.setString(str);
  _text.setCharacterSize(size);
  _text.setColor(sf::Color::White);
  return true;
}

void    Text::setString(const std::string &string)
{
  _string = string;
  _text.setString(string);
}

void    Text::setColor(unsigned int r, unsigned int g, unsigned int b)
{
  _text.setColor(sf::Color(r, g, b));
}

sf::Text&   Text::getText()
{
  return _text;
}

std::string Text::getString()
{
  return _string;
}
