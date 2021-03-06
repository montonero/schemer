#include "if.h"
#include "atom.h"
#include <sstream>

using namespace std;

Expression *IfExpression::parse(list<Token*> &tokens) throw (SchemerException*) {
    IfExpression *expression = new IfExpression();

    expression->condition = Expression::parse(tokens);
    expression->conseq = Expression::parse(tokens);
    expression->otherwise = Expression::parse(tokens);

    expectClose(tokens);
    return expression;
}

ostream & IfExpression::print(ostream &output) const {

    output << "(IF " << condition << " " << conseq << " " << otherwise << ")";
    return output;
}

Expression* IfExpression::evaluate(Environment *env, set<Expression*> &callers) throw (SchemerException*) {

    Expression *evaluatedCondition = condition->evaluate( env );

    if (evaluatedCondition ->type != EXP_ATOM || 
        ((Atom*)evaluatedCondition )->token->type != TOK_BOOL ) {
        throw new SchemerException("If form condition should evaluate to bool");
    }
    else if ( ((BoolToken*)((Atom*)evaluatedCondition)->token)->boolValue ) {
        return conseq->evaluate(env, callers);
    }
    else {
        return otherwise->evaluate(env, callers);
    }
}

void IfExpression::deepReach() {
    GarbageCollectable::deepReach();
    condition->reach();
    conseq->reach();
    otherwise->reach();
}

