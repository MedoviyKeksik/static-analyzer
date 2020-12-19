cmake_minimum_required(VERSION 3.17)
project(static_analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(static_analyzer main.cpp)
add_library(lexer STATIC lexer.cpp)
add_library(dict STATIC dictionary.cpp)
add_library(CRC32 STATIC CRC32.cpp)
add_library(WShingling STATIC WShingling.cpp)
add_library(Editorial EditorialDistanceCompare.cpp)
target_link_libraries(static_analyzer lexer dict WShingling CRC32 Editorial)
target_link_options(static_analyzer PUBLIC -static-libgcc -static-libstdc++)

add_executable(StaticAnalyzerUI StaticAnalyzerUI.cpp)
target_link_libraries(StaticAnalyzerUI lexer dict WShingling CRC32 Editorial)
target_link_options(StaticAnalyzerUI PUBLIC -municode)
target_link_options(StaticAnalyzerUI PUBLIC -static-libgcc -static-libstdc++)