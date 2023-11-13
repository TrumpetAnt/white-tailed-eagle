cmake_minimum_required(VERSION 3.16)
project(eagle LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_executable(eagle 
    src/main.cpp 
    src/Engine/InputManager/inputmanager.cpp
    src/Engine/TextureManager/texturemanager.cpp
    src/Engine/UIManager/uimanager.cpp
    src/Engine/UIManager/GuiManager/guimanager.cpp
    src/Engine/UIManager/GuiManager/guielement.cpp
    src/Engine/UIManager/GuiManager/guielementfactory.cpp
    src/Engine/UIManager/GuiManager/fontmanager.cpp
    src/Engine/UIManager/Renderer/renderer.cpp
    src/Engine/Drawable/drawable.cpp
    src/Engine/Drawable/drawablefactory.cpp
    src/Engine/Entity/entity.cpp
    src/Engine/StateManager/state.cpp
    src/Engine/StateManager/statemanager.cpp
    src/Systems/GameObjects/Map.cpp
    src/Systems/GameObjects/MinHeap.cpp
    src/Systems/GameObjects/Tile.cpp
    src/Systems/GameObjects/Factories/EntityFactory.cpp
    src/Systems/GameObjects/Units/Battalion.cpp
    src/Systems/GameObjects/Units/BattalionProjectile.cpp
    src/Systems/GameObjects/Units/ProjectilePool.cpp
    src/Systems/GameObjects/Units/HealthBar.cpp
    src/Systems/GameObjects/CapturePoint.cpp
    src/Systems/GameObjects/TransformUtils.cpp
    src/Systems/GameObjects/Path/PathSegment.cpp
    src/Systems/GameObjects/Path/PathSegmentPool.cpp
    src/Systems/GameObjects/NoiseMap/NoiseMap.cpp
    src/Systems/GameObjects/NoiseMap/SimplexNoise/SimplexNoise.cpp
    src/Systems/Npc/Npc.cpp)
target_link_libraries(eagle PRIVATE sfml-graphics X11 ${X11_LIBRARIES})
target_compile_features(eagle PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET eagle
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:eagle>
        VERBATIM)
endif()

install(TARGETS eagle)
