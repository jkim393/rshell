#include "cmdAnd.h"

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
