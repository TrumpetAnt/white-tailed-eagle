#include "HealthBar.hpp"

namespace egl
{
    HealthBar::HealthBar(float hp, sf::VertexArray *vertexArray) : max_hp(hp),
                                                                   current_hp(hp),
                                                                   EgDrawable(vertexArray){};

    void HealthBar::AlterHp(float hp)
    {
        auto new_hp = std::min(std::max(current_hp + hp, 0.f), max_hp);
        if ((current_hp - new_hp) < eps)
        {
            return;
        }
        current_hp = new_hp;

        auto ratio = current_hp / max_hp;
        auto width = (*vertexArray)[1].position.x - (*vertexArray)[0].position.x;
        auto height = (*vertexArray)[2].position.y - (*vertexArray)[0].position.y;
        auto offset_x = ratio * width - width / 2;
        auto width_red = (1.f - ratio) * width;

        (*vertexArray)[6].position = sf::Vector2f(offset_x, height / -2);
        (*vertexArray)[7].position = sf::Vector2f(offset_x + width_red, height / -2);
        (*vertexArray)[8].position = sf::Vector2f(offset_x, height / 2);
        (*vertexArray)[9].position = sf::Vector2f(offset_x + width_red, height / -2);
        (*vertexArray)[10].position = sf::Vector2f(offset_x, height / 2);
        (*vertexArray)[11].position = sf::Vector2f(offset_x + width_red, height / 2);

        auto target_color = std::abs(max_hp - current_hp) < eps ? sf::Color::Transparent : sf::Color::Red;

        (*vertexArray)[6].color = target_color;
        (*vertexArray)[7].color = target_color;
        (*vertexArray)[8].color = target_color;
        (*vertexArray)[9].color = target_color;
        (*vertexArray)[10].color = target_color;
        (*vertexArray)[11].color = target_color;
    }
}
