#include "PathSegment.hpp"
namespace egl
{
    PathSegment::PathSegment() : Entity(EntityType::E_PathSegment)
    {
        float sqrt3 = 0.86602540378f * 2;
        auto drawable = DrawableFactory::GetRectangle(sf::Vector2f(Tile::radius * sqrt3, 10.f));
        AddDrawable(drawable);
    };

    bool PathSegment::IsDrawable()
    {
        return !hidden;
    }

    void PathSegment::Hide()
    {
        hidden = true;
    }

    void PathSegment::Show(sf::Vector2f from, sf::Vector2f to, bool angry)
    {
        hidden = false;
        auto pos = vecop::InBetween(from, to);
        setPosition(pos);
        UpdateTransforms();
        auto dir = to - from;
        auto angle = vecop::AngleBetweenVectors(sf::Vector2f(1.f, 0.f), dir);
        angle = dir.y < 0.f ? 180.f - angle : angle;
        drawable->setRotation(angle);
        drawable->SetColor(angry ? sf::Color::Red : sf::Color::Cyan);
    }
}
