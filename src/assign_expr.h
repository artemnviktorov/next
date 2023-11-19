#pragma once

#include "expr.h"

namespace next {

template <typename T>
class assign_expr : public expr<T> {
public:
    explicit assign_expr(token name, uptr<expr<T>> value) :
        m_name(std::move(name)), m_value(std::move(value)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    token m_name;
    std::unique_ptr<expr<T>> m_value;
};

}
