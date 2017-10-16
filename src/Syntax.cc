#include <iostream>
#include <sstream>
#include "Format.h"
#include "Syntax.h"
std::string SyntaxC::write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix) {
	std::stringstream ss;
	const auto EOL = '\n';
	const auto indent = '\t';
	ss
		<< "#pragma once" << EOL
		<< "#include <stdint.h>" << EOL
		<< "std::size_t toDumpSpace(std::size_t location) {" << EOL;
	for (auto &&map : maps) {
		const auto [start, end, to] = map;
		ss
			<< indent
			<< "if (location >= " << Format::hex(start)
			<< " && location <= " << Format::hex(end) << ") {"
			<< EOL << indent << indent
			<< "return " << Format::hex(to) << " + location - " << Format::hex(start) << ";"
			<< EOL
			<< indent << "}" << EOL;
	}
	ss << "}";
	return ss.str();
}
std::string SyntaxCpp::write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix) {
	std::stringstream ss;
	const auto EOL = '\n';
	const auto indent = '\t';
	ss
		<< "#pragma once" << EOL
		<< "#include <cstdint>" << EOL
		<< "namespace " << prefix << " {" << EOL
		<< indent << "constexpr std::size_t toDumpSpace(std::size_t location) {" << EOL;
	for (auto &&map : maps) {
		const auto [start, end, to] = map;
		ss
			<< indent << indent
			<< "if (location >= " << Format::hex(start)
			<< " && location <= " << Format::hex(end) << ") {"
			<< EOL << indent << indent << indent
			<< "return " << Format::hex(to) << " + location - " << Format::hex(start) << ";"
			<< EOL
			<< indent << indent << "}" << EOL;
	}
	ss << indent << "}" << EOL << "}";
	return ss.str();
}
std::string SyntaxES::write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix) {
	std::stringstream ss;
	const auto EOL = '\n';
	const auto indent = '\t';
	ss
		<< "export const toDumpSpace = location => {" << EOL;
	for (auto &&map : maps) {
		const auto [start, end, to] = map;
		ss
			<< indent
			<< "if (location >= " << Format::hex(start)
			<< " && location <= " << Format::hex(end) << ") {"
			<< EOL << indent << indent
			<< "return " << Format::hex(to) << " + location - " << Format::hex(start) << ";"
			<< EOL
			<< indent << "}" << EOL;
	}
	ss << "};";
	return ss.str();
}