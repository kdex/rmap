#pragma once
#include <vector>
#include <tuple>
#include <cstdint>
#include "MapContext.h"
namespace rmap {
	struct SyntaxC {
		std::string prefix = "";
		std::string functionName = "";
		std::string write(const MapContext &mapContext);
	};
	struct SyntaxCpp {
		std::string prefix = "rmap::";
		std::string write(const MapContext &mapContext);
	};
	struct SyntaxES {
		std::string prefix = "";
		std::string write(const MapContext &mapContext);
	};
}