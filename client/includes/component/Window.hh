#ifndef TESTSFML_WINDOWCOMPONENT_HH
#define TESTSFML_WINDOWCOMPONENT_HH


#include <SFML/Graphics/RenderWindow.hpp>
#include "../../ecs/Component.hpp"

class WindowComponent : public Component
{
public:
    WindowComponent(const std::string& id);

    sf::RenderWindow *get_win() const;
    void    CreateWindow(const std::string &name, int sizeX, int sizeY);
private:
    sf::RenderWindow    *_win;

};


#endif //TESTSFML_WINDOWCOMPONENT_HH
