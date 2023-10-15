cmake_minimum_required(VERSION 3.16)
project(eagle LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(eagle 
    src/main.cpp 
    src/InputManager/inputmanager.cpp)
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
