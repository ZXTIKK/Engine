#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <SFML/Window.hpp>
#include "include/simpleStruct.h"
#include "include/linMath.h"
#include "include/camera.h"
#include <cmath>

#include "include/render.h"

#ifndef WIDTH_WINDOW
#define WIDTH_WINDOW 1600
#endif

#ifndef HEIGHT_WINDOW
#define HEIGHT_WINDOW 900
#endif

#ifndef FPS_MAX
#define FPS_MAX 1000
#endif

void drawVector(sf::RenderWindow& window, const simpleStruct::Vector& VecUp , const simpleStruct::Vector& VecRight, const simpleStruct::Vector& VecView);
void lineSet(sf::RenderWindow& window);

int main() {
    const unsigned int WIDTH = WIDTH_WINDOW;
    const unsigned int HEIGHT = HEIGHT_WINDOW;
    bool CV = false; //for debug
    bool currentMousePosition = true;
    bool debugWindow = false;

    //Debug window
    sf::RenderWindow windowDebug = sf::RenderWindow(sf::VideoMode({300, 1000}), "DEBUG WINDOW");

    std::vector<int> d;

    auto camera = new engine::Camera(simpleStruct::Vector{1,0,0},simpleStruct::Point{-20,10,10});
    camera->setFOV(30);

    //COMPLETED
    //std::cout << "[TEST] POLIGON NORMAL " << std::endl << p << std::endl;

    auto* window = new sf::RenderWindow(sf::VideoMode({WIDTH, HEIGHT}), "Engine");
    window->setMouseCursorVisible(true);
    window->setFramerateLimit(FPS_MAX);
    sf::Vector2i windowCenter({ static_cast<int>(window->getSize().x / 2),
                            static_cast<int>(window->getSize().y / 2) });
    auto* image = new sf::Image({WIDTH, HEIGHT}, sf::Color::Black);
    auto* texture = new sf::Texture(*image);
    auto* sprite = new sf::Sprite(*texture);
    auto* zBuffer = new ZBuffer(WIDTH, HEIGHT);
    auto* light = new engine::Light();

    engine::Mesh mesh = engine::Mesh::getCube();

    auto* meshes = new std::vector<engine::Mesh>{mesh};
    auto* lights = new std::vector<engine::Light>{*light}; // разыменовываем одиночный light



    auto* render = new engine::Render(
        camera,
        window,
        image,
        texture,
        sprite,
        meshes,
        lights,
        zBuffer
    );

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

    while (window->isOpen()) {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition(*window);
        int deltaX = currentMousePos.x - windowCenter.x;
        int deltaY = currentMousePos.y - windowCenter.y;

        if ((deltaX != 0 || deltaY != 0) && currentMousePosition) {

            if (deltaX != 0) {
                camera->rotateHorizontal(-deltaX);
                if (d.size() > 10) {
                    d.clear();
                }
                d.push_back(deltaX);
            }
            if (deltaY != 0) {
                camera->rotateVertical(deltaY);
            }
            sf::Mouse::setPosition(windowCenter, *window);
        }



        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    currentMousePosition = !currentMousePosition;
                    window->setMouseCursorVisible(!currentMousePosition);
                }
                if (keyPressed->code == sf::Keyboard::Key::W) {
                    camera->goForward();
                }
                if (keyPressed->code == sf::Keyboard::Key::S) {
                    camera->goBack();
                }
                if (keyPressed->code == sf::Keyboard::Key::A) {
                    camera->goLeft();
                }
                if (keyPressed->code == sf::Keyboard::Key::D) {
                    camera->goRight();
                }
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    camera->goUp();
                }
                if (keyPressed->code == sf::Keyboard::Key::Z) {
                    camera->goDown();
                }


                // DEBUG
                if (keyPressed->code == sf::Keyboard::Key::F1) {
                    CV = !CV;
                    window->setMouseCursorVisible(CV);
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
                if (keyPressed->code == sf::Keyboard::Key::F3) {
                    camera->rotateHorizontal(180);
                    camera->rotateVertical(180);
                }
                if (keyPressed->code == sf::Keyboard::Key::F4) {
                    std::cout << *camera << std::endl;
                }
                if (keyPressed->code == sf::Keyboard::Key::F5) {
                    std::cout << "Len RV: " << LinMath::lenVec(camera->getRightVec()) << std::endl;
                    std::cout << "Len UV: " << LinMath::lenVec(camera->getUpVec()) << std::endl;
                    std::cout << "Len VV: " << LinMath::lenVec(camera->getViewVector()) << std::endl;
                    std::cout << "DOT RV UV: " << LinMath::dot(camera->getRightVec(), camera->getUpVec()) << std::endl;
                    std::cout << "DOT RV VV: " << LinMath::dot(camera->getViewVector(), camera->getRightVec()) << std::endl;
                    std::cout << "DOT UV VV: " << LinMath::dot(camera->getViewVector(), camera->getUpVec()) << std::endl;
                }
                if (keyPressed->code == sf::Keyboard::Key::F6) {
                    std::cout << camera->getPosition() << std::endl;
                }
                if (keyPressed->code == sf::Keyboard::Key::F12) {
                    debugWindow = !debugWindow;
                }

            }
        }

        render->renderOneFrame();

        texture->update(image->getPixelsPtr());

        if (texture->loadFromImage(*image)) {
            window->clear();
            window->draw(*sprite, sf::RenderStates(sf::BlendAlpha));
        }

        if (debugWindow) {
            if (!windowDebug.isOpen()) {
                windowDebug = sf::RenderWindow(sf::VideoMode({600, 950}), "DEBUG WINDOW");
            }
            drawVector(windowDebug,camera->getUpVec(),camera->getRightVec(),camera->getViewVector());
            windowDebug.display();
        } else {
            windowDebug.close();
        }

        window->display();
    }

    return 0;
}


