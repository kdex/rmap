#pragma once
#include <fstream>
#include <tuple>
#include <vector>
#include "Syntax.h"
#include "MapInfo.h"
#include "MapContext.h"
namespace rmap {
	template<typename Syntax>
	class FileWriter {
		public:
			FileWriter(const std::string &prefix, const std::string &outputPath)
				: prefix(prefix)
				, outputFile(outputPath) {}
			void addMapping(std::size_t start, std::size_t end, std::size_t to) {
				mapInfos.push_back({ start, end, to });
			}
			void write() {
				const MapContext context(mapInfos, prefix);
				const std::string module = syntax.write(context);
				outputFile << module;
			}
			Syntax syntax;
		private:
			const std::string prefix;
			std::ofstream outputFile;
			std::vector<MapInfo> mapInfos;
	};

}