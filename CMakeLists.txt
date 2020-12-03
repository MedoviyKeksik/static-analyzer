cmake_minimum_required(VERSION 3.17)
project(static_analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(static_analyzer main.cpp  ast.cpp ast.h CRC32.h CRC32.cpp)
add_library(lexer lexer.h lexer.cpp)
add_library(dict dictionary.h dictionary.cpp)
add_library(bor bor.h bor.cpp)
add_library(CRC32 CRC32.h CRC32.cpp)
add_library(WShingling WShingling.cpp WShingling.h)
target_link_libraries(static_analyzer lexer dict bor CRC32 WShingling)