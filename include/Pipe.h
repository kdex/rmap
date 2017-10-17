#pragma once
#include <fstream>
#include "FileWriter.h"
#include "File.h"
namespace rmap {
	template<typename Syntax>
	struct Pipe {
		std::ifstream input;
		const std::size_t inputSize;
		std::ofstream output;
		std::size_t mostRecentStart = 0, mostRecentEnd = 0;
		std::string prefix = "";
		FileWriter<Syntax> writer;
		Pipe(const std::string &inputPath, const std::string &outputPath, const std::string &prefix)
			: input(File::open(inputPath))
			, inputSize(input.tellg())
			, output(std::ofstream(outputPath, std::ios::binary))
			, writer(FileWriter<Syntax>(prefix, outputPath + ".h")) {
			input.seekg(0);
		}
		Pipe(const Pipe &) = delete;
		Pipe& operator=(const Pipe &) = delete;
		Pipe(Pipe &&) = delete;
		Pipe& operator=(Pipe &&) = delete;
		~Pipe() = default;
		void checkBounds(std::size_t start, std::size_t end) const {
			if (start >= inputSize || end >= inputSize) {
				std::stringstream ss;
				ss
					<< "Invalid read from range "
					<< "[" << Format::hex(start) << ", " << Format::hex(end) << "]: "
					<< "Input file terminates at index " << Format::hex(inputSize - 1)
					;
				throw std::runtime_error(ss.str());
			}
		}
		void transfer(std::size_t start, std::size_t end) {
			const std::size_t bytes = end - start + 1;
			mostRecentStart = output.tellp();
			input.seekg(start);
			std::vector<char> result;
			result.resize(bytes);
			input.read(&result[0], bytes);
			output.write(result.data(), bytes);
			mostRecentEnd = static_cast<std::size_t>(output.tellp()) - 1;
			report(start, end, mostRecentStart);
			writer.addMapping(start, end, mostRecentStart);
		}
		void report(std::size_t inputStart, std::size_t inputEnd, std::size_t dumpStart) {
			std::cout
				<< "[" << Format::hex(inputStart) << ", " << Format::hex(inputEnd) << "]"
				<< " ↦ "
				<< "[" << Format::hex(dumpStart) << ", " << Format::hex(mostRecentEnd) << "] "
				<< "(" << prefix << ")"
				<< std::endl;
		}
	};
}