#pragma once

#include <vector>

#include "expr.h"

namespace next {

template <typename T>
class call_expr : public expr<T> {
public:
    call_expr(uptr<expr<T>> callee, token paren, std::vector<uptr<expr<T>>> &args) :
        m_callee(std::move(callee)), m_paren(std::move(paren)), m_args(std::move(args)) {}

    T accept(expr_visitor<T> &visitor) const override {
        return visitor.visit(*this);
    }

private:
    uptr<expr<T>> m_callee;
    token m_paren;
    std::vector<uptr<expr<T>>> m_args;
};

}
