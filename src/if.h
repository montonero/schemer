#ifndef __IF_H__
#define __IF_H__

#include "expression.h"

class IfExpression : public Expression {

    public:

        Expression *condition;
        Expression *conseq;
        Expression *otherwise;

        IfExpression() : Expression(EXP_IF) {}
        ~IfExpression();

        Expression *evaluate(Environment *env) throw (SchemerException*);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException*);
};

std::ostream & operator << (std::ostream &output, const IfExpression *expression);

#endif

