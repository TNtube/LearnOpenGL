#pragma once
#include <cstdint>


class VertexBuffer
{
public:
	VertexBuffer(float* vertices, int size);
	void bind() const;
	void unbind() const;

private:
	uint32_t m_BufferID {};
};
