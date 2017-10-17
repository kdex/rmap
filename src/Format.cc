#include <sstream>
#include "Format.h"
std::string rmap::Format::hex(std::size_t n) {
	std::stringstream ss;
	ss
		<< "0x"
		<< std::setfill('0')
		<< std::setw(6)
		<< std::hex
		<< n;
	return ss.str();
}
std::string rmap::Format::append(const std::string &prefix, const std::string &appendix) {
	if (prefix.empty()) {
		return appendix;
	}
	return prefix + "." + appendix;
}
std::string rmap::Format::enumerate(const MapContext &context, const std::function<std::size_t(MapInfo)> &extract) {
	std::stringstream ss;
	for (auto i = 0u; i < context.mapInfos.size(); ++i) {
		ss << extract(context.mapInfos[i]);
		if (i != context.mapInfos.size() - 1) {
			ss << ", ";
		}
	}
	return ss.str();
}