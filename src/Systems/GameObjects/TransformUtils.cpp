#include "TransformUtils.hpp"

namespace egl
{
    namespace vecop
    {
        float Magnitude(sf::Vector2f vec)
        {
            return sqrt(vec.x * vec.x + vec.y * vec.y);
        }

        float AngleBetweenVectors(sf::Vector2f a, sf::Vector2f b)
        {
            auto dot_product = a.x * b.x + a.y * b.y;
            auto theta = acos(dot_product / (Magnitude(a) * Magnitude(b)));
            return 180.f * theta / M_PI;
        }

        sf::Vector2f InBetween(sf::Vector2f a, sf::Vector2f b)
        {
            return sf::Vector2f(a.x + ((b.x - a.x) / 2), a.y + ((b.y - a.y) / 2));
        }

        void PrintVector(sf::Vector2f a)
        {
            std::cout << "("
                      << a.x
                      << ","
                      << a.y
                      << ")";
        }
    }
}
