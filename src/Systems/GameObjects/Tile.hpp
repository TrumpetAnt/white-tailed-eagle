#pragma once

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/Drawable/drawablefactory.hpp"
#include "../../Engine/TextureManager/texturemanager.hpp"
#include "TileType.hpp"
#include "Units/Battalion.hpp"

namespace egl
{
    class Tile : public Entity
    {
    private:
        TileType tileType;
        Battalion *battalion = nullptr;
        sf::Color baseColor = sf::Color::Magenta;

    public:
        void AddDrawable(TileType type);
        void AddBattalion(Battalion *bat);
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;
        bool IsSelectable() override;
        bool AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;
    };
}