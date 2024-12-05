#include "CapturePoint.hpp"

namespace egl
{
    sf::Color TeamToColor(int team);
    CapturePoint::CapturePoint(int team) : team(team), Entity(E_CapturePoint) {}

    void CapturePoint::AddDrawable()
    {
        auto pos = this->getPosition();
        auto scale = 1.5f;
        auto texSize = sf::Vector2f(18, 38);
        drawable = DrawableFactory::GetRectangle(texSize * scale, texSize);

        auto tm = TextureManager::GetInstance();
        auto texture = tm->LoadTexture("assets/img/kenney_tiny-battle/Tiles/tile_0071.png");
        drawable->SetTexture(texture);
        drawable->setPosition(pos);
        auto color = team == 0 ? sf::Color(255, 128, 128) : sf::Color(70, 120, 255);
        drawable->SetColor(sf::Color::White);
    }
}
