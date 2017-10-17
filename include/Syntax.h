#pragma once
#include "MapContext.h"
namespace rmap {
	struct SyntaxC {
		std::string prefix = "", extension = "h";
		std::string write(const MapContext &mapContext);
	};
	struct SyntaxCpp {
		std::string prefix = "rmap", extension = "h";
		std::string write(const MapContext &mapContext);
	};
	struct SyntaxES {
		std::string prefix = "", extension = "mjs";
		std::string write(const MapContext &mapContext);
	};
}