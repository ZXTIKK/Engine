cmake_minimum_required(VERSION 3.24)
project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.0.2
)

set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOC OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(SFML)

add_executable(CppProject main.cpp
        include/linMath.h
        include/simpleStruct.h
        include/mesh.h
        include/camera.h
        src/camera.cpp
        src/Mesh.cpp
        include/light.h)

target_link_libraries(CppProject PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)