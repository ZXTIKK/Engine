#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <SFML/Window.hpp>
#include "include/simpleStruct.h"
#include "include/linMath.h"
#include "include/camera.h"
#include <cmath>

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
    bool CV = false; //for debug
    bool currentMousePosition = true;

    std::vector<int> d;

    auto camera = engine::Camera(simpleStruct::Vector{1,0,0});

    auto p = simpleStruct::Poligon{
        {0,1,0},
        {0,0,0},
        {0,0,1},
        {0,0,0},
        simpleStruct::Color{.r=255,.g=100,.b=100,.a=255},
    };
    LinMath::culcNormal(p);

    //COMPLETED
    //std::cout << "[TEST] POLIGON NORMAL " << std::endl << p << std::endl;

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Engine");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(FPS_MAX);
    sf::Vector2i windowCenter({ static_cast<int>(window.getSize().x / 2),
                            static_cast<int>(window.getSize().y / 2) });
    sf::Image image({WIDTH, HEIGHT}, sf::Color::Black);
    sf::Texture texture;
    sf::Sprite sprite(texture);

    // COMPLETED
    // std::cout << "[TEST] rotation";
    // std::cout << "H 0:\nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;
    // camera.rotateHorizontal(360);
    // std::cout << "H 360\nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;
    // camera.rotateHorizontal(180);
    // std::cout << "H 180 \nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;
    // std::cout << std::endl << std::endl;
    // std::cout << "V 0:\nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;
    // camera.rotateVertical(360);
    // std::cout << "V 360\nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;
    // camera.rotateVertical(180);
    // std::cout << "V 180 \nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;
    // camera.rotateVertical(90);
    // std::cout << "V 90 \nx: " << camera.getViewVector().x << std::endl << "y: " << camera.getViewVector().y << std::endl<< "z: " << camera.getViewVector().z << std::endl;

    unsigned x = 0;
    unsigned y = 0;
    unsigned i = 0;
    while (window.isOpen()) {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
        int deltaX = currentMousePos.x - windowCenter.x;
        int deltaY = currentMousePos.y - windowCenter.y;

        if ((deltaX != 0 || deltaY != 0) && currentMousePosition) {

            if (deltaX != 0) {
                camera.rotateHorizontal(deltaX);
                d.push_back(deltaX);
            }
            if (deltaY != 0) {
                camera.rotateVertical(deltaY);
            }
            sf::Mouse::setPosition(windowCenter, window);
        }



        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    currentMousePosition = !currentMousePosition;
                    window.setMouseCursorVisible(!currentMousePosition);
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


                // DEBUG
                if (keyPressed->code == sf::Keyboard::Key::F1) {
                    CV = !CV;
                    window.setMouseCursorVisible(CV);
                }
                if (keyPressed->code == sf::Keyboard::Key::F2) {
                    int max = 0;
                    for (int i : d) {
                        if (abs(i) > max) {
                            max = abs(i);
                        }
                    }
                    std::cout << max << std::endl;
                }
            }
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

