#pragma once
#include <vector>
#include <tuple>
#include <cstdint>
struct Syntax {
	virtual std::string write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix) = 0;
};
struct SyntaxC : Syntax {
	virtual std::string write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix);
};
struct SyntaxCpp : Syntax {
	virtual std::string write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix);
};
struct SyntaxES : Syntax {
	virtual std::string write(const std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> &maps, const std::string &prefix);
};