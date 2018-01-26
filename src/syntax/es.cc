#include <functional>
#include <sstream>
#include "Format.h"
#include "Syntax.h"
using rmap::Format::EOL;
using rmap::Format::T;
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