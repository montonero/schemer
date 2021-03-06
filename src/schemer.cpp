
#include "application.h"
#include "atom.h"
#include "begin.h"
#include "builtin.h"
#include "cond.h"
#include "define.h"
#include "if.h"
#include "lambda.h"
#include "procedure.h"
#include "quote.h"

#include <iostream>

using namespace std;

Expression * plusBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {
    if (arguments.size() < 2) {
        throw new SchemerException("(+) function should receive at least two arguments");
    }

    Token *token;
    bool isFloat = false;
    long double accum = 0;

    for (list<Expression*>::const_iterator i = arguments.begin();
         i != arguments.end();
         i ++) {
        if ((*i)->type == EXP_ATOM) {
            token = ((Atom*)(*i))->token;
            switch (token->type) {
                case TOK_FLOAT:
                    isFloat = true;
                    accum += ((FloatToken*)token)->floatValue;
                    break;
                case TOK_INT:
                    accum += ((IntToken*)token)->intValue;
                    break;
                default:
                    throw new SchemerException("Arguments for (+) should be numeric");
            }
        }
        else {
            throw new SchemerException("Invalid argument in (+) function");
        }
    }

    return (isFloat? new Atom(new FloatToken(accum) ) :
                     new Atom(new IntToken((long int)accum) ) );
}

Expression * timesBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() < 2) {
        throw new SchemerException("(*) function should receive at least two arguments");
    }

    Token *token;
    bool isFloat = false;
    long double accum = 1;

    for (list<Expression*>::const_iterator i = arguments.begin();
         i != arguments.end();
         i ++) {
        if ((*i)->type == EXP_ATOM) {
            token = ((Atom*)(*i))->token;
            switch (token->type) {
                case TOK_FLOAT:
                    isFloat = true;
                    accum *= ((FloatToken*)token)->floatValue;
                    break;
                case TOK_INT:
                    accum *= ((IntToken*)token)->intValue;
                    break;
                default:
                    throw new SchemerException("Arguments for (*) should be numeric");
            }
        }
        else {
            throw new SchemerException("Invalid argument in (*) function");
        }
    }

    return (isFloat? new Atom(new FloatToken(accum) ) :
                     new Atom(new IntToken((long int)accum) ) );
}

Expression * divideBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {
    if (arguments.size() != 2) {
        throw new SchemerException("(/) function should receive exactly two arguments");
    }

    Token *token;
    long double v, a, b;
    int count;
    list<Expression*>::const_iterator i;

    for (i = arguments.begin(), count = 0;
         i != arguments.end();
         i ++, count++) {
        if ((*i)->type == EXP_ATOM) {
            token = ((Atom*)(*i))->token;
            switch (token->type) {
                case TOK_FLOAT:
                    v = ((FloatToken*)token)->floatValue;
                    break;
                case TOK_INT:
                    v = ((IntToken*)token)->intValue;
                    break;
                default:
                    throw new SchemerException("Arguments for (/) should be numeric");
            }

            if (count == 0) { a = v; }
            else if (count == 1) { b = v; }
        }
        else {
            throw new SchemerException("Invalid argument in (/) function");
        }
    }

    return new Atom(new FloatToken(a / b) );
}

Expression * modulusBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() != 2) {
        throw new SchemerException("(%) function should receive exactly two arguments");
    }

    Token *token;
    long int v, a, b;
    int count;
    list<Expression*>::const_iterator i;

    for (i = arguments.begin(), count = 0;
         i != arguments.end();
         i ++, count++) {
        if ((*i)->type == EXP_ATOM) {
            token = ((Atom*)(*i))->token;
            switch (token->type) {
                case TOK_INT:
                    v = ((IntToken*)token)->intValue;
                    break;
                default:
                    throw new SchemerException("Arguments for (%) should be integer");
            }

            if (count == 0) { a = v; }
            else if (count == 1) { b = v; }
        }
        else {
            throw new SchemerException("Invalid argument in (%) function");
        }
    }

    return new Atom(new IntToken(a % b) );
}

Expression * lessThanBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() != 2) {
        throw new SchemerException("(<) function should receive exactly two arguments");
    }

    Token *token;
    long double v, a, b;
    int count;
    list<Expression*>::const_iterator i;

    for (i = arguments.begin(), count = 0;
         i != arguments.end();
         i ++, count++) {
        if ((*i)->type == EXP_ATOM) {
            token = ((Atom*)(*i))->token;
            switch (token->type) {
                case TOK_FLOAT:
                    v = ((FloatToken*)token)->floatValue;
                    break;
                case TOK_INT:
                    v = ((IntToken*)token)->intValue;
                    break;
                default:
                    throw new SchemerException("Arguments for (<) should be numeric");
            }

            if (count == 0) { a = v; }
            else if (count == 1) { b = v; }
        }
        else {
            throw new SchemerException("Invalid argument in (<) function");
        }
    }

    return new Atom( new BoolToken( a < b ) );
}

