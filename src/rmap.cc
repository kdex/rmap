#include <yaml-cpp/yaml.h>
#include "apx/Parser.h"
#include "Configuration.h"
#include "Pipe.h"
#include "Syntax.h"
int main(int argc, const char *argv[]) {
	auto parser = apx::Parser();
	parser
		.option([](auto &&config) {
			config
				.flag('h')
				.flag("help")
				.description("Displays this help");
		})
		.option([](auto &&config) {
			config
				.flag('r')
				.flag("range-file")
				.description("Specifies the extraction range")
				.argument([](auto &&config) {
					config
						.name("yaml-file")
						.optional("ranges.yaml")
						.description("A YAML file that specifies the ranges to extract");
				});
		})
		.option([](auto &&config) {
			config
				.flag('s')
				.flag("syntax")
				.description("Specifies the syntax for the emitted module")
				.argument([](auto &&config) {
					config
						.name("name")
						.optional("c++")
						.restrict({
							"c",
							"c++",
							"es"
						})
						.description("A syntax name. Currently, C/C++ headers and ECMAScript modules are supported.");
				});
		})
		.argument([](auto &&config) {
			config
				.name("INPUT")
				.description("The file to extract data from")
				.optional();
		})
		.argument([](auto &&config) {
			config
				.name("OUTPUT")
				.description("The output file")
				.optional("dump.dat");
		});
	auto config = parser.parse(argc, argv);
	if (config.argument["INPUT"].values.empty() || config.option["help"]) {
		parser.help(argv);
		std::exit(EXIT_FAILURE);
	}
	const auto rangesPath = config.option["range-file"]["yaml-file"].as<std::string>();
	const auto inputPath = config.argument["INPUT"].as<std::string>();
	const auto outputPath = config.argument["OUTPUT"].as<std::string>();
	const auto syntax = config.option["syntax"]["name"].as<std::string>();
	const auto prefix = "lol::what";
	const auto yamlConfig = YAML::LoadFile(rangesPath);
	if (syntax == "c") {
		auto pipe = Pipe<SyntaxC>(inputPath, outputPath, prefix);
		descend(yamlConfig, pipe);
	}
	else if (syntax == "c++") {
		auto pipe = Pipe<SyntaxCpp>(inputPath, outputPath, prefix);
		descend(yamlConfig, pipe);
	}
	else if (syntax == "es") {
		auto pipe = Pipe<SyntaxES>(inputPath, outputPath, prefix);
		descend(yamlConfig, pipe);
	}
}