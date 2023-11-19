cmake_minimum_required(VERSION 3.8)

project(next)

set(CMAKE_CXX_STANDARD 20)

add_executable(next
    "src/main.cpp"
    "src/token_type.h"
    "src/token.h"
    "src/token.cpp"
    "src/scanner.h"
    "src/scanner.cpp"
    "src/expr.h"
    "src/assign_expr.h"
    "src/binary_expr.h"
    "src/call_expr.h"
    "src/grouping_expr.h"
    "src/literal_expr.h"
    "src/logical_expr.h"
    "src/unary_expr.h"
    "src/var_expr.h")
