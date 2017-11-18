#include "cmdOr.h"

bool cmdOr::isExec(){
return false;
}

bool cmdOr::evaluate(){
	if(left->evaluate() ){
		return true;
	}
	else {
		if ( right->evaluate() ){
			return true;
		}
		else {
			return false;
		}
	}
}