void drawVector(sf::RenderWindow& window, const simpleStruct::Vector& VecUp , const simpleStruct::Vector& VecRight, const simpleStruct::Vector& VecView) {
    window.clear();

    lineSet(window);

    auto XVU = VecUp.x;
    auto YVU = VecUp.y;
    auto ZVU = VecUp.z;
    auto XVR = VecRight.x;
    auto YVR = VecRight.y;
    auto ZVR = VecRight.z;
    auto XVV = VecView.x;
    auto YVV = VecView.y;
    auto ZVV = VecView.z;

    sf::Vertex vecVVXY1[] = {
        sf::Vertex(sf::Vector2f(150,150), sf::Color::Red),
        sf::Vertex(sf::Vector2f(150+XVV*140,150+YVV*140), sf::Color::Red)
    };
    sf::Vertex vecVUXY1[] = {
        sf::Vertex(sf::Vector2f(150,150), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(150+XVU*140,150+YVU*140), sf::Color::Blue)
    };

    window.draw(vecVVXY1, 2, sf::PrimitiveType::Lines);
    window.draw(vecVUXY1, 2, sf::PrimitiveType::Lines);


    sf::Vertex vecVVYZ[] = {
        sf::Vertex(sf::Vector2f(150,450), sf::Color::Red),
        sf::Vertex(sf::Vector2f(150+YVV*140,450+ZVV*140), sf::Color::Red)
    };
    sf::Vertex vecVRYZ[] = {
        sf::Vertex(sf::Vector2f(150,450), sf::Color::Green),
        sf::Vertex(sf::Vector2f(150+YVR*140,450+ZVR*140), sf::Color::Green)
    };
    window.draw(vecVVYZ, 2, sf::PrimitiveType::Lines);
    window.draw(vecVRYZ, 2, sf::PrimitiveType::Lines);

    sf::Vertex vecVVXZ[] = {
        sf::Vertex(sf::Vector2f(150,750), sf::Color::Red),
        sf::Vertex(sf::Vector2f(150+XVV*140,750+ZVV*140), sf::Color::Red)
    };
    sf::Vertex vecVRXZ[] = {
        sf::Vertex(sf::Vector2f(150,750), sf::Color::Green),
        sf::Vertex(sf::Vector2f(150+XVR*140,750+ZVR*140), sf::Color::Green)
    };
    window.draw(vecVVXZ, 2, sf::PrimitiveType::Lines);
    window.draw(vecVRXZ, 2, sf::PrimitiveType::Lines);

    sf::Vertex vecVVYZ2[] = {
        sf::Vertex(sf::Vector2f(450,150), sf::Color::Red),
        sf::Vertex(sf::Vector2f(450+YVV*140,150+ZVV*140), sf::Color::Red)
    };
    sf::Vertex vecVUYZ[] = {
        sf::Vertex(sf::Vector2f(450,150), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(450+YVR*140,150+ZVR*140), sf::Color::Blue)
    };
    window.draw(vecVVYZ2, 2, sf::PrimitiveType::Lines);
    window.draw(vecVUYZ, 2, sf::PrimitiveType::Lines);

    sf::Vertex vecVUXY2[] = {
        sf::Vertex(sf::Vector2f(450,450), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(450+XVU*140,450+YVU*140), sf::Color::Blue)
    };
    sf::Vertex vecVRXY2[] = {
        sf::Vertex(sf::Vector2f(450,450), sf::Color::Green),
        sf::Vertex(sf::Vector2f(450+XVR*140,450+YVR*140), sf::Color::Green)
    };
    window.draw(vecVUXY2, 2, sf::PrimitiveType::Lines);
    window.draw(vecVRXY2, 2, sf::PrimitiveType::Lines);

    sf::Vertex vecVUXZ2[] = {
        sf::Vertex(sf::Vector2f(450,750), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(450+XVU*140,750+ZVU*140), sf::Color::Blue)
    };
    sf::Vertex vecVRXZ2[] = {
        sf::Vertex(sf::Vector2f(450,750), sf::Color::Green),
        sf::Vertex(sf::Vector2f(450+XVR*140,750+ZVR*140), sf::Color::Green)
    };
    window.draw(vecVUXZ2, 2, sf::PrimitiveType::Lines);
    window.draw(vecVRXZ2, 2, sf::PrimitiveType::Lines);

}

