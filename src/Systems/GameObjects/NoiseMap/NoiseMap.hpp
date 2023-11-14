#pragma

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"
#include "SimplexNoise/SimplexNoise.hpp"

namespace egl
{
    class NoiseMap : public Entity
    {
    protected:
        SimplexNoise noiseMachine;
        sf::Vector2i size;
        float scale;
        float *calculatedValues;

        sf::Image *GenerateNoiseImage();

        void AddDrawable();

    public:
        NoiseMap();
        NoiseMap(sf::Vector2i size);

        float ValAt(sf::Vector2i pos);
        float CalcAt(sf::Vector2f pos);
    };
}
