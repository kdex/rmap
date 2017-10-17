#pragma once
#include <string>
namespace rmap {
	struct PipeContext {
		const std::string &inputPath, &outputPath;
		std::string &prefix, &functionName, &extension;
	};
}