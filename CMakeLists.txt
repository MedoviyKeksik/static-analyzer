cmake_minimum_required(VERSION 3.17)
project(static_analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(static_analyzer main.cpp lexer.cpp lexer.h cmake-build-debug/dictionary.cpp dictionary.h bor.cpp bor.h ast.cpp ast.h)