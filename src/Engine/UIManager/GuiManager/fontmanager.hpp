#pragma once

#include <iostream>
#include <mutex>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace egl
{

    class FontManager
    {
    private:
        static FontManager *pinstance_;
        static std::mutex mutex_;

        std::unordered_map<std::string, sf::Font *> *fonts = new std::unordered_map<std::string, sf::Font *>();

    protected:
        FontManager()
        {
        }
        ~FontManager() {}

    public:
        FontManager(FontManager &other) = delete;
        void operator=(const FontManager &) = delete;
        static FontManager *GetInstance();

        bool LoadFont(std::string path, std::string fontName);
        sf::Font *GetFont(std::string fontName);

        class Fonts
        {
        public:
            static std::string Oswald;
        };
    };
}
