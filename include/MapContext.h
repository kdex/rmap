#pragma once
#include <vector>
#include "MapInfo.h"
#include "PipeContext.h"
namespace rmap {
	struct MapContext {
		const std::vector<MapInfo> &mapInfos;
		const PipeContext &pipeContext;
	};
}