#pragma once
#include <string>
#include <sstream>
#include <fstream>


std::string readShaderFile(const std::string& filename) {
	std::ifstream stream(filename);
	std::stringstream ss{};
	std::string line;

	while (getline(stream, line)) {
		ss << line << "\n";
	}
	return ss.str();
}