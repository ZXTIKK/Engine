//
// Created by Саша on 09.06.2026.
//

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#ifndef WIDTH_WINDOW
#define WIDTH_WINDOW 1600
#endif

#ifndef HEIGHT_WINDOW
#define HEIGHT_WINDOW 900
#endif

#ifndef FPS_MAX
#define FPS_MAX 1000
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//Math
#include "linMath.h"

//struct
#include "simpleStruct.h"
#include "zBuffer.h"

//object for render
#include "camera.h"
#include "light.h"
#include "mesh.h"
namespace engine {

    class Render {
    private:
        Camera* camera;
        sf::RenderWindow* window;
        sf::Image* image;
        sf::Texture* texture;
        sf::Sprite* sprite;
        std::vector<Mesh>* meshes;
        std::vector<Light>* lights;
        ZBuffer* zBuffer;
        float f;
        int cx;
        int cy;
        int i = 0;

        void clearScreen();
        void clearZBuffer();
    public:
        Render(
            Camera* camera,
            sf::RenderWindow* window,
            sf::Image* image,
            sf::Texture* texture,
            sf::Sprite* sprite,
            std::vector<Mesh>* meshes,
            std::vector<Light>* lights,
            ZBuffer* zBuffer

        );
        ~Render() = default;

        void renderOneFrame();
    };
}

#endif //ENGINE_RENDER_H
