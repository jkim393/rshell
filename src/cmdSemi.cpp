#include "cmdSemi.h"
#include <cstddef>

bool cmdSemi::isExec(){
return false;
}

bool cmdSemi::evaluate() {
	left->evaluate();
	bool s=	right->evaluate();
	if (s){
		return true;
	}
	return false;
}
