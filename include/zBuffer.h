//
// Created by Саша on 09.06.2026.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>
#include <limits>

class ZBuffer {
private:
    unsigned int width;
    unsigned int height;
    std::vector<float> buffer;

public:
    ZBuffer(unsigned int w, unsigned int h) : width(w), height(h) {
        buffer.resize(width * height);
        clear();
    }
    void clear() {
        std::fill(buffer.begin(), buffer.end(), std::numeric_limits<float>::infinity());
    }
    float getZ(unsigned int x, unsigned int y) const {
        return buffer[y * width + x];
    }
    void setZ(unsigned int x, unsigned int y, float value) {
        buffer[y * width + x] = value;
    }
};
#endif //ENGINE_ZBUFFER_H
