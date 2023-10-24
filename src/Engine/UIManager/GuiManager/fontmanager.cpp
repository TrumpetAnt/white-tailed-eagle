#include "fontmanager.hpp"

namespace egl
{
    FontManager *FontManager::pinstance_{nullptr};
    std::mutex FontManager::mutex_;

    FontManager *FontManager::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new FontManager();
        }
        return pinstance_;
    }

    bool FontManager::LoadFont(std::string path, std::string fontName)
    {
        auto font = new sf::Font();

        if (!font->loadFromFile(path + fontName))
        {
            std::cout << "Unable to load font from path: " << path << std::endl;
            return false;
        }

        fonts->insert({fontName, font});

        return true;
    }

    sf::Font *FontManager::GetFont(std::string fontName)
    {
        return fonts->count(fontName) > 0
                   ? fonts->at(fontName)
                   : nullptr;
    }

    std::string FontManager::Fonts::Oswald = "Oswald-VariableFont_wght.ttf";
}
