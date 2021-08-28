#pragma once
#include <string>


class Texture
{
public:
	explicit Texture(const std::string& filename);
	~Texture();
	void bind(uint32_t slot = 0) const;
	void unbind() const;
private:
	uint32_t m_TexID {};
};
