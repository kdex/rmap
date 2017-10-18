#include <iostream>
#include <sstream>
#include <functional>
#include "Format.h"
#include "Syntax.h"
using rmap::Format::EOL;
using rmap::Format::T;
std::string rmap::SyntaxC::write(const MapContext &context) {
	std::stringstream ss;
	const auto buildArray = [&](std::string_view &&name, const auto &&extract) {
		std::stringstream ss;
		ss
			<< "const static size_t " << name << "[] = { "
			<< Format::enumerate(context, extract)
			<< " };";
		return ss.str();
	};
	ss
		<< "#pragma once" << EOL
		<< "#include <stdbool.h>" << EOL
		<< "#include <stddef.h>" << EOL
		<< buildArray("sourceOffsets", [](MapInfo &&mapInfo) {
			return mapInfo.start;
		}) << EOL
		<< buildArray("sourceLengths", [](MapInfo &&mapInfo) {
			return mapInfo.end - mapInfo.start + 1;
		}) << EOL
		<< buildArray("dumpOffsets", [](MapInfo &&mapInfo) {
			return mapInfo.to;
		}) << EOL
		<< "bool " << context.pipeContext.prefix << context.pipeContext.functionName << "(size_t location, size_t *mappedLocation) {" << EOL
		<< T << "for (size_t i = 0u; i < " << context.mapInfos.size() << "; ++i) {" << EOL
		<< T << T << "if (location >= sourceOffsets[i]) {" << EOL
		<< T << T << T << "const size_t offset = location - sourceOffsets[i];" << EOL
		<< T << T << T << "if (offset < sourceLengths[i]) {" << EOL
		<< T << T << T << T << "*mappedLocation = dumpOffsets[i] + offset;" << EOL
		<< T << T << T << T << "return true;" << EOL
		<< T << T << T << "}" << EOL
		<< T << T << "}" << EOL
		<< T << "}" << EOL
		<< T << "return false;" << EOL
		<< "}";
	return ss.str();
}
std::string rmap::SyntaxCpp::write(const MapContext &context) {
	std::stringstream ss;
	const auto buildArray = [&](std::string_view &&name, const auto &&extract) {
		std::stringstream ss;
		ss
			<< "constexpr static std::size_t " << name << "[] = { "
			<< Format::enumerate(context, extract)
			<< " };";
		return ss.str();
	};
	ss
		<< "#pragma once" << EOL
		<< "#include <cstdint>" << EOL
		<< "#include <iomanip>" << EOL
		<< "#include <sstream>" << EOL
		<< "namespace " << context.pipeContext.prefix << " {" << EOL
		<< T << buildArray("sourceOffsets", [](MapInfo &&mapInfo) {
			return mapInfo.start;
		}) << EOL
		<< T << buildArray("sourceLengths", [](MapInfo &&mapInfo) {
			return mapInfo.end - mapInfo.start + 1;
		}) << EOL
		<< T << buildArray("dumpOffsets", [](MapInfo &&mapInfo) {
			return mapInfo.to;
		}) << EOL
		<< T << "std::size_t " << context.pipeContext.functionName << "(std::size_t location) {" << EOL
		<< T << T << "for (auto i = 0u; i < " << context.mapInfos.size() << "; ++i) {" << EOL
		<< T << T << T << "if (location >= sourceOffsets[i]) {" << EOL
		<< T << T << T << T << "const auto offset = location - sourceOffsets[i];" << EOL
		<< T << T << T << T << "if (offset < sourceLengths[i]) {" << EOL
		<< T << T << T << T << T << "return dumpOffsets[i] + offset;" << EOL
		<< T << T << T << T << "}" << EOL
		<< T << T << T << "}" << EOL
		<< T << T << "}" << EOL
		<< T << T << "std::stringstream ss;" << EOL
		<< T << T << "ss" << EOL
		<< T << T << T << "<< \"Invalid access to address 0x\" << std::hex << location" << EOL
		<< T << T << T << "<< \" (decimal offset: \" << std::dec << location << \"). \"" << EOL
		<< T << T << T << "<< \" This address has not been included in the dump.\";" << EOL
		<< T << T << "throw std::invalid_argument(ss.str());" << EOL
		<< T << "}" << EOL
		<< "}";
	return ss.str();
}
std::string rmap::SyntaxES::write(const MapContext &context) {
	std::stringstream ss;
	const auto buildArray = [&](std::string_view &&name, const auto &&extract) {
		std::stringstream ss;
		ss
			<< "const " << name << " = ["
			<< Format::enumerate(context, extract)
			<< "];";
		return ss.str();
	};
	ss
		<< buildArray("sourceOffsets", [](MapInfo &&mapInfo) {
			return mapInfo.start;
		}) << EOL
		<< buildArray("sourceLengths", [](MapInfo &&mapInfo) {
			return mapInfo.end - mapInfo.start + 1;
		}) << EOL
		<< buildArray("dumpOffsets", [](MapInfo &&mapInfo) {
			return mapInfo.to;
		}) << EOL
		<< "export const " << context.pipeContext.prefix << context.pipeContext.functionName << " = location => {" << EOL
		<< T << "for (let i = 0; i < " << context.mapInfos.size() << "; ++i) {" << EOL
		<< T << T << "if (location >= sourceOffsets[i]) {" << EOL
		<< T << T << T << "const offset = location - sourceOffsets[i];" << EOL
		<< T << T << T << "if (offset < sourceLengths[i]) {" << EOL
		<< T << T << T << T << "return dumpOffsets[i] + offset;" << EOL
		<< T << T << T << "}" << EOL
		<< T << T << "}" << EOL
		<< T << "}" << EOL
		<< T << "throw new Error(`Invalid access to address 0x${location.toString(16)} (decimal offset: ${location}). This address has not been included in the dump.`);" << EOL
		<< "};";
	return ss.str();
}