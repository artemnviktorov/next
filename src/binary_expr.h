#pragma once

#include "expr.h"

namespace next {

template <typename T>
class binary_expr : public expr<T> {
public:
    explicit binary_expr(uptr<expr<T>> left, token op, uptr<expr<T>> right) :
        m_left(std::move(left)), m_op(std::move(op)), m_right(std::move(right)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    std::unique_ptr<expr<T>> m_left;
    token m_op;
    std::unique_ptr<expr<T>> m_right;
};

}
