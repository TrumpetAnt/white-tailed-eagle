#pragma once

#include <mutex>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

namespace egl
{
    class TextureManager
    {
    private:
        static TextureManager *pinstance_;
        static std::mutex mutex_;
        std::unordered_map<std::string, sf::Texture *> *storedTextures = new std::unordered_map<std::string, sf::Texture *>();

    protected:
        TextureManager()
        {
        }
        ~TextureManager() {}

    public:
        TextureManager(TextureManager &other) = delete;
        void operator=(const TextureManager &) = delete;
        static TextureManager *GetInstance();

        sf::Texture *LoadTexture(const std::string &path);
    };
}