#ifndef GRAPHICMODULE_FONT_HH
#define GRAPHICMODULE_FONT_HH

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../ecs/Component.hpp"

class Font : public Component
{
public:
    Font(const std::string &id);

    bool setFont(const std::string& fontPath);
    sf::Font& getFont();
private:
    sf::Font _font;
};

#endif /* GRAPHICMODULE_FONT_HH */