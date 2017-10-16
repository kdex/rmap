#pragma once
#include <cstdint>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "Format.h"
#include "Pipe.h"
auto sanitize(const YAML::Node &node, bool &sliceBytes, const std::string &prefix) {
	const auto &range = node["range"];
	const auto &extract = node["extract"];
	const auto &bytesPerElement = node["bytesPerElement"];
	if (!range) {
		throw std::runtime_error("Missing `range` parameter in: " + prefix);
	}
	/* Is there an `extract` field? */
	if (extract.IsDefined()) {
		/* Then there must be a `bytesPerElement` field, too */
		if (!bytesPerElement) {
			throw std::runtime_error("The `extract` parameter requires `bytesPerElement`, in: " + prefix);
		}
		if (!extract.size()) {
			throw std::runtime_error("The `extract` parameter must specify slices, in: " + prefix);
		}
		else {
			sliceBytes = true;
		}
	}
}
template<typename Syntax>
auto handleNode(Pipe<Syntax> &pipe) {
	return [&](const YAML::Node &node) {
		const auto &range = node["range"];
		const auto &extract = node["extract"];
		const auto &bytesPerElement = node["bytesPerElement"];
		bool sliceBytes = false;
		sanitize(node, sliceBytes, pipe.prefix);
		const auto start = range[0].as<std::size_t>();
		const auto end = range[1].as<std::size_t>();
		pipe.checkBounds(start, end);
		if (sliceBytes) {
			const auto skip = bytesPerElement.as<std::size_t>();
			const auto positionBefore = pipe.output.tellp();
			for (auto i = start; i < end; i += skip) {
				for (auto &&slice : extract) {
					const auto sliceStart = slice[0].as<std::size_t>();
					const auto sliceEnd = slice[1].as<std::size_t>();
					pipe.transfer(i + sliceStart, i + sliceEnd);
				}
			}
		}
		else {
			pipe.transfer(start, end);
		}
	};
};
template<typename Syntax>
void descend(const YAML::Node &config, Pipe<Syntax> &pipe, const std::string &prefix = "") {
	const auto handle = handleNode(pipe);
	for (auto &&root : config) {
		for (auto &&node : root) {
			const auto currentPrefix = Format::append(prefix, node.first.as<std::string>());
			const auto &value = node.second;
			pipe.prefix = currentPrefix;
			if (value.IsSequence()) {
				descend(value, pipe, currentPrefix);
			}
			else if (value.IsMap()) {
				handle(value);
			}
			else {
				std::cout << "Ignoring: " + currentPrefix << std::endl;
			}
		}
	}
	if (prefix == "") {
		pipe.writer.write();
	}
}