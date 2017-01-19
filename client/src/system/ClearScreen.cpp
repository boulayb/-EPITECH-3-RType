#include "../../includes/system/ClearScreen.hh"

bool SystemClearScreen::doAction(Entity &entity){
    ECSMap<Component> &components = entity.getComponents();
    try
    {
        WindowComponent &win = components.getObject<WindowComponent>("Window");

        win.get_win()->clear(sf::Color(25, 0, 25));
        //win.get_win()->clear(sf::Color(rand()%255, rand()%255, rand()%255));
    }
    catch (const std::out_of_range& err)
    {
        return (false);
    }
    return (true);
}
