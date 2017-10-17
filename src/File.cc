#include "File.h"
#include <cerrno>
#include <cstring>
#include <iostream>
void rmap::File::fail(const std::string &message) {
	std::cerr << message << std::endl;
	std::exit(EXIT_FAILURE);
}
std::ifstream rmap::File::open(const std::string &filename) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(filename, std::ios::ate | std::ios::binary);
	}
	catch (...) {
		fail(std::string(std::strerror(errno)) + ": " + filename);
	}
	return file;
}