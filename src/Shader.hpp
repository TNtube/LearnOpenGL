#pragma once
#include <string>


class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	void bind() const;
	void unbind();

private:
	uint32_t m_ShaderID {};
};
