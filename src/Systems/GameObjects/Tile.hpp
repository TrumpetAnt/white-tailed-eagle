#pragma once

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/Drawable/drawablefactory.hpp"
#include "../../Engine/TextureManager/texturemanager.hpp"
#include "TileType.hpp"
#include "EntityType.hpp"
#include "Units/Battalion.hpp"

namespace egl
{
    class Map;
    class StateManager;

    class Tile : public Entity
    {
    protected:
        TileType tileType;
        Battalion *battalion = nullptr;
        sf::Color baseColor = sf::Color::Magenta;
        sf::Vector2i pos;
        int moveCost = 1;

    public:
        Tile(sf::Vector2i pos) : Entity(EntityType::E_Tile), pos(pos){};
        sf::Vector2i GetDiscretePos();

        void AddDrawable(TileType type);
        void AddBattalion(Battalion *bat);
        Battalion *GetBattalion();
        int GetMoveCost();
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;
        void AlternateHighlight();

        bool InteractWithEntity(Entity *selected) override;
        void ClearBattalion();

        float SqrDistanceToTile(const Tile &other);

        void Hover() override;
        void StopHover() override;

        static constexpr float radius = 40;
    };
}