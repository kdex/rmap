#pragma once
#include <cstdint>
#include <iomanip>
namespace Format {
	std::string hex(std::size_t n);
	std::string append(const std::string &prefix, const std::string &appendix);
}