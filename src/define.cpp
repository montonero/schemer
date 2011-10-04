#include "define.h"
#include "atom.h"
#include <sstream>

using namespace std;

Expression *DefineExpression::parse(list<Token*> &tokens) throw (SchemerException*) {
    Token *token;
    DefineExpression *expression = new DefineExpression();

    token = next_token(tokens);
    if (token->type != TOK_SYMBOL) {
        throw new SchemerException("Expected symbol");
    }

    expression->name = (SymbolToken*)token;
    expression->defined = Expression::parse(tokens);

    expectClose(tokens);

    return expression;
}

ostream & DefineExpression::print(ostream &output) const {

    output << "(DEFINE " << name << " " << defined << ')';
    return output;
}

Expression* DefineExpression::evaluate(Environment *env) throw (SchemerException*) {

    env->insert(name->symbolValue, defined->evaluate( env ));

    return new Atom(new NilToken());
}

void DefineExpression::reach() {
    GarbageCollectable::reach();
    name->reach();
    defined->reach();
}

