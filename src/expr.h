#pragma once

#include <memory>

#include "token.h"

namespace next {

template <typename T>
using uptr = std::unique_ptr<T>;

namespace {

class assign_expr;
class binary_expr;
class call_expr;
class grouping_expr;
class literal_expr;
class logical_expr;
class unary_expr;
class variable_expr;

}

template <typename T>
class expr_visitor {
public:
    virtual ~expr_visitor() = default;

    virtual T visit(assign_expr &expr) const = 0;
    virtual T visit(binary_expr &expr) const = 0;
    virtual T visit(call_expr &expr) const = 0;
    virtual T visit(grouping_expr &expr) const = 0;
    virtual T visit(literal_expr &expr) const = 0;
    virtual T visit(logical_expr &expr) const = 0;
    virtual T visit(unary_expr &expr) const = 0;
    virtual T visit(variable_expr &expr) const = 0;
};

template <typename T>
class expr {
public:
    virtual ~expr() = default;

    virtual T accept(expr_visitor<T> &visitor) const = 0;
};

}
