#pragma once

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/Drawable/drawablefactory.hpp"
#include "../../Engine/TextureManager/texturemanager.hpp"
#include "TileType.hpp"
#include "EntityType.hpp"
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
        Tile() : Entity(EntityType::E_Tile){};
        void AddDrawable(TileType type);
        void AddBattalion(Battalion *bat);
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;

        bool InteractWithEntity(Entity *e) override;
    };
}