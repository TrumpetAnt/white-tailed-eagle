# Portfolio Project

Hi there,
I've built a simple game in C++ using the SFML-library.

This project is meant to be a learning exercise and demostrate games programming fundamentals.

Here is some of what you can find in the project:

- OOP patterns such as singleton and factories ([StateManager.cpp](/src/Engine/StateManager/statemanager.hpp), [DrawableFactory.cpp](/src/Engine/Drawable/drawablefactory.cpp))
- Simple AI-programming and pathfinding with A\* ([Map.cpp](https://github.com/TrumpetAnt/white-tailed-eagle/blob/fc4349c6602327c8f6e53b84142efbfa42f70b17/src/Systems/GameObjects/Map.cpp#L276))
- Seperation of logic into game engine such as drawable objects, game entities, input handling, UI framework, texture loading ([Engine](/src/Engine/))
- Object pooling ([PathSegmentPool.hpp](/src/Systems/GameObjects/Path/PathSegmentPool.hpp))
- Map generation with simplex noise ([EntityFactory.cpp](https://github.com/TrumpetAnt/white-tailed-eagle/blob/fc4349c6602327c8f6e53b84142efbfa42f70b17/src/Systems/GameObjects/Factories/EntityFactory.cpp#L23))

## How to build and run

### Build

Follow `cmake_README.md` for instruction on how to build and what needs to be installed.
No additional requirements.

### Run

You need to download and place assets in the assets folder manually (I don't want to distribute licensed material through github...).

For these, just extract the zip but keep top level folder like this
`/assets/img/kenney_tiny-battle/`.

https://kenney.nl/assets/hexagon-pack \
https://kenney.nl/assets/tiny-battle

For the font you place a single file in the fonts folder like this:
`/assets/fonts/Oswald-VariableFont_wght.tff`

https://fonts.google.com/specimen/Oswald

## Assets

### Textures

https://kenney.nl/assets/hexagon-pack
https://kenney.nl/assets/tiny-battle

### Fonts

https://fonts.google.com/specimen/Oswald

## Gameplay planned

### Tactic battle features

- Battalion
- Artillery
- CAS
- AA
- Fog of war
- Terrain
  - Rivers
  - Cliffs
  - Elevation
  - Terrain features
    - Forested
    - Urban
    - Defensive structure
- AI opponent

### Strategic map features

- Resources
  - Material
  - Electric
  - Transportation
    - Road
    - Ship
    - Railway
  - Internet
  - Telecommunications
- Seasons / Weather
- Armies
- Cities
- Countries
- Industries
- Elevation

### Strategic interactions

- Plan for wartime
- Secure resources through exploitation or trade
- Ensure logistics by infrastructure
- Develop alliances and Foster international relations
