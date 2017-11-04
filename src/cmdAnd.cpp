#include "cmdAnd.h"

bool cmdAnd::evaluate() {
	if(left->evaluate() && right->evaluate()){
		return true;
	}
}