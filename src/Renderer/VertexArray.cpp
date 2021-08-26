#include "VertexArray.hpp"
#include <glad/glad.h>

static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		default:
			std::cout << "Unknown ShaderDataType." << std::endl;
			assert(false);
			return 0;
	}
}


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer)
{
	glBindVertexArray(m_ArrayID);
	vertexBuffer->bind();
	uint32_t index = 0;
	auto layout = vertexBuffer->getLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
				      element.getElementCount(),
				      ShaderDataTypeToOpenGLType(element.type),
				      element.normalized ? GL_TRUE : GL_FALSE,
				      layout.getStride(),
				      reinterpret_cast<const void*>(element.offset));
		index++;
	}
	m_VertexBuffers.push_back(std::move(vertexBuffer));
}

void VertexArray::setIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
{
	glBindVertexArray(m_ArrayID);
	indexBuffer->bind();
	m_IndexBuffer = std::move(indexBuffer);
}

std::vector<std::unique_ptr<VertexBuffer>>& VertexArray::getVertexBuffers()
{
	return m_VertexBuffers;
}

IndexBuffer& VertexArray::getIndexBuffer() const
{
	return *m_IndexBuffer;
}

