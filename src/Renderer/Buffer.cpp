#include "Buffer.hpp"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(float* vertices, int size)
{

	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setLayout(const BufferLayout &layout)
{
	m_Layout = layout;
}

const BufferLayout &VertexBuffer::getLayout() const
{
	return m_Layout;
}

IndexBuffer::IndexBuffer(uint32_t *indices, int size)
	: m_Count(size / static_cast<int>(sizeof(uint32_t)))
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
