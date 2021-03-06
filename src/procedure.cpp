#include "procedure.h"
#include <sstream>

using namespace std;

ostream & Procedure::print(ostream &output) const {

    output << "<PROCEDURE " << formalParameters.size() << '>';
    return output;
}

void Procedure::deepReach() {
    GarbageCollectable::deepReach();
    for (std::list<SymbolToken*>::iterator i = formalParameters.begin();
         i != formalParameters.end();
         i++) {
        (*i)->reach();
    }
    procedureExpression->reach();
    environment->reach();
}
