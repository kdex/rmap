#pragma once
#include <vector>
#include "MapInfo.h"
namespace rmap {
	struct MapContext {
		const std::vector<MapInfo> &mapInfos;
		const std::string &prefix;
		MapContext(const std::vector<MapInfo> &mapInfos, const std::string &prefix)
			: mapInfos(mapInfos)
			, prefix(prefix) {}
	};
}