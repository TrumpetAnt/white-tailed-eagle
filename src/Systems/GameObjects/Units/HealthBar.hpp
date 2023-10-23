#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Engine/Drawable/drawable.hpp"

namespace egl
{
    class HealthBar : public EgDrawable
    {
    private:
        float max_hp;
        float current_hp;

    public:
        HealthBar(float hp, sf::VertexArray *vertexArray);

        void AlterHp(float hp);

        static constexpr float eps = 0.00001f;
    };
}
