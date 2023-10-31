#include "CapturePoint.hpp"

namespace egl
{
    sf::Color TeamToColor(int team);
    CapturePoint::CapturePoint(int team) : team(team), Entity(E_CapturePoint) {}

    void CapturePoint::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetTriangle(sf::Vector2f(CapturePoint::radius * 2, CapturePoint::radius * 2));
        drawable->setPosition(pos);
        drawable->setRotation(180);
        drawable->SetColor(TeamToColor(team));
    }
}
