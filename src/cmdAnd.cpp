#include "cmdAnd.h"

bool cmdAnd::isExec() {
return false;
}

bool cmdAnd::evaluate() {
	if(left->evaluate() ) {
		if(right->evaluate() ){
			return true;
		}
		else {
			return false;
		}
	}
	return false; //else return false
}
