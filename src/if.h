#ifndef __IF_H__
#define __IF_H__

#include "expression.h"

class IfExpression : public Expression {

    public:

        Expression *condition;
        Expression *conseq;
        Expression *otherwise;

        IfExpression() : Expression(EXP_IF) {}

        Expression *evaluate(Environment *env, std::set<Expression*> &callers) throw (SchemerException*);
        std::ostream & print(std::ostream &output) const;
        void deepReach();

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException*);
};

#endif

