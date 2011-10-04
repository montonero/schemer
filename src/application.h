#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "expression.h"

class ApplicationExpression : public Expression {

    public:

        Expression *function;
        std::list<Expression*> arguments;

        ApplicationExpression() : Expression(EXP_APPLICATION) {}
        ~ApplicationExpression();

        Expression *evaluate(Environment *env) throw (SchemerException*);
        std::ostream & print(std::ostream &output) const;
        void reach();

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException*);
};

#endif

