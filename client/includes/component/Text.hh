#ifndef GRAPHICMODULE_TEXT_HH_HH
#define GRAPHICMODULE_TEXT_HH_HH

#include <SFML/Graphics.hpp>
#include "../../ecs/Component.hpp"
#include "Font.hh"

class Text : public Component
{
public:
    Text(const std::string& id);

    bool setText(unsigned int size, const std::string& str, Font &font);
    void setString(const std::string& string);
    std::string getString();
    void setColor(unsigned int r, unsigned int g, unsigned int b);
    sf::Text&   getText();

private:
    sf::Text _text;
  sf::String  _string;
    sf::Font _font;
};

#endif //GRAPHICMODULE_TEXT_HH_HH
