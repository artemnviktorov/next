#pragma once

#include "expr.h"

namespace next {

template <typename T>
class literal_expr : public expr<T> {
public:
    explicit literal_expr(uptr<expr<T>> expr) : m_expr(std::move(expr)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    uptr<expr<T>> m_expr;
};

}
