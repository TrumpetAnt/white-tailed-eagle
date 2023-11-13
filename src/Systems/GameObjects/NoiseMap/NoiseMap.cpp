#include "NoiseMap.hpp"

namespace egl
{

    NoiseMap::NoiseMap() : Entity(EntityType::E_NoiseMap)
    {
        size = sf::Vector2i(500, 500);
        AddDrawable();
        SetPosition(sf::Vector2f(-200.f, 200.f));
    }

    NoiseMap::NoiseMap(sf::Vector2i size) : Entity(EntityType::E_NoiseMap), size(size)
    {
        AddDrawable();
        SetPosition(sf::Vector2f(-200.f, 200.f));
    }

    void NoiseMap::AddDrawable()
    {
        size = sf::Vector2i(500, 200);

        auto noise = GenerateNoiseImage();
        auto tex = new sf::Texture();
        tex->loadFromImage(*noise);

        auto floatSize = sf::Vector2f(size);
        drawable = DrawableFactory::GetRectangle(floatSize, floatSize);
        drawable->SetTexture(tex);
        drawable->SetLayer(5);
    }

    sf::Image *NoiseMap::GenerateNoiseImage()
    {
        auto pixels = new sf::Uint8[size.x * 4 * size.y];

        auto scale = 0.0025f;
        auto noiseMachine = SimplexNoise(scale);

        for (int j = 0; j < size.y; j++)
        {
            for (int i = 0; i < size.x; i++)
            {
                auto _i = i * 4 + j * size.x * 4;
                // auto noise = SimplexNoise::noise(i * scale, j * scale) * 0.5f + 0.5f;
                auto noise = noiseMachine.fractal(2, i, j) * 0.5f + 0.5f;
                pixels[_i + 0] = (unsigned int)std::round(noise * 255.f);
                pixels[_i + 1] = pixels[_i + 0];
                pixels[_i + 2] = pixels[_i + 0];
                pixels[_i + 3] = 255;
            }
        }

        auto image = new sf::Image();

        image->create(size.x, size.y, pixels);

        return image;
    }
}
