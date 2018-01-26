#include <functional>
#include <sstream>
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