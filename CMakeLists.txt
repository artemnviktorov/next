# CMakeList.txt : CMake project for next, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project("next")

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable(next "src/main.cpp" "src/token_type.h" "src/token.h" "src/token.cpp" "src/scanner.h" "src/scanner.cpp" )

# TODO: Add tests and install targets if needed.
