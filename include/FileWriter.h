#pragma once
#include <fstream>
#include <tuple>
#include <vector>
#include "Syntax.h"
template<typename Syntax>
class FileWriter {
	public:
		FileWriter(const std::string &prefix, const std::string &outputPath)
			: prefix(prefix)
			, outputFile(outputPath) {}
		void addMapping(std::size_t start, std::size_t end, std::size_t to) {
			maps.push_back({ start, end, to });
		}
		void write() {
			const std::string module = syntax.write(maps, prefix);
			outputFile << module;
		}
		Syntax syntax;
	private:
		const std::string prefix;
		std::ofstream outputFile;
		std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> maps;
};
