#pragma once

#include "expr.h"

namespace next {

template <typename T>
class var_expr : public expr<T> {
public:
    explicit var_expr(token name) : m_name(std::move(name)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    token m_name;
};

}
