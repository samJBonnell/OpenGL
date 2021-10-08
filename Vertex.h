#ifndef VERTEX_H
#define VERTEX_H

#include <array>

struct Vec2 {
    float x0, x1;
};

struct Vec3 {
    float x0, x1, x2;
};

struct Vec4 {
    float x0, x1, x2, x3;
};

struct Vertex {
    Vec3 _positions;
};

static std::array<Vertex, 4> CreateQuad(const float x, const float y) {
    constexpr float cell_size = 0.10f;
    Vertex v0, v1, v2, v3;

    // Bottom Left
    v0._positions = { x, y, 1.0f };

    // Top Left
    v1._positions = { x, y + cell_size, 1.0f };

    // Top Right
    v2._positions = { x + cell_size, y + cell_size, 1.0f };

    // Bottom Right
    v3._positions = { x + cell_size, y, 1.0f };

    return { v0, v1, v2, v3 };
}

#endif