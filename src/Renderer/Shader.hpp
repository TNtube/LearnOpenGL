#pragma once
#include <string>
#include <glm/ext/matrix_float4x4.hpp>


class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	void bind() const;
	void unbind();
	void setUniformMat4(const std::string& name, glm::mat4& mat);

private:
	uint32_t m_ShaderID {};
};
