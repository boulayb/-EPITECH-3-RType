#include <iostream>
#include "../../includes/component/Window.hh"

WindowComponent::WindowComponent(const std::string& id) : Component(id)
{
    _win = new sf::RenderWindow();
}

sf::RenderWindow *WindowComponent::get_win() const
{
    return _win;
}

void WindowComponent::CreateWindow(const std::string &name, int sizeX, int sizeY)
{
    _win->create(sf::VideoMode(sizeX, sizeY), name);
}
