#pragma once
#include <vector>
#include <tuple>
#include <cstdint>
#include "MapContext.h"
namespace rmap {
	struct SyntaxC {
		std::string write(const MapContext &mapContext);
	};
	struct SyntaxCpp {
		std::string write(const MapContext &mapContext);
	};
	struct SyntaxES {
		std::string write(const MapContext &mapContext);
	};
}