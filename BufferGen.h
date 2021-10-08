#ifndef BUFFERGEN_H
#define BUFFERGEN_H

#include <array>
#include "Vertex.h"

namespace BufferGen {
	std::array <uint32_t, 6>_genIndex(const uint32_t index);
	void BufferPoint(Vertex* vertexBuffer, uint32_t* indexBuffer, uint32_t pointNum);
};

#endif