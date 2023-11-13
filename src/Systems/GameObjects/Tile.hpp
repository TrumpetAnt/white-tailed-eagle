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
        EgDrawable *outline = nullptr;
        sf::Color outlineBaseColor = sf::Color(0, 0, 0, 25);
        bool displayOutline = true;

        int height;

    public:
        Tile(sf::Vector2i pos, int height) : Entity(EntityType::E_Tile), pos(pos), height(height){};
        sf::Vector2i GetDiscretePos();

        void AddDrawable(TileType type);
        void AddBattalion(Battalion *bat);
        Battalion *GetBattalion();
        float GetMoveCost(int team);
        void ConcatDrawable(std::unordered_map<int, std::vector<EgDrawable *> *> *res) override;
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void Highlight(sf::Color color);
        void Highlight(sf::Color color, int layer);
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