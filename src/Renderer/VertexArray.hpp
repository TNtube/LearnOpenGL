#pragma once
#include "Buffer.hpp"
#include <memory>


class VertexArray
{
public:
	VertexArray();
	virtual ~VertexArray() = default;
	void bind() const;
	void unbind() const;
	void addVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer);
	void setIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);
	std::vector<std::unique_ptr<VertexBuffer>>& getVertexBuffers ();
	IndexBuffer& getIndexBuffer () const;

private:
	uint32_t m_ArrayID{};
	std::vector<std::unique_ptr<VertexBuffer>> m_VertexBuffers;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
};
