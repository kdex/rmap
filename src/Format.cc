#include "Format.h"
std::string Format::hex(std::size_t n) {
	std::stringstream ss;
	ss
		<< "0x"
		<< std::setfill('0')
		<< std::setw(6)
		<< std::hex
		<< n;
	return ss.str();
}
std::string Format::append(const std::string &prefix, const std::string &appendix) {
	if (prefix.empty()) {
		return appendix;
	}
	return prefix + "." + appendix;
}