#pragma once

#include "expr.h"

namespace next {

template <typename T>
class binary_expr : public expr<T> {
public:
    explicit binary_expr(token op, uptr<expr<T>> right) :
        m_op(std::move(op)), m_right(std::move(right)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    token m_op;
    std::unique_ptr<expr<T>> m_right;
};

}