void lineSet(sf::RenderWindow& window) {
    sf::Vertex VecField1[] = {
        sf::Vertex(sf::Vector2f(0,300), sf::Color::White),
        sf::Vertex(sf::Vector2f(600,300), sf::Color::White),
    };
    sf::Vertex VecField2[] = {
        sf::Vertex(sf::Vector2f(0,600), sf::Color::White),
        sf::Vertex(sf::Vector2f(600,600), sf::Color::White),
    };

    sf::Vertex VecField3[] = {
        sf::Vertex(sf::Vector2f(300,0), sf::Color::White),
        sf::Vertex(sf::Vector2f(300,900), sf::Color::White),
    };
    sf::Vertex VecField4[] = {
        sf::Vertex(sf::Vector2f(0,900), sf::Color::White),
        sf::Vertex(sf::Vector2f(600,900), sf::Color::White),
    };
    window.draw(VecField1, 2, sf::PrimitiveType::Lines);
    window.draw(VecField2, 2, sf::PrimitiveType::Lines);
    window.draw(VecField3, 2, sf::PrimitiveType::Lines);
    window.draw(VecField4, 2, sf::PrimitiveType::Lines);

    //color coding of vectors
    sf::Vertex litterV1[] = {
        sf::Vertex(sf::Vector2f(20,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(25,930), sf::Color::White),
    };
    sf::Vertex litterV2[] = {
        sf::Vertex(sf::Vector2f(25,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(30,920), sf::Color::White),
    };
    window.draw(litterV1, 2, sf::PrimitiveType::Lines);
    window.draw(litterV2, 2, sf::PrimitiveType::Lines);

    sf::Vertex litterV3[] = {
        sf::Vertex(sf::Vector2f(31,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(36,930), sf::Color::White),
    };
    sf::Vertex litterV4[] = {
        sf::Vertex(sf::Vector2f(36,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(41,920), sf::Color::White),
    };
    window.draw(litterV3, 2, sf::PrimitiveType::Lines);
    window.draw(litterV4, 2, sf::PrimitiveType::Lines);
    //------- VR
    sf::Vertex litterVV1[] = {
        sf::Vertex(sf::Vector2f(150,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(155,930), sf::Color::White),
    };
    sf::Vertex litterVV2[] = {
        sf::Vertex(sf::Vector2f(155,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(160,920), sf::Color::White),
    };
    window.draw(litterVV1, 2, sf::PrimitiveType::Lines);
    window.draw(litterVV2, 2, sf::PrimitiveType::Lines);

    sf::Vertex litterR1[] = {
        sf::Vertex(sf::Vector2f(162,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(172,920), sf::Color::White),
    };
    sf::Vertex litterR2[] = {
        sf::Vertex(sf::Vector2f(162,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(162,920), sf::Color::White),
    };
    sf::Vertex litterR3[] = {
        sf::Vertex(sf::Vector2f(172,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(162,925), sf::Color::White),
    };
    sf::Vertex litterR4[] = {
        sf::Vertex(sf::Vector2f(162,925), sf::Color::White),
        sf::Vertex(sf::Vector2f(172,925), sf::Color::White),
    };
    sf::Vertex litterR5[] = {
        sf::Vertex(sf::Vector2f(172,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(172,925), sf::Color::White),
    };
    window.draw(litterR1, 2, sf::PrimitiveType::Lines);
    window.draw(litterR2, 2, sf::PrimitiveType::Lines);
    window.draw(litterR3, 2, sf::PrimitiveType::Lines);
    window.draw(litterR4, 2, sf::PrimitiveType::Lines);
    window.draw(litterR5, 2, sf::PrimitiveType::Lines);
    //-------
    sf::Vertex litterVVV1[] = {
        sf::Vertex(sf::Vector2f(300,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(305,930), sf::Color::White),
    };
    sf::Vertex litterVVV2[] = {
        sf::Vertex(sf::Vector2f(305,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(310,920), sf::Color::White),
    };
    sf::Vertex litterU1[] = {
        sf::Vertex(sf::Vector2f(312,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(312,930), sf::Color::White),
    };
    sf::Vertex litterU2[] = {
        sf::Vertex(sf::Vector2f(312,930), sf::Color::White),
        sf::Vertex(sf::Vector2f(322,930), sf::Color::White),
    };
    sf::Vertex litterU3[] = {
        sf::Vertex(sf::Vector2f(322,920), sf::Color::White),
        sf::Vertex(sf::Vector2f(322,930), sf::Color::White),
    };
    window.draw(litterVVV1, 2, sf::PrimitiveType::Lines);
    window.draw(litterVVV2, 2, sf::PrimitiveType::Lines);
    window.draw(litterU1, 2, sf::PrimitiveType::Lines);
    window.draw(litterU2, 2, sf::PrimitiveType::Lines);
    window.draw(litterU3, 2, sf::PrimitiveType::Lines);

    //set color for this Vec
    sf::Vertex VV[] = {
        sf::Vertex(sf::Vector2f(50,925), sf::Color::Red),
        sf::Vertex(sf::Vector2f(100,925), sf::Color::Red)
    };
    window.draw(VV, 2, sf::PrimitiveType::Lines);

    sf::Vertex RV[] = {
        sf::Vertex(sf::Vector2f(180,925), sf::Color::Green),
        sf::Vertex(sf::Vector2f(230,925), sf::Color::Green)
    };
    window.draw(RV, 2, sf::PrimitiveType::Lines);

    sf::Vertex UV[] = {
        sf::Vertex(sf::Vector2f(330,925), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(380,925), sf::Color::Blue)
    };
    window.draw(UV, 2, sf::PrimitiveType::Lines);
}