#pragma

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"
#include "SimplexNoise/SimplexNoise.hpp"

namespace egl
{
    class NoiseMap : public Entity
    {
    protected:
        sf::Vector2i size;
        float *calculatedValues;

        sf::Image *GenerateNoiseImage();

        void AddDrawable();

    public:
        NoiseMap();
        NoiseMap(sf::Vector2i size);

        float ValAt(sf::Vector2i pos);
    };
}
