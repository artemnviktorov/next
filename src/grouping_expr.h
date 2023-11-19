#pragma once

#include <any>

#include "expr.h"

namespace next {

template <typename T>
class grouping_expr : public expr<T> {
public:
    explicit grouping_expr(std::any literal) : m_literal(std::move(literal)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    std::any m_literal;
};

}
