#include "atom.h"
#include <sstream>

using namespace std;

Atom *Atom::nilExpression = NULL;

ostream & Atom::print(ostream &output) const {
    output << token;
    return output;
}

Expression* Atom::evaluate(Environment *env, set<Expression*> &callers) throw (SchemerException*) {

    Expression *evaluated;

    switch (token->type) {
        case TOK_FLOAT:
        case TOK_INT:
        case TOK_NIL:
        case TOK_BOOL:
            return this;
        case TOK_SYMBOL:
            evaluated = env->findEvaluated(((SymbolToken*)token)->symbolValue);
            if (evaluated != NULL) {
                return evaluated;
            }
            else {
                throw new SchemerException("Symbol \"" + ((SymbolToken*)token)->symbolValue + "\" not defined in scope",
                        token->line, token->column);
            }
        default:
            throw new SchemerException("Invalid Atom token",
                        token->line, token->column);
    }
}

void Atom::deepReach() {
    GarbageCollectable::deepReach();
    token->reach();
}

