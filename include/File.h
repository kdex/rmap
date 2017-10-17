#pragma once
#include <fstream>
namespace rmap {
	class File {
		public:
			static std::ifstream open(const std::string &filename);
		private:
			static void fail(const std::string &message);
	};
}