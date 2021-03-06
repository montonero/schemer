#ifndef __LAMBDA_H__
#define __LAMBDA_H__

#include "expression.h"

class LambdaExpression : public Expression {

    public:

        std::list<SymbolToken*> formalParameters;
        Expression *lambdaExpression;

        LambdaExpression() : Expression(EXP_LAMBDA) {}

        Expression *evaluate(Environment *env, std::set<Expression*> &callers) throw (SchemerException*);
        std::ostream & print(std::ostream &output) const;
        void deepReach();

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException*);
};

#endif

