#pragma once
#include <cstdint>
#include <iomanip>
#include <functional>
#include "MapContext.h"
namespace rmap::Format {
	std::string hex(std::size_t n);
	std::string append(const std::string &prefix, const std::string &appendix);
	std::string enumerate(const MapContext &context, const std::function<std::size_t(MapInfo)> &extract);
	constexpr auto EOL = '\n';
	constexpr auto T = '\t';
}