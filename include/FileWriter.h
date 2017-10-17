#pragma once
#include <fstream>
#include <tuple>
#include <vector>
#include "Syntax.h"
#include "MapInfo.h"
#include "MapContext.h"
#include "PipeContext.h"
namespace rmap {
	template<typename Syntax>
	class FileWriter {
		public:
			FileWriter(PipeContext &pipeContext) : pipeContext(pipeContext) {
				configure(pipeContext);
				outputFile = std::ofstream(pipeContext.outputPath + "." + pipeContext.extension);
			}
			void addMapping(std::size_t start, std::size_t end, std::size_t to) {
				mapInfos.push_back({ start, end, to });
			}
			void write() {
				const MapContext mapContext = { mapInfos, pipeContext };
				const std::string module = syntax.write(mapContext);
				outputFile << module;
			}
			Syntax syntax;
		private:
			const PipeContext &configure(PipeContext &context) {
				if (pipeContext.prefix.empty()) {
					pipeContext.prefix = syntax.prefix;
				}
				if (pipeContext.extension.empty()) {
					pipeContext.extension = syntax.extension;
				}
				return context;
			}
			PipeContext &pipeContext;
			std::ofstream outputFile;
			std::vector<MapInfo> mapInfos;
	};

}