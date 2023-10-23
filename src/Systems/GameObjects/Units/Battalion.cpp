#include "Battalion.hpp"

namespace egl
{
    void Battalion::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetCircle(pos);

        drawable->SetColor(sf::Color::Red);
    }
}
