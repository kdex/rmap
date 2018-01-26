cmake_minimum_required(VERSION 3.9.4)
project(rmap)
set(CMAKE_CXX_STANDARD 17)
find_package(yaml-cpp REQUIRED)
include(ExternalProject)
ExternalProject_Add(apx-git
	GIT_REPOSITORY git@github.com:kdex/apx.git
	PREFIX ${CMAKE_BINARY_DIR}/apx
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
	UPDATE_DISCONNECTED true
)
ExternalProject_Get_Property(apx-git INSTALL_DIR)
include_directories(
	include
	${INSTALL_DIR}/include
)
link_directories(${INSTALL_DIR}/lib)
SET(GLOBAL_CXX_FLAGS
	"\
	-fno-builtin\
	-pedantic\
	-Wall\
	-Wcast-align\
	-Wextra\
	-Wfloat-equal\
	-Wmissing-declarations\
	-Woverloaded-virtual\
	-Wredundant-decls\
	-Wundef\
	-Wwrite-strings\
	-Wno-parentheses\
	"
)
SET(GLOBAL_CXX_RELEASE_FLAGS
	"\
	${GLOBAL_CXX_FLAGS}\
	"
)
SET(GLOBAL_CXX_DEBUG_FLAGS
	"\
	${GLOBAL_CXX_FLAGS}\
	-fsanitize=address\
	-fsanitize=undefined\
	"
)
SET(GLOBAL_CXX_WASM_FLAGS
	"\
	-emit-llvm\
	--target=wasm64\
	-S\
	-Oz\
	"
)
OPTION(WASM "Output a `wasm` binary" OFF)
IF (WASM)
	SET(GLOBAL_CXX_RELEASE_FLAGS
		"${GLOBAL_CXX_RELEASE_FLAGS}\
		${GLOBAL_CXX_WASM_FLAGS}\
		"
	)
ELSE ()
	SET(GLOBAL_CXX_RELEASE_FLAGS
		"\
		${GLOBAL_CXX_RELEASE_FLAGS}\
		-O3\
		"
	)
ENDIF()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GLOBAL_CXX_RELEASE_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GLOBAL_CXX_DEBUG_FLAGS}")
add_executable(${PROJECT_NAME}
	src/${PROJECT_NAME}.cc
	src/File.cc
	src/Format.cc
	src/syntax/c.cc
	src/syntax/c++.cc
	src/syntax/es.cc
)
add_dependencies(${PROJECT_NAME} apx-git)
target_link_libraries(${PROJECT_NAME}
	apx
	yaml-cpp
)
install(TARGETS rmap RUNTIME DESTINATION bin)