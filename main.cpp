#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <SFML/Window.hpp>
#include "include/simpleStruct.h"
#include "include/linMath.h"
#include "include/camera.h"
#ifndef WIDTH_WINDOW
#define WIDTH_WINDOW 1600
#endif
#ifndef HEIGHT_WINDOW
#define HEIGHT_WINDOW 900
#endif
#ifndef FPS_MAX
#define FPS_MAX 1000
#endif
int main() {
    const unsigned int WIDTH = WIDTH_WINDOW;
    const unsigned int HEIGHT = HEIGHT_WINDOW;
    auto camera = engine::Camera(simpleStruct::Vector{1,0,0});

    auto p = simpleStruct::Poligon{
        {0,1,0},
        {0,0,0},
        {0,0,1},
        {0,0,0},
        simpleStruct::Color{.r=255,.g=100,.b=100,.a=255},
    };
    LinMath::culcNormal(p);
    std::cout << "[TEST] POLIGON NORMAL " << std::endl << p << std::endl;

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Engine");
    window.setFramerateLimit(FPS_MAX);
    sf::Image image({WIDTH, HEIGHT}, sf::Color::Black);
    sf::Texture texture;
    sf::Sprite sprite(texture);
    unsigned x = 0;
    unsigned y = 0;
    unsigned i = 0;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                if (keyPressed->code == sf::Keyboard::Key::W) {
                    camera.goForward();
                }
                if (keyPressed->code == sf::Keyboard::Key::S) {
                    camera.goBack();
                }
                if (keyPressed->code == sf::Keyboard::Key::A) {
                    camera.goLeft();
                }
                if (keyPressed->code == sf::Keyboard::Key::D) {
                    camera.goRight();
                }
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    camera.goUp();
                }
                if (keyPressed->code == sf::Keyboard::Key::LShift) {
                    camera.goDown();
                }
            }
        }


        //image.setPixel({x, y}, sf::Color::Black);
        if (x < WIDTH-1) {
            x++;
        }else {
            x = 0;
        }
        if (y < HEIGHT-1) {
            y=HEIGHT-1-(((x+camera.getPosition().x-WIDTH/2)*(x+camera.getPosition().x-WIDTH/2))/500);
            if (y > HEIGHT-1) {
                y=HEIGHT-1;
            }
        }else {
            y = 0;
        }
        image.setPixel({x, y}, sf::Color::Red);

        if (texture.loadFromImage(image)) {
            sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture.getSize())));
        }

        window.clear();
        window.draw(sprite);
        window.display();
        simpleStruct::Vector viewVector = camera.getViewVector();
        simpleStruct::Point cameraPosition = camera.getPosition();
       // std::cout << "coord camera:" << std::endl;
       // std::cout << "x: " << cameraPosition.x << std::endl << "y: " << cameraPosition.y << std::endl << "z: " << cameraPosition.z << std::endl;
    }

    return 0;
}

