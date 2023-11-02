#include "texturemanager.hpp"

namespace egl
{
    TextureManager *TextureManager::pinstance_{nullptr};
    std::mutex TextureManager::mutex_;

    TextureManager *TextureManager::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new TextureManager();
        }
        return pinstance_;
    }

    sf::Texture *TextureManager::LoadTexture(const std::string &path)
    {
        if (storedTextures->count(path))
        {
            return storedTextures->at(path);
        }
        auto t = new sf::Texture();
        auto r = t->loadFromFile(path);
        std::cout << "Success loading texture? " << (r ? "True" : "False") << std::endl;
        storedTextures->insert({path, t});
        return t;
    }
}