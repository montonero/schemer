#ifndef __PARSER_H__
#define __PARSER_H__

#include "tokenizer.h"
#include "environment.h"
#include <list>
#include <ostream>

typedef enum {
    EXP_ATOM,
    EXP_DEFINE,
    EXP_LAMBDA,
    EXP_BEGIN,
    EXP_COND,
    EXP_QUOTE,
    EXP_APPLICATION,
    EXP_PROCEDURE,
    EXP_BUILTIN
}
ExpressionType;

class Expression {

    public:

        ExpressionType type;

        Expression(const ExpressionType type) {
            this->type = type;
        }

        Expression *evaluate(Environment *env) throw (SchemerException) {
            return this;
        }
        virtual bool boolValue() { return false; }

        static Expression* parse(std::list<Token*> &tokens) throw (SchemerException);
};

class Atom : public Expression {

    public:

        Token *token;

        Atom() : Expression(EXP_ATOM) {}
        Atom(Token *token) : Expression(EXP_ATOM) {
            this->token = token;
        }
        bool boolValue();

        Expression *evaluate(Environment *env) throw (SchemerException);
};

class DefineExpression : public Expression {

    public:

        SymbolToken *name;
        Expression *defined;

        DefineExpression() : Expression(EXP_DEFINE) {}
        ~DefineExpression() { delete defined; }

        Expression *evaluate(Environment *env) throw (SchemerException);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException);
};

class LambdaExpression : public Expression {

    public:

        std::list<SymbolToken*> formalParameters;
        Expression *lambdaExpression;

        LambdaExpression() : Expression(EXP_LAMBDA) {}
        ~LambdaExpression() { delete lambdaExpression; }

        Expression *evaluate(Environment *env) throw (SchemerException);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException);
};

class CondExpression : public Expression {

    public:

        std::list<Expression*> conditions;
        std::list<Expression*> implications;

        CondExpression() : Expression(EXP_COND) {}
        ~CondExpression();

        Expression *evaluate(Environment *env) throw (SchemerException);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException);
};

class QuoteExpression : public Expression {

    public:

        Expression *quoted;

        QuoteExpression() : Expression(EXP_QUOTE) {}
        ~QuoteExpression() { delete quoted; }

        Expression *evaluate(Environment *env) throw (SchemerException);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException);
};

class BeginExpression : public Expression {

    public:

        std::list<Expression*> expressions;

        BeginExpression() : Expression(EXP_BEGIN) {}
        ~BeginExpression();

        Expression *evaluate(Environment *env) throw (SchemerException);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException);
};

class ApplicationExpression : public Expression {

    public:

        Expression *function;
        std::list<Expression*> arguments;

        ApplicationExpression() : Expression(EXP_APPLICATION) {}
        ~ApplicationExpression();

        Expression *evaluate(Environment *env) throw (SchemerException);

        static Expression *parse(std::list<Token*> &tokens) throw (SchemerException);
};

class Procedure : public Expression {

    public:

        std::list<SymbolToken*> formalParameters;
        Expression *procedureExpression;
        Environment *environment;

        Procedure() : Expression(EXP_PROCEDURE) {}
        ~Procedure() { delete procedureExpression; }
};

class BuiltInProcedure : public Expression {

    public:
        std::string name;
        Expression* (*function)(const std::list<Expression*> &arguments);

        BuiltInProcedure() : Expression(EXP_BUILTIN) {}
        BuiltInProcedure(const std::string name, 
                Expression* (*function)(const std::list<Expression*> &arguments));
};

std::ostream & operator << (std::ostream &output, const Expression *expression);
std::ostream & operator << (std::ostream &output, const Atom *expression);
std::ostream & operator << (std::ostream &output, const DefineExpression *expression);
std::ostream & operator << (std::ostream &output, const LambdaExpression *expression);
std::ostream & operator << (std::ostream &output, const CondExpression *expression);
std::ostream & operator << (std::ostream &output, const QuoteExpression *expression);
std::ostream & operator << (std::ostream &output, const BeginExpression *expression);
std::ostream & operator << (std::ostream &output, const ApplicationExpression *expression);
std::ostream & operator << (std::ostream &output, const Procedure *expression);
std::ostream & operator << (std::ostream &output, const BuiltInProcedure *expression);

#endif