Expression * greaterThanBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() != 2) {
        throw new SchemerException("(>) function should receive exactly two arguments");
    }

    Token *token;
    long double v, a, b;
    int count;
    list<Expression*>::const_iterator i;

    for (i = arguments.begin(), count = 0;
         i != arguments.end();
         i ++, count++) {
        if ((*i)->type == EXP_ATOM) {
            token = ((Atom*)(*i))->token;
            switch (token->type) {
                case TOK_FLOAT:
                    v = ((FloatToken*)token)->floatValue;
                    break;
                case TOK_INT:
                    v = ((IntToken*)token)->intValue;
                    break;
                default:
                    throw new SchemerException("Arguments for (>) should be numeric");
            }

            if (count == 0) { a = v; }
            else if (count == 1) { b = v; }
        }
        else {
            throw new SchemerException("Invalid argument in (>) function");
        }
    }

    return new Atom( new BoolToken( a > b ) );
}

Expression * compareBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() != 2) {
        throw new SchemerException("(=) function should receive exactly two arguments");
    }

    Token *a, *b;
    int count;
    list<Expression*>::const_iterator i;

    for (i = arguments.begin(), count = 0;
         i != arguments.end();
         i ++, count++) {
        if ((*i)->type == EXP_ATOM) {
            if (count == 0) { a = ((Atom*)(*i))->token; }
            else if (count == 1) { b = ((Atom*)(*i))->token; }
        }
        else {
            return new Atom(new BoolToken(false));
        }
    }

    bool isEqual = false;

    if (a->type == TOK_NIL && b->type == TOK_NIL) {
        isEqual = true;
    }
    else if (a->type == TOK_BOOL && b->type == TOK_BOOL) {
        isEqual = ( ((BoolToken*)a)->boolValue == ((BoolToken*)b)->boolValue );
    }
    else {
        long double va, vb;

        if (a->type == TOK_INT) { va = ((IntToken*)a)->intValue; }
        else if (a->type == TOK_FLOAT) { va = ((FloatToken*)a)->floatValue; }
        else {
            throw new SchemerException("Incompatible arguments in (=) function");
        }

        if (b->type == TOK_INT) { vb = ((IntToken*)b)->intValue; }
        else if (b->type == TOK_FLOAT) { vb = ((FloatToken*)b)->floatValue; }
        else {
            throw new SchemerException("Incompatible arguments in (=) function");
        }

        isEqual = (va == vb);
    }

    return new Atom( new BoolToken(isEqual));
}

Expression * displayBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() != 1) {
        throw new SchemerException("display function should receive exactly one argument");
    }

    cout << arguments.front() << endl;

    return Atom::nilExpression;
}

Expression * putcharBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (arguments.size() != 1) {
        throw new SchemerException("putchar function should receive exactly one argument");
    }

    Expression *output = arguments.front();

    if (output->type != EXP_ATOM) {
        throw new SchemerException("putchar argument should be an Atom");
    }

    Token *token = ((Atom*)output)->token;
    char c;
    switch (token->type) {
        case TOK_INT:
            c = (char)((IntToken*)token)->intValue;
            break;
        case TOK_FLOAT:
            c = (char)((FloatToken*)token)->floatValue;
            break;
        case TOK_NIL:
            c = '\0';
            break;
        case TOK_BOOL:
            c = (char)((BoolToken*)token)->boolValue;
            break;
        default:
            c = '\0';
            break;
    }

    cout << c;

    return Atom::nilExpression;
}

Expression * getcharBuiltIn( const list<Expression*> &arguments) throw (SchemerException*) {

    if (!arguments.empty()) {
        throw new SchemerException("getchar function takes no arguments");
    }

    return new Atom( new IntToken( cin.get() ));
}

void setup_schemer() {

    NilToken::nilToken = new NilToken();
    Atom::nilExpression = new Atom( NilToken::nilToken );
    Environment::globalEnvironment = new Environment();

    Environment::globalEnvironment->insert("+", new BuiltInProcedure("+", &plusBuiltIn));
    Environment::globalEnvironment->insert("*", new BuiltInProcedure("*", &timesBuiltIn));
    Environment::globalEnvironment->insert("/", new BuiltInProcedure("/", &divideBuiltIn));
    Environment::globalEnvironment->insert("%", new BuiltInProcedure("/", &modulusBuiltIn));
    Environment::globalEnvironment->insert("<", new BuiltInProcedure("<", &lessThanBuiltIn));
    Environment::globalEnvironment->insert(">", new BuiltInProcedure(">", &greaterThanBuiltIn));
    Environment::globalEnvironment->insert("=", new BuiltInProcedure("=", &compareBuiltIn));
    Environment::globalEnvironment->insert("display", new BuiltInProcedure("display", &displayBuiltIn));
    Environment::globalEnvironment->insert("getchar", new BuiltInProcedure("getchar", &getcharBuiltIn));
    Environment::globalEnvironment->insert("putchar", new BuiltInProcedure("putchar", &putcharBuiltIn));
}

