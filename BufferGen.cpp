#include "BufferGen.h"
#include <iostream>
#include <algorithm>

std::array<uint32_t, 6> BufferGen::_genIndex(const uint32_t index) {		// Function to return index elements to be loaded into memory for each quad requested to draw
	return { 0 + 4 * index, 1 + 4 * index, 3 + 4 * index, 1 + 4 * index, 2 + 4 * index, 3 + 4 * index };
}

void BufferGen::BufferPoint(Vertex *vertexBuffer, uint32_t* indexBuffer, uint32_t pointNum) {
	float x0, y0;
	std::cin >> x0 >> y0;
	auto quad = CreateQuad(x0, y0);
	auto index = _genIndex(pointNum);

	memcpy(static_cast<void*>(vertexBuffer + (quad.size() * pointNum)), static_cast<const void*>(quad.data()), quad.size() * sizeof(Vertex));
	memcpy(static_cast<void*>(indexBuffer + (index.size() * pointNum)), static_cast<const void*>(index.data()), index.size() * sizeof(uint32_t));
}