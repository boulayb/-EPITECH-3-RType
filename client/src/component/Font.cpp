#include "../../includes/component/Font.hh"

Font::Font(const std::string& id) : Component(id)
{
}

bool Font::setFont(const std::string& fontPath)
{
    if (!_font.loadFromFile(fontPath))
    {
        std::cerr << "Cannot load " << fontPath << std::endl;
        return false;
    }
    return true;
}

sf::Font&    Font::getFont()
{
    return _font;
}
