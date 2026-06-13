//
// Created by Саша on 09.06.2026.
//
#include "../include/render.h"

namespace engine {
    Render::Render(
        Camera* camera,
        sf::RenderWindow* window,
        sf::Image* image,
        sf::Texture* texture,
        sf::Sprite* sprite,
        std::vector<Mesh>* meshes,
        std::vector<Light>* lights,
        ZBuffer* zBuffer
    ) : camera(camera),
        window(window),
        image(image),
        texture(texture),
        sprite(sprite),
        meshes(meshes),
        lights(lights),
        zBuffer(zBuffer)
    {
        this->f = WIDTH_WINDOW/(2*tan(LinMath::conversionToRadian(camera->getFOV())/2));
        this->cx = WIDTH_WINDOW / 2;
        this->cy = HEIGHT_WINDOW / 2;
    }

    void Render::clearScreen() {
        for (unsigned int y = 0; y < HEIGHT_WINDOW; ++y) {
            for (unsigned int x = 0; x < WIDTH_WINDOW; ++x) {
                this->image->setPixel({x, y}, sf::Color::Black);
            }
        }
    }


    void Render::renderOneFrame() {
        clearScreen();
        zBuffer->clear();

        for (const auto& mesh : *meshes) {
            for (const auto& poly : mesh.getPolygons()) {
                if ((poly.normal * simpleStruct::Vector(
                    {
                        this->camera->getPosition().x,
                        this->camera->getPosition().y,
                        this->camera->getPosition().z
                    }))<=0.f) {
                    continue;
                }

                std::optional<simpleStruct::Point2D> p0 = LinMath::projectPoint(
                    poly.point1,
                    this->camera->getPosition(),
                    this->camera->getViewVector(),
                    this->camera->getUpVec(),
                    this->camera->getRightVec(),
                    this->f,
                    WIDTH_WINDOW,HEIGHT_WINDOW
                    );
                std::optional<simpleStruct::Point2D> p1 = LinMath::projectPoint(
                    poly.point2,
                    this->camera->getPosition(),
                    this->camera->getViewVector(),
                    this->camera->getUpVec(),
                    this->camera->getRightVec(),
                    this->f,
                    WIDTH_WINDOW,HEIGHT_WINDOW
                );
                std::optional<simpleStruct::Point2D> p2 = LinMath::projectPoint(
                    poly.point3,
                    this->camera->getPosition(),
                    this->camera->getViewVector(),
                    this->camera->getUpVec(),
                    this->camera->getRightVec(),
                    this->f,
                    WIDTH_WINDOW,HEIGHT_WINDOW
                );

                if (p0 == std::nullopt || p1 == std::nullopt || p2 == std::nullopt ) {
                    continue;
                }

                int minX = std::max(0, std::min({p0->x, p1->x, p2->x}));
                int maxX = std::min(WIDTH_WINDOW - 1, std::max({p0->x, p1->x, p2->x}));
                int minY = std::max(0, std::min({p0->y, p1->y, p2->y}));
                int maxY = std::min(HEIGHT_WINDOW - 1, std::max({p0->y, p1->y, p2->y}));

                for (int y = minY; y <= maxY; ++y) {
                    for (int x = minX; x <= maxX; ++x) {

                        if (LinMath::isPixelInsideTriangle(x, y, *p0, *p1, *p2)) {

                            float currentZ = LinMath::calculateDepth(x, y, *p0, *p1, *p2,p0->z, p1->z, p2->z);

                            if (currentZ < zBuffer->getZ(x, y)) {
                                zBuffer->setZ(x, y, currentZ);

                                image->setPixel({static_cast<unsigned>(x), static_cast<unsigned>(y)}, sf::Color(poly.color.r, poly.color.g, poly.color.b, poly.color.a));
                            }
                        }
                    }
                }
            }
        }
    }


}
