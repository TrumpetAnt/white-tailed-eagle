#include "NoiseMap.hpp"

namespace egl
{

    NoiseMap::NoiseMap() : Entity(EntityType::E_NoiseMap)
    {
        size = sf::Vector2i(1316, 720);
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
        auto noise = GenerateNoiseImage();
        auto tex = new sf::Texture();
        tex->loadFromImage(*noise);

        auto factor = 500.f / size.x;

        auto worldSize = sf::Vector2(500.f, size.y * factor);
        drawable = DrawableFactory::GetRectangle(worldSize, sf::Vector2f(size));
        drawable->SetTexture(tex);
        drawable->SetLayer(5);
    }

    sf::Image *NoiseMap::GenerateNoiseImage()
    {
        auto pixels = new sf::Uint8[size.x * 4 * size.y];
        calculatedValues = new float[size.x * size.y];

        scale = 0.0012f;
        noiseMachine = SimplexNoise(scale);

        for (int j = 0; j < size.y; j++)
        {
            for (int i = 0; i < size.x; i++)
            {
                auto _i = i * 4 + j * size.x * 4;
                // auto noise = SimplexNoise::noise(i * scale, j * scale) * 0.5f + 0.5f;
                auto noise = noiseMachine.fractal(2, i, j) * 0.5f + 0.5f;
                auto val = (unsigned int)std::round(noise * 255.f);
                calculatedValues[i + j * size.x] = noise;
                pixels[_i + 0] = val;
                pixels[_i + 1] = val;
                pixels[_i + 2] = val;
                pixels[_i + 3] = 255;
            }
        }

        auto image = new sf::Image();

        image->create(size.x, size.y, pixels);

        return image;
    }

    float NoiseMap::ValAt(sf::Vector2i pos)
    {
        if (pos.x < 0 || pos.y < 0 || size.x < pos.x + 1 || size.y < pos.y + 1)
        {
            return -1.f;
        }
        return calculatedValues[pos.x + pos.y * size.x];
    }

    float NoiseMap::CalcAt(sf::Vector2f pos)
    {
        return noiseMachine.noise(pos.x * scale, pos.y * scale) * 0.5f + 0.5f;
    }
}
