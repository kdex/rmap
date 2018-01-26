#include <functional>
#include <sstream>
#include "Format.h"
#include "Syntax.h"
using rmap::Format::EOL;
using rmap::Format::T;
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