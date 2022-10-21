#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>

inline std::string read_all(std::string_view filename) {
	std::ifstream sourceFile(filename.data());
	return std::string(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));
}